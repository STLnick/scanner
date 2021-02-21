#include <string>
#include "TokenRecord.hpp"

/**
 * @param name string value of the token
 * @param tokenId the type of the token
 * @param lineNum the line number the token is on
 * @return newly instantiated TokenRecord
 */
TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum) {
    TokenRecord *newToken;
    newToken = (TokenRecord *) malloc(1 * sizeof(TokenRecord));
    newToken->stringVal = name;
    newToken->tokenId = tokenId;
    newToken->lineNum = lineNum;
    return newToken;
}