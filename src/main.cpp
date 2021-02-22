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


    /* ------------------------------------ */
    // Testing a SCANNER
    /* ------------------------------------ */

    // TODO: open the file based on the arguments provided to the program
    // TODO: file extenstion checks, etc. GET CODE FROM P0 for CL ARGS PARSING!

    // Setup a file stream to assign src in scanner
    std::ifstream srcFile("../test.fs");

    Scanner *scanner = initScanner(srcFile);
    /* ------------------------------------ */
    // Free memory
    /* ------------------------------------ */
    free(myToken);
    scanner->src = nullptr;
    free(scanner);
    srcFile.close();

    return 0;
}