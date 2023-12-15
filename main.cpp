#include "DSString.h"
#include "SentimentAnalyzer.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 6)
    {
        cerr << "Incorrect Number of Command Line Arguments, Expected: 5, Recieved: " << argc - 1 << "\n"; // checks to make sure argument count is correct
        return -1;
    }
    SentimentAnalyzer SA = SentimentAnalyzer(argv[1], argv[2], argv[3], argv[4], argv[5]); // construct our SentimentAnalyzer object with the file DSStrings
    SA.train(); // trains itself
    SA.test(); // tests itself
    SA.debrief(); // checks itself
    return 0;
}

