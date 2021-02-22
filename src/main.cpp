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
    // Testing a SCANNER
    /* ------------------------------------ */

    // TODO: open the file based on the arguments provided to the program
    // TODO: file extenstion checks, etc. GET CODE FROM P0 for CL ARGS PARSING!

    // Setup a file stream to assign src in scanner
    std::ifstream srcFile("../test2.fs");

    std::string srcString;

    readSrcIntoString(srcFile, srcString);

    Scanner *scanner = initScanner(srcString);

    /*
    int colNum = 0; // TODO: fully implement
    int lineCnt = 0; // TODO: fully implmeent - will need too add lineNum back onto TokenRecord
    int prevLineCnt = 0;
    std::cout << "[" << lineCnt + 1 << "]: " << scanner->c;
    advanceScanner(scanner);

    for (int i = scanner->i; i < scanner->src->length(); i++) {
        // Print the line number on a new line from the src file
        if (lineCnt != prevLineCnt) {
            std::cout << "[" << lineCnt + 1 << "]: ";
            prevLineCnt++;
        }

        if (scanner->c == '\n') {
            colNum = 0;
            lineCnt++;
        } else {
            colNum++;
        }

        if (scanner->c == '\0')
            std::cout << "NULL TERMINATOR";

        std::cout << scanner->c;

        advanceScanner(scanner);
    }
     */

    // Get next token until we receive the EOF_tk
    while (1) {
        TokenRecord *token = getNextToken(scanner);
        printToken(token);
        if (token->tokenId == EOF_tk)
            break;
    }

    /* ------------------------------------ */
    // Free memory
    /* ------------------------------------ */
    free(scanner);

    srcFile.close();

    return 0;
}