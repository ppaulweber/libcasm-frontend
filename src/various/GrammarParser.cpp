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
#line 69 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "src/Lexer.h"
    #include "src/Exceptions.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    std::pair< FunctionDefinition::Classification, bool > parseFunctionAttributes(
        const NodeList< IdentifierNode >::Ptr& attributes )
    {
        using Classification = FunctionDefinition::Classification;

        auto functionClass = Classification::CONTROLLED;
        bool symbolicFunction = false;

        bool classAttributeAlreadyUsed = false;
        IdentifierNode::Ptr classAttribute;

        bool symbolicAttributeAlreadyUsed = false;
        IdentifierNode::Ptr symbolicAttribute;

        for( const auto& attribute : *attributes )
        {
            const auto& name = attribute->identifier();

            if( name == "symbolic" )
            {
                symbolicFunction = true;

                if( symbolicAttributeAlreadyUsed )
                {
                    /*driver.error
                    ( { symbolicAttribute->location(), attribute->location() }
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    ); TODO */
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
                /*driver.error
                ( attribute->location()
                , "`" + name + "` is no valid function attribute, only in, monitored, "
                + "controlled, shared, out, static and symbolic are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                ); TODO */
            }

            if( classAttributeAlreadyUsed )
            {
                /*driver.error
                ( { classAttribute->location(), attribute->location() }
                , "a function classifier attribute can only be used once per function"
                , libcasm_fe::Codes::FunctionAttributeMultipleUseOfFunctionClassifier
                ); TODO */
            }
            else
            {
                classAttributeAlreadyUsed = true;
                classAttribute = attribute;
            }
        }

        return { functionClass, symbolicFunction };
    }

    static FunctionDefinition::Ptr createProgramFunction( location& sourceLocation )
    {
        //auto argTypes = { new Type( TypeType::AGENT ) }; // TODO add args and return type
        //auto retType = new Type( TypeType::RuleReference );

        const auto program = make< IdentifierNode >( sourceLocation, "program" );
        return make< FunctionDefinition >( sourceLocation, program, nullptr, nullptr );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = make< Rules >( sourceLocation );
        rules->add( rule );
        return make< BlockRule >( sourceLocation, rules );
    }

#line 173 "GrammarParser.cpp" // lalr1.cc:413


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

#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 259 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Lexer& lexer_yyarg, const std::string& specificationName_yyarg, Specification::Ptr& result_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      specificationName (specificationName_yyarg),
      result (result_yyarg)
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
      case 101: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 137: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 140: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 132: // CaseLabel
        value.move< CaseRule::Case > (that.value);
        break;

      case 131: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 102: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 130: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 125: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 115: // Term
      case 116: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 119: // Terms
      case 120: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 103: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 135: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 122: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 136: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 134: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 118: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 117: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 104: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 127: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 126: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 114: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 128: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 138: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 129: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 100: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 107: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 124: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 139: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 97: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.move< std::string > (that.value);
        break;

      case 133: // CaseLabels
        value.move< std::vector< CaseRule::Case > > (that.value);
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
      case 101: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 137: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 140: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 132: // CaseLabel
        value.copy< CaseRule::Case > (that.value);
        break;

      case 131: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 102: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 130: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 121: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 125: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 115: // Term
      case 116: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 119: // Terms
      case 120: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 103: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 135: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 122: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 136: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 134: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 118: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 117: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 104: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 127: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 126: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 114: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 128: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 138: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 129: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 100: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 107: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 124: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 139: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 97: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case 133: // CaseLabels
        value.copy< std::vector< CaseRule::Case > > (that.value);
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


    // User initialization code.
    #line 61 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 945 "GrammarParser.cpp" // lalr1.cc:741

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
      case 101: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 137: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 140: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 132: // CaseLabel
        yylhs.value.build< CaseRule::Case > ();
        break;

      case 131: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 102: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 123: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 130: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 80: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 81: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 121: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 93: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 125: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 115: // Term
      case 116: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 119: // Terms
      case 120: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 103: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 135: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 94: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 122: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 136: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 134: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 118: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 117: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 104: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 127: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 126: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 114: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 128: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 138: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 129: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 79: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 100: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 107: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 124: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 89: // Initializer
      case 139: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 97: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      case 133: // CaseLabels
        yylhs.value.build< std::vector< CaseRule::Case > > ();
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
#line 375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto name = make< IdentifierNode >( yylhs.location, specificationName );
      result = make< Specification >( yylhs.location, name, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< IdentifierNode::Ptr > ();

      auto function = make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );

      const auto attributes = parseFunctionAttributes( yystack_[7].value.as< NodeList< IdentifierNode >::Ptr > () );
      function->setClassification( attributes.first );
      function->setSymbolic( attributes.second );

      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( identifier );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 453 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      auto arguments = make< Expressions >( yylhs.location );
      // TODO add `default` agent to arguments
      const auto program = make< DirectCallExpression >(
          yylhs.location, programDefinition->identifier(), arguments );

      const auto ruleReference = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );

      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), nullptr ); // TODO
  }
#line 1621 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1681 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 767 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 771 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1950 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1958 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1990 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1027 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1059 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2206 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1089 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1097 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1113 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1131 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2289 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1139 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1195 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1207 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1220 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1233 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1246 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2456 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1254 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2464 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1262 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1274 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1294 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2512 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1315 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2558 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -141;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      15,   187,    21,   -40,   -51,   -51,   -51,   -17,  -141,   187,
    -141,  -141,  -141,  -141,  -141,  -141,   769,  -141,  -141,    -4,
       0,    -4,   -51,   -51,  -141,   -51,   824,   -51,  -141,  -141,
    -141,   824,   824,   824,   384,   494,   -29,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,    -6,    12,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  1134,  -141,  -141,  -141,
      11,  -141,  -141,  -141,  -141,  -141,   -51,    16,    23,   -36,
    -141,    29,    31,    36,    43,    65,   549,   913,    66,  -141,
    -141,  -141,  -141,   824,  1104,    49,   604,  -141,  1074,   659,
    -141,   769,  -141,   714,  -141,   824,   824,   824,   824,   824,
     824,   824,   824,   824,   824,   824,   824,   824,   824,   824,
     824,   824,   824,  -141,    25,   -51,   -51,   361,   -51,   -51,
    -141,   -51,   -51,   824,  1164,   824,   824,  1194,  -141,  -141,
    -141,  -141,  1224,  -141,   824,  -141,  -141,  1254,  1538,  1494,
    1519,  1464,    94,    94,    33,   131,   131,    41,    41,    41,
    -141,  1404,    33,   131,   131,  1404,  -141,   -51,    10,    63,
    -141,  -141,  -141,  -141,    -7,   361,   361,  -141,   -51,   -51,
     361,   -30,   824,   824,    52,   361,   361,    60,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
      68,  -141,    58,    64,  -141,  -141,  1044,   982,   -26,    82,
    -141,  1284,  -141,   -51,   824,   824,  -141,  -141,    35,   294,
      85,   136,  -141,  -141,  -141,   948,  1014,   309,   346,   824,
     361,   -51,   -51,   824,   824,   824,  -141,  -141,  -141,    28,
    1314,  1404,  -141,  -141,  -141,   824,   824,   361,   108,  -141,
    -141,  1404,  -141,  -141,   149,  -141,  1404,  -141,  -141,   -51,
     824,   824,   848,   878,   141,   439,   128,   166,  -141,  1434,
     361,   361,   361,   135,   142,  1344,   439,   129,   824,   133,
    -141,   824,  -141,  -141,  -141,   361,   361,   361,  -141,  -141,
    1374,   769,  -141,  -141,  -141,  -141,   137,  -141
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,     0,     0,     0,    61,    63,
      62,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      69,    68,    64,    27,    28,     0,   109,    79,    59,    60,
      58,    54,    55,    56,    57,    53,    23,    76,    78,    77,
       0,    71,    72,    73,    74,    75,     0,     0,     0,     0,
      34,    35,     0,     0,    38,     0,     0,     0,     0,   100,
      81,    83,   108,     0,     0,    76,     0,   102,     0,     0,
      70,     0,    22,     0,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
      19,    18,     0,     0,     0,     0,     0,     0,    82,   106,
      80,   107,     0,   103,     0,   104,    26,     0,    98,    96,
      97,    99,    84,    85,    91,    92,    93,    86,    87,    88,
      89,    24,    90,    94,    95,    25,    41,     0,    47,     0,
      43,    44,    45,    46,     0,     0,     0,   129,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   147,   149,   115,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       0,    33,    17,     0,    16,    37,     0,     0,     0,     0,
     105,     0,    39,     0,     0,     0,    31,   128,     0,     0,
       0,     0,   140,   146,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,   101,    52,     0,
       0,    30,   144,   127,   142,     0,     0,     0,     0,   141,
     143,   145,   116,    15,    14,   113,   112,   114,    48,     0,
      49,     0,     0,     0,   130,     0,     0,    12,    51,     0,
       0,     0,     0,     0,     0,     0,   137,     0,     0,     0,
       9,    50,   138,   139,   131,     0,     0,     0,   136,   132,
       0,    29,   133,   134,   135,    13,     0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -141,  -141,   189,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,   110,  -141,   -82,  -141,  -141,    -3,    88,  -141,    14,
    -141,   184,   -19,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,    34,   -25,  -141,
    -141,   173,   -41,     4,    79,  -141,  -141,  -141,  -141,  -113,
    -140,  -141,  -141,  -141,  -141,   -57,  -141,  -141,  -141,  -141,
    -141,  -141,  -141
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   270,   257,   192,   193,    23,
      11,    43,    44,    45,    12,    13,    46,    71,    72,    75,
     114,    67,   159,   160,   161,   162,   163,   229,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    86,    60,    61,    62,    63,    64,    65,    14,   207,
     208,   180,   181,   182,   266,   267,   183,   184,   185,   186,
     187,   188,   189
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      18,    19,    20,    21,   179,    94,   225,   117,    16,    85,
      95,    96,    97,    98,   174,    99,   100,   101,     1,    70,
      73,    15,    74,    17,    74,   118,   209,    22,   102,   103,
     104,   105,   106,   107,    17,   217,   218,   109,   110,   111,
      66,    78,   206,    68,    17,    90,   119,    91,   165,   232,
     166,    85,   167,   168,   203,   169,   170,   212,   171,   172,
      77,    92,   173,    74,   204,    79,    80,    81,    84,    88,
     156,   116,   112,   248,    99,   100,   120,   115,   157,   174,
     113,   249,   119,   175,   123,   126,   121,   102,   103,   104,
     105,   106,   107,   122,   130,   233,   233,   110,   111,   190,
     107,   176,   194,   195,   233,   233,   205,   242,    83,    17,
     124,   220,   158,    70,   221,   158,   191,   127,   158,   158,
     132,   177,   219,   132,   254,   222,    93,   137,   235,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   272,   273,   274,
     104,   105,   106,   107,    74,   236,   255,   196,   226,   197,
     198,   256,   282,   283,   284,    74,    74,   262,   201,   177,
     177,   202,    99,   100,   177,   213,   268,   269,   279,   177,
     177,   281,   210,   211,   228,   275,   287,   104,   105,   106,
     107,     3,   276,     4,     5,     6,   178,     7,    24,   286,
     158,   136,   243,   244,   164,    69,   215,   216,    89,   278,
       0,     0,   177,   177,     0,     0,     0,     0,   158,   158,
       0,   177,   177,     0,   177,     0,     0,     0,     0,     0,
     258,     0,     0,     0,     0,     0,     0,     0,   230,   231,
       0,   177,     0,     0,   178,   178,   158,     0,     0,   178,
     214,     0,     0,   241,   178,   178,     0,   245,   246,   247,
       0,     0,     0,     0,   177,   177,   177,     0,     0,   252,
     253,     0,     0,     0,     0,     0,     0,     0,     0,   177,
     177,   177,     0,     0,   146,   259,     0,   178,   178,   265,
       0,     0,     0,     0,     0,     0,   178,   178,     0,   178,
     265,     0,   280,     0,     0,   146,     0,   165,     0,   166,
     234,   167,   168,     0,   169,   170,   178,   171,   172,     0,
       0,   173,   165,     0,   166,     0,   167,   168,     0,   169,
     170,     0,   171,   172,     0,     0,   173,     0,   174,   178,
     178,   178,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   174,   178,   178,   178,   175,   239,   165,
     176,   166,     0,   167,   168,     0,   169,   170,    17,   171,
     172,     0,     0,   173,   165,   176,   166,     0,   167,   168,
       0,   169,   170,    17,   171,   172,     0,     0,   173,     0,
     174,     0,     0,     0,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,   174,     0,     0,    26,   175,
       0,     0,   176,   240,     0,    27,     0,    28,    29,    30,
      17,     0,     0,     0,    31,    32,    33,   176,    76,    82,
      35,     0,     0,     0,     0,    17,    36,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,    42,    17,    25,
       0,     0,     0,    26,     0,     0,     0,     0,   263,     0,
      27,     0,    28,    29,    30,     0,     0,     0,     0,    31,
      32,    33,     0,    76,     0,    35,     0,     0,     0,     0,
     264,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,    17,    25,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,    27,     0,    28,    29,    30,
       0,     0,     0,     0,    31,    32,    33,     0,    76,     0,
      35,    87,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,    42,    17,    25,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
      27,     0,    28,    29,    30,     0,     0,     0,     0,    31,
      32,    33,     0,    76,     0,    35,     0,     0,     0,     0,
       0,    36,     0,     0,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,    17,    25,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,    27,     0,    28,    29,    30,
       0,     0,     0,     0,    31,    32,    33,     0,    76,   131,
      35,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,    42,    17,    25,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
      27,     0,    28,    29,    30,     0,     0,     0,     0,    31,
      32,    33,     0,    76,     0,    35,   135,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,    17,    25,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,    27,     0,    28,    29,    30,
       0,     0,     0,     0,    31,    32,    33,     0,    76,    82,
      35,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,    41,    42,    17,    25,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
      27,     0,    28,    29,    30,     0,     0,     0,     0,    31,
      32,    33,     0,    34,     0,    35,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,    17,    25,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,    27,     0,    28,    29,    30,
       0,     0,     0,     0,    31,    32,    33,   260,    76,     0,
      35,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,    95,    96,    97,    98,     0,    99,
     100,   101,    37,    38,    39,    40,    41,    42,    17,     0,
     261,     0,   102,   103,   104,   105,   106,   107,     0,     0,
       0,   109,   110,   111,    95,    96,    97,    98,     0,    99,
     100,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   103,   104,   105,   106,   107,   125,     0,
       0,   109,   110,   111,     0,     0,     0,     0,     0,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,   237,     0,     0,   109,   110,   111,     0,
       0,     0,     0,     0,    95,    96,    97,    98,     0,    99,
     100,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   103,   104,   105,   106,   107,   224,     0,
       0,   109,   110,   111,     0,     0,     0,     0,    95,    96,
      97,    98,     0,    99,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,   103,   104,   105,
     106,   107,   238,     0,     0,   109,   110,   111,     0,     0,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,   223,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,   133,     0,     0,     0,     0,     0,   129,   102,   103,
     104,   105,   106,   107,   134,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,   128,
       0,     0,     0,     0,     0,     0,     0,   129,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,   108,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,   128,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,   199,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   200,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,   227,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   250,
     104,   105,   106,   107,   251,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,   277,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,   285,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,    98,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   271,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,    96,    97,     0,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,     0,     0,   109,   110,   111,
      95,     0,    97,     0,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   103,
     104,   105,   106,   107,     0,    95,     0,   109,   110,   111,
      99,   100,   101,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   102,   103,   104,   105,   106,   107,    99,
     100,   101,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,   102,   103,   104,   105,   106,   107,     0,     0,
       0,   109,   110,   111
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,   117,    46,    32,    43,    48,    34,
      36,    37,    38,    39,    44,    41,    42,    43,     3,    22,
      23,     0,    25,    74,    27,    61,   166,    44,    54,    55,
      56,    57,    58,    59,    74,   175,   176,    63,    64,    65,
      44,    27,    49,    43,    74,    74,    53,    53,    13,    14,
      15,    76,    17,    18,    44,    20,    21,   170,    23,    24,
      26,    49,    27,    66,    54,    31,    32,    33,    34,    35,
      45,    48,    61,    45,    41,    42,    45,    61,    53,    44,
      66,    53,    53,    48,    19,    19,    50,    54,    55,    56,
      57,    58,    59,    50,    45,   208,   209,    64,    65,   118,
      59,    66,   121,   122,   217,   218,    43,   220,    56,    74,
      76,    43,   115,   116,    56,   118,   119,    83,   121,   122,
      86,   117,    62,    89,   237,    61,    44,    93,    43,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   260,   261,   262,
      56,    57,    58,    59,   157,    19,    48,   123,   199,   125,
     126,    12,   275,   276,   277,   168,   169,    26,   134,   165,
     166,   157,    41,    42,   170,   171,    48,    11,    49,   175,
     176,    48,   168,   169,   203,    50,    49,    56,    57,    58,
      59,     4,    50,     6,     7,     8,   117,    10,     9,   281,
     203,    91,   221,   222,   116,    21,   172,   173,    35,   266,
      -1,    -1,   208,   209,    -1,    -1,    -1,    -1,   221,   222,
      -1,   217,   218,    -1,   220,    -1,    -1,    -1,    -1,    -1,
     249,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   204,   205,
      -1,   237,    -1,    -1,   165,   166,   249,    -1,    -1,   170,
     171,    -1,    -1,   219,   175,   176,    -1,   223,   224,   225,
      -1,    -1,    -1,    -1,   260,   261,   262,    -1,    -1,   235,
     236,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
     276,   277,    -1,    -1,   250,   251,    -1,   208,   209,   255,
      -1,    -1,    -1,    -1,    -1,    -1,   217,   218,    -1,   220,
     266,    -1,   268,    -1,    -1,   271,    -1,    13,    -1,    15,
      16,    17,    18,    -1,    20,    21,   237,    23,    24,    -1,
      -1,    27,    13,    -1,    15,    -1,    17,    18,    -1,    20,
      21,    -1,    23,    24,    -1,    -1,    27,    -1,    44,   260,
     261,   262,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,   275,   276,   277,    48,    49,    13,
      66,    15,    -1,    17,    18,    -1,    20,    21,    74,    23,
      24,    -1,    -1,    27,    13,    66,    15,    -1,    17,    18,
      -1,    20,    21,    74,    23,    24,    -1,    -1,    27,    -1,
      44,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    44,    -1,    -1,    24,    48,
      -1,    -1,    66,    67,    -1,    31,    -1,    33,    34,    35,
      74,    -1,    -1,    -1,    40,    41,    42,    66,    44,    45,
      46,    -1,    -1,    -1,    -1,    74,    52,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    19,    44,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    68,    69,    70,    71,    72,    73,    74,    -1,
      22,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    63,    64,    65,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    25,    -1,
      -1,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    25,    -1,    -1,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    26,    -1,
      -1,    63,    64,    65,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    28,    -1,    -1,    63,    64,    65,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    30,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    61,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    37,    38,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      36,    -1,    38,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    36,    -1,    63,    64,    65,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    41,
      42,    43,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    63,    64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    79,     4,     6,     7,     8,    10,    80,    81,
      82,    88,    92,    93,   126,     0,    48,    74,    94,    94,
      94,    94,    44,    87,    80,    20,    24,    31,    33,    34,
      35,    40,    41,    42,    44,    46,    52,    68,    69,    70,
      71,    72,    73,    89,    90,    91,    94,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     120,   121,   122,   123,   124,   125,    44,    99,    43,    99,
      94,    95,    96,    94,    94,    97,    44,   115,    97,   115,
     115,   115,    45,    56,   115,   116,   119,    47,   115,   119,
      74,    53,    49,    44,   120,    36,    37,    38,    39,    41,
      42,    43,    54,    55,    56,    57,    58,    59,    61,    63,
      64,    65,    61,    97,    98,    61,    48,    43,    61,    53,
      45,    50,    50,    19,   115,    25,    19,   115,    45,    53,
      45,    45,   115,    47,    60,    47,    89,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,    45,    53,    94,   100,
     101,   102,   103,   104,    95,    13,    15,    17,    18,    20,
      21,    23,    24,    27,    44,    48,    66,   121,   122,   127,
     129,   130,   131,   134,   135,   136,   137,   138,   139,   140,
     100,    94,    85,    86,   100,   100,   115,   115,   115,    45,
      53,   115,    97,    44,    54,    43,    49,   127,   128,   128,
      97,    97,   127,   121,   122,   115,   115,   128,   128,    62,
      43,    56,    61,    30,    26,    32,   120,    47,   100,   105,
     115,   115,    14,   127,    16,    43,    19,    25,    28,    49,
      67,   115,   127,   100,   100,   115,   115,   115,    45,    53,
      55,    60,   115,   115,   127,    48,    12,    84,   100,   115,
      19,    22,    26,    29,    51,   115,   132,   133,    48,    11,
      83,    55,   127,   127,   127,    50,    50,    50,   133,    49,
     115,    48,   127,   127,   127,    49,    91,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    78,    79,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    91,    91,
      92,    93,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   103,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   108,   108,   109,   110,   110,   111,   112,   113,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   117,   118,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   123,   124,   125,   126,   126,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   128,   128,   129,
     130,   130,   131,   132,   132,   132,   133,   133,   134,   135,
     136,   137,   137,   138,   138,   139,   140,   140,   140,   140
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     2,     1,     9,
       1,     4,     0,     4,     0,     3,     1,     1,     0,     3,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     1,     0,     3,     1,     3,
       1,     3,     0,     1,     1,     1,     1,     1,     4,     4,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     5,     2,     3,     3,     3,     2,     3,     2,     1,
       2,     5,     6,     6,     6,     5,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       4,     6,     6,     3,     3,     3,     2,     1,     6,     6,
       2,     3,     3,     3,     3,     3,     2,     1,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"",
  "\"xor\"", "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"",
  "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"..\"",
  "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"floating\"", "\"string\"", "\"identifier\"", "UPLUS", "UMINUS",
  "DIRECT_CALL_EXPR_NO_ARG", "$accept", "Specification", "Definition",
  "Definitions", "FunctionDefinition", "MaybeInitially", "MaybeDefined",
  "FunctionParameters", "MaybeFunctionParameters",
  "MaybeFunctionAttributes", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers", "MaybeIdentifiers",
  "Variable", "Parameters", "MaybeParameters", "Type", "BasicType",
  "ComposedType", "FixedSizedType", "RangedType", "Types", "Atom",
  "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "RuleReference", "Term",
  "Expression", "Range", "List", "Terms", "Arguments",
  "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   374,   374,   383,   387,   391,   395,   403,   409,   419,
     440,   448,   452,   460,   464,   472,   478,   488,   492,   500,
     504,   512,   529,   546,   555,   566,   578,   584,   594,   598,
     606,   614,   622,   630,   636,   646,   650,   658,   662,   670,
     676,   686,   690,   698,   702,   706,   710,   718,   726,   734,
     742,   750,   756,   766,   770,   774,   778,   782,   786,   790,
     794,   802,   810,   815,   824,   833,   838,   847,   856,   865,
     874,   883,   887,   891,   895,   899,   903,   907,   911,   915,
     923,   927,   931,   935,   940,   944,   948,   952,   956,   960,
     964,   968,   972,   976,   980,   984,   988,   992,   996,  1000,
    1004,  1013,  1021,  1026,  1032,  1039,  1045,  1054,  1058,  1067,
    1072,  1080,  1088,  1096,  1104,  1112,  1117,  1126,  1130,  1134,
    1138,  1142,  1146,  1150,  1154,  1158,  1162,  1170,  1176,  1186,
    1194,  1198,  1206,  1214,  1219,  1224,  1232,  1237,  1245,  1253,
    1261,  1269,  1273,  1281,  1285,  1293,  1301,  1307,  1314,  1320
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


#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 3407 "GrammarParser.cpp" // lalr1.cc:1167
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const location_type& l, const std::string& m )
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );

        /*driver.error
        ( location( position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        ); TODO */
    }
    else
    {
        //driver.error( l, m, libcasm_fe::Codes::SyntaxError ); TODO
    }

    std::cerr << l << ": " << m << std::endl;
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
