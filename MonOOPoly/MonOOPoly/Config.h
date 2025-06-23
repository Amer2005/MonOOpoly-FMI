#pragma once

class Config {
public:
    static const int MaxPlayers;
    static const int MinPlayers;

    static const int FieldWidth;
    static const int FieldHeight;

    static const int StartingMoney;
    static const int MoneyGivenOnStartField;
    
    static const char* SaveFilePath;
    static const char* FieldsFilePath;

    static const int BoardWidth;
    static const int BoardHeight;

    static const int MaxNumberOfCottages;
    static const int MaxNumberOfCastles;

    static const int CottagePriceIncreasePercentage;
    static const int CastlePriceIncreasePercentage;

    static const int MoneyChangeMaxCardAmount;
    static const int TakeMoneyAmount;

    static const int NumberOfCardsInDeck;

    static const int JailBailCost;
};