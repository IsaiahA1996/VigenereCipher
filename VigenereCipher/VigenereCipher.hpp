#ifndef VIGENERE_CIPHER_HPP
#define VIGENERE_CIPHER_HPP

#include "Cipher.hpp"
#include <cstddef>  
#include <string>


struct Key { /* Defines a new type 'Key' that bundles together the raw key data and its length. */
    char* data;   /* Character pointer to the uppercase letters of the key string. Serves as a raw pointer to a dynamically allocated array of 'char.' */
    size_t  length; /* Number of letters in the key. Determines the size of the array. */

    
    explicit Key(const std::string& s);

    
    ~Key(); /* A destructor. This will run automatically when a key object goes out of scope or is deleted. It's only job is to delete data to prevent a memory leak. */

    
    Key(const Key&) = delete; /* Prevents copy-constrcution. */
    Key& operator=(const Key&) = delete; /* Prevents copy-assignmnent. */

    
    Key(Key&& other) noexcept;
    Key& operator=(Key&& other) noexcept;
};


class VigenereCipher : public Cipher { /* Inheritance! This derived class will inherit the abstract interface from the cipher. */
public:
    
    explicit VigenereCipher(const std::string& keyString);
    ~VigenereCipher() override = default; /* Another destructor. Override marks this line of code as overriding Cipher's virtual destructor. */

    std::string encrypt(const std::string& plaintext) override; /* Takes plaintext and returns ciphertext. */
    std::string decrypt(const std::string& ciphertext) override; /* Takes ciphertext and returns recovered plaintext. */

private:
    Key key_;  /* The Key struct holds holds an uppercase, validated copy of the key that's stored in a dynamically allocated char array managed by RAII. */

   
    std::string transform(const std::string& text, bool decryptMode); /* The core transform routine used by both encrypt() and decrypt(). Returns the trasnformed string. */
};

#endif 
