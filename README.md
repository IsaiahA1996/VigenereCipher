A simple C++17 command-line utility that implements the classic Vigenere cipher. It can encrypt or decrypt any text file using an alphabetic key.

Overview -
The Vigenere cipher is a polyalphabetic substitution cipher. This project demonstrates
- Modular C++ design using classes, inheritance, and pure-virtual interfaces
- RAII with Key managing its own heap-allocated memory
- Polymorphism via a Cipher base class and concrete VigenereCipher implementation
- Smart pointers (unique_ptr) to own cipher objects
- Streams (ifstream, ofstream, ostringstream) for file I/O
- Error checking via exceptions (invalid_argument, runtime_error)
- A unit-test suite (test_vigenere.cpp) that verifies all key behaviors

Features
- Encrypt or decrypt text files of any size
- Case-preserving: uppercase stays uppercase, lowercase stays lowercase
- Non-letters (spaces, digits, punctuation) pass through unchanged
- Key cycling: automatically repeats your key to cover the entire message
- Robust validation:
• Key must be non-empty and alphabetic
• File I/O errors produce clear error messages
- Unit tests demonstrating correctness on various inputs

Requirements
- A C++17-conforming compiler (for example, MSVC in Visual Studio 2022, g++ 7 or later, clang 5 or later)
- No external dependencies beyond the C++ standard library

Building
Visual Studio 2022
Open the solution file VigenereCipher.sln.

In Project -> Properties -> C/C++ -> Language, set the C++ Language Standard to ISO C++17.

Build the solution (Ctrl+Shift+B).

To run from within Visual Studio:
- Set VigenereCipher as the startup project
- Open Project -> Properties -> Debugging
- In Command Arguments enter, for example:
encrypt LEMON plain.txt cipher.txt
- Press Ctrl+F5

Command-Line (g++)
From your project root directory:

g++ -std=c++17 src/VigenereCipher.cpp src/main.cpp -o VigenereCipher
g++ -std=c++17 src/VigenereCipher.cpp tests/test_vigenere.cpp -o test_vigenere

Usage
Invoke the tool with four arguments: mode key input_file output_file

mode must be either encrypt or decrypt.
key is your alphabetic cipher key.
input_file is the path to the plaintext or ciphertext file.
output_file is where the result will be written.

Examples:

To encrypt a file:
VigenereCipher encrypt KEY plain.txt cipher.txt

To decrypt:
VigenereCipher decrypt KEY cipher.txt decrypted.txt

After decrypting, decrypted.txt should match your original plain.txt

Unit Tests
A small test harness (test_vigenere.cpp) uses assert to verify:
- Key validation rejects empty or non-alphabetic strings
- Known-answer example for a simple uppercase string
- Round-trip correctness on mixed and empty inputs

To run:

test_vigenere
(you should see “All unit tests passed”)

Error Handling
- A bad or empty key throws invalid_argument
- File open failures throw runtime_error
– All exceptions are caught in main, printed as “Error: <message>” and return exit code 1
