#pragma once
#include "Cell.h"

class FormulaCell : public Cell {
private:
    MyString expression;

    bool isValidFormula() const;
public:
    MyString getValue() const override;
    void setValue(const MyString& value) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
    double calculateFormula(const MyString& expression);
};