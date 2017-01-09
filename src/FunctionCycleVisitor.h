//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#ifndef CASMI_LIBPARSE_INIT_CYCLE_VISITOR
#define CASMI_LIBPARSE_INIT_CYCLE_VISITOR

#include <set>
#include <utility>

#include "Visitor.h"

namespace libcasm_fe
{
    class InitCycleVisitor : public libcasm_fe::Visitor< bool, bool >
    {
      public:
        std::set< std::string > dependency_names;

        LIB_CASMFE_VISITOR_INTERFACE( bool, bool );
    };
}

#endif // CASMI_LIBINTERPRETER_EXEC_VISITOR
