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
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//

%skeleton "lalr1.cc" /* -*- C++ -*- */
%defines
%define parser_class_name {Parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires
{
    #include "src/Driver.h"
    #include "src/Codes.h"

    #include "src/ast/Specification.h"

    #include "../stdhl/cpp/Type.h"

    #include "../casm-ir/src/Value.h"

    using namespace libcasm_fe;
    using namespace Ast;
}

// The parsing context.
%parse-param { libcasm_fe::Driver& driver }
%lex-param   { libcasm_fe::Driver& driver }

%locations
%initial-action
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
};

%define parse.trace
%define parse.error verbose


%code
{
    yy::Parser::symbol_type yylex( libcasm_fe::Driver& driver );

    std::pair< FunctionDefinition::Classification, bool > parseFunctionAttributes(
        libcasm_fe::Driver& driver, const NodeList< IdentifierNode >& attributes )
    {
        using Classification = FunctionDefinition::Classification;

        auto functionClass = Classification::CONTROLLED;
        bool symbolicFunction = false;

        bool classAttributeAlreadyUsed = false;
        IdentifierNode::Ptr classAttribute;

        bool symbolicAttributeAlreadyUsed = false;
        IdentifierNode::Ptr symbolicAttribute;

        for( auto attribute : attributes )
        {
            const auto& name = attribute->identifier();

            if( name == "symbolic" )
            {
                symbolicFunction = true;

                if( symbolicAttributeAlreadyUsed )
                {
                    driver.error
                    ( { symbolicAttribute->location(), attribute->location() }
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
                }
                else
                {
                    symbolicAttributeAlreadyUsed = true;
                    symbolicAttribute = attribute;
                }

                continue;
            }

            if( name == "in" or name == "monitored" )
            {
                functionClass = Classification::IN;
            }
            else if( name == "controlled" )
            {
                functionClass = Classification::CONTROLLED;
            }
            else if( name == "shared" )
            {
                functionClass = Classification::SHARED;
            }
            else if( name == "out" )
            {
                functionClass = Classification::OUT;
            }
            else if( name == "static" )
            {
                functionClass = Classification::STATIC;
            }
            else
            {
                driver.error
                ( attribute->location(),
                , "`" + name + "` is no valid function attribute, only in, monitored, "
                + "controlled, shared, out, static and symbolic are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }

            if( classAttributeAlreadyUsed )
            {
                driver.error
                ( { classAttribute->location(), attribute->location() }
                , "a function classifier attribute can only be used once per function"
                , libcasm_fe::Codes::FunctionAttributeMultipleUseOfFunctionClassifier
                );
            }
            else
            {
                classAttributeAlreadyUsed = true;
                classAttribute = attribute;
            }
        }

        return { functionClass, symbolicFunction };
    }

    static FunctionDefinition::Ptr createProgramFunction( yy::location& location )
    {
        //auto argTypes = { new Type( TypeType::AGENT ) }; // TODO add args and return type
        //auto retType = new Type( TypeType::RuleReference );

        const auto program = make< IdentifierNode >( location, "program" );
        return make< FunctionDefinition >( location, program, nullptr, nullptr );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::BLOCK_RULE )
                or (rule->id() == Node::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        return make< BlockRule >( rule );
    }
}


%token
END       0 "end of file"
{{grammartoken}}
;

%token <std::string> BINARY      "binary"
%token <std::string> HEXADECIMAL "hexadecimal"
%token <std::string> INTEGER     "integer"
%token <std::string> RATIONAL    "rational"
%token <std::string> FLOATING    "floating"
%token <std::string> STRING      "string"
%token <std::string> IDENTIFIER  "identifier"

%type <Specification::Ptr> Specification
%type <IdentifierNode::Ptr> Identifier
%type <NodeList< IdentifierNode >::Ptr> Identifiers MaybeIdentifiers

// definitions
%type <Definition::Ptr> Definition
%type <Definitions::Ptr> Definitions
%type <VariableDefinition::Ptr> Variable
%type <FunctionDefinition::Ptr> FunctionDefinition
%type <DerivedDefinition::Ptr> DerivedDefinition
%type <RuleDefinition::Ptr> RuleDefinition
%type <EnumerationDefinition::Ptr> EnumerationDefinition

// expressions
%type <Expression::Ptr> Expression Atom
%type <Expressions::Ptr> Expressions MaybeExpressions
%type <ValueAtom::Ptr> Boolean String BitNumber IntegerNumber FloatingNumber RationalNumber RuleReference
%type <UndefAtom::Ptr> Undefined
%type <RangeExpression::Ptr> Range
%type <ListExpression::Ptr> List
%type <DirectCallExpression::Ptr> DirectCallExpression
%type <IndirectCallExpression::Ptr> IndirectCallExpression

// rules
%type <Rule::Ptr> Rule
%type <Rules::Ptr> Rules
%type <SkipRule::Ptr> SkipRule
%type <ConditionalRule::Ptr> ConditionalRule
%type <CaseRule::Ptr> CaseRule
%type <LetRule::Ptr> LetRule
%type <ForallRule::Ptr> ForallRule
%type <IterateRule::Ptr> IterateRule
%type <BlockRule::Ptr> BlockRule
%type <SequenceRule::Ptr> SequenceRule
%type <UpdateRule::Ptr> UpdateRule
%type <CallRule::Ptr> CallRule

// types
%type <Type::Ptr> Type
%type <Types::Ptr> Types
%type <BasicType::Ptr> BasicType
%type <ComposedType::Ptr> ComposedType
%type <StaticallySizedType::Ptr> StaticallySizedType
%type <RangedType::Ptr> RangedType

// other
%type <FunctionDefinition::Ptr> ProgramFunctionDefinition
%type <CaseRule::Case> CaseLabel
%type <std::vector< CaseRule::Case >> CaseLabels
%type <UpdateRule::Ptr> Initializer
%type <NodeList< UpdateRule >::Ptr> Initializers MaybeInitializers MaybeInitially
%type <NodeList< IdentifierNode >::Ptr> MaybeFunctionAttributes
%type <Expression::Ptr> MaybeDefined
%type <Types::Ptr> FunctionParameters MaybeFunctionParameters
%type <Expressions::Ptr> Arguments MaybeArguments
%type <NodeList< VariableDefinition >::Ptr> Parameters MaybeParameters


%start Specification

%precedence THEN
%precedence ELSE

//%precedence UPDATE ASSERT ASSURE ABORT
// %precedence IDENTIFIER
//%precedence INTEGER STRING FLOATING RATIONAL
// %precedence UNDEF
// %precedence TRUE
// %precedence FALSE

%left AND
%left XOR
%left OR

%left EQUAL
%left NEQUAL

%left GREATEREQ
%left LESSEQ

%left GREATER
%left LESSER

%left PLUS
%left MINUS
%left PERCENT
%left SLASH
%left STAR

%precedence NOT

%nonassoc UPLUS
%nonassoc UMINUS

%%

Specification
: CASM Definitions
  {
      const std::string& filepath = driver.get_filename();
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      const std::string& filenameWithoutExtension
          = filename.substr( 0, filename.rfind( "." ) );

      const auto name = make< IdentifierNode >( filenameWithoutExtension );
      const auto specification = make< Specification >( @$, name, $2 );

      //driver.result = specification; TODO
  }
;


Definition
: FunctionDefinition
  {
      $$ = $1;
  }
| DerivedDefinition
  {
      $$ = $1;
  }
| RuleDefinition
  {
      $$ = $1;
  }
| EnumerationDefinition
  {
      $$ = $1;
  }
;


Definitions
: Definitions Definition
  {
      auto definitions = $1;
      definitions->add( $2 );
      $$ = definitions;
  }
| Definition
  {
      auto definitions = make< Definitions >( @$ );
      definitions->add( $1 );
      $$ = definitions;
  }
;


FunctionDefinition
: FUNCTION MaybeFunctionAttributes Identifier COLON MaybeFunctionParameters ARROW Type MaybeDefined MaybeInitially
  {
      auto function = make< FunctionDefinition >( @$, $3, $5, $7 );

      const auto attributes = parseFunctionAttributes( driver, $2 );
      function->setClassification( attributes.first );
      function->setSymbolic( attributes.second );

      function->setDefaultValue( $8 );

      // apply the name of the function declaration to the initializer functions
      auto initializers = $9;
      for (auto initializer : *initializers) {
           initializer->function()->setIdentifier( functionDefinition->identifier() );
      }
      function->setInitializers( initializers );

      $$ = function;
  }
| ProgramFunctionDefinition
  {
      $$ = $1; // `init` special case
  }
;


MaybeInitially
: INITIALLY LCURPAREN MaybeInitializers RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = make< NodeList< UpdateRule > >( @$ );
  }
;


MaybeDefined
: DEFINED LCURPAREN Atom RCURPAREN
  {
      $$ = $3;
  }
| %empty
  {
      $$ = make< UndefAtom >( @$ );
  }
;


FunctionParameters
: FunctionParameters STAR Type
  {
      auto types = $1;
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = make< Types >( @$ );
      types->add( $1 );
      $$ = types;
  }
;


MaybeFunctionParameters
: FunctionParameters
  {
      $$ = $1;
  }
| %empty
  {
      $$ = make< Types >( @$ );
  }
;


MaybeFunctionAttributes
: LPAREN MaybeIdentifiers RPAREN
  {
      $$ = $2;
  }
| %empty
  {
      $$ = make< NodeList< IdentifierNode > >( @$ );
  }
;


ProgramFunctionDefinition
: INIT RuleReference
  {
      auto programDefinition = createProgramFunction();

      auto arguments = make< Expressions >( @$ );
      // TODO add `default` agent to arguments
      const auto program = make< DirectCallExpression >(
          @$, programDefinition->identifier(), arguments );

      auto initializers = make< NodeList< UpdateRule > >( @$ );
      initializers->add( make< UpdateRule >( @$, program, $2 ) );
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
| INIT LCURPAREN MaybeInitializers RCURPAREN
  {
      auto programDefinition = createProgramFunction();

      // apply the name of the program declaration to the initializer functions
      auto initializers = $3;
      for (auto initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      $$ = programDefinition;
  }
;


Initializer
: Atom
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( @$, std::string() );
      const auto arguments = make< Expressions >( @$ );
      const auto function = make< DirectCallExpression >( @$, unknown, arguments );

      $$ = make< UpdateRule >( @$, function, $1 );
  }
| MaybeArguments ARROW Atom
  {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( @$, std::string() );
      const auto function = make< DirectCallExpression >( @$, unknown, $1 );

      $$ = make< UpdateRule >( @$, function, $3 );
  }
;


Initializers
: Initializers COMMA Initializer
  {
      auto initializers = $1;
      initializers->add( $3 );
      $$ = initializers;
  }
| Initializer
  {
      auto initializers = make< NodeList< UpdateRule > >( @$ );
      initializers->add( $1 );
      $$ = initializers;
  }
;


MaybeInitializers
: Initializers
  {
      $$ = $1;
  }
| Initializers COMMA
  {
      $$ = $1;
  }
| %empty
  {
      $$ = make< NodeList< UpdateRule > >( @$ );
  }
;


DerivedDefinition
: DERIVED Identifier MaybeParameters COLON Type EQUAL Expression
  {
      $$ = make< DerivedDefinition >( @$, $2, $3, $5, $7 );
  }
;


EnumerationDefinition
: ENUM Identifier EQUAL LCURPAREN MaybeIdentifiers RCURPAREN
  {
      $$ = make< EnumerationDefinition >( @$, $2, $5 );
  }
;


Identifier
: IDENTIFIER
  {
      $$ = make< IdentifierNode >( @$, $1 );
  }
;


Identifiers
: Identifiers COMMA Identifier
  {
      auto identifiers = $1;
      identifiers->add( $3 );
      $$ = identifiers;
  }
| Identifier
  {
      auto identifiers = make< NodeList< Identifier > >( @$ );
      identifiers->add( $1 );
      $$ = identifiers;
  }
;


MaybeIdentifiers
: Identifiers
  {
      $$ = $1;
  }
| Identifiers COMMA
  {
      $$ = $1;
  }
| %empty
  {
      $$ = make< NodeList< Identifier > >( @$ );
  }
;


Variable
: Identifier COLON Type
  {
      $$ = make< VariableDefinition >( @$, $1, $3 );
  }
;


Parameters
: Parameters COMMA Variable
  {
      auto parameters = $1;
      parameters->add( $3 );
      $$ = parameters;
  }
| Variable
  {
      auto parameters = make< NodeList< VariableDefinition > >( @$ );
      parameters->add( $1 );
      $$ = parameters;
  }
;


MaybeParameters
: LPAREN Parameters RPAREN
  {
      $$ = $2;
  }
| LPAREN RPAREN
  {
      $$ = make< NodeList< VariableDefinition > >( @$ );
  }
| %empty
  {
      $$ = make< NodeList< VariableDefinition > >( @$ );
  }
;


Type
: BasicType
  {
      $$ = $1;
  }
| ComposedType
  {
      $$ = $1;
  }
| StaticallySizedType
  {
      $$ = $1;
  }
| RangedType
  {
      $$ = $1;
  }
;


BasicType
: Identifier
  {
      $$ = make< BasicType >( @$, $1 );
  }
;


ComposedType
: Identifier LPAREN Types RPAREN
  {
      $$ = make< ComposedType >( @$, $1, $3 );
  }
;


StaticallySizedType
: Identifier LPAREN Atom RPAREN
  {
      $$ = make< StaticallySizedType >( @$, $1, $3 );
  }
;


RangedType
: Identifier LPAREN Atom DOTDOT Atom RPAREN
  {
      $$ = make< RangedType >( @$, $1, $3, $5 );
  }
;


Types
: Types COMMA Type
  {
      auto types = $1;
      types->add( $3 );
      $$ = types;
  }
| Type
  {
      auto types = make< Types >( @$ );
      types->add( $1 );
      $$ = types;
  }
;


Atom
: DirectCallExpression
  {
      $$ = $1;
  }
| IndirectCallExpression
  {
      $$ = $1;
  }
| LPAREN Expression RPAREN
  {
      $$ = $2;
  }
| PLUS LPAREN Expression RPAREN %prec UPLUS
  {
      $$ = $3;
  }
| MINUS LPAREN Expression RPAREN %prec UMINUS
  {
      const auto zero = make< ZeroAtom >( @$ );
      $$ = make< BinaryExpression >( @$, zero, $3,
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
| RuleReference
  {
      $$ = $1;
  }
| BitNumber
  {
      $$ = $1;
  }
| IntegerNumber
  {
      $$ = $1;
  }
| FloatingNumber
  {
      $$ = $1;
  }
| RationalNumber
  {
      $$ = $1;
  }
| String
  {
      $$ = $1;
  }
| List
  {
      $$ = $1;
  }
| Range
  {
      $$ = $1;
  }
| Undefined
  {
      $$ = $1;
  }
| Boolean
  {
      $$ = $1;
  }
;


Undefined
: UNDEF
  {
      $$ = make< UndefAtom >( @$ );
  }
;


Boolean
: TRUE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      $$ = make< ValueAtom >( @$, value );
  }
| FALSE
  {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      $$ = make< ValueAtom >( @$, value );
  }
;


String
: STRING
  {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


BitNumber
: BINARY
  {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, 2 );
      $$ = make< ValueAtom >( @$, value );
  }
| HEXADECIMAL
  {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( $1, 16 );
      $$ = make< ValueAtom >( @$, value );
  }
;


IntegerNumber
: INTEGER
  {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


FloatingNumber
: FLOATING
  {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


RationalNumber
: RATIONAL
  {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( $1 );
      $$ = make< ValueAtom >( @$, value );
  }
;


RuleReference
: AT IDENTIFIER
  {
      const auto value = libstdhl::get< libcasm_ir::RuleReferenceConstant >( $2 );
      $$ = make< ValueAtom >( @$, value );
  }
;


Range
: LSQPAREN Atom DOTDOT Atom RSQPAREN
  {
      $$ = make< RangeExpression >( @$, $2, $4 );
  }
;


List
: LSQPAREN MaybeExpressions RSQPAREN
  {
      $$ = make< ListExpression >( @$, $2 );
  }
;


Expression
: Expression PLUS Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::ADD_INSTRUCTION );
  }
| Expression MINUS Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::SUB_INSTRUCTION );
  }
| Expression STAR Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MUL_INSTRUCTION );
  }
| Expression SLASH Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::DIV_INSTRUCTION );
  }
| Expression PERCENT Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::MOD_INSTRUCTION );
  }
| Expression NEQUAL Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::NEQ_INSTRUCTION );
  }
| Expression EQUAL Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::EQU_INSTRUCTION );
  }
| Expression LESSER Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LTH_INSTRUCTION );
  }
| Expression GREATER Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GTH_INSTRUCTION );
  }
| Expression LESSEQ Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::LEQ_INSTRUCTION );
  }
| Expression GREATEREQ Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::GEQ_INSTRUCTION );
  }
| Expression OR Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::OR_INSTRUCTION );
  }
| Expression XOR Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::XOR_INSTRUCTION );
  }
| Expression AND Expression
  {
      $$ = make< BinaryExpression >( @$, $1, $3, libcasm_ir::Value::AND_INSTRUCTION );
  }
| NOT Expression
  {
      $$ = make< UnaryExpression >( @$, $2, libcasm_ir::Value::NOT_INSTRUCTION );
  }
| Atom
  {
      $$ = $1;
  }
;


Expressions
: Expressions COMMA Expression
  {
      auto expressions = $1;
      expressions->add( $3 );
      $$ = expressions;
  }
| Expression
  {
      auto expressions = make< Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
;


MaybeExpressions
: Expressions
  {
      $$ = $1;
  }
| Expressions COMMA
  {
      $$ = $1;
  }
| %empty
  {
      $$ = make< Expressions >( @$ );
  }
;


Arguments
: LPAREN Expressions RPAREN
  {
      $$ = $2;
  }
| LPAREN RPAREN
  {
      $$ = make< Expressions >( @$ );
  }
;


MaybeArguments
: Arguments
  {
      $$ = $1;
  }
| Expression
  {
      auto expressions = make< Expressions >( @$ );
      expressions->add( $1 );
      $$ = expressions;
  }
| %empty
  {
      $$ = make< Expressions >( @$ );
  }
;


DirectCallExpression
: Identifier MaybeArguments
  {
      $$ = make< DirectCallExpression >( @$, $1, $2 );
  }
;


IndirectCallExpression
: LPAREN Expression RPAREN Arguments
  {
      $$ = make< IndirectCallExpression >( @$, $2, $4 );
  }
;


RuleDefinition
: RULE Identifier MaybeParameters EQUAL Rule
  {
      $$ = make< RuleDefinition >( @$, $2, $3, nullptr,
                                             wrapInBlockRule( $5 ) ); // TODO nullptr -> void
  }
;


Rule
: SkipRule
  {
      $$ = $1;
  }
| ConditionalRule
  {
      $$ = $1;
  }
| CaseRule
  {
      $$ = $1;
  }
| LetRule
  {
      $$ = $1;
  }
| ForallRule
  {
      $$ = $1;
  }
| IterateRule
  {
      $$ = $1;
  }
| BlockRule
  {
      $$ = $1;
  }
| SequenceRule
  {
      $$ = $1;
  }
| UpdateRule
  {
      $$ = $1;
  }
| CallRule
  {
      $$ = $1;
  }
;


Rules
: Rules Rule
  {
      auto rules = $1;
      rules->add( $2 );
      $$ = rules;
  }
| Rule
  {
      auto rules = make< Rules >( @$ );
      rules->add( $1 );
      $$ = rules;
  }
;


SkipRule
: SKIP
  {
      $$ = make< SkipRule >( @$ );
  }
;


ConditionalRule
: IF Expression THEN Rule
  {
      $$ = make< ConditionalRule >( @$, $2, $4 );
  }
| IF Expression THEN Rule ELSE Rule
  {
      $$ = make< ConditionalRule >( @$, $2, $4, $6 );
  }
;


CaseRule
: CASE Expression OF LCURPAREN CaseLabels RCURPAREN
  {
      $$ = make< CaseRule >( @$, $2, $5 );
  }
;


CaseLabel
: DEFAULT COLON Rule
  {
      // default case
      $$ = CaseRule::Case( nullptr, $3 );
  }
| UNDERLINE COLON Rule
  {
      // default case
      $$ = CaseRule::Case( nullptr, $3 );
  }
| Atom COLON Rule
  {
      $$ = CaseRule::Case( $1, $3 );
  }
;


CaseLabels
: CaseLabel CaseLabels
  {
      $$ = std::move( $2 );
      $$.push_back( $1 );
  }
| CaseLabel
  {
      $$ = { $1 };
  }
;


LetRule
: LET Variable EQUAL Expression IN Rule
  {
      $$ = make< LetRule >( @$, $2, $4, $6 );
  }
;


ForallRule
: FORALL Variable IN Expression DO Rule
  {
      $$ = make< ForallRule >( @$, $2, $4, $6 );
  }
;


IterateRule
: ITERATE Rule
  {
      $$ = make< IterateRule >( @$, $2 );
  }
;


BlockRule
: LCURPAREN Rules RCURPAREN
  {
      $$ = make< BlockRule >( @$, $2 );
  }
| PAR Rules ENDPAR
  {
      $$ = make< BlockRule >( @$, $2 );
  }
;


SequenceRule
: SEQ_BRACKET Rules ENDSEQ_BRACKET
  {
      $$ = make< SequenceRule >( @$, $2 );
  }
| SEQ Rules ENDSEQ
  {
      $$ = make< SequenceRule >( @$, $2 );
  }
;


UpdateRule
: DirectCallExpression UPDATE Expression
  {
      $$ = make< UpdateRule >( @$, $1, $3 );
  }
;


CallRule
: CALL DirectCallExpression
  {
      $$ = make< CallRule >( @$, $2, { CallExpression::TargetType::RULE } );
  }
| DirectCallExpression
  {
      $$ = make< CallRule >( @$, $1, { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
| CALL IndirectCallExpression
  {
      $$ = make< CallRule >( @$, $2, { CallExpression::TargetType::RULE } );
  }
| IndirectCallExpression
  {
      $$ = make< CallRule >( @$, $1, { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
;

%%

void yy::Parser::error
( const location_type& l
, const std::string& m
)
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );

        driver.error
        ( yy::location( yy::position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        );
    }
    else
    {
        driver.error( l, m, libcasm_fe::Codes::SyntaxError );
    }
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
