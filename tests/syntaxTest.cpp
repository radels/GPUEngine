#include<geCore/Syntax.h>
#include<geCore/NodeContext.h>
#include<geCore/Text.h>

#define CATCH_CONFIG_MAIN
#include"catch.hpp"

using namespace ge::core;

SCENARIO("Syntax basic tests"){
  GIVEN("c++ syntax"){
    std::string lexSource=
      "START, \\t\\r\\n,START\n"
      "START,+,PLUS\n"
      "START,-,MINUS\n"
      "START,*,MULTIPLICATION\n"
      "START,/,SLASH\n"
      "START,%,MODULO\n"
      "START,<,LESSER\n"
      "START,>,GREATER\n"
      "START,=,ASSIGNMENT\n"
      "START,!,EXCLAMATION\n"
      "START,&,AMPERSAND\n"
      "START,|,BAR\n"
      "START,^,XOR\n"
      "START,(,START,(\n"
      "START,),START,)\n"
      "START,{,START,{\n"
      "START,},START,}\n"
      "START,[,START,[\n"
      "START,],START,]\n"
      "START,~,START,~\n"
      "START,;,START,;\n"
      "START,\\,,START,\\,\n"
      "START,_a\\\\-zA\\\\-Z,IDENTIFIER,,b\n"
      "START,\",DOUBLE_QUOTES,,b\n"
      "START,\',QUOTES,,b\n"
      "START,.,DOT,,b\n"
      "START,0\\\\-9,DIGIT,,b\n"
      "START,\\\\e,END\n"
      "START,,,unexpected symbol\n"
      "\n"
      "PLUS,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,+,g\n"
      "PLUS, \\t\\r\\n,START,+\n"
      "PLUS,=,START,+=\n"
      "PLUS,+,START,++\n"
      "PLUS,/,SLASH,+\n"
      "PLUS,\\\\e,END,+\n"
      "PLUS,,,expected + or =\n"
      "\n"
      "MINUS,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,-,g\n"
      "MINUS, \\t\\r\\n,START,-\n"
      "MINUS,=,START,-=\n"
      "MINUS,-,START,--\n"
      "MINUS,/,SLASH,-\n"
      "MINUS,\\\\e,END,-\n"
      "MINUS,,,expected - or =\n"
      "\n"
      "MULTIPLICATION,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,*,g\n"
      "MULTIPLICATION, \\t\\r\\n,START,*\n"
      "MULTIPLICATION,=,START,*=\n"
      "MULTIPLICATION,/,SLASH,*\n"
      "MULTIPLICATION,\\\\e,END,*\n"
      "MULTIPLICATION,,,expected =\n"
      "\n"
      "SLASH,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,/,g\n"
      "SLASH, \\t\\r\\n,START,/\n"
      "STASH,=,START,/=\n"
      "SLASH,/,COMMENT0\n"
      "SLASH,*,COMMENT1\n"
      "SLASH,\\\\e,END,/\n"
      "SLASH,,,expected = or *\n"
      "\n"
      "MODULO,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,%,g\n"
      "MODULO, \\t\\r\\n,START,%\n"
      "MODULO,=,START,%=\n"
      "MODULO,/,SLASH,%\n"
      "MODULO,\\\\e,END,%\n"
      "MODULO,,,expected =\n"
      "\n"
      "LESSER,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,<,g\n"
      "LESSER, \\t\\r\\n,START,<\n"
      "LESSER,=,START,<=\n"
      "LESSER,<,LSHIFT\n"
      "LESSER,/,SLASH,<\n"
      "LESSER,\\\\e,END,<\n"
      "LESSER,,,expected =\n"
      "\n"
      "GREATER,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,>,g\n"
      "GREATER, \\t\\r\\n,START,>\n"
      "GREATER,=,START,>=\n"
      "GREATER,>,RSHIFT\n"
      "GREATER,/,SLASH,>\n"
      "GREATER,\\\\e,END,>\n"
      "GREATER,,,expected =\n"
      "\n"
      "ASSIGNMENT,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,=,g\n"
      "ASSIGNMENT, \\t\\r\\n,START,= \n"
      "ASSIGNMENT,=,START,==\n"
      "ASSIGNMENT,/,SLASH,=\n"
      "ASSIGNMENT,\\\\e,END,=\n"
      "ASSIGNMENT,,,expected =\n"
      "\n"
      "EXCLAMATION,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,!,g\n"
      "EXCLAMATION, \\t\\r\\n,START,!\n"
      "EXCLAMATION,=,START,!=\n"
      "EXCLAMATION,!,START,!!\n"
      "EXCLAMATION,/,SLASH,!\n"
      "EXCLAMATION,\\\\e,END,!\n"
      "EXCLAMATION,,,expected = or !\n"
      "\n"
      "AMPERSAND,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,&,g\n"
      "AMPERSAND, \\t\\r\\n,START,&\n"
      "AMPERSAND,=,START,&=\n"
      "AMPERSAND,&,START,&&\n"
      "AMPERSAND,/,SLASH,&\n"
      "AMPERSAND,\\\\e,END,&\n"
      "AMPERSAND,,,expected = or &\n"
      "\n"
      "BAR,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,|,g\n"
      "BAR, \\t\\r\\n,START,|\n"
      "BAR,=,START,|=\n"
      "BAR,|,START,||\n"
      "BAR,/,SLASH,|\n"
      "BAR,\\\\e,END,|\n"
      "BAR,,,expected = or |\n"
      "\n"
      "XOR,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,^,g\n"
      "XOR, \\t\\r\\n,START,^\n"
      "XOR,=,START,^=\n"
      "XOR,/,SLASH,^\n"
      "XOR,\\\\e,END,^\n"
      "XOR,,,expected =\n"
      "\n"
      "IDENTIFIER,_a\\\\-zA\\\\-Z0\\\\-9,IDENTIFIER\n"
      "IDENTIFIER, \\t\\r\\n,START,identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void string struct typedef return,e\n"
      "IDENTIFIER,,START,identifier for while if else bool i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 void string struct typedef return,eg\n"
      "\n"
      "DOUBLE_QUOTES,\\\\\\\\,DQ_BACKSLASH\n"
      "DOUBLE_QUOTES,\",START,string-value,e\n"
      "DOUBLE_QUOTES,,DOUBLE_QUOTES\n"
      "DOUBLE_QUOTES,\\\\e,,unexpected end of file in string\n"
      "\n"
      "DQ_BACKSLASH,\\\\.,DOUBLE_QUOTES\n"
      "DQ_BACKSLASH,\\\\e,,unexpected end of file after backslash\n"
      "\n"
      "QUOTES,\\\\\\\\,Q_BACKSLASH\n"
      "QUOTES,\',START,char,e\n"
      "QUOTES,,QUOTES\n"
      "QUOTES,\\\\e,,unexpected end of file in char\n"
      "Q_BACKSLASH,\\\\.,QUOTES\n"
      "Q_BACKSLASH,\\\\e,,unexpected end of file after backslash\n"
      "\n"
      "DOT,0\\\\-9,FRACTION\n"
      "DOT,\\\\e,END,.\n"
      "DOT,,START,.,g\n"
      "\n"
      "DIGIT,0\\\\-9,DIGIT\n"
      "DIGIT,eE,EXPONENT\n"
      "DIGIT,.,FRACTION\n"
      "DIGIT,\\\\e,END,integer-value\n"
      "DIGIT,,START,integer-value,eg\n"
      "\n"
      "FRACTION,0\\\\-9,FRACTION\n"
      "FRACTION,eE,EXPONENT\n"
      "FRACTION,\\\\e,END,float-value\n"
      "FRACTION,,START,float-value,eg\n"
      "\n"
      "EXPONENT,+-,EXP_SIGN\n"
      "EXPONENT,0\\\\-9,EXP_DIGIT\n"
      "EXPONENT,\\\\e,,unexpected end of file in float exponent\n"
      "EXPONENT,,,expected + or - or digit in float exponent\n"
      "\n"
      "EXP_SIGN,0\\\\-9,EXP_DIGIT\n"
      "EXP_SIGN,\\\\e,,unexpected end of file in float exponent\n"
      "EXP_SIGN,,,expected digit in float exponent\n"
      "\n"
      "EXP_DIGIT,0\\\\-9,EXP_DIGIT\n"
      "EXP_DIGIT,\\\\e,END,float-value\n"
      "EXP_DIGIT,,START,float-value,eg\n"
      "\n"
      "COMMENT0,\\r\\n,START\n"
      "COMMENT0,\\\\e,END\n"
      "COMMENT0,,COMMENT0\n"
      "\n"
      "COMMENT1,*,COMMENT1_STAR\n"
      "COMMENT1,\\\\e,END\n"
      "COMMENT1,,COMMENT1\n"
      "\n"
      "COMMENT1_STAR,/,START\n"
      "COMMENT1_STAR,*,COMMENT1_STAR\n"
      "COMMENT1_STAR,\\\\e,END\n"
      "COMMENT1_STAR,,COMMENT1\n"
      "\n"
      "LSHIFT,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,<<,g\n"
      "LSHIFT, \\t\\r\\n,START,<<\n"
      "LSHIFT,=,START,<<=\n"
      "LSHIFT,/,SLASH,<<\n"
      "LSHIFT,\\\\e,END,<<\n"
      "LSHIFT,,,expected =\n"
      "\n"
      "RSHIFT,_a\\\\-zA\\\\-Z0\\\\-9.\\,!(){}[]~;\"\',START,>>,g\n"
      "RSHIFT, \\t\\r\\n,START,>>\n"
      "RSHIFT,=,START,>>=\n"
      "RSHIFT,/,SLASH,>>\n"
      "RSHIFT,\\\\e,END,>>\n"
      "RSHIFT,,,expected =\n";
    std::string synSource=
      "statement-declaration STATEMENT TYPE identifier ;\n"
      "statement-function STATEMENT TYPE identifier ( COMMA-DECL-LIST ) { BODY }\n"
      "statement-return STATEMENT return EXPRESSION ;\n"
      "statement-expression STATEMENT EXPRESSION ;\n"
      "statement-ifelse STATEMENT if ( EXPRESSION ) STATEMENT else STATEMENT\n"
      "statement-if STATEMENT if ( EXPRESSION ) STATEMENT\n"
      "statement-while STATEMENT while ( EXPRESSION ) STATEMENT\n"
      "statement-{} STATEMENT { BODY }\n"
      "statement-typedef-struct STATEMENT typedef struct { DECL-LIST } identifier ;\n"
      "statement-typedef-array STATEMENT typedef TYPE [ integer-value ] identifier ;\n"
      "\n"
      "exp-assign-pass EXPRESSION EXP-OR\n"
      "exp-assign EXPRESSION EXPRESSION ASSIGN-OPER EXP-OR\n"
      "\n"
      "exp-or-pass EXP-OR EXP-AND\n"
      "exp-or EXP-OR EXP-AND || EXP-OR\n"
      "\n"
      "exp-and-pass EXP-AND EXP-BOR\n"
      "exp-and EXP-AND EXP-BOR && EXP-AND\n"
      "\n"
      "exp-bor-pass EXP-BOR EXP-XOR\n"
      "exp-bor EXP-BOR EXP-XOR | EXP-BOR\n"
      "\n"
      "exp-xor-pass EXP-XOR EXP-BAND\n"
      "exp-xor EXP-XOR EXP-BAND ^ EXP-XOR\n"
      "\n"
      "exp-band-pass EXP-BAND EXP-EQUALITY\n"
      "exp-band EXP-BAND EXP-EQUALITY & EXP-BAND\n"
      "\n"
      "exp-equality-pass EXP-EQUALITY EXP-RELATIONAL\n"
      "exp-equality EXP-EQUALITY EXP-RELATIONAL EQUALITY-OPER EXP-EQUALITY\n"
      "\n"
      "exp-relational-pass EXP-RELATIONAL EXP-SHIFT\n"
      "exp-relational EXP-RELATIONAL EXP-SHIFT RELATIONAL-OPER EXP-RELATIONAL\n"
      "\n"
      "exp-shift-pass EXP-SHIFT EXP-ADDITIVE\n"
      "exp-shift EXP-SHIFT EXP-ADDITIVE SHIFT-OPER EXP-SHIFT\n"
      "\n"
      "exp-additive-pass EXP-ADDITIVE EXP-MULTIPLICATIVE\n"
      "exp-additive EXP-ADDITIVE EXP-MULTIPLICATIVE ADDITIVE-OPER EXP-ADDITIVE\n"
      "\n"
      "exp-multiplicative-pass EXP-MULTIPLICATIVE EXP-UNARY\n"
      "exp-multiplicative EXP-MULTIPLICATIVE EXP-UNARY MULTIPLICATIVE-OPER EXP-MULTIPLICATIVE\n"
      "\n"
      "exp-unary-pass EXP-UNARY EXP-TERM\n"
      "exp-unary EXP-UNARY UNARY-OPER EXP-TERM\n"
      "\n"
      "exp-() EXP-TERM ( EXPRESSION )\n"
      "exp-identifier EXP-TERM identifier\n"
      "exp-value EXP-TERM VALUE\n"
      "exp-function EXP-TERM identifier ( COMMA-EXP-LIST )\n"
      "\n"
      "comma-exp-list-term COMMA-EXP-LIST EXPRESSION\n"
      "comma-exp-list COMMA-EXP-LIST EXPRESSION , COMMA-EXP-LIST\n"
      "\n"
      "body-term BODY STATEMENT\n"
      "body BODY STATEMENT BODY\n"
      "\n"
      "decl-list-term DECL-LIST TYPE identifier ;\n"
      "decl-list DECL-LIST TYPE identifier ; DECL-LIST\n"
      "\n"
      "comma-decl-list-term COMMA-DECL-LIST TYPE identifier\n"
      "comma-decl-list COMMA-DECL-LIST TYPE identifier , COMMA-DECL-LIST\n"
      "\n"
      "comma-list-term COMMA-LIST identifier\n"
      "comma-list COMMA-LIST identifier , COMMA-LIST\n"
      "\n"
      "value-float VALUE float-value\n"
      "value-integer VALUE integer-value\n"
      "value-string VALUE string-value\n"
      "\n"
      "type-bool TYPE bool\n"
      "type-i8 TYPE i8\n"
      "type-i16 TYPE i16\n"
      "type-i32 TYPE i32\n"
      "type-i64 TYPE i64\n"
      "type-u8 TYPE u8\n"
      "type-u16 TYPE u16\n"
      "type-u32 TYPE u32\n"
      "type-u64 TYPE u64\n"
      "type-f32 TYPE f32\n"
      "type-f64 TYPE f64\n"
      "type-string TYPE string\n"
      "type-identifier TYPE identifier\n"
      "\n"
      "assign-= ASSIGN-OPER =\n"
      "assign-+= ASSIGN-OPER +=\n"
      "assign--= ASSIGN-OPER -=\n"
      "assign-*= ASSIGN-OPER *=\n"
      "assign-/= ASSIGN-OPER /=\n"
      "assign-%= ASSIGN-OPER %=\n"
      "assign-&= ASSIGN-OPER &=\n"
      "assign-|= ASSIGN-OPER |=\n"
      "assign-^= ASSIGN-OPER ^=\n"
      "assign-<<= ASSIGN-OPER <<=\n"
      "assign->>= ASSIGN-OPER >>=\n"
      "\n"
      "equality-== EQUALITY-OPER ==\n"
      "equality-!= EQUALITY-OPER !=\n"
      "\n"
      "relational-< RELATIONAL-OPER <\n"
      "relational-> RELATIONAL-OPER >\n"
      "relational-<= RELATIONAL-OPER <=\n"
      "relational->= RELATIONAL-OPER >=\n"
      "\n"
      "shift-<< SHIFT-OPER <<\n"
      "shift->> SHIFT-OPER >>\n"
      "\n"
      "additive-+ ADDITIVE-OPER +\n"
      "additive-- ADDITIVE-OPER -\n"
      "\n"
      "multiplicative-* MULTIPLICATIVE-OPER *\n"
      "multiplicative-/ MULTIPLICATIVE-OPER /\n"
      "multiplicative-% MULTIPLICATIVE-OPER %\n"
      "\n"
      "unary-+ UNARY-OPER +\n"
      "unary-- UNARY-OPER -\n"
      "unary-~ UNARY-OPER ~\n"
      "unary-! UNARY-OPER !\n";
    Syntax syn(lexSource,synSource);
    WHEN("parsing i32 a;"){
      syn.begin();
      THEN("it should pass"){
        auto res=syn.parse("i32 a;");
        REQUIRE(res.first==ge::core::NodeContext::Status::TRUE_STATUS);
      }
      syn.end();
    }
  }
}


