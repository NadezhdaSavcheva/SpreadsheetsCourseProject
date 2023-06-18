#include "FormulaCell.h"
#include "Utils.h"
#include <sstream>
#include "Vector.hpp"

template <typename T>
MyString toString(const T& data) {
    std::ostringstream oss;
    oss << data;
    return oss.str().c_str();
}

FormulaCell::FormulaCell(const MyString& value) : Cell(value, CellType::Formula) {}

MyString FormulaCell::getValue() const {
    if (isNaN(formulaResult))
        return "Error";

    MyString result;
    result = toString<double>(formulaResult);

    return result;
}

bool FormulaCell::isValidFormula(const MyString& value) const {
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

void FormulaCell::setValue(const MyString& value) {
	if (!isValidFormula(value))
		throw;

	data = value;
    cellType = CellType::Formula;
}

CellType FormulaCell::getCellType() const {
	return CellType::Formula;
}

bool FormulaCell::isNumeric() const {
	return false;
}

double FormulaCell::calculateFormula(const MyString& formula) {
    return 0.0;
}