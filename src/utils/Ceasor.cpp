#include "../include/Ceasor.h"
#include <ctime>
#include <cctype>

int getRandomKey() {
    srand(time(NULL));
    return rand() % 26 + 1;
}

string ceasorEncrypt(string input_str, int key) {
    string cipher_str = "";
    for (char c : input_str) {
        if (isalpha(c)) {
            if (isupper(c)) cipher_str += (c - 'A' + key) % 26 + 'A';
            else cipher_str += (c - 'a' + key) % 26 + 'a';
        }
        else cipher_str += c;
    }
    return cipher_str;
}

string ceasorDecrypt(string input_str, int key) {
    string cipher_str = "";
    for (char c : input_str) {
        if (isalpha(c)) {
            if (isupper(c)) cipher_str += (c - 'A' - key) % 26 + 'A';
            else cipher_str += (c - 'a' - key) % 26 + 'a';
        }
        else cipher_str += c;
    }
    return cipher_str;
}
