/*
 * Nick Ray
 * 2/15/21
 */

#ifndef TOKEN_RECORD_HPP
#define TOKEN_RECORD_HPP

#include <string>

//   =     =>   =<  ==   : := + - * / % . ( ) , { } ; [ ]
// assign gteq lteq eq 

// TODO: Make these TokenTypes the actual needed types
enum tokenID {
    ID_tk, NUM_tk
};
const std::string tokenNames[] =
        {"Identifier", "Number"};

typedef struct {
    tokenID tokenId;       // The token type
    std::string stringVal; // The identifying string value for the token
    //int lineNum;           // Line number which the token is on in source
} TokenRecord;

#endif /* TOKEN_RECORD_HPP */