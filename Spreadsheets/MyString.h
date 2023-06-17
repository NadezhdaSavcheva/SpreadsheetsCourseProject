#include <iostream>
#pragma once

class MyString
{
	static const short SSO_MAX_SIZE = sizeof(char*) + sizeof(size_t) - 1;

	union
	{
		struct
		{
			char* _data;
			size_t _size;
		};
		char ssoData[MyString::SSO_MAX_SIZE + 1]{ '\0' };
	};

	bool isSso() const;
	void move(MyString&& other);
	void copyFrom(const MyString& other);
	void free();

	explicit MyString(size_t size);

	void notUsingSso();

	size_t findChar(char ch) const;
public:

	MyString();
	MyString(const char* data);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	MyString& operator+=(const MyString& other);
	MyString& operator+=(char ch);

	const char* c_str() const;
	size_t length() const;
	size_t size() const;
	bool empty() const;
	void clear();
	char front() const;
	char back() const;
	size_t find(char c, size_t pos = 0) const;
	size_t find_first_of(const MyString& str, size_t pos = 0) const;
	size_t find_last_of(const MyString& str, size_t pos = npos) const;
	size_t find_first_not_of(const MyString& str, size_t pos = 0) const;
	size_t find_last_not_of(const MyString& str, size_t pos = npos) const;
	MyString substr(size_t pos = 0, size_t len = npos) const;

	static constexpr auto npos{ static_cast<size_t>(-1) };


	char& operator[](size_t index);
	char operator[](size_t index) const;

	~MyString();

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& getline(std::istream& is, MyString& str, char delimiter);
};

std::ostream& operator<<(std::ostream& os, const MyString& obj);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);