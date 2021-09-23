/*******************************************************************************
 * Name    : unique.cpp
 * Author  : Jason Rossi
 * Version : 1.0
 * Date    : September 24, 2020
 * Description : Determines if the input is all lowercase and has unique letters.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
	int length = s.length();
	for (int i = 0; i<length; i++) {
		if (isupper(s[i]) || isdigit(s[i])) {
			return false;
		}
	}
	return true;
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
}

bool all_unique_letters(const string &s) {
	unsigned int vector = 0;
	unsigned int setter;
	int length = s.length();
	for (int i = 0; i < length; i++) {
		setter = 1 << (s[i] - 'a');
		if ((vector & setter) != 0) {
			return false;
		}
		else
		{
			vector = vector | setter;
		}
	}
	return true;

    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
}

int main(int argc, char * const argv[]) {
	if (argc != 2) {
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}
	if (is_all_lowercase(argv[1]) == false) {
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	if (all_unique_letters(argv[1]) == false) {
		cout << "Duplicate letters found." << endl;
	}
	else
	{
		cout << "All letters are unique." << endl;
	}
	return 0;
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
}
