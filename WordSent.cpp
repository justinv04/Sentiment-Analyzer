#include "WordSent.h"
#include "DSString.h"

using namespace std;

WordSent::WordSent() // default constructor
{
    wordData = "/0";
    numPos = 0;
    numNeg = 0;
    ratio = 0;
}

WordSent::WordSent(DSString word) // argument constructor
{
    wordData = word;
    numPos = 0;
    numNeg = 0;
    ratio = 0;
}

// get functions

DSString WordSent::getWord() const 
{
    return wordData;
}

size_t WordSent::getPos() const
{
    return numPos;
}

size_t WordSent::getNeg() const
{
    return numNeg;
}

double WordSent::getRatio() const
{
    return ratio;
}

void WordSent::count(bool isPos) // this function is called during training to update how many times a wordSent has been seen in positive and negative tweets
{
    isPos ? numPos++ : numNeg++;
    updateRatio();
}

void WordSent::updateRatio() // this function calucates the updated ratio
{
    if(numNeg != 0)
        ratio = double(numPos - numNeg)/(numPos + numNeg);
    else
        (numPos > 0) ? ratio = 1 : ratio = 0;
}


bool WordSent::operator<(const WordSent &WS1) const // comparisons between WordSentiment objects are as simple as comparing their DSString members
{
    if(wordData < WS1.getWord())
    {
        return true;
    }
    else
    {
        return false;
    }
}