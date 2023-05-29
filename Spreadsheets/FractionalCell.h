#pragma once
#include "Cell.h"

class FractionalCell : public Cell {
private:
    double value;

    bool isValidFractionalNumber() const;
    double getNumericValue() const;
public:
    MyString getValue() const override;
    void setValue(const MyString& value) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
};