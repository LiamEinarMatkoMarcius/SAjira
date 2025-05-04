#include <iostream>
#include <string>
#include<vector>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <array>
#include <sstream>
using namespace std;

vector<char> removeDuplicateChar(vector<char>& key) {
	unordered_set<char> seen;
	vector<char> uniqueChars;

	for (char c : key) {
		if (seen.find(c) == seen.end()) {
			seen.insert(c);
			uniqueChars.push_back(c);
		}
	}
	return uniqueChars;
}
void createKeyMatrix(int keyMatrix[16][16], vector<char> key) {
	vector<char> uniqueKey = removeDuplicateChar(key);
	unordered_set<int> used;

	int matrixIndex = 0;

	for (char c : uniqueKey) {
		used.insert(static_cast<unsigned char>(c)); // store ASCII value
		keyMatrix[matrixIndex / 16][matrixIndex % 16] = static_cast<unsigned char>(c);
		matrixIndex++;
	}

	for (int ascii = 0; ascii <= 255 && matrixIndex < 256; ++ascii) {
		if (used.count(ascii)) continue;
		keyMatrix[matrixIndex / 16][matrixIndex % 16] = ascii;
		matrixIndex++;
	}
}
void convertToAsciiString(string& str) {
	string result;
	for (char c : str) {
		result += to_string(static_cast<unsigned char>(c)) + ' ';
	}
	if (!result.empty()) result.pop_back();
	str = result;
}

int main(int argc, const char* argv[]) {
    
}