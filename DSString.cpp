#include "DSString.h"
#include <iostream>

DSString::DSString() // default constructor
{
    len = 0;
    data = nullptr;
}

DSString::DSString(const char* newData) // char* constructor
{
    if (newData == nullptr) 
    {
        data = new char[1];
        data[0] = '\0';
        len = 0;
    } 
    else 
    {
        size_t size = 0;
        while (newData[size] != '\0') 
        {
            size++;
        }
        len = size;

        data = new char[len+1];
        for (size_t i = 0; i < len; ++i) 
        {
            data[i] = newData[i];
        }
        data[len] = '\0';
    }
}

DSString::DSString(const DSString& DSS1) // copy constructor
{
    len = DSS1.length();
    data = new char[len+1];
    char* newData = DSS1.c_str();
    for(size_t i = 0; i < len; ++i)
    {
        data[i] = newData[i];
    }
    data[len] = '\0';

}

DSString::~DSString() // destructor
{
    delete[] data;
    data = nullptr;
}

DSString &DSString::operator=(const DSString& DSS1) // copy assignment operator
{
    if(this != &DSS1)
    {
        delete[] data;
    }
    len = DSS1.length();
    data = new char[len+1];
    char* newData = DSS1.c_str();
    for(size_t i = 0; i < len; ++i)
    {
        data[i] = newData[i];
    }
    data[len] = '\0';
    return *this;
}

size_t DSString::length() const // returns size_t length
{
    return len;
}

char* DSString::c_str() const // returns char* data
{
    return data;
}

char& DSString::operator[](size_t index) const
{
    if (index >= len) 
    {
        std::cerr << ("Index out of range");
    }
    return data[index];
}

DSString DSString::operator+(const DSString &DSS1) const 
{
    size_t newLen = len + DSS1.length();
    char *newData = new char[newLen + 1];
    size_t i;
    for (i = 0; i < len; ++i)
    {
        newData[i] = data[i];
    }
    for (size_t j = 0; j < DSS1.length(); ++j, ++i)
    {
        newData[i] = DSS1.c_str()[j];
    }
    newData[newLen] = '\0';
    return DSString(newData);
}

bool DSString::operator==(const DSString &DSS1) const // eeq eeq operator overload
{
    if(len != DSS1.length())
    {
        return false;
    }
    for(size_t i = 0; i < len; ++i)
    {
        if(data[i] != DSS1.c_str()[i])
        {
            return false;
        }
    }
    return true;
}

bool DSString::operator<(const DSString &DSS1) const // less than operator overload
{
    if(len < DSS1.length())
    {
        return true;
    }
    if(len == DSS1.length())
    {
        for(size_t i = 0; i < len; ++i)
        {
            if(data[i] < DSS1.c_str()[i])
            {
                return true;
            }
            if(data[i] > DSS1.c_str()[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool DSString::operator>(const DSString &DSS1) const // more than operator overload
{
    if(len > DSS1.length())
    {
        return true;
    }
    if(len == DSS1.length())
    {
        for(size_t i = 0; i < len; ++i)
        {
            if(data[i] > DSS1.c_str()[i])
            {
                return true;
            }
            if(data[i] < DSS1.c_str()[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

DSString& DSString::operator+=(const DSString& DSS1) // plus equals operator overload, DSString argument
{
    size_t newLen = len + DSS1.length();
    char* newData = new char[newLen + 1];
    size_t i;
    for (i = 0; i < len; ++i)
    {
        newData[i] = data[i];
    }
    for (size_t j = 0; j < DSS1.length(); ++j, ++i)
    {
        newData[i] = DSS1.c_str()[j];
    }
    newData[newLen] = '\0';

    delete[] data;

    data = newData;
    len = newLen;

    return *this;
}

DSString& DSString::operator+=(const char*& newCharString) // plus equals operator overload, charString agrument
{
    size_t newLen = len;
    const char* ptr = newCharString;
    while (*ptr != '\0') 
    {
        newLen++;
        ptr++;
    }
    char* newCharStringCopy = new char[newLen + 1];
    size_t i;
    for (i = 0; i < len; ++i) 
    {
        newCharStringCopy[i] = data[i];
    }
    ptr = newCharString;
    for (size_t j = 0; j < newLen - len; ++j, ++i) 
    {
        newCharStringCopy[i] = *ptr;
        ptr++;
    }
    newCharStringCopy[newLen] = '\0';
    delete[] data;
    data = newCharStringCopy;
    len = newLen;
    return *this;
}

DSString& DSString::operator+=(const char& newChar) // plus equals operator overload, char argument
{
    size_t newLen = len + 1;
    char* newData = new char[newLen + 1];
    for (size_t i = 0; i < len; ++i) 
    {
        newData[i] = data[i];
    }
    newData[len] = newChar;
    newData[newLen] = '\0';
    delete[] data;
    data = newData;
    len = newLen;
    return *this;
}

DSString DSString::substring(size_t start, size_t numChars) const // substring function, returns subtring of numChars characters starting after index start
{
    DSString subString = DSString();
    if (start >= len || numChars > len || start + numChars > len)
    {
        std::cerr << "Invalid start or number of characters specified:  start: " << start << "  len: " << len << "  numChars: " << numChars << "\n";;
    }
    char *substring = new char[numChars + 1];
    for(size_t i = 0; i < numChars; ++i) 
    {
        substring[i] = data[start + i];
    }
    substring[numChars] = '\0';
    subString = substring;
    delete[] substring;
    return subString;
}

DSString DSString::substring(size_t start) const // subtring overload, returns a substring of everything past index start
{
    DSString subString = DSString();
    if (start >= len)
    {
        std::cerr << ("Invalid start");
    }
    size_t newLen = len - start;
    char *substring = new char[newLen + 1];
    for(size_t i = 0; i < newLen; ++i) 
    {
        substring[i] = data[start + i];
    }
    substring[newLen] = '\0';
    subString = substring;
    delete[] substring;
    return subString;
}

void DSString::toLower() // converts to lowercase and removes all non-alphabetic characters except for spaces
{
    char* lowercase = new char[len + 1];
    int j = 0;
    for (size_t i = 0; i < len; ++i) 
    {
        if (data[i] >= 'A' && data[i] <= 'Z') 
        {
            lowercase[j] = char(data[i] + 32);
            j++;
        }
        else if ((data[i] >= 'a' && data[i] <= 'z') || data[i] == ' ')
        {
            lowercase[j] = data[i];
            j++;
        }
    }
    lowercase[j] = '\0';
    delete[] data;
    data = lowercase;
    len = j;
}

long int DSString::findIOC(char searchChar, size_t occurance) // find the index of the occurance-th occurance of searchChar
{
    size_t count = 0;
    for(size_t i = 0; i < len; ++i)
    {
        if(data[i] == searchChar)
        {
            count++; 
            if(count == occurance) // when the occurance equals the passed argument
                return i;
        }
    }
    return -1; // return if not found
}

std::ostream &operator<<(std::ostream &output, const DSString &DSS) // output stream overload
{
    output << DSS.c_str();
    return output;
}

std::istream &operator>>(std::istream &input, DSString &DSS) // input stream overload
{
    char buffer[1024];
    input >> buffer;
    DSS = buffer;
    return input;
}
