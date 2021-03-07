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

    // Setup / validate file to read from using keyboard input, input redirection or command line argument
    init(argc, argv, fileNameToRead);

    // Setup a file stream to assign src in scanner
    std::ifstream srcFile(fileNameToRead + ".fs");
    std::string srcString;
    readSrcIntoString(srcFile, srcString);

    // Initialize the Scanner
    Scanner *scanner = initScanner(srcString);


    /* ------------------------------------ */
    // Test Scanner
    /* ------------------------------------ */
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
