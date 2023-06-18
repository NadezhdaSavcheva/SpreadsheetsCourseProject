#pragma once
#include "Cell.h"

class FormulaCell : public Cell {
private:
    double formulaResult = 0;
public:
    FormulaCell(const MyString& value);
    MyString getValue() const override;
    bool isValidFormula(const MyString& value) const;
    void setValue(const MyString& value) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
    double calculateFormula(const MyString& formula);
};