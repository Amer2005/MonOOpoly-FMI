#pragma once
#include "Field.h"
class StartField : public Field
{
private:

public:
	StartField(int index);

	PrintableField* getPrintable() const override;
};
