/*
 * Nick Ray
 * 2/15/21
 * scanner
 */
#include <iostream>
#include "TokenRecord.hpp"
#include "token.hpp"

int main() {

    // TODO: basic setup here of calling a function to init a token and storing it
    TokenRecord *myToken = initToken("NICK", ID_tk, 1);

    std::cout << "Token: '" << myToken->stringVal << "'";
    std::cout << " Type: '" << tokenNames[myToken->tokenId] << "'";
    std::cout << " Line " << myToken->lineNum << "'" << std::endl << std::endl;

    // Free memory
    free(myToken);

    return 0;
}