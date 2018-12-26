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
    vector<double> sentiment = vector<double>(Util::amountOfCoins, INFINITY);
public:
    User(string);
    void addTweet(Tweet *);
    string GetUserId();
    void ComputeSentiments();
    vector<double> GetSentimentVector();
    bool AllZero();
};


#endif //RECOMMENDATION_USER_H
