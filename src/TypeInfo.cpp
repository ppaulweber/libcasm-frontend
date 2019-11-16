//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
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

#include "TypeInfo.h"

#include <libstdhl/String>

#include <unordered_set>

using namespace libcasm_fe;

//
//
// TypeInfo
//

TypeInfo::TypeInfo( void )
{
    setType( TypeInfo::TYPE_NAME_VOID, libstdhl::Memory::get< libcasm_ir::VoidType >() );
    setType( TypeInfo::TYPE_NAME_BOOLEAN, libstdhl::Memory::get< libcasm_ir::BooleanType >() );
    setType( TypeInfo::TYPE_NAME_INTEGER, libstdhl::Memory::get< libcasm_ir::IntegerType >() );
    setType( TypeInfo::TYPE_NAME_STRING, libstdhl::Memory::get< libcasm_ir::StringType >() );
    setType( TypeInfo::TYPE_NAME_RATIONAL, libstdhl::Memory::get< libcasm_ir::RationalType >() );
    setType( TypeInfo::TYPE_NAME_DECIMAL, libstdhl::Memory::get< libcasm_ir::DecimalType >() );
    setType( TypeInfo::TYPE_NAME_RANGE, nullptr );  // template type
    setType( TypeInfo::TYPE_NAME_LIST, nullptr );   // template type
    // setType( TypeInfo::TYPE_NAME_SET, nullptr ); // TODO: FIXME: @ppaulweber: feature/set
    setType( TypeInfo::TYPE_NAME_PORT, nullptr );  // template type
    setType( TypeInfo::TYPE_NAME_FILE, nullptr );  // template type
    setType(
        TypeInfo::TYPE_NAME_OBJECT, libstdhl::Memory::get< libcasm_ir::ObjectType >( "Object" ) );
}

void TypeInfo::setType( const std::string& name, const libcasm_ir::Type::Ptr& type )
{
    const auto result = m_typeName2typePtr.emplace( name, type );
    if( not result.second )
    {
        throw std::domain_error( "already set ptr of type with name '" + name + "'" );
    }
}

libcasm_ir::Type::Ptr TypeInfo::getType( const std::string& name ) const
{
    const auto it = m_typeName2typePtr.find( name );
    if( it == m_typeName2typePtr.cend() )
    {
        throw std::domain_error( "could not find type with name '" + name + "'" );
    }

    return it->second;
}

u1 TypeInfo::hasType( const std::string& name ) const
{
    const auto it = m_typeName2typePtr.find( name );
    return it != m_typeName2typePtr.cend();
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
