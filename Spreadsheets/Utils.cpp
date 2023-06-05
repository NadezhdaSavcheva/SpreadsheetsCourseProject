#include "Utils.h"
#include <sstream>

bool isDigit(char character)
{
    return (character >= '0' && character <= '9');
}

bool isArithmeticOperator(char character)
{
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

template <typename T>
MyString toString(const T& data) {
    MyString result;

    std::stringstream temp;
    temp << data;
    result = temp.str();

    return result;
}
