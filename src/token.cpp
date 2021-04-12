#include <iostream>
#include <stdlib.h>
#include <string>
#include "TokenRecord.hpp"

TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum) {
    TokenRecord *newToken = new TokenRecord();
    newToken->stringVal = name;
    newToken->tokenId = tokenId;
    newToken->lineNum = lineNum;
    return newToken;
}

void printToken(TokenRecord *token) {
    std::cout << "[" << tokenNames[token->tokenId] << "] '" << token->stringVal << "' on line " << token->lineNum << std::endl;
}
