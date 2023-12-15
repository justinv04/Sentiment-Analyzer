#ifndef WORDSENT_H
#define WORDSENT_H

#include "DSString.h"

class WordSent
{
    private:
        DSString wordData; // word contained
        long int numPos = 0; // number of times word has appeared in a positive tweet
        long int numNeg = 0; // number of times word has appeared in a negative tweet
        double ratio = 0; // calculated net sentiment
    public:
        WordSent();
        WordSent(DSString word);
        DSString getWord() const;
        size_t getPos() const;
        size_t getNeg() const;
        double getRatio() const;
        void count(bool isPos); // updates numPos/numNeg based on isPos
        bool operator<(const WordSent &WS1) const; // comparison operator
        void updateRatio(); // function that updates ratio at the end of training
};
#endif