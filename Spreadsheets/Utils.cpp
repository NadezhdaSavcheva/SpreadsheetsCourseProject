#include "Utils.h"
#include <fstream>
#include <sstream>

bool isDigit(char character) {
    return (character >= '0' && character <= '9');
}

bool isArithmeticOperator(char character) {
    return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^') ? true : false;
}

int toInteger(const MyString& value) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (value.front() == '-') {
        sign = -1;
        i = 1;
    }

    while (value[i] != '\0') {
        if (isDigit(value[i])) {
            int digit = value[i] - '0';

            result = result * 10 + digit;
        }
        else {
            throw;
        }

        i++;
    }
    return sign * result;
}

double toDouble(const MyString& value) {
    double result = 0.0;
    double sign = 1.0;
    double decimal = 0.0;
    int i = 0;

    while (value[i] == ' ')
        i++;

    if (value[i] == '-' || value[i] == '+') {
        if (value[i] == '-')
            sign = -1.0;
        i++;
    }

    while (isDigit(value[i])) {
        result = result * 10.0 + (value[i] - '0');
        i++;
    }

    if (value[i] == '.') {
        i++;
        double factor = 0.1;
        while (isDigit(value[i])) {
            if (!isDigit(value[i]))
                throw;

            decimal += (value[i] - '0') * factor;
            factor /= 10.0;
            i++;
        }
    }
    result = result * sign + decimal;

    return result;
}

bool isNotNumber(const MyString& value) {
    if (value.empty())
        return true;

    bool hasDigit = false;
    bool hasSign = false;
    bool hasDecimal = false;

    for (size_t i = 0; i < value.length(); ++i) {
        char c = value[i];

        if (c == '+' || c == '-') {
            if (hasSign || hasDigit || hasDecimal)
                return true;
            hasSign = true;
        }
        else if (c == '.') {
            if (hasDecimal || !hasDigit)
                return true;
            hasDecimal = true;
        }
        else if (c >= '0' && c <= '9') {
            hasDigit = true;
        }
        else {
            return true;
        }
    }

    return !hasDigit;
}

bool isNaN(double number) {
    return number != number;
}

bool isInteger(const MyString& value) {
    if (value.empty()) {
        return false;
    }

    size_t pos = 0;
    if (value[pos] == '+' || value[pos] == '-') {
        ++pos;
    }

    while (pos < value.length()) {
        if (!isDigit(value[pos])) {
            return false;
        }
        ++pos;
    }

    return true;
}

bool isFractional(const MyString& data) {
    if (data.empty()) {
        return false;
    }

    size_t pos = 0;
    if (data[pos] == '+' || data[pos] == '-') {
        ++pos;
    }

    bool dotFound = false;
    while (pos < data.length()) {
        if (data[pos] == '.') {
            if (dotFound) {
                return false;
            }
            dotFound = true;
        }
        else if (!isDigit(data[pos])) {
            return false;
        }
        ++pos;
    }

    return dotFound;
}

bool isFormula(const MyString& value) {
    size_t stringSize = value.length();
    if (stringSize == 0 || value[0] != '=')
        return false;

    for (size_t i = 1; i < stringSize; i++) {
        char ch = value[i];

        if (!isArithmeticOperator(ch))
            continue;

        if (isDigit(ch) || ch == '.')
            continue;

        if (ch == 'R' && i < stringSize - 1 && isDigit(value[i + 1])) {
            i++;
            continue;
        }

        if (ch == 'C' && i < stringSize - 1 && isDigit(value[i + 1])) {
            i++;
            continue;
        }

        return false;
    }

    return true;
}

bool isString(const MyString& data) {
    size_t stringSize = data.length();

    if (data[0] != '\"' || data[stringSize - 1] != '\"')
        return false;

    for (size_t i = 0; i < stringSize; i++) {
        if (data[i] == '\'' || data[i] == '\"' || data[i] == '\\') {
            if (data[i - 1] != '\\')
                return false;
        }
    }

    return true;
}

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
    size_t currentPosition = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    if (!ifs.is_open())
        return 0;

    unsigned int count = 0;

    while (true) {
        char current = ifs.get();
        if (ifs.eof())
            break;

        if (current == ch)
            count++;
    }

    ifs.clear();
    ifs.seekg(currentPosition);
    return count;
}
unsigned getLinesCount(const char* fileName)
{
    std::ifstream myFile(fileName);

    if (!myFile.is_open())
        return 0;

    return getCharCountFromFile(myFile, '\n') + 1;
}

MyString trimString(const MyString& str) {
    size_t first = str.find_first_not_of(" ");

    if (first == MyString::npos)
        return "";

    size_t last = str.find_last_not_of(" ");

    return str.substr(first, last - first + 1);
}