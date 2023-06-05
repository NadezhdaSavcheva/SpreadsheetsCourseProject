#pragma once
#include "Cell.h"

class IntegerCell : public Cell {
private:
    int value;

    int getNumericValue() const;
public:
    IntegerCell(const MyString&);
    bool isValidInteger(const MyString&) const;
    MyString getValue() const override;
    void setValue(const MyString&) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
};