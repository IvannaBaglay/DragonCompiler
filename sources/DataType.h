#pragma once
#include <iostream>
#include <sstream>
#include "Word.h"

class DataType : public Word
{
public:
	DataType(std::string str, Tag t, int w);
	virtual ~DataType(void);
	bool operator==(const DataType& rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const DataType& type);
	static DataType* TypeSIGNAL;
	static DataType* TypeINTEGER;
	static DataType* TypeFLOATS;
	static DataType* TypeBLOCKFLOAT;
	static DataType* TypeCOMPLEX;
	static DataType* TypeEXT;
	int d_width;
};