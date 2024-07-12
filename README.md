<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <div class="container">
        <h1>Playfair Cipher</h1>
        <p>This C++ program encrypts text using the Playfair cipher with a fixed keyword.</p>
        <h2>Code</h2>
        <pre class="code">
#include &lt;iostream&gt;
#include &lt;cctype&gt;
#include &lt;cstring&gt;
#include &lt;algorithm&gt;
#include &lt;string&gt;

// Function to remove duplicate characters from a string
std::string remove_duplicate_chars(const std::string&amp; key) {
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
        std::cerr &lt;&lt; "Error: Unexpected issue in generating the Playfair matrix." &lt;&lt; std::endl;
        exit(EXIT_FAILURE);
    }

    // Fill the 5x5 Playfair matrix with the key and remaining alphabet letters
    for (size_t i = 0, k = 0; i &lt; 5; ++i) {
        for (size_t j = 0; j &lt; 5; ++j, ++k) {
            play_fair_matrix[i][j] = key_without_duplicates[k];
        }
    }
}

// Function to find the positions of two characters in the Playfair matrix
void find_positions(const char play_fair_matrix[5][5], char ch, size_t&amp; row, size_t&amp; col) {
    for (size_t i = 0; i &lt; 5; ++i) {
        for (size_t j = 0; j &lt; 5; ++j) {
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
std::string play_fair_encrypt(const std::string&amp; plain_text, const char play_fair_matrix[5][5]) {
    std::string cipher_text;
    for (size_t i = 0; i &lt; plain_text.length(); i += 2) {
        char a = std::toupper(plain_text[i]);
        char b = (i + 1 &lt; plain_text.length()) ? std::toupper(plain_text[i + 1]) : 'X';

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
    std::cout &lt;&lt; "Enter the text to encrypt: ";
    std::getline(std::cin, plain_text);

    // Convert the plaintext to uppercase
    std::transform(plain_text.begin(), plain_text.end(), plain_text.begin(), ::toupper);

    // Remove non-alphabetic characters from the plaintext
    plain_text.erase(std::remove_if(plain_text.begin(), plain_text.end(), [](unsigned char c) { return !std::isalpha(c); }), plain_text.end());

    // Encrypt the plaintext using the Playfair cipher
    std::string cipher_text = play_fair_encrypt(plain_text, play_fair_matrix);

    // Print the encrypted text to the console
    std::cout &lt;&lt; "Encrypted text: " &lt;&lt; cipher_text &lt;&lt; std::endl;

    return 0;
}
        </pre>
        <h2>Usage</h2>
        <p>To use this program, follow these steps:</p>
        <ol>
            <li>Compile the program using a C++ compiler (e.g., <code>g++ PlayfairCipher.cpp -o PlayfairCipher</code>).</li>
            <li>Run the executable (e.g., <code>./PlayfairCipher</code>).</li>
            <li>Enter the text you want to encrypt when prompted.</li>
            <li>The program will output the encrypted text using the Playfair cipher.</li>
        </ol>
        <h2>Output</h2>
        <p>When you run the program and enter the text to encrypt, it will display the encrypted text in the console.</p>
    </div>
</body>
</html>
