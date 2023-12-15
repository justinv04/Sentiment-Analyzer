# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Justin Vincent

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > I tokenize each tweet I read in from file into words, count the number of times each word appears in a positive or negative tweet, get a calculated net sentiment for that word, compare the test tweets to those words, and then get a calculated net sum sentiment for the whole word

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > Your answer

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > My SentimentAnalyzer can complete its classifications in 255 to 373 milleseconds, and has a complexity of only O(N). This calculation takes in:
   reading from file (*O(N)*), 
   looping through the tweet until it finds the first instance of a comma (*O(U)*),
   looping through the tweet in toLower (*O(L)*),
   looping through to parse out words from the tweet in processTestingData (*O(W)*)
   finding the position that word is at in the WordSentiments Vector (*O(log(N)*)
   Therefore the total calculate is O(N) * O(U) * O(L) * O(W) * O(log(N)) = *O(N)*

4. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > I used valgrind to check if my program had any memory leaks after every change that could effect memory allocation and deletion. The code now exits with no memory issues

5. What was the most challenging part of the assignment?

   > debugging for hours on end until I finally find the thing that was causing the memory error only to be slightly further along by the time I fix the problem. That and the UML diagram, because I had never made one of code that I had written before
