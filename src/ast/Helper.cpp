//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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

#include "Helper.h"

#include "../various/GrammarToken.h"

#include <cassert>

using namespace libcasm_fe;
using namespace Ast;

static const auto unresolvedToken = std::make_shared< Ast::Token >( Grammar::Token::UNRESOLVED );

//
//
// Helper
//

Helper::Helper(
    const Node::ID id, const Token::Ptr& leftBraceToken, const Token::Ptr& rightBraceToken )
: Node( id )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
, m_delimiterToken( unresolvedToken )
{
}

const Token::Ptr& Helper::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& Helper::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

void Helper::setDelimiterToken( const Token::Ptr& delimiterToken )
{
    assert( m_delimiterToken->token() == Grammar::Token::UNRESOLVED );
    m_delimiterToken = delimiterToken;
}

const Token::Ptr& Helper::delimiterToken( void ) const
{
    return m_delimiterToken;
}

//
//
// Defined
//

Defined::Defined(
    const Token::Ptr& definedToken,
    const Token::Ptr& leftBraceToken,
    const Expression::Ptr& expression,
    const Token::Ptr& rightBraceToken )
: Helper( Node::ID::DEFINED, leftBraceToken, rightBraceToken )
, m_expression( expression )
, m_definedToken( definedToken )
{
}

const Expression::Ptr& Defined::expression( void ) const
{
    return m_expression;
}

const Token::Ptr& Defined::definedToken( void ) const
{
    return m_definedToken;
}

void Defined::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// Initializer
//

Initializer::Initializer(
    const Token::Ptr& leftBraceToken,
    const Expressions::Ptr& arguments,
    const Token::Ptr& rightBraceToken,
    const Token::Ptr& mapsToken,
    const Expression::Ptr& value )
: Helper( Node::ID::INITIALIZER, leftBraceToken, rightBraceToken )
, m_arguments( arguments )
, m_value( value )
, m_updateRule( std::make_shared< UpdateRule >(
      std::make_shared< DirectCallExpression >( nullptr, arguments ), value ) )
, m_mapsToken( mapsToken )
{
}

const Expressions::Ptr& Initializer::arguments( void ) const
{
    return m_arguments;
}

const Expression::Ptr& Initializer::value( void ) const
{
    return m_value;
}

const UpdateRule::Ptr& Initializer::updateRule( void ) const
{
    return m_updateRule;
}

const Token::Ptr& Initializer::mapsToken( void ) const
{
    return m_mapsToken;
}

void Initializer::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// Initially
//

Initially::Initially(
    const Token::Ptr& initiallyToken,
    const Token::Ptr& leftBraceToken,
    const Initializers::Ptr& initializers,
    const Token::Ptr& rightBraceToken )
: Helper( Node::ID::INITIALLY, leftBraceToken, rightBraceToken )
, m_initializers( initializers )
, m_initiallyToken( initiallyToken )
{
}

const Initializers::Ptr& Initially::initializers( void ) const
{
    return m_initializers;
}

const Token::Ptr& Initially::initiallyToken( void ) const
{
    return m_initiallyToken;
}

void Initially::accept( Visitor& visitor )
{
    visitor.visit( *this );
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