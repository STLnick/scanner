/*
 * Nick Ray
 * 2/15/21
 * scanner
 */
#include <fstream>
#include <istream>
#include <iostream>
#include "scanner.hpp"
#include "TokenRecord.hpp"
#include "token.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {

    /* ------------------------------------ */
    // Testing a TOKEN
    /* ------------------------------------ */
    TokenRecord *myToken = initToken("NICK", ID_tk/*, 1*/);

    std::cout << "Token: '" << myToken->stringVal << "'";
    std::cout << " Type: '" << tokenNames[myToken->tokenId] << "'" << std::endl << std::endl;
    //std::cout << " Line " << myToken->lineNum << "'" << std::endl << std::endl;


    /* ------------------------------------ */
    // Testing a SCANNER
    /* ------------------------------------ */

    // TODO: open the file based on the arguments provided to the program
    // TODO: file extenstion checks, etc. GET CODE FROM P0 for CL ARGS PARSING!

    // Setup a file stream to assign src in scanner
    std::ifstream srcFile("../test.fs");

    std::string srcString;

    readSrcIntoString(srcFile, srcString);
    int prevLineCnt = 0;

    Scanner *scanner = initScanner(srcString);
    std::cout << "[" << lineCnt + 1 << "]: " << scanner->c;
    advanceScanner(scanner);

    while (!scanner->src->eof()) {
        // Print the line number on a new line from the src file
        if (lineCnt != prevLineCnt) {
            std::cout << "[" << lineCnt + 1 << "]: ";
            prevLineCnt += 1;
        }


        if (scanner->c == '\n')
            lineCnt += 1;

        std::cout << scanner->c;

        advanceScanner(scanner);
    }

    // TODO: Manually log the EOF token

    /* ------------------------------------ */
    // Free memory
    /* ------------------------------------ */
    free(myToken);
    free(scanner);
    srcFile.close();

    return 0;
}