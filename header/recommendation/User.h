//
// Created by vassilis on 19/12/2018.
//

#ifndef RECOMMENDATION_USER_H
#define RECOMMENDATION_USER_H


#include "Tweet.h"
#include "../Util.h"

class User {
private:
    string user_id;
    vector<Tweet*> tweets;
    vector<double> sentiment = vector<double>(Util::amountOfCoins,0);
public:
    User(string);
    void addTweet(Tweet *);
    string GetUserId();
    void ComputeSentiments();
};


#endif //RECOMMENDATION_USER_H
