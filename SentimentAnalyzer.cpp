#include <vector>
#include "SentimentAnalyzer.h"
#include "DSString.h"
#include "WordSent.h"

using namespace std;

SentimentAnalyzer::SentimentAnalyzer() // default constructor
{
    trainFile = DSString();
    testFile = DSString();
    testSentimentFile = DSString();
    resultsFile = DSString();
    accuracyFile = DSString();
    wordSentiments = {};
    totalAccuracy = 0;
}

SentimentAnalyzer::SentimentAnalyzer(DSString train, DSString test, DSString testSentiment, DSString results, DSString accuracy) // argument constructor
{
    trainFile = train;
    testFile = test;
    testSentimentFile = testSentiment;
    resultsFile = results;
    accuracyFile = accuracy;
    wordSentiments = {};
    totalAccuracy = 0;
}

void SentimentAnalyzer::train() // performs the training actions; reading in from file, tokenizing, storing individual word sentiments for use in testing
{
    FILE* input;
    char buffer[1001];
    char* b = buffer;
    size_t maxLen = 1000;
    input = fopen(trainFile.c_str(), "r");
    if (input == NULL)
    {
        cerr << "Failed to open input file!\n";
        return;
    }
    bool isPositive = false;
    getline(&b, &maxLen, input);    // catch the title row from input file
    buffer[0] = '\0';               // and release it from the buffer
    while(fgets(b, maxLen, input) != NULL)
    {
        DSString line = b;
        isPositive = (line[0] == '4'); // store the word sentiment in a bool form

        DSString tweet = line.substring(50); // cut out everything before the usename
        tweet = tweet.substring(tweet.findIOC(',', 1)); // cut out the username
        tweet.toLower(); // cut out all non-lowercase letter characters

        processTrainingData(isPositive, tweet); // send the trimmed tweet to be processed
        buffer[0] = '\0'; 
    }
    fclose(input);
}

void SentimentAnalyzer::test() // performs the testing actions; reading in from file, comparing contents against wordSentiments vector, and giving tweets a calculated sentiment value and writting them to results.csv
{
    FILE* input;
    FILE* output;
    char buffer[1001];
    char* b = buffer;
    size_t maxLen = 1000;
    input = fopen(testFile.c_str(), "r");
    if (input == NULL)
    {
        cerr << "Failed to open input file!\n";
        return;
    }
    output = fopen(resultsFile.c_str(), "w");
    if (output == NULL)
    {
        cerr << "Failed to open output file!\n";
        return;
    }
    DSString line, tweet, tweetID;
    int tweetSentiment = 2; // initialize with a non-reachable value for debugging
    getline(&b, &maxLen, input);
    buffer[0] = '\0'; // catch and release title line again
    while(fgets(b, maxLen, input) != NULL)
    {
        line = b;
        tweetID = line.substring(0, 10); // store the tweet ID, chars 0 to 10
        tweet = line.substring(49); // store the tweet + username
        tweet = tweet.substring(tweet.findIOC(',', 1)); // remove username
        tweet.toLower(); 
        tweetSentiment = processTestingData(tweet);
        buffer[0] = '\0';
        fprintf(output, "%d,%s\n", tweetSentiment, tweetID.c_str()); // print calculated tweet sentiment and tweet ID to results file
    }
    fclose(input);
    fclose(output);
}

void SentimentAnalyzer::debrief() // performs the accuracy check functions; read in from test sentiment answer key file, compare to results, calculate accuracy, and write accuracy and incorrect guesses to accuracy.txt
{
    FILE* input1; 
    FILE* input2; 
    FILE* output;
    char buffer1[1001];
    char buffer2[1001];
    char* testLine = buffer1; // results file input
    char* keyLine = buffer2; // key file input
    size_t maxLen = 1000;
    input1 = fopen(resultsFile.c_str(), "r");
    input2 = fopen(testSentimentFile.c_str(), "r"); // have all three files open at the same time for maximum efficiency
    output = fopen(accuracyFile.c_str(), "w");
    double accuracy = -1; // initialize with debug
    if (input1 == NULL)
    {
        cerr << "Failed to open input file #1!\n";
        return;
    }
    if (input2 == NULL)
    {
        cerr << "Failed to open input file #2!\n";
        return;
    }
    if(output == NULL)
    {
        cerr << "Failed to open output file!\n";
        return;
    }
    getline(&keyLine, &maxLen, input2);
    testLine[0] = '\0'; 
    keyLine[0] = '\0';
    DSString testString, keyString;
    vector<DSString> incorrects; // declare a vector of incorrect answers, storing sentiments and IDs in a DSString
    double count = 0; // used for accuracy calculations
    while(fgets(testLine, maxLen, input1) != NULL && fgets(keyLine, maxLen, input2) != NULL) // loops through until one of the files ends
    {
        testString = testLine;
        keyString = keyLine;
        testString = testString.substring(0, 10); // take testing sentiment and tweet ID
        keyString = keyString.substring(0,1); // stores just the correct sentiment
        if(testString[0] != keyString[0]) // checks if sentiments agree
        {
            count++; 
            incorrects.push_back(testString);
        }
        testLine[0] = '\0';
        keyLine[0] = '\0';
    }
    accuracy = 1 - (count/10000); // calculate accuracy
    fprintf(output, "%.3f\n", accuracy); // print accuracy to file, wanted to find something that would let me print a blank line, print out each incorrect option in the previous loop so I wouldn't need a vector, then go back to the top and let me print this, but didn't find anything that made it work
    for(size_t i = 0; i < incorrects.size(); ++i)
    {
        fprintf(output, "%s\n", incorrects.at(i).c_str()); // print inccorect tweet sentiments and IDs to accuracy file
    }
    fclose(input1);
    fclose(input2);
    fclose(output);
}

void SentimentAnalyzer::processTrainingData(const bool& isPositive, DSString &tweet) // processes each tweet sent to it by the train() loop
{
    DSString word = DSString();
    double wordPosition = 0; // the word's position (or new position) will be stored here
    size_t count = 1;
    long int index1;
    long int numChars;
    index1 = tweet.findIOC(' ', count) + 1; // find the index of the space at the beginning of the word
    numChars = tweet.findIOC(' ', count+1) - index1; // find the index of the space at the end of the word
    while(numChars > 0)
    {
        word = tweet.substring(index1, numChars); // store each individual word from the tweet
        wordPosition = findPosition(word); // find where in the vector it is (returns positive) or where it should be if not in the vector yet (returns negative)
        if(wordPosition >= 0)
            wordSentiments.at(wordPosition).count(isPositive); // has the WordSent object equal to the word just found in the tweet increment its counter based on the training tweet sentiment
        else
        {
            WordSent newWord(word); 
            newWord.count(isPositive);
            wordSentiments.insert(wordSentiments.begin() - int(wordPosition), newWord); // creates a new WordSent object, has it count, then add it to the correct position in the vector based on wordPosition form findPositionTraining
        }
        count++; // shift to the next set of spaces for the next word
        index1 = tweet.findIOC(' ', count) + 1;
        numChars = tweet.findIOC(' ', count + 1) - index1;
    }
}

int SentimentAnalyzer::processTestingData(DSString &tweet) // processes each tweet from the test() loop
{
    DSString word = DSString();
    double totalSentiment = 0;
    double wordPosition = 0;
    size_t count = 1;
    long int index1;
    long int numChars;
    index1 = tweet.findIOC(' ', count) + 1;
    numChars = tweet.findIOC(' ', count+1) - index1;
    while(numChars > 0)
    {
        word = tweet.substring(index1, numChars);
        wordPosition = findPosition(word);
        if(wordPosition >= 0)
            totalSentiment += wordSentiments.at(wordPosition).getRatio(); // if the word is found in the vector, then the totalSentiment for the tweet is adjusted by the calculated sentiment of the word
        count++;
        index1 = tweet.findIOC(' ', count) + 1;
        numChars = tweet.findIOC(' ', count + 1) - index1;
    }
    if(totalSentiment >= 0) // boils tweet down to positive or negative
        return 4;
    else
        return 0;
}

double SentimentAnalyzer::findPosition(const DSString &word) // finds the position in the vector for the word passed from process training data
{
    if(wordSentiments.size() == 0) // base case prevents 
        return -0.1;
    long int left = 0;
    long int right = wordSentiments.size() - 1; // start with the lower and upper bounds of the vector
    double mid = size_t((double(left + right) / 2.0) + 0.9); // gets mid, rounding up
    DSString midWord = wordSentiments[mid].getWord(); // get the word from the mid index in the vector
    while (left < right)
    {
        if (midWord == word) // return positive mid if word is identified in the vector
            return mid;
        if (word > midWord)
            left = size_t(mid); // look higher if word is 'greater than' the midWord, not mid - 1 because it breaks otherwise
        else
            right = size_t(mid) - 1; // 
        mid = size_t((double(left + right) / 2.0) + 0.9);
        midWord = wordSentiments[mid].getWord(); // get a new mid
    }
    if(word == midWord) // check once more
        return mid;
    if(mid == 0)
        return -0.1;
    else if (word < midWord) // word should be inserted at the left of the mid index
        return -mid;
    else
        return -(mid + 1); // word should be inserted at the right of the mid index
}
