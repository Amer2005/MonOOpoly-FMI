#include "MyString.h"
#include <cstring>
#pragma warning(disable: 4996)

static unsigned roundToPowerOfTwo(unsigned n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

MyString::MyString(size_t stringLength)
{
    allocatedDataCapacity = dataToAllocByStringLen(stringLength);
    data = new char[allocatedDataCapacity];
    data[0] = '\0';
}

void MyString::resize(size_t newAllocatedDataCapacity)
{
    char* resizedData = new char[newAllocatedDataCapacity];
    strcpy(resizedData, data);
    delete[] data;
    data = resizedData;
    allocatedDataCapacity = newAllocatedDataCapacity;
}

void MyString::free() {
    delete[] data;
    data = nullptr;
    currentSize = allocatedDataCapacity = 0;
}

void MyString::copyFrom(const MyString& other) {
    currentSize = other.currentSize;
    allocatedDataCapacity = other.allocatedDataCapacity;
    data = new char[allocatedDataCapacity];
    strcpy(data, other.data);
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* str)
{
    currentSize = strlen(str);
    allocatedDataCapacity = dataToAllocByStringLen(currentSize);
    data = new char[allocatedDataCapacity];
    strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString& MyString::operator=(const int num)
{
    free();

    if (num == 0) {
        allocatedDataCapacity = dataToAllocByStringLen(1);
        data = new char[allocatedDataCapacity];
        data[0] = '0';
        data[1] = '\0';
        currentSize = 1;
        return *this;
    }

    char buffer[12];
    int temp = num;
    int i = 0;
    bool isNegative = false;

    if (temp < 0) {
        isNegative = true;
        temp = -temp;
    }

    while (temp > 0) {
        buffer[i++] = '0' + (temp % 10);
        temp /= 10;
    }

    if (isNegative) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';

    allocatedDataCapacity = dataToAllocByStringLen(i);
    data = new char[allocatedDataCapacity];
    currentSize = i;

    for (int j = 0; j < i; j++) {
        data[j] = buffer[i - j - 1];
    }
    data[i] = '\0';

    return *this;
}

MyString::~MyString()
{
    free();
}

size_t MyString::length() const
{
    return currentSize;
}

const char* MyString::c_str() const
{
    return data;
}

MyString& MyString::operator+=(const MyString& other)
{
    if (currentSize + other.currentSize + 1 > allocatedDataCapacity) {
        resize(dataToAllocByStringLen(currentSize + other.currentSize));
    }

    strncat(data, other.data, other.currentSize);
    currentSize += other.currentSize;

    return *this;
}

char& MyString::operator[](size_t index)
{
    // if (index >= currentSize) {
    //     throw std::out_of_range("Invalid index!");
    // }
    return data[index];
}

char MyString::operator[](size_t index) const
{
    // if (index >= currentSize) {
    //     throw std::out_of_range("Invalid index!");
    // }
    return data[index];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs.length() + rhs.length());
    result += lhs;
    result += rhs;
    return result;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str)
{
    char buff[1024];
    is >> buff; // since operator>> for strings is formatted input, we will use is >> instead of getline
    // if you want to read with getline, create a separate function readStringLine(std::istream& is, MyString& str) 
    // and use is.getline(buff, 1024) inside it
    size_t buffLength = strlen(buff);

    if (buffLength > str.allocatedDataCapacity) {
        str.resize(dataToAllocByStringLen(buffLength));
    }

    strcpy(str.data, buff);
    str.currentSize = buffLength;

    return is;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return !(lhs < rhs || lhs == rhs);
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return !(lhs < rhs);
}