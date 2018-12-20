//
// Created by vassilis on 19/12/2018.
//

#ifndef RECOMMENDATION_TWEET_H
#define RECOMMENDATION_TWEET_H

#include <string>
#include <vector>
#include "Coin.h"

using namespace std;

class Tweet {
private:
    string user_id; // hope it is not necessary
    string tweet_id;
    vector<string>words;
    vector<Coin*>associatedCoins;
    double score;

    void calculateScore();
public:
    explicit Tweet(vector<string>&);
    string GetTweetId();
};


#endif //RECOMMENDATION_TWEET_H
