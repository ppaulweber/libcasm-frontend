//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
//
//  This file is part of libcasm-fe.
//
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "SymbolResolverPass.h"

#include "../Logger.h"
#include "../analyze/AttributionPass.h"
#include "../ast/RecursiveVisitor.h"

#include <libcasm-ir/Builtin>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <unordered_map>

using namespace libcasm_fe;
using namespace Ast;

char SymbolResolverPass::id = 0;

static libpass::PassRegistration< SymbolResolverPass > PASS(
    "ASTSymbolResolverPass",
    "resolves AST identifiers of type-, call-, ... nodes",
    "ast-sym-resolve",
    0 );

class SymbolResolveVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( ReferenceAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;

  private:
    void pushVariable( const VariableDefinition::Ptr& variable );
    void popVariable( const VariableDefinition::Ptr& variable );

    /**
     * If the \a definition is a type alias, it will be resolved and the aliased
     * definition will be returned. Otherwise the given \a definition will be
     * returned.
     */
    Definition::Ptr resolveIfAlias( const Definition::Ptr& definition ) const;

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;

    std::unordered_map< std::string, VariableDefinition::Ptr > m_variables;
};

SymbolResolveVisitor::SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_variables()
{
}

void SymbolResolveVisitor::visit( DerivedDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        pushVariable( argument );
    }

    node.expression()->accept( *this );

    const auto end = node.arguments()->rend();
    for( auto it = node.arguments()->rbegin(); it != end; ++it )
    {
        popVariable( *it );
    }
}

void SymbolResolveVisitor::visit( RuleDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        pushVariable( argument );
    }

    node.rule()->accept( *this );

    const auto end = node.arguments()->rend();
    for( auto it = node.arguments()->rbegin(); it != end; ++it )
    {
        popVariable( *it );
    }
}

void SymbolResolveVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );

    const auto& name = node.identifier()->path();

    if( libcasm_ir::Builtin::available( name ) )
    {
        node.setReferenceType( ReferenceAtom::ReferenceType::BUILTIN );
        node.setBuiltinId( libcasm_ir::Annotation::find( name ).valueID() );
        return;
    }

    try
    {
        const auto symbol = m_symboltable.find( *node.identifier() );

        switch( symbol->id() )
        {
            case Node::ID::FUNCTION_DEFINITION:
            {
                node.setReferenceType( ReferenceAtom::ReferenceType::FUNCTION );
                node.setReference( symbol );
                break;
            }
            case Node::ID::DERIVED_DEFINITION:
            {
                node.setReferenceType( ReferenceAtom::ReferenceType::DERIVED );
                node.setReference( symbol );
                break;
            }
            case Node::ID::RULE_DEFINITION:
            {
                node.setReferenceType( ReferenceAtom::ReferenceType::RULE );
                node.setReference( symbol );
                break;
            }
            default:
            {
                m_log.error(
                    { node.identifier()->sourceLocation() },
                    "cannot reference '" + symbol->description() + "'" );
            }
        }
    }
    catch( const std::domain_error& e )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "'" + name + "' has not been defined",
            Code::SymbolIsUnknown );
    }
}

void SymbolResolveVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    assert( node.identifier() );
    const auto& identifier = node.identifier();
    const auto& identifierPath = identifier->path();
    const auto& identifierBaseName = identifier->baseName();

    if( identifier->type() == IdentifierPath::Type::RELATIVE )
    {
        // only absolute types can be resolved here, relative types will be
        // resolved later in the type inference pass
        return;
    }

    const auto variableIt = m_variables.find( identifierBaseName );
    if( variableIt != m_variables.cend() and identifierPath == identifierBaseName )
    {
        node.setTargetType( CallExpression::TargetType::VARIABLE );
        node.setTargetDefinition( variableIt->second );
        return;
    }

    if( libcasm_ir::Builtin::available( identifierBaseName ) )
    {
        const auto& annotation = libcasm_ir::Annotation::find( identifierBaseName );

        node.setTargetType( CallExpression::TargetType::BUILTIN );
        node.setTargetBuiltinId( annotation.valueID() );

        const auto expectedNumberOfArguments = annotation.relations().front().argument.size();

        if( node.arguments()->size() != expectedNumberOfArguments )
        {
            m_log.error(
                { node.sourceLocation() },
                "invalid argument size: builtin '" + identifierPath + "' expects " +
                    std::to_string( expectedNumberOfArguments ) + " arguments",
                Code::SymbolArgumentSizeMismatch );
        }
        return;
    }

    try
    {
        auto symbol = m_symboltable.find( *identifier );
        symbol = resolveIfAlias( symbol );

        std::size_t expectedNumberOfArguments = 0;

        switch( symbol->id() )
        {
            case Node::ID::FUNCTION_DEFINITION:
            {
                node.setTargetType( CallExpression::TargetType::FUNCTION );
                const auto function = std::static_pointer_cast< FunctionDefinition >( symbol );
                expectedNumberOfArguments = function->argumentTypes()->size();
                break;
            }
            case Node::ID::DERIVED_DEFINITION:
            {
                node.setTargetType( CallExpression::TargetType::DERIVED );
                const auto derived = std::static_pointer_cast< DerivedDefinition >( symbol );
                expectedNumberOfArguments = derived->arguments()->size();
                break;
            }
            case Node::ID::RULE_DEFINITION:
            {
                node.setTargetType( CallExpression::TargetType::RULE );
                const auto rule = std::static_pointer_cast< RuleDefinition >( symbol );
                expectedNumberOfArguments = rule->arguments()->size();
                break;
            }
            case Node::ID::ENUMERATOR_DEFINITION:
            {
                node.setTargetType( CallExpression::TargetType::CONSTANT );
                break;
            }
            case Node::ID::ENUMERATION_DEFINITION:
            {
                node.setTargetType( CallExpression::TargetType::TYPE_DOMAIN );
                break;
            }
            default:
            {
                m_log.error(
                    { node.identifier()->sourceLocation() },
                    "cannot reference '" + symbol->description() + "'" );
                return;
            }
        }

        node.setTargetDefinition( symbol );

        if( node.arguments()->size() != expectedNumberOfArguments )
        {
            m_log.error(
                { node.sourceLocation() },
                "invalid argument size: " + symbol->description() + " '" + identifierPath +
                    "' expects " + std::to_string( expectedNumberOfArguments ) + " arguments",
                Code::SymbolArgumentSizeMismatch );
        }
    }
    catch( const std::domain_error& e )
    {
        static const auto SELF( "self" );
        static const auto AGENT( "Agent" );
        static const auto SINGLE_AGENT_CONSTANT( "$" );

        if( identifierPath == SELF )
        {
            try
            {
                const auto& symbol = m_symboltable.find( AGENT );
                node.setTargetType( CallExpression::TargetType::SELF );
                node.setTargetDefinition( symbol );
            }
            catch( const std::domain_error& e )
            {
                m_log.error( { node.sourceLocation() }, "unable to find 'Agent' symbol" );
            }
        }
        // single agent execution notation --> agent type domain ==
        // Enumeration!
        else if( identifierPath == SINGLE_AGENT_CONSTANT )
        {
            assert( node.targetType() == CallExpression::TargetType::CONSTANT );

            const auto agent = std::make_shared< EnumeratorDefinition >(
                std::make_shared< Identifier >( SINGLE_AGENT_CONSTANT ) );
            const auto agentEnumerators = std::make_shared< Enumerators >();
            agentEnumerators->add( agent );
            const auto agentEnum = std::make_shared< EnumerationDefinition >(
                std::make_shared< Identifier >( AGENT ), agentEnumerators );

            const auto kind = libstdhl::Memory::make< libcasm_ir::Enumeration >( AGENT );
            kind->add( SINGLE_AGENT_CONSTANT );

            const auto type = libstdhl::Memory::make< libcasm_ir::EnumerationType >( kind );
            agent->setType( type );
            agentEnum->setType( type );

            m_symboltable.registerSymbol( AGENT, agentEnum );

            node.setTargetDefinition( agent );
            node.setType( type );
        }
        else
        {
            m_log.error(
                { node.sourceLocation() },
                "unknown " +
                    ( node.targetType() != CallExpression::TargetType::UNKNOWN
                          ? node.targetTypeName() + " "
                          : "" ) +
                    "symbol '" + identifierPath + "' found",
                ( node.targetType() == CallExpression::TargetType::FUNCTION )
                    ? Code::FunctionSymbolIsUnknown
                    : Code::SymbolIsUnknown );
        }
    }

    m_log.debug( "call: " + identifierPath + "{ " + node.targetTypeName() + " }" );
}

void SymbolResolveVisitor::visit( LetExpression& node )
{
    node.initializer()->accept( *this );

    pushVariable( node.variable() );
    node.expression()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::visit( ChooseExpression& node )
{
    node.universe()->accept( *this );

    pushVariable( node.variable() );
    node.expression()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushVariable( node.predicateVariable() );
    node.proposition()->accept( *this );
    popVariable( node.predicateVariable() );
}

void SymbolResolveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushVariable( node.predicateVariable() );
    node.proposition()->accept( *this );
    popVariable( node.predicateVariable() );
}

void SymbolResolveVisitor::visit( LetRule& node )
{
    node.expression()->accept( *this );

    pushVariable( node.variable() );
    node.rule()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::visit( ForallRule& node )
{
    node.universe()->accept( *this );

    pushVariable( node.variable() );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );

    pushVariable( node.variable() );
    node.rule()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::pushVariable( const VariableDefinition::Ptr& variable )
{
    const auto& name = variable->identifier()->name();

    const auto result = m_variables.emplace( name, variable );
    if( not result.second )
    {
        m_log.error(
            { variable->sourceLocation() },
            "redefinition of symbol '" + name + "'",
            Code::SymbolAlreadyDefined );

        const auto& existingVariable = result.first->second;
        m_log.info(
            { existingVariable->sourceLocation() },
            "previous definition of '" + name + "' is here" );
    }
}

void SymbolResolveVisitor::popVariable( const VariableDefinition::Ptr& variable )
{
    const auto& name = variable->identifier()->name();
    m_variables.erase( name );
}

Definition::Ptr SymbolResolveVisitor::resolveIfAlias( const Definition::Ptr& definition ) const
{
    if( definition->id() != Node::ID::USING_DEFINITION )
    {
        return definition;
    }

    const auto usingDefinition = std::static_pointer_cast< UsingDefinition >( definition );
    const auto symbol = m_symboltable.find( *usingDefinition->type()->name() );
    return resolveIfAlias( symbol ); // resolve again, the symbol may be another alias
}

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolRegistrationPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< SymbolRegistrationPass >();
    const auto specification = data->specification();

    SymbolResolveVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during symbol resolving", errors );
        return false;
    }

    pr.setResult< SymbolResolverPass >( data );

    return true;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
