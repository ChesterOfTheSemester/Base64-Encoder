#include <iostream>
#include <string>

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string stringToBase64(const std::string &input)
{
    std::string result;
    size_t inputLength = input.length();

    for (size_t i=0; i<inputLength; i+=3) {
        uint32_t octetA = i < inputLength ? static_cast<uint8_t>(input[i]) : 0;
        uint32_t octetB = i + 1 < inputLength ? static_cast<uint8_t>(input[i + 1]) : 0;
        uint32_t octetC = i + 2 < inputLength ? static_cast<uint8_t>(input[i + 2]) : 0;

        uint32_t triple = (octetA << 16) + (octetB << 8) + octetC;

        result += base64_chars[(triple >> 18) & 0x3F];
        result += base64_chars[(triple >> 12) & 0x3F];
        result += base64_chars[(triple >> 6) & 0x3F];
        result += base64_chars[triple & 0x3F];
    }

    // Handle padding
    size_t padding = 3 - (inputLength % 3);
    if (padding != 3)
        for (size_t i = 0; i < padding; i++) {
            result.pop_back(); // Remove extra characters
            result += '=';
        }

    return result;
}
