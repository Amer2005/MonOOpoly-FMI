#pragma once
#include "Field.h"
#include "MyString.h"
#include "Player.h"
#include "PrintableField.h"

class PropertyField : public Field
{
private:
	int price;
	int defaultRent;
	int cottagePrice;
	int castlePrice;

	MyString color;
	Player* owner = nullptr;

public:

	PropertyField(int index, const MyString& name,
		const MyString& color, 
		int price, int defaultRent, int cottagePrice, int castlePrice);

	int getPrice();
	int getDefaultRent();
	int getCottagePrice();
	int getCastlePrice();

	Player* getOwner();
	void setOwner(Player* newOwner);

	PrintableField* getPrintable() const override;
};