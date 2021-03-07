/*
 * Nick Ray
 * 2/15/21
 * scanner
 */
#include <fstream>
#include <istream>
#include <iostream>
#include "init.hpp"
#include "parseCommandLineOpts.hpp"
#include "scanner.hpp"
#include "TokenRecord.hpp"
#include "token.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    std::string fileNameToRead;
    int lineCnt = 1;

    // Parse Command Line Options
    switch (parseCommandLineOpts(argc, argv)) {
        case -1:
            std::cout << "Invalid Usage - Terminating" << std::endl;
            return -1;
        case 1: // Help flag was used, gracefully exit
            return 0;
    }

    init(argc, argv, fileNameToRead);

    // Setup a file stream to assign src in scanner
    std::ifstream srcFile(fileNameToRead + ".fs");
    std::string srcString;
    readSrcIntoString(srcFile, srcString);

    Scanner *scanner = initScanner(srcString);

    /*
    int colNum = 0; // TODO: fully implement
    int lineCnt = 0; // TODO: fully implement - will need too add lineNum back onto TokenRecord
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

     */

    // TODO: break this out into 'testing driver' or something like that...
    // Get next token until we receive the EOF_tk
    while (1) {
        TokenRecord *token = getNextToken(scanner, lineCnt);
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
