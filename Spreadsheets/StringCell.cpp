#include "StringCell.h"
#include "MyString.h"

//static const char specialSymbols[] = { '\'', '\"', '\\' };

bool StringCell::isValidString(const MyString& data) const {
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

MyString StringCell::getValue() const {
	return data;
}

void StringCell::setValue(const MyString& value) {
	if (!isValidString(value))
		throw;

	data = data.substr(1, value.length() - 2);
}

CellType StringCell::getCellType() const {
	return CellType::String;
}

bool StringCell::isNumeric() const {
	return false;
}