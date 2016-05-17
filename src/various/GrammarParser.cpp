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
#line 62 "../../src/GrammarParser.yy" // lalr1.cc:413

    #include "src/Driver.h"

    std::pair<bool, bool> parse_function_attributes(Driver& driver, const yy::location& loc,
                                                    const std::vector<std::string>& attribute_names) {
        bool is_static = false;
        bool is_symbolic = false;
        bool is_controlled = false;

        for (const auto& attribute_name : attribute_names) {
            if (attribute_name == "static") {
                if (is_static) {
                    driver.error(loc, "`static` attribute can only be used once per function");
                    break;
                } else {
                    is_static = true;
                }
            } else if (attribute_name == "symbolic") {
                if (is_symbolic) {
                    driver.error(loc, "`symbolic` attribute can only be used once per function");
                    break;
                } else {
                    is_symbolic = true;
                }
            } else if (attribute_name == "controlled") {
                if (is_controlled) {
                    driver.error(loc, "`controlled` attribute can only be used once per function");
                    break;
                } else {
                    is_controlled = true;
                }
            } else {
              driver.error(loc, "`"+attribute_name+"` is no valid function attribute, only static, symbolic and controlled are allowed");
            }
        }
        if (is_static && is_controlled) {
            driver.error(loc, "attributes `controlled` and `static` are mutually exclusive");
        }

        return std::pair<bool, bool>(is_static, is_symbolic);
    }

#line 96 "GrammarParser.cpp" // lalr1.cc:413


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


namespace yy {
#line 182 "GrammarParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  casmi_parser::yytnamerr_ (const char *yystr)
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
  casmi_parser::casmi_parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  casmi_parser::~casmi_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  casmi_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  casmi_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  casmi_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  casmi_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  casmi_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  casmi_parser::symbol_number_type
  casmi_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  casmi_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  casmi_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.move< AtomNode* > (that.value);
        break;

      case 121: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 141: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 95: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 79: // FLOATCONST
        value.move< FLOAT_T > (that.value);
        break;

      case 153: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 80: // INTEGERCONST
        value.move< INTEGER_T > (that.value);
        break;

      case 147: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 112: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 148: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 152: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 130: // DEBUG_SYNTAX
      case 132: // PRINT_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 151: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 81: // RATIONALCONST
        value.move< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 109: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 124: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 131: // DEBUG_ATOM_LIST
        value.move< std::vector<ExpressionBase*> > (that.value);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  casmi_parser::stack_symbol_type&
  casmi_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.copy< AtomNode* > (that.value);
        break;

      case 121: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 141: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 95: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 79: // FLOATCONST
        value.copy< FLOAT_T > (that.value);
        break;

      case 153: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 80: // INTEGERCONST
        value.copy< INTEGER_T > (that.value);
        break;

      case 147: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 112: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 148: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 152: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 130: // DEBUG_SYNTAX
      case 132: // PRINT_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 151: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 81: // RATIONALCONST
        value.copy< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 109: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 124: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 131: // DEBUG_ATOM_LIST
        value.copy< std::vector<ExpressionBase*> > (that.value);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        value.copy< std::vector<std::string> > (that.value);
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
  casmi_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  casmi_parser::yy_print_ (std::ostream& yyo,
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
  casmi_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  casmi_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  casmi_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  casmi_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  casmi_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  casmi_parser::debug_level_type
  casmi_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  casmi_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline casmi_parser::state_type
  casmi_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  casmi_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  casmi_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  casmi_parser::parse ()
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
    #line 52 "../../src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 802 "GrammarParser.cpp" // lalr1.cc:741

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
            symbol_type yylookahead (yylex (driver));
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
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        yylhs.value.build< AtomNode* > ();
        break;

      case 121: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 141: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 134: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 128: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 95: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 79: // FLOATCONST
        yylhs.value.build< FLOAT_T > ();
        break;

      case 153: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 80: // INTEGERCONST
        yylhs.value.build< INTEGER_T > ();
        break;

      case 147: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 112: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 148: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 152: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 130: // DEBUG_SYNTAX
      case 132: // PRINT_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 151: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 133: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 81: // RATIONALCONST
        yylhs.value.build< rational_t > ();
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 109: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 124: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 100: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 131: // DEBUG_ATOM_LIST
        yylhs.value.build< std::vector<ExpressionBase*> > ();
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 135: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 123: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        yylhs.value.build< std::vector<std::string> > ();
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
#line 199 "../../src/GrammarParser.yy" // lalr1.cc:859
    { driver.result = yystack_[0].value.as< AstListNode* > (); }
#line 1084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 204 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
            driver.spec_name = yystack_[0].value.as< std::string > ();
        }
#line 1092 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 209 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > (); }
#line 1098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 210 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
                yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
             }
#line 1107 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 216 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::PROVIDER); }
#line 1113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 217 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION); }
#line 1119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 218 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ()); }
#line 1125 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 219 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
                if (yystack_[0].value.as< Function* > ()->is_builtin()) {
                    driver.error(yylhs.location, "cannot use `"+yystack_[0].value.as< Function* > ()->name+"` as function identifier because it is a builtin name");
                }
                if (!driver.function_table.add(yystack_[0].value.as< Function* > ())) {
                    driver.error(yylhs.location, "redefinition of symbol");
                    // if another symbol with same name exists we need to delete
                    // the symbol here, because it is not inserted in the symbol table
                    delete yystack_[0].value.as< Function* > ();
                }
            }
#line 1142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 231 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yystack_[0].value.as< Function* > ()->binding_offsets = std::move(driver.binding_offsets);
                driver.binding_offsets.clear();
                yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
                if (!driver.function_table.add(yystack_[0].value.as< Function* > ())) {
                    driver.error(yylhs.location, "redefinition of symbol");
                    // if another symbol with same name exists we need to delete
                    // the symbol here, because it is not inserted in the symbol table
                    delete yystack_[0].value.as< Function* > ();
                }
            }
#line 1158 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 242 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > (); }
#line 1164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 243 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
              // TODO check, we trust bison to pass only RuleNodes up
              if (!driver.add(reinterpret_cast<RuleNode*>(yystack_[0].value.as< AstNode* > ()))) {
                    driver.error(yylhs.location, "redefinition of rule");
                    // we do not need to delete $1 here, because it's already in
                    // the AST, so it will be deleted later
              }
           }
#line 1178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 254 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              yylhs.value.as< AstNode* > () = new AstNode(NodeType::INIT);
              driver.init_name = yystack_[0].value.as< std::string > ();
           }
#line 1187 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 265 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > ());
                if (!driver.function_table.add(yylhs.value.as< Enum* > ())) {
                    driver.error(yylhs.location, "redefinition of symbol `"+yystack_[4].value.as< std::string > ()+"`");
                }
                for (const std::string& name : yystack_[1].value.as< std::vector<std::string> > ()) {
                    if (yylhs.value.as< Enum* > ()->add_enum_element(name)) {
                        if (!driver.function_table.add_enum_element(name, yylhs.value.as< Enum* > ())) {
                            driver.error(yylhs.location, "redefinition of symbol `"+name+"`");
                        }
                    } else {
                        driver.error(yylhs.location, "name `"+name+"` already used in enum");
                    }
                }
           }
#line 1207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 282 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  // TODO: 2nd argument should be a reference
                  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 286 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 289 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 293 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 296 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 299 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 304 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
                      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
                   }
#line 1265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 308 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
                      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
                   }
#line 1274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 312 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
                   }
#line 1282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 316 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr); }
#line 1288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 319 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 1294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 320 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ()); }
#line 1300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 323 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[2].value.as< std::vector<std::string> > ());
                            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
                        }
#line 1309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 327 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
                            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
                        }
#line 1318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 333 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    /* this constructor is implementation dependant! */
                    std::vector<Type*> foo;
                    yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
                  }
#line 1328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 339 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ()); }
#line 1334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 342 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
        yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
     }
#line 1344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 347 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
        // TODO: fail for rules without types and print warnings
        yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
     }
#line 1355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 356 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ()); }
#line 1361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 357 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ()); }
#line 1367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 359 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                        yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
                        yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
                   }
#line 1376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 363 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ()); }
#line 1382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 367 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
                            yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
                        }
#line 1391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 371 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          // TODO: limit memory size
                            yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
                        }
#line 1400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 375 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
                        }
#line 1408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 380 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(yystack_[0].value.as< std::string > ()); /* TODO check invalid types */}
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 381 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
               yylhs.value.as< Type* > () = new Type(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<Type*> > ());
           }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 384 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
               yylhs.value.as< Type* > () = new Type(yystack_[5].value.as< std::string > ());
               yylhs.value.as< Type* > ()->subrange_start = yystack_[3].value.as< IntegerAtom* > ()->val_;
               yylhs.value.as< Type* > ()->subrange_end = yystack_[1].value.as< IntegerAtom* > ()->val_;
               if (yylhs.value.as< Type* > ()->subrange_start >= yylhs.value.as< Type* > ()->subrange_end) {
                   driver.error(yylhs.location, "start of subrange must be smaller than the end");
               }
           }
#line 1435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 394 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
               yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > () );
               yylhs.value.as< Type* > ()->bitsize = yystack_[1].value.as< IntegerAtom* > ()->val_;
               if( yylhs.value.as< Type* > ()->bitsize < 0 || yylhs.value.as< Type* > ()->bitsize > 256 )
               {
                   driver.error(yylhs.location, "invalid size for Bit type");
               }
           }
#line 1448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 404 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yystack_[0].value.as< std::vector<Type*> > ().push_back(yystack_[2].value.as< Type* > ());
                      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
                    }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 408 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ()); }
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 409 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ()); }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 412 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); }
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 413 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr; }
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 416 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back(yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > ()); }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 417 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); }
#line 1493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 418 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
                    yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back(yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > ());
                }
#line 1502 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 425 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ()); }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 426 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ()); }
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 429 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > (); }
#line 1520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 430 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 431 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > (); }
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 434 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RuleAtom(yylhs.location, std::move(yystack_[0].value.as< std::string > ())); }
#line 1538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 435 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 436 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new StringAtom(yylhs.location, std::move(yystack_[0].value.as< std::string > ())); }
#line 1550 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 437 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new ListAtom(yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > ()); }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 438 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 439 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new IntegerAtom(yylhs.location, 0); }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 440 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new SelfAtom(yylhs.location); }
#line 1574 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 441 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new UndefAtom(yylhs.location); }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 442 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new BooleanAtom(yylhs.location, true); }
#line 1586 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 443 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new BooleanAtom(yylhs.location, false); }
#line 1592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 446 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, yystack_[0].value.as< INTEGER_T > ()); }
#line 1598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 447 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > ()); }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 448 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, yystack_[0].value.as< INTEGER_T > ()); }
#line 1610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 449 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > (); }
#line 1616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 450 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatAtom(yylhs.location, yystack_[0].value.as< FLOAT_T > ()); }
#line 1622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 451 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatAtom(yylhs.location, (-1) * yystack_[0].value.as< FLOAT_T > ()); }
#line 1628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 452 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatAtom(yylhs.location, yystack_[0].value.as< FLOAT_T > ()); }
#line 1634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 453 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ()); }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 454 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
          yystack_[0].value.as< rational_t > ().numerator *= -1;
          yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ());
        }
#line 1649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 458 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ()); }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 461 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 464 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              if (yystack_[3].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM && yystack_[1].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM) {
                yylhs.value.as< AtomNode* > () = new NumberRangeAtom(yylhs.location, reinterpret_cast<IntegerAtom*>(yystack_[3].value.as< AtomNode* > ()), reinterpret_cast<IntegerAtom*>(yystack_[1].value.as< AtomNode* > ()));
              } else {
                driver.error(yylhs.location, "numbers in range expression must be Integer");
                yylhs.value.as< AtomNode* > () = nullptr;
              }
            }
#line 1674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 475 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > (); }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 476 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector<ExpressionBase*>(); }
#line 1686 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 480 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > (); }
#line 1692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 481 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > (); }
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 483 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
                          yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back(yystack_[0].value.as< ExpressionBase* > ());
                        }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 487 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector<ExpressionBase*>;
                          yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back(yystack_[0].value.as< ExpressionBase* > ());
                        }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 495 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD); }
#line 1722 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 497 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB); }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 499 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL); }
#line 1734 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 501 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV); }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 503 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD); }
#line 1746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 505 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV); }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 507 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ); }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 509 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ); }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 511 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER); }
#line 1770 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 513 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER); }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 515 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ); }
#line 1782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 517 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ); }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 519 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR); }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 521 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR); }
#line 1800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 523 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND); }
#line 1806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 525 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT);}
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 526 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > (); }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 529 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > (); }
#line 1824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 532 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[0].value.as< std::string > ()); }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 533 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[2].value.as< std::string > ()); }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 535 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                   if( Builtin::isBuiltin( yystack_[3].value.as< std::string > () ) )
                   {
                       yylhs.value.as< BaseFunctionAtom* > () = new BuiltinAtom(yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ());
                   }
                   else
                   {
                       yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ());
                   }
               }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 547 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > ()); }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 548 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > ());
           }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 551 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > ());
           }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 555 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 1882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 559 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 1891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 563 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 569 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move(yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ()); yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back(yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > ()); }
#line 1906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 570 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector<std::pair<std::string,std::vector<std::string>>>();
                yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back(std::move(yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > ()));
             }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 576 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair<std::string, std::vector<std::string>>(yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > ());
        }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 581 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 1929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 582 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 1935 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 583 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > (); }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 584 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > (); }
#line 1947 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 585 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > (); }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 586 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > (); }
#line 1959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 587 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > (); }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 588 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > (); }
#line 1971 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 589 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > (); }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 590 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > () ; }
#line 1983 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 591 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 592 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 1995 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 593 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 594 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > (); }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 595 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > (); }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 596 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > (); }
#line 2019 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 597 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > (); }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 598 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > (); }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 599 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 600 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::SKIP); }
#line 2043 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 601 "../../src/GrammarParser.yy" // lalr1.cc:859
    { driver.error(yylhs.location, "this call syntax is obsolete, use `call "+yystack_[0].value.as< std::string > ()+"`"); }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 602 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::STATEMENT); }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 603 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::STATEMENT);}
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 606 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2067 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 608 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 611 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< DiedieNode* > () = new DiedieNode(yylhs.location, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 612 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< DiedieNode* > () = new DiedieNode(yylhs.location, nullptr); }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 622 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(yylhs.location, NodeType::IMPOSSIBLE); }
#line 2091 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 625 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< PrintNode* > () = new PrintNode(yylhs.location, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<ExpressionBase*> > ()); }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 628 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*> > () = std::move(yystack_[2].value.as< std::vector<ExpressionBase*> > ()); yylhs.value.as< std::vector<ExpressionBase*> > ().push_back(yystack_[0].value.as< ExpressionBase* > ()); }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 629 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*> > ().push_back(yystack_[0].value.as< ExpressionBase* > ()); }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 631 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< PrintNode* > () = new PrintNode(yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*> > ()); }
#line 2115 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 634 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  if (yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::FUNCTION_ATOM) {
                    yylhs.value.as< UpdateNode* > () = new UpdateNode(yylhs.location, reinterpret_cast<FunctionAtom*>(yystack_[2].value.as< BaseFunctionAtom* > ()), yystack_[0].value.as< ExpressionBase* > ());
                  } else {
                    driver.error(yylhs.location, "can only use functions for updates but `"+
                                     std::string("TODO NAME HERE")+"` is a `"+type_to_str(yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_));
                  }
                }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 644 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< CaseNode* > () = new CaseNode(yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ());
           }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 649 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move(yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ());
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back(yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ());
               }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 653 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move(std::vector<std::pair<AtomNode*, AstNode*>>());
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back(yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ());
               }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 659 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () =yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 660 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2166 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 661 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 662 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 665 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(nullptr, yystack_[0].value.as< AstNode* > ());
                  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 670 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > ());
                 }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 675 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > ());
                }
#line 2202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 680 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(new StringAtom(yylhs.location, std::move(yystack_[2].value.as< std::string > ())), yystack_[0].value.as< AstNode* > ());
                 }
#line 2210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 685 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ()); }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 686 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, "", yystack_[1].value.as< ExpressionBase* > ()); }
#line 2222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 687 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > ()); }
#line 2228 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 688 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, yystack_[0].value.as< std::string > (), nullptr); }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 692 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > ());
                  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 697 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > ());
               }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 702 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > ());
                  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 706 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > ());
               }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 711 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > (); }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 712 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::STATEMENTS); yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); }
#line 2278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 715 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr);
          }
#line 2286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 718 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode(yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 724 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                auto var = Symbol(yystack_[1].value.as< std::string > (), Symbol::SymbolType::LET);
                if (!driver.function_table.add(&var)) {
                    driver.error(yylhs.location, "redefinition of symbol `"+yystack_[1].value.as< std::string > ()+"`");
                }
            }
#line 2305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 730 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              driver.function_table.remove(yystack_[5].value.as< std::string > ());
              yylhs.value.as< LetNode* > () = new LetNode(yylhs.location, Type(TypeType::UNKNOWN), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 735 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                auto var = Symbol(yystack_[3].value.as< std::string > (), Symbol::SymbolType::LET);
                if (!driver.function_table.add(&var)) {
                    driver.error(yylhs.location, "redefinition of symbol `"+yystack_[3].value.as< std::string > ()+"`");
                }
            }
#line 2325 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 741 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              driver.function_table.remove(yystack_[7].value.as< std::string > ());
              yylhs.value.as< LetNode* > () = new LetNode(yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 747 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                if (yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop to builtin `"+yystack_[0].value.as< BaseFunctionAtom* > ()->name+"`");
                } else {
                    yylhs.value.as< PushNode* > () = new PushNode(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), reinterpret_cast<FunctionAtom*>(yystack_[0].value.as< BaseFunctionAtom* > ()));
                }
          }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 757 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                if (yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop to builtin `"+yystack_[2].value.as< BaseFunctionAtom* > ()->name+"`");
                } else if (yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop to builtin `"+yystack_[0].value.as< BaseFunctionAtom* > ()->name+"`");
                } else {
                    yylhs.value.as< PopNode* > () = new PopNode(yylhs.location, reinterpret_cast<FunctionAtom*>(yystack_[2].value.as< BaseFunctionAtom* > ()), reinterpret_cast<FunctionAtom*>(yystack_[0].value.as< BaseFunctionAtom* > ()));
                }
          }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 768 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< ForallNode* > () = new ForallNode(yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
             }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 773 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > ()); }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2378 "GrammarParser.cpp" // lalr1.cc:859
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
  casmi_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  casmi_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int casmi_parser::yypact_ninf_ = -201;

  const signed char casmi_parser::yytable_ninf_ = -106;

  const short int
  casmi_parser::yypact_[] =
  {
     -37,   -69,    54,   170,  -201,  -201,   -54,    -5,    31,    47,
      56,    57,    63,   170,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,    64,    -6,    26,    11,   -18,  -201,  -201,    67,
    -201,  -201,    86,    79,   -51,   117,   321,   -52,    71,    90,
      91,   577,     3,    76,    80,    88,    71,   110,   121,   101,
     111,  -201,   321,  -201,  -201,  -201,  -201,  -201,    13,    55,
     321,   193,    97,  -201,  -201,  -201,  -201,   118,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,   804,  -201,  -201,    50,   131,
    -201,   116,   132,   141,    64,    64,   -15,  -201,   321,   321,
     321,  -201,  -201,   577,   577,   134,   321,   912,   135,   321,
     138,   139,   577,   -46,   321,   321,   150,   577,   577,   -13,
     172,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,   -16,   164,   148,    -6,  -201,  -201,     8,    71,    71,
     883,   804,  -201,  -201,  -201,  -201,  -201,  -201,   493,  -201,
     180,   167,   162,   804,  -201,   277,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,    71,    71,    61,   153,   321,   177,   176,   577,
      91,   804,   804,   804,  -201,    12,   398,    62,   556,  -201,
     186,   912,   617,   221,   232,  -201,   321,   187,   647,  -201,
     169,   451,   514,   321,    91,   577,   -14,  -201,   117,   173,
     178,   183,   197,   -38,  -201,  -201,  -201,   -34,  -201,   209,
    -201,    48,  -201,   321,  -201,   199,   832,   832,    -1,  -201,
     863,   863,   863,    -1,    -1,   863,   863,   863,  -201,  -201,
    -201,   804,   203,  -201,   321,    71,  -201,   804,  -201,   213,
    -201,  -201,  -201,  -201,  -201,  -201,    71,   577,   912,   186,
     138,   138,   321,   679,   321,    87,   204,  -201,  -201,   804,
      33,  -201,    91,   577,  -201,    71,  -201,    20,  -201,  -201,
     912,   912,   210,   804,  -201,   321,   804,   207,   195,   321,
     216,   264,  -201,  -201,  -201,   708,   226,   231,   220,   230,
     234,   235,    22,  -201,  -201,  -201,  -201,  -201,  -201,   577,
      49,  -201,  -201,   237,  -201,  -201,  -201,   804,   321,  -201,
     743,  -201,   577,   577,   321,  -201,   577,   577,   577,   577,
    -201,  -201,  -201,   577,  -201,   804,   577,   321,  -201,  -201,
     238,  -201,  -201,  -201,  -201,  -201,  -201,   771,  -201,   577,
    -201
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     0,     2,     5,    11,     6,     7,     8,    10,
       9,    12,     0,     0,     0,     0,     0,    14,    13,     0,
       4,    30,     0,    28,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,    42,     0,    41,
       0,    25,     0,    65,    66,    67,    68,    64,     0,     0,
       0,     0,     0,    75,    71,    78,    61,   105,   103,    57,
      72,    60,    59,    63,    62,    18,    58,    56,     0,    34,
      38,     0,    35,     0,     0,     0,     0,   115,     0,     0,
     143,   144,   136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
       0,   108,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,     0,     0,     0,     0,    29,    31,     0,     0,    40,
       0,   102,    73,    69,    76,    74,    70,    77,     0,    82,
      60,     0,    83,    86,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,   140,   141,   142,   170,     0,     0,     0,     0,   147,
     148,     0,     0,     0,     0,   180,     0,   164,     0,   138,
       0,     0,     0,     0,     0,     0,     0,    15,    24,     0,
       0,    48,     0,     0,    32,    39,    50,     0,    53,    54,
     104,     0,    81,    84,   106,     0,   101,    99,   100,    92,
      93,    97,    98,    87,    88,    94,    95,    96,    89,    90,
      91,    19,     0,    33,     0,     0,    37,    21,    16,     0,
     111,   114,   165,   169,   167,   173,     0,     0,     0,   145,
       0,     0,     0,     0,     0,     0,     0,   166,   168,   149,
       0,   109,     0,     0,    23,    47,    43,     0,    45,    49,
      52,     0,     0,    85,   107,     0,    17,     0,     0,     0,
       0,   171,   146,   177,   178,     0,   162,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   139,     0,
       0,   110,    46,     0,    51,    55,    80,    22,     0,   116,
       0,   175,     0,     0,     0,   163,     0,     0,     0,     0,
     150,   151,   112,     0,    44,    20,     0,     0,   172,   179,
       0,   157,   160,   158,   159,   113,   174,     0,   161,     0,
     176
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -201,  -201,  -201,  -201,   296,  -201,  -201,  -201,  -201,  -201,
    -201,    34,  -201,   179,   136,   268,  -201,   175,   -30,    40,
     109,  -201,    38,   -80,  -201,  -136,   -59,  -201,  -201,  -201,
     -99,  -201,    27,  -201,   -41,  -201,  -200,   145,   -29,  -201,
    -201,  -201,  -201,  -201,   128,  -201,  -201,  -201,  -201,    28,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,    -9,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    13,    14,    15,    16,    17,    18,    19,
      20,    32,    33,    35,    80,    81,    82,    48,    49,   212,
      51,   217,   218,    68,    69,    70,    71,    72,    73,    74,
     151,   152,   153,    76,    77,    21,    86,    87,   184,   112,
     113,   114,   115,   116,   190,   117,   118,   119,   302,   303,
     304,   305,   306,   307,   120,   121,   122,   123,   124,   185,
     125,   126,   289,   337,   127,   128,   129,   130
  };

  const short int
  casmi_parser::yytable_[] =
  {
     110,   213,   150,    46,   270,    40,   199,   204,    83,   272,
      22,     1,   111,    78,     4,   277,   136,   189,   196,    88,
      89,    90,    91,    92,    93,   252,    94,   278,    95,    23,
      96,    79,    47,    97,    98,   279,    99,   197,   100,   280,
     101,   102,  -105,   103,   104,    41,    42,   205,   179,   273,
     159,   155,   110,   110,     5,   298,   225,   330,   180,   193,
     219,   110,   105,    75,   106,    34,   110,   110,   131,   209,
     210,   107,   310,   195,    39,   168,   169,   170,    24,   141,
     108,   209,   210,    58,    59,   186,    79,   148,    64,    36,
      37,    47,   142,   143,   144,   109,   309,    38,   201,   202,
      64,    63,    64,    65,   299,    67,   180,   211,   214,    58,
      59,   189,   333,   171,    25,   181,   182,   183,   177,   178,
     298,   172,   180,   188,   244,   255,   192,    63,    64,    65,
      26,   198,   245,   256,   145,   146,   147,    43,   110,    27,
      28,   313,   242,   243,   110,   110,    29,    31,    58,    59,
     250,    44,    45,    50,    47,    85,   253,   253,    84,   133,
     110,   110,   282,   134,   110,   297,    63,    64,    65,   299,
      67,   135,   253,   253,   137,   138,   271,   139,   292,   140,
     154,   174,   155,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,    52,
     219,   315,   173,   247,   176,   175,   300,     6,     7,     8,
       9,    10,    11,    12,   200,   287,   110,   187,   191,   293,
     294,    67,   194,   263,   301,   340,   290,   203,   291,   206,
     269,   207,   110,   221,   222,   223,    79,    53,    54,    55,
      56,   249,    57,   300,   311,   211,   248,   258,   261,   262,
     283,   264,   266,   143,    58,    59,   275,    60,   146,    61,
     149,   301,   276,   281,   284,    62,   285,   288,   110,   308,
     318,   286,    63,    64,    65,    66,    67,   316,   319,   321,
     332,   110,   110,    52,   322,   110,   110,   110,   110,   295,
     324,   326,   110,   338,   339,   110,   325,   341,   342,   343,
     344,   327,   334,   348,   345,   328,   329,   346,   110,    30,
     132,   246,   317,   208,   215,   312,   320,   274,   314,   259,
     350,    53,    54,    55,    56,   251,    57,    52,     0,     0,
     331,     0,     0,     0,     0,     0,     0,     0,    58,    59,
       0,    60,   224,    61,     0,   335,     0,     0,     0,    62,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,     0,     0,     0,   347,    53,    54,    55,    56,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,     0,    60,     0,    61,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    88,    89,    90,    91,    92,
      93,     0,    94,   254,    95,     0,    96,     0,     0,    97,
      98,     0,    99,     0,   100,     0,   101,   102,     0,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
     106,     0,     0,     0,     0,     0,     0,   107,    88,    89,
      90,    91,    92,    93,     0,    94,   108,    95,     0,    96,
       0,     0,    97,    98,     0,    99,     0,   100,     0,   101,
     102,   109,   103,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   156,   157,   158,     0,
       0,   105,     0,   106,     0,     0,     0,     0,     0,     0,
     107,   267,     0,     0,     0,     0,     0,     0,     0,   108,
       0,    88,    89,    90,    91,    92,    93,     0,    94,     0,
      95,     0,    96,     0,   109,    97,    98,     0,    99,     0,
     100,     0,   101,   102,   159,   103,   104,     0,     0,   160,
     161,   162,     0,     0,   163,   164,   165,     0,   220,   156,
     157,   158,     0,     0,   105,     0,   106,   166,   167,   168,
     169,   170,     0,   107,     0,   257,     0,     0,     0,     0,
       0,     0,   108,   268,    88,    89,    90,    91,    92,    93,
       0,    94,     0,    95,     0,    96,     0,   109,    97,    98,
       0,    99,     0,   100,     0,   101,   102,   159,   103,   104,
       0,     0,   160,   161,   162,     0,     0,   163,   164,   165,
     156,   157,   158,     0,     0,     0,     0,   105,     0,   106,
     166,   167,   168,   169,   170,     0,   107,     0,     0,     0,
       0,     0,   260,     0,     0,   108,     0,     0,     0,     0,
     156,   157,   158,     0,     0,     0,     0,     0,     0,     0,
     109,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,   160,   161,   162,     0,     0,   163,   164,
     165,   265,   156,   157,   158,     0,     0,     0,     0,     0,
       0,   166,   167,   168,   169,   170,     0,     0,   159,     0,
       0,     0,     0,   160,   161,   162,     0,     0,   163,   164,
     165,   156,   157,   158,     0,     0,     0,     0,     0,     0,
       0,   166,   167,   168,   169,   170,     0,     0,     0,     0,
     159,     0,     0,     0,     0,   160,   161,   162,   323,     0,
     163,   164,   165,     0,   296,     0,   156,   157,   158,     0,
       0,     0,     0,   166,   167,   168,   169,   170,     0,   159,
     336,     0,     0,     0,   160,   161,   162,     0,     0,   163,
     164,   165,     0,     0,   156,   157,   158,     0,     0,     0,
       0,     0,   166,   167,   168,   169,   170,     0,   349,     0,
       0,     0,     0,     0,   159,     0,     0,     0,     0,   160,
     161,   162,     0,     0,   163,   164,   165,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,   166,   167,   168,
     169,   170,   159,     0,     0,     0,     0,   160,   161,   162,
       0,     0,   163,   164,   165,  -106,  -106,   158,     0,     0,
       0,     0,     0,     0,     0,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,   159,     0,     0,     0,     0,
     160,   161,   162,     0,     0,   163,   164,   165,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,   169,   170,   159,     0,     0,     0,     0,   160,   161,
     162,     0,     0,   163,   164,   165,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   166,   167,   168,   169,
     170,     0,     0,     0,   159,     0,     0,     0,     0,  -106,
    -106,  -106,     0,     0,   163,   164,  -106,    53,    54,    55,
      56,     0,    57,     0,     0,     0,     0,  -106,  -106,   168,
     169,   170,     0,     0,    58,    59,     0,    60,     0,    61,
       0,     0,   216,     0,     0,    62,    53,    54,    55,    56,
       0,    57,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,    58,    59,     0,    60,     0,    61,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
       0,    63,    64,    65,    66,    67
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      41,   137,    61,    54,   204,    23,   105,    23,    38,    23,
      64,    48,    41,    65,    83,    53,    46,    97,    64,     7,
       8,     9,    10,    11,    12,    13,    14,    65,    16,    83,
      18,    83,    83,    21,    22,    69,    24,    83,    26,    73,
      28,    29,    55,    31,    32,    63,    64,    63,    63,    63,
      51,    64,    93,    94,     0,    33,   155,    35,    73,   100,
     140,   102,    50,    36,    52,    71,   107,   108,    65,    61,
      62,    59,   272,   102,    63,    76,    77,    78,    83,    52,
      68,    61,    62,    61,    62,    94,    83,    60,    80,    63,
      64,    83,    79,    80,    81,    83,    63,    71,   107,   108,
      80,    79,    80,    81,    82,    83,    73,   137,   138,    61,
      62,   191,    63,    63,    83,    88,    89,    90,    84,    85,
      33,    71,    73,    96,    63,    63,    99,    79,    80,    81,
      83,   104,    71,    71,    79,    80,    81,    70,   179,    83,
      83,   277,   172,   173,   185,   186,    83,    83,    61,    62,
     179,    65,    73,    36,    83,    64,   185,   186,    68,    83,
     201,   202,   221,    83,   205,   264,    79,    80,    81,    82,
      83,    83,   201,   202,    64,    54,   205,    76,   258,    68,
      83,    65,    64,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,     6,
     280,   281,    71,   176,    63,    73,   265,    37,    38,    39,
      40,    41,    42,    43,    64,   245,   257,    83,    83,   260,
     261,    83,    83,   196,   265,   324,   256,    55,   257,    65,
     203,    83,   273,    53,    67,    73,    83,    44,    45,    46,
      47,    65,    49,   302,   273,   275,    69,    61,    27,    17,
     223,    64,    83,    80,    61,    62,    73,    64,    80,    66,
      67,   302,    65,    54,    65,    72,    63,    54,   309,    65,
      63,   244,    79,    80,    81,    82,    83,    67,    83,    63,
     309,   322,   323,     6,    20,   326,   327,   328,   329,   262,
      64,    71,   333,   322,   323,   336,    65,   326,   327,   328,
     329,    71,    65,    65,   333,    71,    71,   336,   349,    13,
      42,   175,   285,   134,   139,   275,   289,   208,   280,   191,
     349,    44,    45,    46,    47,   180,    49,     6,    -1,    -1,
     302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    64,    65,    66,    -1,   318,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,    82,
      83,    -1,    -1,    -1,   337,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    62,    -1,    64,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    80,    81,    82,    83,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    16,    -1,    18,    -1,    -1,    21,
      22,    -1,    24,    -1,    26,    -1,    28,    29,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    59,     7,     8,
       9,    10,    11,    12,    -1,    14,    68,    16,    -1,    18,
      -1,    -1,    21,    22,    -1,    24,    -1,    26,    -1,    28,
      29,    83,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
      -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,     7,     8,     9,    10,    11,    12,    -1,    14,    -1,
      16,    -1,    18,    -1,    83,    21,    22,    -1,    24,    -1,
      26,    -1,    28,    29,    51,    31,    32,    -1,    -1,    56,
      57,    58,    -1,    -1,    61,    62,    63,    -1,    65,     3,
       4,     5,    -1,    -1,    50,    -1,    52,    74,    75,    76,
      77,    78,    -1,    59,    -1,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,     7,     8,     9,    10,    11,    12,
      -1,    14,    -1,    16,    -1,    18,    -1,    83,    21,    22,
      -1,    24,    -1,    26,    -1,    28,    29,    51,    31,    32,
      -1,    -1,    56,    57,    58,    -1,    -1,    61,    62,    63,
       3,     4,     5,    -1,    -1,    -1,    -1,    50,    -1,    52,
      74,    75,    76,    77,    78,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    68,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    56,    57,    58,    -1,    -1,    61,    62,
      63,    34,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    56,    57,    58,    -1,    -1,    61,    62,
      63,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    30,    -1,
      61,    62,    63,    -1,    65,    -1,     3,     4,     5,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    51,
      17,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,    61,
      62,    63,    -1,    -1,     3,     4,     5,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    -1,    -1,    61,    62,    63,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      -1,    -1,    61,    62,    63,     3,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    -1,    -1,    61,    62,    63,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    77,    78,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    -1,    -1,    61,    62,    63,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    61,    62,    -1,    64,    -1,    66,
      -1,    -1,    69,    -1,    -1,    72,    44,    45,    46,    47,
      -1,    49,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    64,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    81,    82,    83
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,    48,    88,    89,    83,     0,    37,    38,    39,    40,
      41,    42,    43,    90,    91,    92,    93,    94,    95,    96,
      97,   122,    64,    83,    83,    83,    83,    83,    83,    83,
      91,    83,    98,    99,    71,   100,    63,    64,    71,    63,
      23,    63,    64,    70,    65,    73,    54,    83,   104,   105,
      36,   107,     6,    44,    45,    46,    47,    49,    61,    62,
      64,    66,    72,    79,    80,    81,    82,    83,   110,   111,
     112,   113,   114,   115,   116,   119,   120,   121,    65,    83,
     101,   102,   103,   105,    68,    64,   123,   124,     7,     8,
       9,    10,    11,    12,    14,    16,    18,    21,    22,    24,
      26,    28,    29,    31,    32,    50,    52,    59,    68,    83,
     121,   125,   126,   127,   128,   129,   130,   132,   133,   134,
     141,   142,   143,   144,   145,   147,   148,   151,   152,   153,
     154,    65,   102,    83,    83,    83,   105,    64,    54,    76,
      68,   119,    79,    80,    81,    79,    80,    81,   119,    67,
     113,   117,   118,   119,    83,    64,     3,     4,     5,    51,
      56,    57,    58,    61,    62,    63,    74,    75,    76,    77,
      78,    63,    71,    71,    65,    73,    63,    98,    98,    63,
      73,   119,   119,   119,   125,   146,   146,    83,   119,   110,
     131,    83,   119,   121,    83,   125,    64,    83,   119,   117,
      64,   146,   146,    55,    23,    63,    65,    83,   100,    61,
      62,   105,   106,   112,   105,   104,    69,   108,   109,   110,
      65,    53,    67,    73,    65,   117,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   105,   105,    63,    71,   101,   119,    69,    65,
     125,   124,    13,   125,    15,    63,    71,    19,    61,   131,
      25,    27,    17,   119,    64,    34,    83,    60,    69,   119,
     123,   125,    23,    63,   107,    73,    65,    53,    65,    69,
      73,    54,   113,   119,    65,    63,   119,   105,    54,   149,
     105,   125,   110,   121,   121,   119,    65,   117,    33,    82,
     113,   121,   135,   136,   137,   138,   139,   140,    65,    63,
     123,   125,   106,   112,   109,   110,    67,   119,    63,    83,
     119,    63,    20,    30,    64,    65,    71,    71,    71,    71,
      35,   136,   125,    63,    65,   119,    17,   150,   125,   125,
     117,   125,   125,   125,   125,   125,   125,   119,    65,    17,
     125
  };

  const unsigned char
  casmi_parser::yyr1_[] =
  {
       0,    87,    88,    89,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    92,    93,    94,    95,    96,    96,    96,
      96,    96,    96,    97,    97,    97,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   105,   105,   105,   105,   106,   106,   106,   107,
     107,   108,   108,   108,   109,   109,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   114,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   121,   121,   121,   122,   122,
     122,   122,   122,   122,   123,   123,   124,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   127,   128,   128,   129,   130,   131,   131,   132,   133,
     134,   135,   135,   136,   136,   136,   136,   137,   138,   139,
     140,   141,   141,   141,   141,   142,   143,   144,   145,   146,
     146,   147,   147,   149,   148,   150,   148,   151,   152,   153,
     154
  };

  const unsigned char
  casmi_parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     5,     6,     7,     4,     6,
       9,     6,     8,     7,     6,     4,     3,     2,     1,     3,
       1,     3,     4,     3,     1,     1,     2,     3,     1,     3,
       2,     1,     1,     4,     6,     4,     3,     2,     1,     4,
       3,     3,     2,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       5,     3,     2,     1,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     3,     1,     3,     4,     4,     6,
       7,     6,     8,     9,     3,     1,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       2,     2,     2,     1,     1,     3,     3,     1,     2,     3,
       5,     2,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     7,     4,     5,     2,     3,     3,     3,     3,     2,
       1,     4,     6,     0,     7,     0,     9,     4,     4,     6,
       2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const casmi_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "AND", "OR", "XOR", "NOT",
  "ASSERT", "ASSURE", "DIEDIE", "IMPOSSIBLE", "SKIP", "SEQBLOCK",
  "ENDSEQBLOCK", "PARBLOCK", "ENDPARBLOCK", "LET", "IN", "IF", "THEN",
  "ELSE", "PRINT", "DEBUG", "DUMPS", "PUSH", "INTO", "POP", "FROM",
  "FORALL", "ITERATE", "DO", "CALL", "CASE", "DEFAULT", "OF", "ENDCASE",
  "INITIALLY", "FUNCTION", "DERIVED", "ENUM", "RULE", "PROVIDER", "INIT",
  "OPTION", "SELF", "UNDEF", "TRUE", "FALSE", "CASM", "SYMBOL", "INTERN",
  "RATIONAL_DIV", "OBJDUMP", "DOTDOT", "ARROW", "UPDATE", "NEQUAL",
  "LESSEQ", "GREATEREQ", "SEQBLOCK_BRACKET", "ENDSEQBLOCK_BRACKET",
  "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"",
  "\"}\"", "\".\"", "\":\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"",
  "\"/\"", "\"%\"", "FLOATCONST", "INTEGERCONST", "RATIONALCONST",
  "STRCONST", "\"identifier\"", "UMINUS", "UPLUS", "XIF", "$accept",
  "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
  "INIT_SYNTAX", "PROVIDER_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX",
  "DERIVED_SYNTAX", "FUNCTION_DEFINITION", "IDENTIFIER_LIST",
  "IDENTIFIER_LIST_NO_COMMA", "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST",
  "PARAM_LIST_NO_COMMA", "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX",
  "TYPE_SYNTAX_LIST", "INITIALIZERS", "INITIALIZER_LIST", "INITIALIZER",
  "ATOM", "VALUE", "INTEGER_NUMBER", "NUMBER", "RULEREF", "NUMBER_RANGE",
  "LISTCONST", "EXPRESSION_LIST", "EXPRESSION_LIST_NO_COMMA", "EXPRESSION",
  "BRACKET_EXPRESSION", "FUNCTION_SYNTAX", "RULE_SYNTAX", "DUMPSPEC_LIST",
  "DUMPSPEC", "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX",
  "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX", "DEBUG_SYNTAX", "DEBUG_ATOM_LIST",
  "PRINT_SYNTAX", "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST",
  "CASE_LABEL", "CASE_LABEL_DEFAULT", "CASE_LABEL_NUMBER",
  "CASE_LABEL_IDENT", "CASE_LABEL_STRING", "CALL_SYNTAX",
  "KW_SEQBLOCK_SYNTAX", "SEQBLOCK_SYNTAX", "KW_PARBLOCK_SYNTAX",
  "PARBLOCK_SYNTAX", "STATEMENTS", "IFTHENELSE", "LET_SYNTAX", "$@1",
  "$@2", "PUSH_SYNTAX", "POP_SYNTAX", "FORALL_SYNTAX", "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  casmi_parser::yyrline_[] =
  {
       0,   199,   199,   203,   209,   210,   216,   217,   218,   219,
     231,   242,   243,   254,   260,   263,   265,   282,   286,   289,
     293,   296,   299,   304,   308,   312,   315,   319,   320,   323,
     327,   333,   338,   342,   347,   356,   357,   359,   363,   367,
     371,   375,   380,   381,   384,   393,   404,   408,   409,   412,
     413,   416,   417,   418,   425,   426,   429,   430,   431,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   458,   461,
     464,   475,   476,   480,   481,   483,   487,   494,   496,   498,
     500,   502,   504,   506,   508,   510,   512,   514,   516,   518,
     520,   522,   524,   526,   529,   532,   533,   534,   547,   548,
     551,   555,   559,   563,   569,   570,   576,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     606,   608,   611,   612,   622,   625,   628,   629,   631,   634,
     644,   649,   653,   659,   660,   661,   662,   665,   670,   675,
     680,   685,   686,   687,   688,   692,   697,   702,   706,   711,
     712,   715,   718,   724,   723,   735,   734,   747,   757,   768,
     773
  };

  // Print the state stack on the debug stream.
  void
  casmi_parser::yystack_print_ ()
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
  casmi_parser::yy_reduce_print_ (int yyrule)
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



} // yy
#line 3138 "GrammarParser.cpp" // lalr1.cc:1167
#line 777 "../../src/GrammarParser.yy" // lalr1.cc:1168


void yy::casmi_parser::error(const location_type& l,
                              const std::string& m) {
    driver.error (l, m);
}
