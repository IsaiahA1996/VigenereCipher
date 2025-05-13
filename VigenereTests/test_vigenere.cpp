#include "VigenereCipher.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

void test_key_validation() { /*…*/ }
void test_simple_upper() { /*…*/ }
void test_mixed_text() { /*…*/ }
void test_empty_string() { /*…*/ }

int main() {
	test_key_validation();
	test_simple_upper();
	test_mixed_text();
	test_empty_string();
	std::cout << "All unit tests passed.\n";
	return 0;
}
