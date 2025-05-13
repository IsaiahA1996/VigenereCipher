/* File: COMPSCI2_Final Project.cpp : This file contains the 'main' function. Program execution begins and ends here.
   
   Name: Isaiah Avila
   
   Date: 05/12/2025 (Last Modified)
   
   Description: This program will be used to transform plaintext into ciphertext (encryption). It it is also capable 
                of transforming ciphertext back into plaintext (decryption).
   
   Usage: This program will utilize data structures, dynamic arrays, inheritance, and polymorphism to shift characters
          either forwards or backwards between 0-25 places based upon the user given key in their second command-line
          argument. */
          
#include <iostream>
#include <fstream>
#include <sstream>      
#include <memory>
#include <string>
#include <stdexcept>
#include "VigenereCipher.hpp"

int main(int argc, char* argv[]) { /* The enrty point of the program. The magic. argc: Number of command-line arguements. argv: Array of C-style strings for each argument. */
    if (argc != 5) { /* Ensures the user provides exactly four arguments. 1.) Encrypt/Decrypt. 2.) Key. 3.) input filename. 4.) output filename. */
        std::cerr << "Usage: " << argv[0]
            << " <encrypt|decrypt> <key> <input_file> <output_file>\n";
        return 1;
    }

    std::string mode = argv[1]; /* Either encrypt or decrypt. */
    std::string key = argv[2]; /* The Vigenere key, alphabetic only. */
    std::string inPath = argv[3]; /* Input filename. */
    std::string outPath = argv[4]; /* Output filename. */

    try {
        
        std::unique_ptr<Cipher> cipher = /* Creates a polymorphic Cipher pointer holding a VigenereCipher instance. 'make_unique' allocates on the heap and returns a unique ptr. */
            std::make_unique<VigenereCipher>(key);

        
        std::ifstream inFile(inPath, std::ios::binary); /* Input stream that opens the input file in binary mode to preserve all bytes. */
        if (!inFile)
            throw std::runtime_error("Cannot open input file"); /* Throw an exception if the file cannot be opened. */

        std::ostringstream ss;/* Read the entire contents of the file into a std::string. */
        ss << inFile.rdbuf();
        std::string text = ss.str(); /* Extracts as a string. */
        inFile.close(); /* Closes the file. */

        
        std::string result; /* Prepares a container for whatever text we'll write out. It'll hold ciphertext if encrypting, or plaintext if decrypting. */
        if (mode == "encrypt") { /* Decide which operation to perform based on the user's 'mode' arguement. */
            result = cipher->encrypt(text); /* Cipher is a std::unique_ptr<Cipher> pointing to a VigenereCipher. Polymorphic dispatch: this calls VigenereCipher::encrypt(text). 'text' holds the entire contents of the input file. 
                                               The returned string is the full ciphertext. */
        }
        else if (mode == "decrypt") { 
            result = cipher->decrypt(text); /* Likewise, this calls VigenereCipher::decrypt(text), taking the "gibberish" in 'text' and converting it back to plaintext. */
        }
        else { /* In case the user user supplies anything other than 'encrypt' or 'decrypt', we'll consider it a usage error. Prints a message. */
            throw std::invalid_argument("Mode must be 'encrypt' or 'decrypt'");
        }

        
        std::ofstream outFile(outPath, std::ios::binary); /* Opens an output file stream in binary mode. */
        if (!outFile) /* The stream object outFile wraps a file hadle; this tests whether it opened successfully. */
            throw std::runtime_error("Cannot open output file"); /* Lets the user know that something went wrong. Could be a bad path, no permissions, disk size full, etc.) */
        outFile << result; /* Writes the entirety of our result string into the file. */
        outFile.close(); /* Closes the file explicitly. Flushes any buffered data. */

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n"; /* Any std::invalid_argument or std::runtime_error thrown above lands here. Prints "Error:_" message and returns a non-zero exit code. */
        return 1;
    }

    return 0; /* If we made it this far with no exceptions, return 0 ----> success! */
}

