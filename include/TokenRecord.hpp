/*
 * Nick Ray
 * 2/15/21
 */

#ifndef TOKEN_RECORD_HPP
#define TOKEN_RECORD_HPP

#include <string>

/* Single char tokens */
// = + - / * ( ) { } [ ] % . , ; : < >

/* Double char tokens */
// <= >= == != :=

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
    EQ_tk,   // TODO
    GTEQ_tk, // TODO
    LTEQ_tk  // TODO
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
        "Equality Operator",
        "Greater Than or Equal To Operator",
        "Less Than or Equal To Operator",
};

typedef struct {
    tokenID tokenId;       // The token type
    std::string stringVal; // The identifying string value for the token
    //int lineNum;           // Line number which the token is on in source
} TokenRecord;

#endif /* TOKEN_RECORD_HPP */