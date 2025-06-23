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
	
	int numberOfCottages;
	int numberOfCastles;

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

	int getCurrentRent();

	Player* getOwner();
	void setOwner(Player* newOwner);

	int getNumberOfCottages();
	void setNumberOfCottages(int value);

	int getNumberOfCastles();
	void setNumberOfCastles(int value);

	PrintableField* getPrintable() override;
};