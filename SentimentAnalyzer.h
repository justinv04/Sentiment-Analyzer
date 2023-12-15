#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H

#include <vector>
#include "DSString.h"
#include "WordSent.h"

class SentimentAnalyzer
{
    private:
        std::vector<WordSent> wordSentiments; // vector of WordSent objects for training and testing purposes
        DSString trainFile, testFile, testSentimentFile, resultsFile, accuracyFile; // DSString containers for all of the file names from command line
        double totalAccuracy; // stores total accuracy of the sentiment

        double findPosition(const DSString& word); // uses binary search to insert and search with the wordSentiment vector
        void processTrainingData(const bool& isPositive, DSString& data); // processes words during training
        int processTestingData(DSString& data); // processes words during testing
    public:
        SentimentAnalyzer();
        SentimentAnalyzer(DSString trainFile, DSString testFile, DSString testSentimentFile, DSString resultsFile, DSString accuracyFile);
        void train(); // trains itself
        void test(); // tests itself
        void debrief(); // checks itself
};

#endif