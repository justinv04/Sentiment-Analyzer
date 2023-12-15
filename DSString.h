#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

class DSString
{
    private:
        size_t len; // len data member
        char *data; // charString data member
        
    public:
        DSString(); // default constructor

        // big three
        DSString(const char* newData);
        DSString(const DSString &DSS1);          
        ~DSString(); 

        void toLower(); // lowers all letters to loowercase and removes everything else that isn't a space

        // get functions
        size_t length() const;
        char* c_str() const;          
        long int findIOC(char searchChar, size_t occurance); // gets the index of the occurance-th occurance of searchChar
        DSString substring(size_t start, size_t numChars) const; 
        DSString substring(size_t start) const; // substring overload, takes start index and continues until the end of the DSString

        // operator overloads
        char& operator[](size_t index) const;
        bool operator<(const DSString &DSS1) const;
        bool operator>(const DSString &DSS1) const;
        bool operator==(const DSString &DSS1) const;
        DSString &operator=(const DSString &DSS1);
        DSString operator+(const DSString &DSS1) const;
        DSString& operator+=(const DSString &DSS1);
        DSString& operator+=(const char* &newCharString);
        DSString& operator+=(const char &newChar); 
        friend std::ostream &operator<<(std::ostream &output, const DSString &DSS);
        friend std::istream &operator>>(std::istream &input, DSString &DSS);
};

#endif
