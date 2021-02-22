#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "TokenRecord.hpp"

TokenRecord *initToken(std::string name, tokenID tokenId/*, int lineNum*/);

void printToken(TokenRecord *token);

#endif // !TOKEN_HPP
