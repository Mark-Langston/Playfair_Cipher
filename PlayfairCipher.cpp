#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>

// Function to remove duplicate characters from a string
std::string remove_duplicate_chars(const std::string& key) {
    std::string result;
    for (char c : key) {
        if (result.find(c) == std::string::npos) {
            result += c;
        }
    }
    return result;
}

// Function to generate the Playfair matrix with an automatically assigned keyword
void generate_auto_play_fair_matrix(char play_fair_matrix[5][5]) {
    // Fixed keyword
    std::string fixed_keyword = "KEYWORD";

    // Remove duplicate characters from the fixed keyword and add the remaining alphabet letters
    std::string key_without_duplicates = remove_duplicate_chars(fixed_keyword + "ABCDEFGHIKLMNOPQRSTUVWXYZ");

    // Ensure the size is exactly 25 characters
    if (key_without_duplicates.size() != 25) {
        std::cerr << "Error: Unexpected issue in generating the Playfair matrix." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Fill the 5x5 Playfair matrix with the key and remaining alphabet letters
    for (size_t i = 0, k = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j, ++k) {
            play_fair_matrix[i][j] = key_without_duplicates[k];
        }
    }
}

// Function to find the positions of two characters in the Playfair matrix
void find_positions(const char play_fair_matrix[5][5], char ch, size_t& row, size_t& col) {
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (play_fair_matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of characters using the Playfair cipher rules
std::string encryptPair(const char play_fair_matrix[5][5], char a, char b) {
    size_t rowA, colA, rowB, colB;
    find_positions(play_fair_matrix, a, rowA, colA);
    find_positions(play_fair_matrix, b, rowB, colB);

    if (rowA == rowB) {
        return std::string(1, play_fair_matrix[rowA][(colA + 1) % 5]) +
            std::string(1, play_fair_matrix[rowB][(colB + 1) % 5]);
    }
    else if (colA == colB) {
        return std::string(1, play_fair_matrix[(rowA + 1) % 5][colA]) +
            std::string(1, play_fair_matrix[(rowB + 1) % 5][colB]);
    }
    else {
        return std::string(1, play_fair_matrix[rowA][colB]) +
            std::string(1, play_fair_matrix[rowB][colA]);
    }
}

// Function to encrypt text using the Playfair cipher
std::string play_fair_encrypt(const std::string& plain_text, const char play_fair_matrix[5][5]) {
    std::string cipher_text;
    for (size_t i = 0; i < plain_text.length(); i += 2) {
        char a = std::toupper(plain_text[i]);
        char b = (i + 1 < plain_text.length()) ? std::toupper(plain_text[i + 1]) : 'X';

        // Since I and J are considered the same letter
        if (a == 'J') a = 'I';
        if (b == 'J') b = 'I';

        // Check if the characters are the same, and handle accordingly
        if (a != b) {
            cipher_text += encryptPair(play_fair_matrix, a, b);
        }
        else {
            cipher_text += encryptPair(play_fair_matrix, a, 'X');
        }
    }
    return cipher_text;
}

int main() {
    char play_fair_matrix[5][5];
    generate_auto_play_fair_matrix(play_fair_matrix);

    std::string plain_text;
    std::cout << "Enter the text to encrypt: ";
    std::getline(std::cin, plain_text);

    // Convert the plaintext to uppercase
    std::transform(plain_text.begin(), plain_text.end(), plain_text.begin(), ::toupper);

    // Remove non-alphabetic characters from the plaintext
    plain_text.erase(std::remove_if(plain_text.begin(), plain_text.end(), [](unsigned char c) { return !std::isalpha(c); }), plain_text.end());

    // Encrypt the plaintext using the Playfair cipher
    std::string cipher_text = play_fair_encrypt(plain_text, play_fair_matrix);

    // Print the encrypted text to the console
    std::cout << "Encrypted text: " << cipher_text << std::endl;

    return 0;
}
