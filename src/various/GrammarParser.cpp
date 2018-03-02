// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "GrammarParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 88 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exception.h"
    #include "Logger.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< Identifier >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( rule == nullptr )
        {
            // this can happen while recovering from a syntax error
            return nullptr;
        }

        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return Ast::make< BlockRule >( sourceLocation, rules );
    }

#line 131 "GrammarParser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 217 "GrammarParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      specification (specification_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 176: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 175: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 177: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 148: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 111: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 120: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 114: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 105: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 104: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 106: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 128: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 109: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 149: // ComposedType
      case 150: // TupleType
      case 151: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 127: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 103: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 90: // AttributedDefinition
      case 91: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 89: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 97: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 98: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 130: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 117: // Term
      case 118: // SimpleOrClaspedTerm
      case 119: // OperatorExpression
      case 160: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 178: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 155: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 154: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 108: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 95: // FunctionDefinition
      case 96: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 88: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 165: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 166: // IdentifierPath
      case 167: // AbsoluteIdentifierPath
      case 168: // RelativeIdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 124: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 110: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 126: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 107: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 140: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 131: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 123: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 122: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 145: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 144: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 141: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 143: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 139: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 153: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 100: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 94: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 101: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 112: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 102: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 87: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 152: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 142: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 125: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 146: // Types
      case 156: // FunctionParameters
      case 157: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 132: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 129: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // UpdateRule
      case 163: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 161: // MaybeInitially
      case 162: // Initializers
      case 164: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 99: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 133: // BooleanLiteral
      case 134: // IntegerLiteral
      case 135: // RationalLiteral
      case 136: // DecimalLiteral
      case 137: // BinaryLiteral
      case 138: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 158: // Parameters
      case 159: // MaybeParameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 115: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 147: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
      case 79: // "absoluteIdentifierPath"
      case 80: // "relativeIdentifierPath"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 176: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 175: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 177: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 148: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 111: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 120: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 114: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 105: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 104: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 106: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 128: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 109: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 149: // ComposedType
      case 150: // TupleType
      case 151: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 127: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 103: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 90: // AttributedDefinition
      case 91: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 89: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 97: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 98: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 130: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 117: // Term
      case 118: // SimpleOrClaspedTerm
      case 119: // OperatorExpression
      case 160: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 178: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 155: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 154: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 108: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 95: // FunctionDefinition
      case 96: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 88: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 165: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 166: // IdentifierPath
      case 167: // AbsoluteIdentifierPath
      case 168: // RelativeIdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 124: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 110: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 126: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 107: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 140: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 131: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 123: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 122: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 145: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 144: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 141: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 143: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 139: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 153: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 100: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 94: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 101: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 112: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 102: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 87: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 152: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 142: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 125: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 146: // Types
      case 156: // FunctionParameters
      case 157: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 132: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 129: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // UpdateRule
      case 163: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 161: // MaybeInitially
      case 162: // Initializers
      case 164: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 99: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 133: // BooleanLiteral
      case 134: // IntegerLiteral
      case 135: // RationalLiteral
      case 136: // DecimalLiteral
      case 137: // BinaryLiteral
      case 138: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 158: // Parameters
      case 159: // MaybeParameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 115: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 147: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
      case 79: // "absoluteIdentifierPath"
      case 80: // "relativeIdentifierPath"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 176: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 175: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 177: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 148: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 111: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 120: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
        break;

      case 114: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 105: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 104: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 106: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 128: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 109: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 149: // ComposedType
      case 150: // TupleType
      case 151: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 127: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 103: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 90: // AttributedDefinition
      case 91: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 89: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 93: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 121: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 92: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 97: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 98: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 130: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 117: // Term
      case 118: // SimpleOrClaspedTerm
      case 119: // OperatorExpression
      case 160: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 178: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 116: // Terms
      case 155: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 154: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 108: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 95: // FunctionDefinition
      case 96: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 88: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 165: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 166: // IdentifierPath
      case 167: // AbsoluteIdentifierPath
      case 168: // RelativeIdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 124: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 110: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 126: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 107: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 140: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 131: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 123: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 122: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 145: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 144: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 141: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 143: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 139: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 153: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 100: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 94: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 101: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 112: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 102: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 87: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 152: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 142: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 125: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 146: // Types
      case 156: // FunctionParameters
      case 157: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 132: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 129: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 113: // UpdateRule
      case 163: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 161: // MaybeInitially
      case 162: // Initializers
      case 164: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 99: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 133: // BooleanLiteral
      case 134: // IntegerLiteral
      case 135: // RationalLiteral
      case 136: // DecimalLiteral
      case 137: // BinaryLiteral
      case 138: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 158: // Parameters
      case 159: // MaybeParameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 115: // WhileRule
        yylhs.value.build< WhileRule::Ptr > ();
        break;

      case 147: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
      case 79: // "absoluteIdentifierPath"
      case 80: // "relativeIdentifierPath"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1551 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1632 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 508 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< UpdateRules::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( DirectCallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), programArguments );

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< UpdateRules::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
              asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1759 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1775 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< WhileRule::Ptr > ();
  }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1883 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1907 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1931 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1947 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1967 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1983 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinitions::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2075 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2083 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2091 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1043 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1051 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1160 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2618 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1197 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1254 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1315 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1323 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1360 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2820 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1400 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Record" );
      auto namedSubTypes = yystack_[3].value.as< VariableDefinitions::Ptr > ();
      namedSubTypes->add( yystack_[1].value.as< VariableDefinition::Ptr > () );

      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      auto subTypes = Ast::make< Types >( yylhs.location );
      for( const auto& namedSubType : *namedSubTypes )
      {
          identifiers->add( namedSubType->identifier() );
          subTypes->add( namedSubType->variableType() );
      }

      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes, identifiers );
  }
#line 2925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2994 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1539 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1555 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1559 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1563 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3117 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3140 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = yystack_[0].value.as< IdentifierPath::Ptr > ();
  }
#line 3180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = yystack_[0].value.as< IdentifierPath::Ptr > ();
  }
#line 3188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, GrammarParser::parseIdentifierPath( yylhs.location, yystack_[0].value.as< std::string > () ), IdentifierPath::Type::ABSOLUTE );
  }
#line 3196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1685 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = asIdentifierPath( yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3204 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, GrammarParser::parseIdentifierPath( yylhs.location, yystack_[0].value.as< std::string > () ), IdentifierPath::Type::RELATIVE );
  }
#line 3212 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3220 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3373 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3377 "GrammarParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int Parser::yypact_ninf_ = -150;

  const short int Parser::yytable_ninf_ = -170;

  const short int
  Parser::yypact_[] =
  {
      18,  -150,    21,    11,    49,    26,  -150,    -8,  -150,  -150,
    1460,    24,    44,  -150,  -150,    -3,    25,    25,    25,    25,
      25,   164,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
     101,  -150,  -150,  -150,     1,     1,     1,  1460,     1,  -150,
    -150,  -150,  1460,  1538,  1538,   987,   859,     5,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  2289,    28,  -150,    98,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,    98,  -150,  -150,  -150,  -150,  1524,
    -150,   109,   112,   109,   122,   124,  -150,  -150,   135,  -150,
    -150,   130,     1,     7,  -150,    33,  1852,    34,  -150,  -150,
    -150,   141,   134,  2058,    32,  -150,   139,   144,  -150,   -20,
    2091,  -150,  1460,  1460,  1460,  1460,  1460,  1460,  1460,  1460,
    1460,  1460,  1460,  1460,  1460,  1460,  1460,  1460,  1460,     2,
      15,   923,  -150,  -150,   987,  2289,   138,   154,  -150,   159,
      12,   150,   166,    93,     2,     2,     2,  1460,  -150,  1460,
       1,  1460,  1460,  1460,  -150,  1460,  -150,  -150,    25,  1460,
    -150,  -150,  1460,  1460,  2389,  2355,  2383,  2322,   147,   147,
     354,   137,   137,   156,   156,   156,  -150,  2322,   354,   137,
     137,     2,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
      78,  -150,    98,   171,  -150,    86,  2289,  2124,  1460,  1524,
    -150,   172,    92,   135,  -150,  -150,     1,     2,    23,  1332,
       2,  -150,  -150,   162,   157,  -150,  1587,  1992,  -150,  1698,
    1925,  2025,  2157,  -150,   139,  2289,  2289,  2190,   168,  -150,
     135,   169,  -150,     2,  1460,  -150,  -150,  -150,   160,  2289,
    -150,  -150,  -150,     1,  -150,   176,  -150,  -150,    13,  -150,
       1,   521,   591,  -150,     1,     1,     1,  1332,  1460,  1460,
    1460,   661,   731,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,   163,    -1,   161,   181,
       2,     2,  1460,  1460,  1460,  1460,  1460,  -150,  -150,     2,
      25,    41,   -19,   173,  -150,  1460,  -150,  1460,  -150,    23,
    -150,   216,  -150,  1056,   215,  1125,   194,    46,    48,  -150,
    1889,  1959,  1737,   190,  1194,   177,  1263,  1460,  1332,  -150,
     232,  2289,  2289,  2289,  2289,  2289,   198,   201,     2,  -150,
       2,  2289,  2289,  -150,  -150,  -150,  -150,  -150,  -150,  1460,
    1460,  1460,  1332,   200,  1332,  -150,  -150,  -150,  -150,  2289,
    -150,   202,   240,  -150,  -150,  -150,   196,  1620,  1659,  1776,
     228,   795,  -150,  1460,   205,  -150,  -150,  1332,  1332,  1460,
    1332,  1332,   207,   204,   210,  -150,  1396,  2223,  2256,  1524,
    -150,  -150,  1815,  -150,  -150,  -150,  1332,  1332,  -150,  -150,
    1332,  -150,   212,  1332,  -150,  -150,  -150,  -150,  -150
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   207,     0,   189,   188,
     211,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   206,   210,     0,     0,     0,     0,     0,   131,
     133,   132,     0,     0,     0,     0,     0,     0,   137,   138,
     134,   135,   136,   139,   192,   194,   212,    71,    73,    81,
     104,   105,    82,   106,    72,    74,    75,    76,    77,    78,
      83,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   193,   107,   190,   191,   208,   209,   187,
      21,   176,     0,   176,     0,     0,     5,     7,   196,   203,
     195,     0,     0,     0,   198,     0,     0,     0,   103,    84,
      85,     0,     0,    70,     0,   148,   193,     0,   141,     0,
      70,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   108,     0,   183,   129,   186,   182,     0,
       0,     0,     0,     0,     0,   171,     0,     0,   202,     0,
       0,     0,     0,     0,    80,     0,    79,   146,     0,     0,
     143,   142,     0,     0,   100,    98,    99,   102,    86,    87,
      93,    94,    95,    88,    89,    90,    91,   101,    92,    96,
      97,     0,   113,   152,   153,   158,   159,   154,   155,   156,
     157,   111,   109,     0,   167,     0,    70,    70,     0,     0,
      22,     0,     0,     0,   205,   173,     0,     0,     0,     0,
       0,    28,   169,   170,     0,   201,     0,     0,   197,     0,
       0,     0,    69,   147,     0,   149,    69,     0,     0,   151,
     193,     0,   200,   171,     0,   110,   166,   165,    79,   185,
     181,   175,   174,     0,   204,     0,    25,    27,     0,    23,
       0,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,    67,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   145,   144,     0,
       0,     0,   151,     0,   164,     0,   172,     0,    15,     0,
      24,     0,    42,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
     178,   114,   117,   116,   115,   118,   150,   199,     0,   162,
       0,   184,    16,    26,    65,    63,    41,    61,    59,     0,
       0,     0,     0,     0,     0,    60,    58,    64,    62,    66,
      18,     0,   180,   160,   161,   150,     0,     0,     0,     0,
      44,     0,    68,     0,     0,    19,   163,     0,     0,     0,
       0,     0,     0,     0,     0,    52,     0,     0,     0,   187,
      53,    54,     0,    56,    45,    47,     0,     0,    46,    51,
       0,   177,     0,     0,    48,    49,    50,   179,    55
  };

  const short int
  Parser::yypgoto_[] =
  {
    -150,  -150,  -150,  -150,   243,   236,  -150,  -150,  -150,  -150,
    -150,   -41,  -150,  -150,    91,  -127,  -150,  -150,  -150,  -117,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
     -37,   -10,   -26,  -150,   123,   131,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,   132,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,   -73,  -150,  -150,   102,
      30,  -149,  -150,  -150,  -150,  -150,  -150,  -150,  -150,   -72,
    -150,    31,  -150,   178,  -150,  -150,  -150,    66,  -113,   165,
      22,  -150,  -150,   175,   -34,  -150,  -142,   -31,    27,    10,
      -4,  -150,  -150
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   257,   258,    29,   312,   313,   274,   275,   276,   385,
     386,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     112,   145,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,   114,   115,
     238,   192,   193,   194,   195,   196,   197,   198,   199,   142,
     223,   224,   212,   151,   362,   375,   147,   148,   149,    83,
      84,    85,    86,    99,   103,   241,   100,   104,   215,   102,
       6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      56,    32,   105,   101,   107,   221,   222,   225,   214,   119,
       5,    13,   143,   211,    30,     8,   146,   109,   110,     8,
       8,     1,     7,     8,   256,   159,    32,   106,   171,    31,
       8,    30,   108,     8,   172,   113,   120,    90,  -169,     8,
      33,     8,   239,     8,   141,  -169,    89,   191,     2,   242,
      14,   161,   163,    15,    16,    17,    18,    19,    20,     2,
     139,   160,   -81,   308,   350,     2,   351,   309,   255,   121,
       2,   289,    87,     2,   254,     9,    54,    55,   167,     9,
       9,    54,    55,     9,    54,    55,   168,   160,   160,    50,
       9,   140,    88,     9,   302,   338,     2,   339,    32,     9,
     160,     9,   160,     9,   205,    15,    16,    17,    18,    19,
      20,   214,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   228,
     245,   206,   247,   243,   207,   315,   146,   219,   252,   244,
     172,   329,   330,   141,   324,   326,   253,   226,     2,   227,
     336,   229,   230,   231,   150,   232,   152,   220,   337,   235,
     216,   200,   236,   237,    -2,    14,   154,    10,    15,    16,
      17,    18,    19,    20,   157,   155,   200,   200,   200,   126,
     127,    91,    92,    93,    94,    95,   156,   164,   165,   365,
     169,   366,   170,   286,   131,   132,   133,   134,   249,    98,
      98,    98,   208,    98,   131,   132,   133,   134,   209,   210,
     116,     2,    32,   200,   217,   218,   134,   246,   251,   290,
     307,   291,   299,   300,   305,   328,   140,   327,   260,   344,
     347,   317,   318,   316,   304,   286,   286,   340,   349,   200,
     355,   286,   200,   361,   363,   286,   286,   364,   357,   371,
     374,   373,   376,   381,   389,   396,    32,   395,   320,   321,
     322,   397,   407,   216,    96,   200,    97,    98,   343,   399,
     233,   153,   201,   301,   303,   250,   402,   158,     0,     0,
     306,     0,   331,   332,   333,   334,   335,   286,     0,   286,
       0,     0,     0,     0,     0,   341,     0,   342,   286,     0,
     286,     0,   286,     0,     0,   202,     0,     0,     0,   116,
     273,     0,   200,   200,     0,   213,   146,   359,     0,   260,
       0,   200,     0,     0,     0,    98,   286,     0,   286,     0,
       0,     0,     0,   234,     0,     0,     0,     0,     0,   367,
     368,   369,   287,     0,     0,     0,     0,     0,     0,     0,
     288,   286,   286,     0,   286,   286,   240,     0,   319,     0,
     200,   387,   200,   388,     0,     0,     0,     0,     0,   392,
     286,   286,     0,     0,   286,     0,   387,   286,     0,     0,
       0,   213,     0,   259,   287,   287,     0,     0,     0,     0,
     287,     0,   288,   288,   287,   287,   126,   127,   288,     0,
       0,     0,   288,   288,   346,     0,   346,     0,     0,   129,
     130,   131,   132,   133,   134,   346,     0,   346,   213,   360,
       0,     0,   137,   138,     0,   310,     0,     0,     0,    98,
      98,    98,     0,     0,     0,     0,   287,     0,   287,     0,
       0,     0,     0,   370,   288,   372,   288,   287,     0,   287,
       0,   287,     0,     0,     0,   288,     0,   288,     0,   288,
       0,     0,     0,     0,     0,   213,     0,     0,   390,   391,
       0,   393,   394,     0,   259,   287,     0,   287,     0,     0,
       0,     0,     0,   288,     0,   288,     0,   404,   405,     0,
       0,   406,     0,     0,   408,     0,     0,     0,     0,     0,
     287,   287,     0,   287,   287,     0,     0,     0,   288,   288,
       0,   288,   288,     0,     0,     0,     0,     0,     0,   287,
     287,     0,   311,   287,     0,     0,   287,   288,   288,     0,
       0,   288,     0,   261,   288,   262,     0,   263,   264,     8,
     265,   266,   267,     0,   268,     0,     0,   269,     0,     0,
       0,     0,     0,     0,   270,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     271,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   272,   314,    48,    49,    50,    51,    52,    53,     9,
      54,    55,     0,   261,     0,   262,     0,   263,   264,     8,
     265,   266,   267,     0,   268,     0,     0,   269,     0,     0,
       0,     0,     0,     0,   270,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     271,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   272,   323,    48,    49,    50,    51,    52,    53,     9,
      54,    55,     0,   261,     0,   262,     0,   263,   264,     8,
     265,   266,   267,     0,   268,     0,     0,   269,     0,     0,
       0,     0,     0,     0,   270,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     271,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   272,   325,    48,    49,    50,    51,    52,    53,     9,
      54,    55,     0,   261,     0,   262,     0,   263,   264,     8,
     265,   266,   267,     0,   268,     0,     0,   269,     0,     0,
       0,     0,     0,     0,   270,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     271,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   382,     0,     0,     0,
       0,   272,     0,    48,    49,    50,    51,    52,    53,     9,
      54,    55,    34,     8,    35,    36,     0,     0,    37,     0,
       0,     0,     0,   383,     0,    38,     0,     0,     0,    39,
      40,    41,     0,     0,     0,     0,    42,    43,    44,     0,
      45,     0,    46,     0,     0,     0,     0,   384,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,     0,     0,     0,     0,     0,    48,    49,    50,
      51,    52,    53,     9,    54,    55,    34,     8,    35,    36,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,    45,     0,    46,   118,     0,     0,
       0,     0,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    52,    53,     9,    54,    55,
      34,     8,    35,    36,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,   204,
      46,     0,     0,     0,     0,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,     9,    54,    55,    34,     8,    35,    36,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,     0,    46,     0,     0,     0,     0,     0,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,     9,    54,    55,   261,   345,
     262,     0,   263,   264,     8,   265,   266,   267,     0,   268,
       0,     0,   269,     0,     0,     0,     0,     0,     0,   270,
      39,    40,    41,     0,     0,     0,     0,     0,    43,    44,
       0,    45,     0,    46,     0,   271,     0,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   272,     0,    48,    49,
      50,    51,    52,    53,     9,    54,    55,   261,     0,   262,
     348,   263,   264,     8,   265,   266,   267,     0,   268,     0,
       0,   269,     0,     0,     0,     0,     0,     0,   270,    39,
      40,    41,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,    46,     0,   271,     0,     0,     0,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   272,     0,    48,    49,    50,
      51,    52,    53,     9,    54,    55,   261,     0,   262,     0,
     263,   264,     8,   265,   266,   267,     0,   268,     0,     0,
     269,     0,     0,     0,     0,     0,     0,   270,    39,    40,
      41,     0,     0,     0,     0,     0,    43,    44,     0,    45,
       0,    46,     0,   271,   356,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   272,     0,    48,    49,    50,    51,
      52,    53,     9,    54,    55,   261,     0,   262,     0,   263,
     264,     8,   265,   266,   267,     0,   268,     0,     0,   269,
       0,     0,     0,     0,     0,     0,   270,    39,    40,    41,
       0,     0,     0,     0,     0,    43,    44,     0,    45,     0,
      46,     0,   271,     0,     0,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   272,   358,    48,    49,    50,    51,    52,
      53,     9,    54,    55,   261,     0,   262,     0,   263,   264,
       8,   265,   266,   267,     0,   268,     0,     0,   269,     0,
       0,     0,     0,     0,     0,   270,    39,    40,    41,     0,
       0,     0,     0,     0,    43,    44,     0,    45,     0,    46,
       0,   271,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   272,     0,    48,    49,    50,    51,    52,    53,
       9,    54,    55,    34,     8,    35,    36,     0,     0,    37,
       0,     0,     0,     0,   383,     0,    38,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
       0,    45,     0,    46,     0,     0,   398,     0,   384,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,    51,    52,    53,     9,    54,    55,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,     0,    46,     0,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    53,     9,    54,
      55,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,     8,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,   144,
       0,    46,    39,    40,    41,     0,     0,    47,     0,     0,
      43,    44,     0,    45,     0,    46,     0,     0,     0,     0,
       0,    47,     0,     0,     0,     0,    48,    49,    50,    51,
      52,    53,     9,    54,    55,   292,     0,     0,     0,     0,
      48,    49,    50,    51,    52,    53,     9,    54,    55,     0,
       0,     0,     0,     0,   122,   123,   124,   125,     0,   126,
     127,   128,     0,     0,     0,     0,     0,     0,   377,     0,
       0,     0,   129,   130,   131,   132,   133,   134,     0,     0,
       0,     0,   135,     0,   136,   137,   138,   122,   123,   124,
     125,     0,   126,   127,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,   133,
     134,   378,     0,     0,     0,   135,     0,   136,   137,   138,
     379,     0,     0,     0,     0,     0,   122,   123,   124,   125,
       0,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,   132,   133,   134,
     294,     0,     0,     0,   135,     0,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   122,   123,   124,   125,     0,
     126,   127,   128,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   354,
       0,     0,     0,   135,     0,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   122,   123,   124,   125,     0,   126,
     127,   128,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   380,     0,
       0,     0,   135,     0,   136,   137,   138,     0,     0,     0,
       0,     0,     0,   122,   123,   124,   125,     0,   126,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   129,   130,   131,   132,   133,   134,   403,     0,     0,
       0,   135,     0,   136,   137,   138,     0,     0,     0,     0,
       0,     0,   122,   123,   124,   125,     0,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,   162,     0,     0,     0,
     135,     0,   136,   137,   138,     0,     0,     0,     0,   122,
     123,   124,   125,     0,   126,   127,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   352,     0,     0,     0,   135,     0,   136,
     137,   138,     0,     0,     0,     0,   122,   123,   124,   125,
       0,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,   132,   133,   134,
     295,     0,     0,     0,   135,     0,   136,   137,   138,     0,
       0,     0,   122,   123,   124,   125,     0,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,   353,     0,     0,     0,
     135,     0,   136,   137,   138,     0,   122,   123,   124,   125,
       0,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,   132,   133,   134,
       0,   293,     0,     0,   135,     0,   136,   137,   138,   122,
     123,   124,   125,     0,   126,   127,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,     0,     0,     0,   296,   135,     0,   136,
     137,   138,   122,   123,   124,   125,     0,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,     0,     0,     0,     0,
     135,     0,   136,   137,   138,   122,   123,   124,   125,     0,
     126,   127,   128,     0,   166,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,   135,     0,   136,   137,   138,   122,   123,
     124,   125,     0,   126,   127,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   130,   131,   132,
     133,   134,     0,   173,     0,     0,   135,     0,   136,   137,
     138,   122,   123,   124,   125,     0,   126,   127,   128,     0,
     248,     0,     0,     0,     0,     0,     0,     0,     0,   129,
     130,   131,   132,   133,   134,     0,     0,     0,     0,   135,
       0,   136,   137,   138,   122,   123,   124,   125,     0,   126,
     127,   128,     0,   297,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,     0,     0,
       0,     0,   135,     0,   136,   137,   138,   122,   123,   124,
     125,     0,   126,   127,   128,     0,     0,     0,   298,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,   133,
     134,     0,     0,     0,     0,   135,     0,   136,   137,   138,
     122,   123,   124,   125,     0,   126,   127,   128,     0,     0,
       0,     0,     0,     0,   400,     0,     0,     0,   129,   130,
     131,   132,   133,   134,     0,     0,     0,     0,   135,     0,
     136,   137,   138,   122,   123,   124,   125,     0,   126,   127,
     128,     0,     0,     0,     0,     0,   401,     0,     0,     0,
       0,   129,   130,   131,   132,   133,   134,     0,     0,     0,
       0,   135,     0,   136,   137,   138,   122,   123,   124,   125,
       0,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,   132,   133,   134,
       0,     0,     0,     0,   135,     0,   136,   137,   138,   122,
     123,   124,     0,     0,   126,   127,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,     0,     0,   136,
     137,   138,   122,     0,   124,     0,     0,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,     0,     0,     0,     0,
     122,     0,   136,   137,   138,   126,   127,   128,     0,     0,
       0,   126,   127,   128,     0,     0,     0,     0,   129,   130,
     131,   132,   133,   134,   129,   130,   131,   132,   133,   134,
     136,   137,   138,     0,     0,     0,   136,   137,   138
  };

  const short int
  Parser::yycheck_[] =
  {
      10,     5,    36,    34,    38,   154,   155,   156,   150,    46,
       0,     0,    84,     1,     4,    18,    89,    43,    44,    18,
      18,     3,     1,    18,     1,    18,    30,    37,    48,     3,
      18,    21,    42,    18,    54,    45,    46,    15,    57,    18,
      48,    18,   191,    18,    45,    64,    49,    45,    47,   191,
       1,    18,    18,     4,     5,     6,     7,     8,     9,    47,
      32,    54,    63,    50,    18,    47,    18,    54,   217,    47,
      47,   220,    48,    47,   216,    78,    79,    80,    46,    78,
      78,    79,    80,    78,    79,    80,    54,    54,    54,    74,
      78,    63,    48,    78,   243,    54,    47,    56,   102,    78,
      54,    78,    54,    78,   141,     4,     5,     6,     7,     8,
       9,   253,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   160,
     202,   141,    46,    55,   144,   262,   209,    44,    46,    61,
      54,   290,   291,    45,   271,   272,    54,   157,    47,   159,
     299,   161,   162,   163,    45,   165,    44,    64,   300,   169,
     150,   139,   172,   173,     0,     1,    44,     2,     4,     5,
       6,     7,     8,     9,    44,    51,   154,   155,   156,    42,
      43,    16,    17,    18,    19,    20,    51,    46,    54,   338,
      51,   340,    48,   219,    57,    58,    59,    60,   208,    34,
      35,    36,    64,    38,    57,    58,    59,    60,    54,    50,
      45,    47,   216,   191,    64,    49,    60,    46,    46,    57,
      44,    64,    54,    54,    64,    44,    63,    66,   218,    13,
      15,   265,   266,   264,   244,   261,   262,    64,    44,   217,
      50,   267,   220,    11,    46,   271,   272,    46,    71,    49,
      10,    49,    56,    25,    49,    51,   260,    50,   268,   269,
     270,    51,    50,   253,    21,   243,    30,   102,   309,   386,
     168,    93,   140,   243,   243,   209,   389,   102,    -1,    -1,
     253,    -1,   292,   293,   294,   295,   296,   313,    -1,   315,
      -1,    -1,    -1,    -1,    -1,   305,    -1,   307,   324,    -1,
     326,    -1,   328,    -1,    -1,   140,    -1,    -1,    -1,   144,
     219,    -1,   290,   291,    -1,   150,   389,   327,    -1,   309,
      -1,   299,    -1,    -1,    -1,   160,   352,    -1,   354,    -1,
      -1,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   349,
     350,   351,   219,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     219,   377,   378,    -1,   380,   381,   191,    -1,   267,    -1,
     338,   371,   340,   373,    -1,    -1,    -1,    -1,    -1,   379,
     396,   397,    -1,    -1,   400,    -1,   386,   403,    -1,    -1,
      -1,   216,    -1,   218,   261,   262,    -1,    -1,    -1,    -1,
     267,    -1,   261,   262,   271,   272,    42,    43,   267,    -1,
      -1,    -1,   271,   272,   313,    -1,   315,    -1,    -1,    55,
      56,    57,    58,    59,    60,   324,    -1,   326,   253,   328,
      -1,    -1,    68,    69,    -1,   260,    -1,    -1,    -1,   264,
     265,   266,    -1,    -1,    -1,    -1,   313,    -1,   315,    -1,
      -1,    -1,    -1,   352,   313,   354,   315,   324,    -1,   326,
      -1,   328,    -1,    -1,    -1,   324,    -1,   326,    -1,   328,
      -1,    -1,    -1,    -1,    -1,   300,    -1,    -1,   377,   378,
      -1,   380,   381,    -1,   309,   352,    -1,   354,    -1,    -1,
      -1,    -1,    -1,   352,    -1,   354,    -1,   396,   397,    -1,
      -1,   400,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,
     377,   378,    -1,   380,   381,    -1,    -1,    -1,   377,   378,
      -1,   380,   381,    -1,    -1,    -1,    -1,    -1,    -1,   396,
     397,    -1,     1,   400,    -1,    -1,   403,   396,   397,    -1,
      -1,   400,    -1,    12,   403,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,     1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,     1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,     1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,
      45,    -1,    47,    -1,    -1,    -1,    -1,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    17,    18,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      41,    42,    43,    -1,    45,    -1,    47,    48,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    17,    18,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    12,    13,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    12,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    12,    -1,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    45,
      -1,    47,    -1,    49,    50,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    12,    -1,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    12,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,
      -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,    -1,    -1,    50,    -1,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    18,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,
      -1,    47,    34,    35,    36,    -1,    -1,    53,    -1,    -1,
      42,    43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    18,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    22,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      31,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      22,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    22,
      -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    22,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    22,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    24,    -1,    -1,    -1,
      65,    -1,    67,    68,    69,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    24,    -1,    -1,    -1,    65,    -1,    67,
      68,    69,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      25,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      -1,    -1,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    27,    -1,    -1,    -1,
      65,    -1,    67,    68,    69,    -1,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    29,    -1,    -1,    65,    -1,    67,    68,    69,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    31,    65,    -1,    67,
      68,    69,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    -1,    67,    68,    69,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    -1,    67,    68,    69,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    65,    -1,    67,    68,
      69,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    -1,    67,    68,    69,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,
      67,    68,    69,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    37,
      38,    39,    -1,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    37,    -1,    39,    -1,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      37,    -1,    67,    68,    69,    42,    43,    44,    -1,    -1,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    55,    56,    57,    58,    59,    60,
      67,    68,    69,    -1,    -1,    -1,    67,    68,    69
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    47,    87,    88,   175,   176,     1,    18,    78,
     165,   177,   178,     0,     1,     4,     5,     6,     7,     8,
       9,    89,    90,    91,    92,    93,    94,    95,    96,    99,
     175,     3,   176,    48,    17,    19,    20,    23,    30,    34,
      35,    36,    41,    42,    43,    45,    47,    53,    72,    73,
      74,    75,    76,    77,    79,    80,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   165,   166,   167,   168,    48,    48,    49,
     166,   165,   165,   165,   165,   165,    90,    91,   165,   169,
     172,   173,   175,   170,   173,   170,   117,   170,   117,   118,
     118,     1,   116,   117,   144,   145,   165,     1,    48,   116,
     117,   166,    37,    38,    39,    40,    42,    43,    44,    55,
      56,    57,    58,    59,    60,    65,    67,    68,    69,    32,
      63,    45,   155,   155,    45,   117,   142,   162,   163,   164,
      45,   159,    44,   159,    44,    51,    51,    44,   169,    18,
      54,    18,    24,    18,    46,    54,    46,    46,    54,    51,
      48,    48,    54,    62,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,    45,   147,   148,   149,   150,   151,   152,   153,   154,
     166,   134,   165,     1,    46,   116,   117,   117,    64,    54,
      50,     1,   158,   165,   172,   174,   175,    64,    49,    44,
      64,   147,   147,   156,   157,   147,   117,   117,   173,   117,
     117,   117,   117,   145,   165,   117,   117,   117,   146,   147,
     165,   171,   172,    55,    61,   155,    46,    46,    46,   117,
     163,    46,    46,    54,   172,   147,     1,    97,    98,   165,
     175,    12,    14,    16,    17,    19,    20,    21,    23,    26,
      33,    49,    70,   100,   102,   103,   104,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   118,   120,   121,   147,
      57,    64,    18,    29,    22,    25,    31,    46,    48,    54,
      54,   146,   147,   157,   117,    64,   174,    44,    50,    54,
     165,     1,   100,   101,     1,   101,   173,   170,   170,   100,
     117,   117,   117,     1,   101,     1,   101,    66,    44,   147,
     147,   117,   117,   117,   117,   117,   147,   172,    54,    56,
      64,   117,   117,    97,    13,    13,   100,    15,    15,    44,
      18,    18,    24,    27,    22,    50,    50,    71,    71,   117,
     100,    11,   160,    46,    46,   147,   147,   117,   117,   117,
     100,    49,   100,    49,    10,   161,    56,    18,    22,    31,
      22,    25,     1,    28,    52,   105,   106,   117,   117,    49,
     100,   100,   117,   100,   100,    50,    51,    51,    50,   105,
      51,    50,   164,    22,   100,   100,   100,    50,   100
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    86,    87,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    91,    91,    91,    92,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    98,    98,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   102,   103,   103,   104,   104,   105,   105,
     105,   106,   106,   107,   108,   108,   109,   110,   111,   111,
     111,   111,   112,   112,   112,   112,   113,   114,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   121,   121,   122,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   132,   133,   133,   134,   135,   136,   137,   137,   138,
     139,   140,   140,   140,   141,   142,   143,   144,   144,   145,
     146,   146,   147,   147,   147,   147,   147,   148,   149,   149,
     150,   151,   152,   153,   154,   155,   155,   155,   156,   156,
     157,   157,   158,   158,   159,   159,   159,   160,   160,   161,
     161,   162,   162,   163,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   168,   169,   169,   170,   170,   171,
     171,   172,   173,   173,   174,   174,   175,   175,   176,   176,
     176,   177,   178
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     6,     7,     5,     7,     8,
       1,     2,     4,     1,     2,     1,     3,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     4,     6,     6,     6,     3,     3,
       3,     2,     1,     6,     6,     8,     6,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     2,     3,
       4,     3,     2,     3,     6,     6,     6,     6,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     5,     5,     3,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     4,     6,     3,     3,     3,     2,     3,     1,
       1,     0,     3,     1,     3,     3,     0,     4,     0,     4,
       0,     3,     1,     1,     5,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     2,     1,     2,     1,     2,     1,     3,     3,
       3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"as\"", "\"while\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "\"absoluteIdentifierPath\"",
  "\"relativeIdentifierPath\"", "ABSOLUTE_PATH", "CALL", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "UsingDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "WhileRule", "Terms", "Term", "SimpleOrClaspedTerm",
  "OperatorExpression", "CallExpression", "DirectCallExpression",
  "MethodCallExpression", "LiteralCallExpression",
  "IndirectCallExpression", "TypeCastingExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "Literal", "UndefinedLiteral", "BooleanLiteral", "IntegerLiteral",
  "RationalLiteral", "DecimalLiteral", "BinaryLiteral", "StringLiteral",
  "ReferenceLiteral", "ListLiteral", "RangeLiteral", "TupleLiteral",
  "RecordLiteral", "Assignments", "Assignment", "Types", "Type",
  "BasicType", "ComposedType", "TupleType", "RecordType", "TemplateType",
  "RelationType", "FixedSizedType", "Arguments", "FunctionParameters",
  "MaybeFunctionParameters", "Parameters", "MaybeParameters",
  "MaybeDefined", "MaybeInitially", "Initializers", "Initializer",
  "MaybeInitializers", "Identifier", "IdentifierPath",
  "AbsoluteIdentifierPath", "RelativeIdentifierPath", "Variable",
  "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "Attributes",
  "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   396,   396,   405,   411,   419,   425,   435,   441,   445,
     453,   457,   461,   465,   469,   477,   485,   493,   498,   507,
     523,   531,   553,   571,   575,   581,   589,   595,   605,   617,
     621,   625,   629,   633,   637,   641,   645,   649,   653,   657,
     661,   669,   675,   685,   693,   697,   705,   709,   717,   721,
     725,   733,   739,   749,   757,   761,   769,   777,   785,   789,
     793,   798,   807,   811,   815,   820,   829,   837,   845,   857,
     863,   873,   877,   881,   885,   889,   893,   897,   901,   909,
     913,   917,   921,   925,   929,   933,   945,   949,   953,   957,
     961,   965,   969,   973,   977,   981,   985,   989,   993,   997,
    1001,  1005,  1009,  1013,  1021,  1025,  1029,  1037,  1042,  1050,
    1055,  1063,  1071,  1079,  1087,  1095,  1103,  1111,  1119,  1131,
    1135,  1139,  1143,  1147,  1151,  1155,  1159,  1163,  1167,  1171,
    1175,  1183,  1191,  1196,  1205,  1221,  1237,  1253,  1265,  1281,
    1297,  1305,  1310,  1314,  1322,  1329,  1337,  1344,  1350,  1359,
    1371,  1377,  1387,  1391,  1395,  1399,  1403,  1411,  1419,  1423,
    1430,  1440,  1460,  1468,  1476,  1488,  1492,  1496,  1510,  1516,
    1526,  1530,  1538,  1544,  1554,  1558,  1562,  1574,  1578,  1586,
    1590,  1598,  1604,  1614,  1621,  1630,  1640,  1644,  1656,  1660,
    1668,  1672,  1680,  1684,  1692,  1704,  1708,  1717,  1723,  1733,
    1739,  1749,  1757,  1763,  1771,  1777,  1788,  1794,  1804,  1808,
    1812,  1820,  1828
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 4470 "GrammarParser.cpp" // lalr1.cc:1167
#line 1834 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( {location}, message, Code::SyntaxError );
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
