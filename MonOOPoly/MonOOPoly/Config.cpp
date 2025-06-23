#include "Config.h"

//CHANGING ANYTHING HERE MAKES SAVE FILES INCOMPATIBLE

const char* Config::FieldsFilePath = "Fields.txt";
const char* Config::SaveFilePath = "Save.txt";

const int Config::MaxPlayers = 6;
const int Config::MinPlayers = 2;

const int Config::StartingMoney = 1500;
const int Config::MoneyGivenOnStartField = 200;

const int Config::FieldWidth = 11;
const int Config::FieldHeight = 4;

const int Config::BoardWidth = 9;
const int Config::BoardHeight = 5;

const int Config::MaxNumberOfCottages = 4;
const int Config::MaxNumberOfCastles = 1;

const int Config::CottagePriceIncreasePercentage = 15;
const int Config::CastlePriceIncreasePercentage = 50;

const int Config::MoneyChangeMaxCardAmount = 200;
const int Config::TakeMoneyAmount = 100;

const int Config::NumberOfCardsInDeck = 30;