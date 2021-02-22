/*
 * Nick Ray
 * 2/15/21
 */

#ifndef TOKEN_RECORD_HPP
#define TOKEN_RECORD_HPP

#include <string>

/* Single char tokens */
// = + - / * ( ) { } [ ] % . , ; :

/* Double char tokens */
// == => := =<

// TODO: Make these TokenTypes the actual needed types
enum tokenID {
    ID_tk,
    NUM_tk,
    EOF_tk,
    ASSIGN_tk,
    SEMI_tk,
    PLUS_tk,
    MINUS_tk,
    MULT_tk,
    DIVIDE_tk,
    MOD_tk,
    DOT_tk,
    COMMA_tk,
    COLON_tk,
    LPAREN_tk,
    RPAREN_tk,
    LBRACE_tk,
    RBRACE_tk,
    LBRACKET_tk,
    RBRACKET_tk,
    EQ_tk,
    GTEQ_tk,
    LTEQ_tk,
    COLONEQ_tk
};
const std::string tokenNames[] = {
        "Identifier",
        "Number",
        "End Of File",
        "Assignment Operator",
        "Semicolon",
        "Addition",
        "Subtraction",
        "Multiplication",
        "Division",
        "Modulus",
        "Dot",
        "Comma",
        "Colon",
        "Left Parenthesis",
        "Right Parenthesis",
        "Left Brace",
        "Right Brace",
        "Left Bracket",
        "Right Bracket",
        "Equality Operator",
        "Greater Than or Equal To Operator",
        "Less Than or Equal To Operator",
        "Colon Equals Operator"
};

typedef struct {
    tokenID tokenId;       // The token type
    std::string stringVal; // The identifying string value for the token
    //int lineNum;           // Line number which the token is on in source
} TokenRecord;

#endif /* TOKEN_RECORD_HPP */