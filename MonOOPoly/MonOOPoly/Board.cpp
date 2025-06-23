#include "PropertyField.h"
#include "StartField.h"
#include "CardField.h"
#include "GoToJailField.h"
#include "JailField.h"
#include "ParkingField.h"

#include "Board.h"
#include "Field.h"
#include "PrintableField.h"
#include "Config.h"
#include "CardDeck.h"
#include <fstream>
#include <iostream>

Board::Board(const char* loadFromFilePath) {
    int boardHeight = Config::BoardHeight;
    int boardWidth = Config::BoardWidth;
    
    this->numberOfFields = boardWidth * 2 + boardHeight * 2 - 4; //-4 for repeat corner cells

    this->cardDeck = new CardDeck(Config::NumberOfCardsInDeck);

    loadFieldsFromFile(loadFromFilePath);
}

void Board::loadFieldsFromFile(const char* path) {
    std::ifstream file(path);

    try
    {
        if (!file.is_open()) {
            return; 
        }

        this->fields = new Field * [this->numberOfFields] { nullptr };

        int index = 0;
        int type;

        while (index < numberOfFields)
        {
            file >> type;

            Field* curr = nullptr;

            if (type == FieldType::Property)
            {
                MyString name;
                MyString color;
                int price;
                int defaultRent;
                int cottagePrice;
                int castlePrice;

                file >> name;
                file >> color;
                file >> price;
                file >> defaultRent;
                file >> cottagePrice;
                file >> castlePrice;

                curr = new PropertyField(index, name, color, price, defaultRent,
                    cottagePrice, castlePrice);
            }
            else if (type == FieldType::Start)
            {
                curr = new StartField(index);
            }
            else if (type == FieldType::Card)
            {
                curr = new CardField(index);
            }
            else if (type == FieldType::GoToJail)
            {
                curr = new GoToJailField(index);
            }
            else if (type == FieldType::Jail)
            {
                curr = new JailField(index);
            }
            else if (type == FieldType::Parking)
            {
                curr = new ParkingField(index);
            }

            this->fields[index] = curr;
            index++;
        }
    }
    catch (const std::exception&)
    {

    }

    file.close();
}

void Board::printEmptyFieldLine()
{
    for (int i = 0; i < Config::FieldWidth + 2; i++)
    {
        std::cout << " ";
    }
}

void Board::printTopOrBottomOfBoard(PrintableField** printableFields,int index)
{
    for (int i = 0; i < Config::FieldHeight + 2;i++)
    {

        for (int j = 0; j < Config::BoardWidth; j++)
        {
            if (i == 0 || i == Config::FieldHeight + 1)
            {
                printableFields[index + j]->printLine(-1);

                continue;
            }

            printableFields[index + j]->printLine(i - 1);
        }

        std::cout << std::endl;
    }
}

void Board::printSideOfBoard(PrintableField** printableFields, int index)
{
    int currentIndex;

    for (int i = 0; i < Config::FieldHeight + 2;i++)
    {
        for (int j = 0; j < Config::BoardWidth; j++)
        {
            if (j != 0 && j != Config::BoardWidth - 1)
            {
                printEmptyFieldLine();

                continue;
            }

            if (j == 0)
            {
                currentIndex = index;
            }
            else
            {
                currentIndex = index + 1;
            }

            if (i == 0 || i == Config::FieldHeight + 1)
            {

                printableFields[currentIndex]->printLine(-1);

                continue;
            }

            printableFields[currentIndex]->printLine(i - 1);
        }

        std::cout << std::endl;
    }
}

int Board::getCorrectIndex(int index)
{
    if (index < Config::BoardWidth)
    {
        return index;
    }

    if (index < numberOfFields - Config::BoardWidth)
    {
        int newIndex;

        if (index % 2 == Config::BoardWidth % 2)
        {
            newIndex = index - Config::BoardWidth;

            newIndex = numberOfFields - (newIndex / 2) - 1;
        }
        else
        {
            newIndex = (index - Config::BoardWidth - 1) / 2;

            newIndex = Config::BoardWidth + newIndex;
        }

        return newIndex;
    }

    if (index >= numberOfFields - Config::BoardWidth)
    {
        int numberOfPrevFields = Config::BoardWidth + ((Config::BoardHeight - 2) * 2);

        int newIndex = index - numberOfPrevFields;

        newIndex = Config::BoardWidth - newIndex - 1;

        newIndex += Config::BoardHeight + Config::BoardWidth - 2;

        return newIndex;
    }

    return index;
}

CardModel* Board::drawCard()
{
    return this->cardDeck->drawCard();
}

void Board::free()
{
    for (int i = 0; i < numberOfFields; ++i) {
        delete fields[i];
    }
    delete[] fields;

    for (int i = 0; i < playerCount; ++i) {
        delete players[i];
    }
    delete[] players;

    delete cardDeck;
}

void Board::print()
{
    PrintableField** printableFields = new PrintableField* [numberOfFields] {nullptr};

    for (int i = 0; i < numberOfFields; i++)
    {
        int newIndex = getCorrectIndex(i);

        Field* curr = fields[newIndex];

        printableFields[i] = curr->getPrintable();
    }

    int index = 0;
    
    
    printTopOrBottomOfBoard(printableFields, index);

    index += Config::BoardWidth;

    for (int i = 0; i < Config::BoardHeight - 2;i++)
    {
        printSideOfBoard(printableFields, index);
        index += 2;
    }

    printTopOrBottomOfBoard(printableFields, index);

    for (int i = 0; i < numberOfFields; ++i) {
        delete printableFields[i];
    }

    delete[] printableFields;
}

bool Board::getIsGameOver()
{
    return this->isGameOver;
}

void Board::setPlayers(MyString** names, int playerCount)
{
    this->playerCount = playerCount;

    players = new Player* [playerCount] {nullptr};

    for (int i = 0; i < playerCount; i++)
    {
        players[i] = new Player(i, *names[i]);
    }
}

Player* Board::getPlayerByIndex(int index)
{
    if (index < 0)
    {

    }

    return players[index];
}

int Board::getActivePlayerIndex()
{
    return this->activePlayerIndex;
}

void Board::setActivePlayerIndex(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (value >= playerCount)
    {
        value = value % playerCount;
    }

    this->activePlayerIndex = value;
}

Field* Board::getFieldByIndex(int index)
{
    return this->fields[index];
}

int Board::getJailFieldIndex()
{
    for (int i = 0; i < numberOfFields; i++)
    {
        if(fields[i]->getType() == FieldType::Jail)
        {
            return i;
        }
    }

    return 0;
}

void Board::endTurn()
{
    int playerIndex = this->getActivePlayerIndex();

    int startingPlayerIndex = playerIndex;

    do
    {
        playerIndex++;

        playerIndex = playerIndex % playerCount;

        if (!this->players[playerIndex]->getIsResigned())
        {
            break;
        }
    } while (playerIndex != startingPlayerIndex);

    this->setActivePlayerIndex(playerIndex);

    //check for game over
    int numberOfActivePlayers = 0;

    for (int i = 0; i < playerCount; i++)
    {
        if (!players[i]->getIsResigned())
        {
            numberOfActivePlayers++;
        }
    }

    if (numberOfActivePlayers <= 1)
    {
        this->isGameOver = true;
    }
}

int Board::getNumberOfPropertiesOwnedByPlayer(int playerIndex)
{
    int result = 0;

    for (int i = 0; i < numberOfFields; i++)
    {
        Field* curr = fields[i];
        if (curr->getType() == FieldType::Property)
        {
            PropertyField* property = static_cast<PropertyField*>(curr);

            if (property->getOwner() == nullptr)
            {
                continue;
            }

            if (property->getOwner()->getIndex() == playerIndex)
            {
                result++;
            }
        }
    }

    return result;
}

int Board::getPlayerCount()
{
    return this->playerCount;
}

int Board::getFieldCount()
{
    return this->numberOfFields;
}

bool Board::doesPlayerOwnAllPropertiesOfColor(int playerIndex, MyString color)
{
    for (int i = 0; i < numberOfFields; i++)
    {
        Field* curr = fields[i];
        if (curr->getType() == FieldType::Property)
        {
            PropertyField* property = static_cast<PropertyField*>(curr);

            if (property->getColor() != color)
            {
                continue;
            }

            if (property->getOwner() == nullptr)
            {
                return false;
            }

            if (property->getOwner()->getIndex() != playerIndex)
            {
                return false;
            }
        }
    }

    return true;
}

void Board::saveToFile(const char* path)
{
    std::ofstream file(path);

    if (!file.is_open()) return;

    try
    {
        file << this->numberOfFields << " ";
        file << this->playerCount << " ";
        file << this->activePlayerIndex << " ";

        for (int i = 0; i < playerCount; i++)
        {
            Player* player = this->getPlayerByIndex(i);

            file << player->getIsResigned() << " ";
            file << player->getCurrentFieldIndex() << " ";
            file << player->getBalance() << " ";
            file << player->getIsInJail() << " ";
            file << player->getName() << " ";
        }

        for (int i = 0; i < numberOfFields; i++)
        {
            file << fields[i]->getType() << " ";
            file << fields[i]->getName() << " ";

            if (fields[i]->getType() == FieldType::Property)
            {
                PropertyField* property = static_cast<PropertyField*>(fields[i]);

                file << property->getPrice() << " ";
                file << property->getDefaultRent() << " ";
                file << property->getCottagePrice() << " ";
                file << property->getCastlePrice() << " ";

                file << property->getNumberOfCottages() << " ";
                file << property->getNumberOfCastles() << " ";
                file << property->getColor() << " ";

                if (property->getOwner() == nullptr)
                {
                    file << -1 << " ";
                }
                else
                {
                    file << property->getOwner()->getIndex() << " ";
                }
            }
        }
    }
    catch (const std::exception&)
    {

    }

    file.close();
}

void Board::loadFromFile(const char* path)
{
    std::ifstream file(path);

    if (!file.is_open()) return;

    free();

    try
    {
        file >> this->numberOfFields;
        file >> this->playerCount;
        file >> this->activePlayerIndex;

        players = new Player* [playerCount] { nullptr };
        fields = new Field* [numberOfFields] { nullptr };
        cardDeck = new CardDeck(Config::NumberOfCardsInDeck);

        for (int i = 0; i < playerCount; i++)
        {
            bool isResigned = false;

            int currentFieldIndex = 0;

            int balance = 0;

            bool isInJail = false;

            MyString name;

            file >> isResigned;
            file >> currentFieldIndex;
            file >> balance;
            file >> isInJail;
            file >> name;

            Player* player = new Player(i, name);

            player->setIsResigned(isResigned);
            player->setCurrentFieldIndex(currentFieldIndex);
            player->setBalance(balance);
            player->setIsInJail(isInJail);

            players[i] = player;
        }

        for (int i = 0; i < numberOfFields; i++)
        {
            int fieldType;
            MyString name;

            file >> fieldType;

            file >> name;

            Field* result = new ParkingField(i);

            if (fieldType == FieldType::Property)
            {
                delete result;

                int price;
                int defaultRent;
                int cottagePrice;
                int castlePrice;

                int numberOfCottages;
                int numberOfCastles;

                MyString color;

                int ownerIndex;

                file >> price;
                file >> defaultRent;
                file >> cottagePrice;
                file >> castlePrice;

                file >> numberOfCottages;
                file >> numberOfCastles;
                file >> color;
                file >> ownerIndex;

                PropertyField* property = 
                    new PropertyField(i, name, color, price, defaultRent, cottagePrice, castlePrice);
                property->setNumberOfCottages(numberOfCottages);
                property->setNumberOfCastles(numberOfCastles);

                if (ownerIndex != -1)
                {
                    property->setOwner(players[ownerIndex]);
                }

                result = property;
            }
            else if (fieldType == FieldType::Start)
            {
                delete result;
                result = new StartField(i);
            }
            else if (fieldType == FieldType::Card)
            {
                delete result;
                result = new CardField(i);
            }
            else if (fieldType == FieldType::GoToJail)
            {
                delete result;
                result = new GoToJailField(i);
            }
            else if (fieldType == FieldType::Jail)
            {
                delete result;
                result = new JailField(i);
            }
            else
            {
                delete result;
                result = new ParkingField(i);
            }

            fields[i] = result;
        }
    }
    catch (const std::exception&)
    {

    }

    file.close();
}

Board::~Board() {
    free();
}