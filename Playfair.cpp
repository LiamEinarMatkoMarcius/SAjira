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
void printencryptedMessage(const vector<array<int, 2>>& encryptedMessage, string state) {
	cout << "" << state << endl;
	for (const auto& pair : encryptedMessage) {
		cout << pair[0] << " " << pair[1] << " ";
	}
	cout << endl;
}
pair<int, int> getCoordinates(int keyMatrix[16][16], int target) {
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 16; ++j) {
			if (keyMatrix[i][j] == target) {
				return { i, j }; 
			}
		}
	}
	return { -1, -1 };
}
void writeEncryptedToFileAscii(const vector<array<int, 2>>& encryptedMessage, const string& filename) {
	ofstream outputFile(filename);

	if (!outputFile.is_open()) {
		cerr << "Error opening file!" << endl;
		return;
	}

	for (const auto& pair : encryptedMessage) {
		outputFile << static_cast<char>(pair[0]) << static_cast<char>(pair[1]);
	}

	outputFile.close();
}
vector<array<int, 2>> encrypt(string message, int keymatrix[16][16]) {
	vector<array<int, 2>> procMessage; 
	vector<array<int, 2>> encryptedMessage;
 
	int i = 0;
	while (i < message.length()) {
		char first = message[i];
		char second;
 
		if (i + 1 >= message.length()) {
			second = 3; 
			i++;
		}
		else if (message[i] == message[i + 1]) {
			second = 0; 
			i++;
		}
		else {
			second = message[i + 1];
			i += 2;
		}
		procMessage.push_back({ { static_cast<int>(first), static_cast<int>(second) } });
 
	}
	printencryptedMessage(procMessage, "po preprocesiranju ");
	//šifriranje parov
	for (const array<int, 2>&a : procMessage) {
		//   i    j
		pair<int, int> first = getCoordinates(keymatrix, a[0]); // vrstica - stolpec
		//   k    f
		pair<int, int> second = getCoordinates(keymatrix, a[1]);
		if (first.first == second.first) { // enaka vrstica
			int newChar1 = keymatrix[first.first][(first.second + 1) % 16];
			int newChar2 = keymatrix[second.first][(second.second + 1) % 16];
			encryptedMessage.push_back({ newChar1, newChar2 });
		}
		else if (first.second == second.second) { // enak stolpec
			int newChar1 = keymatrix[(first.first + 1) % 16][first.second];
			int newChar2 = keymatrix[(second.first + 1) % 16][second.second];
			encryptedMessage.push_back({ newChar1, newChar2 });
		}
		else { // razlicna vrstica in stolpec
 
			int newChar1 = keymatrix[first.first][second.second];
			int newChar2 = keymatrix[second.first][first.second];
 
			encryptedMessage.push_back({ newChar1, newChar2 });
		}
	}
	printencryptedMessage(encryptedMessage, "po šifriranju parov");
	return encryptedMessage;
 }
int main(int argc, const char* argv[]) {
    
}