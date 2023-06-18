#include "MyString.h"
#include <cstring>
#pragma warning (disable : 4996)

MyString::MyString() : MyString("") { }

MyString::MyString(size_t size)
{
	_data = new char[size + 1];
	this->_size = size;
}

MyString::MyString(const char* data)
{
	size_t currentSize = strlen(data);

	if (currentSize <= MyString::SSO_MAX_SIZE) //SSO
	{
		ssoData[MyString::SSO_MAX_SIZE] = MyString::SSO_MAX_SIZE - currentSize;
		strcpy(ssoData, data);
	}
	else
	{
		_size = currentSize;
		_data = new char[_size + 1];
		strcpy(_data, data);
		notUsingSso();
	}
}
void MyString::notUsingSso()
{
	ssoData[MyString::SSO_MAX_SIZE] |= (1 << 7);
}

MyString::MyString(MyString&& other) noexcept
{
	move(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}

	return *this;
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void MyString::move(MyString&& other) {
	_data = other._data;
	_size = other._size;

	if (!other.isSso())
	{
		other._data = nullptr;
		notUsingSso();
	}
}

void MyString::free()
{
	if (!isSso())
		delete[] _data;
	_data = nullptr;
}
MyString::~MyString()
{
	free();
}

bool MyString::isSso() const
{
	return (ssoData[MyString::SSO_MAX_SIZE] & (1 << 7)) == 0;
}

size_t MyString::findChar(char ch) const {
	for (size_t i = 0; i < length(); i++) {
		if (c_str()[i] == ch) {
			return i;
		}
	}

	return npos;
}

const char* MyString::c_str() const
{
	return isSso() ? ssoData : _data;
}

size_t MyString::length() const
{
	if (isSso())
	{
		return MyString::SSO_MAX_SIZE - ssoData[MyString::SSO_MAX_SIZE];
	}
	else
	{
		size_t realSize = _size;
		size_t mask = 1;
		mask = ~(mask << (sizeof(_size) * 8 - 1));
		return realSize & mask;
	}
}

size_t MyString::size() const
{
	size_t count = 0;
	const char* strPtr = c_str();

	while (*strPtr != '\0') {
		++count;
		++strPtr;
	}

	return count;
}

bool MyString::empty() const
{
	return length() == 0;
}

void MyString::clear() {
	if (isSso()) {
		ssoData[0] = '\0';
		ssoData[MyString::SSO_MAX_SIZE] = MyString::SSO_MAX_SIZE;
	}
	else {
		delete[] _data;
		_data = new char[1];
		_data[0] = '\0';
		_size = 0;
		notUsingSso();
	}
}

char MyString::front() const
{
	return c_str()[0];
}

char MyString::back() const
{
	return c_str()[length() - 1];
}

size_t MyString::find(char c, size_t pos) const {
	size_t length = size();
	if (pos >= length) {
		return MyString::npos;
	}

	for (size_t i = pos; i < length; ++i) {
		if (operator[](i) == c) {
			return i;
		}
	}

	return MyString::npos;
}

size_t MyString::find_first_of(const MyString& str, size_t pos) const
{
	size_t length = str.length();
	if (pos >= length) {
		return npos;
	}

	for (size_t i = pos; i < length; i++) {
		if (findChar(str[i]) != npos) {
			return i;
		}
	}

	return npos;
}

size_t MyString::find_last_of(const MyString& str, size_t pos) const
{
	if (length() == 0 || str.length() == 0) {
		return npos;
	}

	if (pos >= length()) {
		pos = length() - 1;
	}

	for (int i = static_cast<int>(pos); i >= 0; i--) {
		if (str.findChar(c_str()[i]) != npos) {
			return static_cast<size_t>(i);
		}
	}

	return npos;
}

size_t MyString::find_first_not_of(const MyString& str, size_t pos) const
{
	size_t length = str.length();
	if (pos >= length) {
		return MyString::npos;
	}

	for (size_t i = pos; i < length; ++i) {
		if (find(str[i]) == MyString::npos) {
			return i;
		}
	}

	return std::string::npos;
}

size_t MyString::find_last_not_of(const MyString& str, size_t pos) const
{
	if (length() == 0) {
		return npos;
	}

	if (pos >= length()) {
		pos = length() - 1;
	}

	for (int i = static_cast<int>(pos); i >= 0; i--) {
		if (str.findChar(c_str()[i]) == npos) {
			return static_cast<size_t>(i);
		}
	}

	return npos;
}

MyString MyString::substr(size_t pos, size_t len) const
{
	if (pos >= length()) {
		return MyString();
	}

	if (len == npos || pos + len > length()) {
		len = length() - pos;
	}

	char* substrData = new char[len + 1];
	strncpy(substrData, c_str() + pos, len);
	substrData[len] = '\0';

	MyString substr(substrData);
	delete[] substrData;

	return substr;
}

void MyString::copyFrom(const MyString& other)
{
	if (!other.isSso())
	{
		_data = new char[other.length() + 1];
		strcpy(_data, other._data);
		_size = other._size;
	}
	else
	{
		strcpy(ssoData, other.ssoData);
		ssoData[MyString::SSO_MAX_SIZE] = other.ssoData[MyString::SSO_MAX_SIZE]; //copy the size
	}
}

MyString& MyString::operator+=(const MyString& other)
{
	size_t newStrSize = length() + other.length();

	if (newStrSize <= MyString::SSO_MAX_SIZE)
	{ //sso is aplied in the current object
		strcat(ssoData, other.ssoData);
		ssoData[MyString::SSO_MAX_SIZE] = MyString::SSO_MAX_SIZE - newStrSize;
	}
	else
	{
		char* newData = new char[newStrSize + 1] {'\0'};

		strcpy(newData, c_str());
		strcat(newData, other.c_str());

		if (!isSso())
			delete[] _data;
		_data = newData;
		_size = newStrSize;
		notUsingSso();
	}

	return *this;
}

MyString& MyString::operator+=(char ch) {
	// Convert the character to a string
	MyString str(1);
	str[0] = ch;
	str[1] = '\0';

	// Concatenate the character string to the current string
	*this += str;

	return *this;
}

char& MyString::operator[](size_t index)
{
	return isSso() ? ssoData[index] : _data[index];
}

char MyString::operator[](size_t index) const
{
	return isSso() ? ssoData[index] : _data[index];
}
std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
	return os << obj.c_str();
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	size_t newStrSize = lhs.length() + rhs.length();

	if (newStrSize <= MyString::SSO_MAX_SIZE)
	{
		MyString res(lhs);
		res += rhs;
		return res;
	}
	else
	{
		MyString res(newStrSize + 1);
		strcpy(res._data, lhs.c_str());
		strcat(res._data, rhs.c_str());
		res.notUsingSso();
		return res;
	}
}

std::istream& operator>>(std::istream& is, MyString& obj) {
	char buff[1024];
	is >> buff; // is.getLine(buff, 1024);

	delete[] obj._data;
	obj._size = strlen(buff);
	obj._data = new char[obj._size + 1];
	strcpy(obj._data, buff);
	return is;
}

std::istream& getline(std::istream& is, MyString& str, char delimiter = '\n')
{
	// Clear the existing string
	str.clear();

	// Read characters from the input stream until the delimiter is encountered or end-of-file is reached
	char ch;
	while (is.get(ch) && ch != delimiter) {
		str += ch;
	}

	return is;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}
