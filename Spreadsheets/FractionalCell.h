#pragma once
#include "Cell.h"

class FractionalCell : public Cell {
private:
    double value;

    double getNumericValue() const;
public:
    FractionalCell(const MyString& data);
    bool isValidFractionalNumber(const MyString& data) const;
    MyString getValue() const override;
    void setValue(const MyString& data) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
};