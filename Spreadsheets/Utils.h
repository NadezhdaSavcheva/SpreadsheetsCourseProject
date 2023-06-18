#pragma once
#include "MyString.h"

bool isDigit(char character);
bool isArithmeticOperator(char character);
int toInteger(const MyString& value);
double toDouble(const MyString& value);
bool isNotNumber(const MyString& value);
bool isNaN(double number);
bool isInteger(const MyString& value);
bool isFractional(const MyString& data);
bool isFormula(const MyString& value);
bool isString(const MyString& data);
unsigned getCharCountFromFile(std::ifstream& ifs, char ch);
unsigned getLinesCount(const char* fileName);
MyString trimString(const MyString& str);