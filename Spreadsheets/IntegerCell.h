#pragma once
#include "Cell.h"

class IntegerCell : public Cell {
private:
    int value;

    bool isValidInteger() const;
    double getNumericValue() const;
public:
    MyString getValue() const override;
    void setValue(const MyString& value) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
};