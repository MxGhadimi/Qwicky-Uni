#ifndef CEASOR_H
#define CEASOR_H

#include <string>

typedef std::string string;

int getRandomKey();
string ceasorEncrypt(string input_str, int key);
string ceasorDecrypt(string input_str, int key);

#endif
