#ifndef SCANNER_TOKEN_HPP
#define SCANNER_TOKEN_HPP

#include "TokenRecord.hpp"

TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum);

void printToken(TokenRecord *token);

#endif // !SCANNER_TOKEN_HPP
