#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <string>

/* This file serves as an abstract interface for the cipher framework.  */

class Cipher {
public:
    virtual ~Cipher() = default; /* Here I declare my member functions as virtual functions, enabling 'dynamic dispatch'; calls go to to the derived-class override at runtime. */

    virtual std::string encrypt(const std::string& plaintext) = 0; /* '= 0' designates these functions as pure virtual functions; they, on thier own, return nothing. It's up to the derived classes to provide their own encrypt() implementation. */
    
    virtual std::string decrypt(const std::string& ciphertext) = 0; /* Constant reference to a string, in this case, our ciphertext. */
};

#endif 
