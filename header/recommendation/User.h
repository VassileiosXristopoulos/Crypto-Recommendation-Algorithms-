//
// Created by vassilis on 19/12/2018.
//

#ifndef RECOMMENDATION_USER_H
#define RECOMMENDATION_USER_H


#include <limits>
#include <cmath>
#include "Tweet.h"
#include "../Util.h"
//#define INFINITY std::numeric_limits<double>::infinity()
class User {
private:
    string user_id;
    vector<Tweet*> tweets;
    bool allZero;
    vector<double> nonNormalizedsentiments = vector<double>(Util::amountOfCoins, INFINITY);
    vector<double> sentiment = vector<double>(Util::amountOfCoins, INFINITY);
public:
    User(string);
    User(string,vector<Tweet*>,vector<double>,vector<double>);
    ~User();
    void deleteTweets();
    void addTweet(Tweet *);
    vector<Tweet*> GetTweets();
    string GetUserId();
    void ComputeSentiments();
    vector<double>& GetSentimentVector();
    void SetSentimentVector(vector<double>);
    bool AllZero();
    void NormalizeVector();
    vector<double>& GetNonNormalizedSentiments();
};


#endif //RECOMMENDATION_USER_H
