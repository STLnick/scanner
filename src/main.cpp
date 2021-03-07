/*
 * Nick Ray
 * 2/15/21
 * scanner
 */
#include <fstream>
#include <istream>
#include <iostream>
#include "parseCommandLineOpts.hpp"
#include "scanner.hpp"
#include "TokenRecord.hpp"
#include "token.hpp"
#include "utils.hpp"

void init(int argc, char **argv, std::string &fileNameToRead);

int main(int argc, char **argv) {
    std::string fileNameToRead;

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

void init(int argc, char **argv, std::string &fileNameToRead) {
    std::string buffer;
    // Read in input if needed and set the filename to be read depending on arguments
    /*  ./scanner or ./scanner < filename  */
    if (argc == 1) {
        std::ofstream tempFile;
        // Open temp file to hold user input or redirected file input
        try {
            tempFile.open("output.fs");
        }
        catch (int e) {
            std::cerr << "Failed to open the temp file for writing!" << std::endl;
            exit(1);
        }

        std::cout
                << "Preparing to read in input (if using keyboard type "
                   "'ctrl + d' on *nix systems and 'ctrl + z' for Windows to finish)"
                << std::endl;

        // While there is input from user/file write it to new file
        try {
            while (std::cin >> buffer) {
                tempFile << buffer << std::endl;
            }
        } catch (int e) {
            std::cerr << "Error while reading from buffer and writing to file!" << std::endl;
        }

        tempFile.close();

        fileNameToRead = "output";
        /*  ./scanner filename  */
    } else if (argc == 2) {
        fileNameToRead = argv[1];
        int dotIndex = fileNameToRead.find('.');

        // IF this filename has a '.' -> make sure the extension is fs and just store filename no extension
        if (dotIndex != -1) {
            std::string fileExt = fileNameToRead.substr(dotIndex);

            if (fileExt.compare(".fs") != 0) {
                std::cerr << "Incorrect file type provided - must use file extension '.fs'" << std::endl;
                exit(1);
            }

            fileNameToRead.erase(dotIndex, std::string::npos);
        }
    } else {
        std::cout << "Incorrect invocation of program! Try again or execute './P0 -h' to view the help info"
                  << std::endl;
        exit(1);
    }
}