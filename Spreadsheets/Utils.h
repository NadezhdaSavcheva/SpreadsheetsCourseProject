#pragma once
#include "MyString.h"

bool isDigit(char character);
bool isArithmeticOperator(char character);
int toInteger(const MyString& value);
double toDouble(const MyString& value);
bool isNotNumber(const MyString& value);
bool isNaN(double number);
template <typename T>
MyString toString(const T& data);