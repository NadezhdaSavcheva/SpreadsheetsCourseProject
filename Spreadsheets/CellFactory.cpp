#include "CellFactory.h"
#include "IntegerCell.h"
#include "FractionalCell.h"
#include "StringCell.h"
#include "FormulaCell.h"

Cell* cellFactory(const MyString& data, CellType type) {
	switch (type)
	{
	case CellType::Integer:
		return new IntegerCell(data);
	case CellType::Fractional:
		return new FractionalCell(data);
	case CellType::String:
		return new StringCell(data);
	case CellType::Formula:
		return new FormulaCell(data);
	}

	return nullptr;
}