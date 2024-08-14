#ifndef CEASOR_H
#define CEASOR_H

#include <string>

typedef std::string string;

/**
 * @file Ceasor.h
 * @brief Utility functions for generating random keys and performing Caesar cipher encryption/decryption.
 * @details This header provides functions to generate a random key and perform Caesar cipher encryption and decryption on strings.
 */

/**
 * @brief Generates a random key for Caesar cipher encryption.
 * @return A random integer between 1 and 26.
 */
int getRandomKey();

/**
 * @brief Encrypts a string using the Caesar cipher algorithm.
 * @param input_str The string to be encrypted.
 * @param key The encryption key.
 * @return The encrypted string.
 */
string ceasorEncrypt(string input_str, int key);

/**
 * @brief Decrypts a string using the Caesar cipher algorithm.
 * @param input_str The string to be decrypted.
 * @param key The decryption key.
 * @return The decrypted string.
 */
string ceasorDecrypt(string input_str, int key);

#endif // CEASOR_H
