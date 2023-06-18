#include "IntegerCell.h"
#include "Utils.h"

int IntegerCell::getNumericValue() const {
    try {
        return toInteger(data);
    }
    catch (const std::exception& exc) {
        std::cout << "Invalid conversion" << std::endl;
    }
}

IntegerCell::IntegerCell(const MyString& data) : Cell(data, CellType::Integer) {
    setValue(data);
}

bool IntegerCell::isValidInteger(const MyString& value) const {
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

MyString IntegerCell::getValue() const {
    return data;
}

void IntegerCell::setValue(const MyString& data) {
    if (!isValidInteger(data))
        throw;

    value = toInteger(data);
    cellType = CellType::Integer;
}

CellType IntegerCell::getCellType() const {
    return CellType::Integer;
}

bool IntegerCell::isNumeric() const {
    return true;
}