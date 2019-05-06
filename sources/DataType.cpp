#include "DataType.h"

DataType* DataType::TypeSIGNAL = new DataType("SIGNAL", BASIC, 1);
DataType* DataType::TypeINTEGER = new DataType("INTEGER", BASIC, 1);
DataType* DataType::TypeEXT = new DataType("EXT", BASIC, 1);
DataType* DataType::TypeFLOATS = new DataType("FLOAT", BASIC, 1);
DataType* DataType::TypeBLOCKFLOAT = new DataType("BLOCKFLOAT", BASIC, 1);
DataType* DataType::TypeCOMPLEX = new DataType("COMPLEX", BASIC, 1);

DataType::DataType(std::string str, Tag t, int w): Word(str, t), d_width(w)
{
}

DataType::~DataType(void)
{
}

bool DataType::operator==(const DataType& rhs) const 
{
	return this->w_lexme.compare(rhs.w_lexme) == 0 && this->d_width == rhs.d_width;
}

std::ostream& operator<<(std::ostream& os, const DataType& type)
{
	os<<"Basic Type: "<<type.w_lexme<<std::endl;
	return os;
}