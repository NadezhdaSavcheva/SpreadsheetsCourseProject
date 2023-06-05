#include "FractionalCell.h"
#include "Utils.h"

double FractionalCell::getNumericValue() const {
    try {
        return toDouble(data);
    }
    catch (const std::exception&) {
        // Invalid conversion
    }
}

FractionalCell::FractionalCell(const MyString& data) : Cell(data, CellType::Fractional) {
	setValue(data);
}

bool FractionalCell::isValidFractionalNumber(const MyString& data) const {
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

MyString FractionalCell::getValue() const {
	return data;
}

void FractionalCell::setValue(const MyString& data) {
	if (!isValidFractionalNumber(data))
		throw;

	value = toDouble(data);
}

CellType FractionalCell::getCellType() const {
    return CellType::Fractional;
}

bool FractionalCell::isNumeric() const {
    return true;
}