#include "CellFactory.h"
#include "IntegerCell.h"
#include "FractionalCell.h"
#include "StringCell.h"
#include "FormulaCell.h"

Cell* cellFactory(CellType type) {
	switch (type)
	{
	case CellType::Integer:
		return new IntegerCell();
	case CellType::Fractional:
		return new FractionalCell();
	case CellType::String:
		return new StringCell();
	case CellType::Formula:
		return new FormulaCell();
	}

	return nullptr;
}