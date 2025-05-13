#include "VigenereCipher.hpp"
#include <stdexcept>
#include <cctype>

/* Key implementation */

Key::Key(const std::string& s) { /* Constructor definition. */
    if (s.empty()) /* If statement; checks for empty key string. */
        throw std::invalid_argument("Key cannot be empty");

    length = s.size(); /* Stores key length. */
    data = new char[length]; /* Dynamic memory allocation that allocates char array on the heap. */
    for (size_t i = 0; i < length; ++i) { /* For-loop; iterates over each character index. */
        char c = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i]))); 
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            delete[] data;
            throw std::invalid_argument("Key must be alphabetic only");
        }
        data[i] = c;
    }
}

Key::~Key() { /* Destructor definition. Frees the heap allocated char array. */
    delete[] data; /* Data pointer and length are discarded automatically. */
}

Key::Key(Key&& other) noexcept /* Move constructor definition, marked no except. */
    : data(other.data), length(other.length) /* Member initializer; steal pointer. */
{
    other.data = nullptr; /* Null out source pointer. */
    other.length = 0; /* Assignment. Resets source length. */
}

Key& Key::operator=(Key&& other) noexcept { /*  */
    if (this != &other) {
        delete[] data; /* Frees existing data. */
        data = other.data; /* Assignment. Steals pointer. */
        length = other.length; /* Steals length. */
        other.data = nullptr; /* Set source pointer to null. */
        other.length = 0; /* Resets source length. */
    }
    return *this; /* Enables chain assignment. */
}

/* VigenereCipher implementation */

VigenereCipher::VigenereCipher(const std::string& keyString)
    : key_(keyString)
{
}

std::string VigenereCipher::encrypt(const std::string& plaintext) {
    return transform(plaintext, /*decryptMode=*/false);
}

std::string VigenereCipher::decrypt(const std::string& ciphertext) {
    return transform(ciphertext, /*decryptMode=*/true);
}

std::string VigenereCipher::transform(const std::string& text, bool decryptMode) {
    std::string result;
    result.reserve(text.size());

    size_t keyIndex = 0;
    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            bool isUpper = std::isupper(static_cast<unsigned char>(ch)); /* Bool. Checks uppercase. */
            char base = isUpper ? 'A' : 'a'; /* Choose base codepoint. */

            int offset = ch - base; /* Computes 0-25 index. */
            int shift = key_.data[keyIndex % key_.length] - 'A'; /* Fetch key shift. */
            int val = decryptMode 
                ? (offset - shift + 26) % 26
                : (offset + shift) % 26;

            result += static_cast<char>(base + val); /* Appends shifted char. */
            ++keyIndex; /* Advnaces key index. */
        }
        else {
            
            result += ch; /* Append original char unchanged. */
        }
    }
    return result; /* Returns the final transformed text. */
 }
