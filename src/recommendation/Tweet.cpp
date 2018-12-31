//
// Created by vassilis on 19/12/2018.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "../../header/recommendation/Tweet.h"
#include "../../header/Util.h"

Tweet::Tweet(vector<string>& tweet) {

    this->user_id = tweet[0];
    this->tweet_id = tweet[1];
    for(unsigned int i= 2 ; i< tweet.size(); i++){
        this->words.push_back(tweet[i]);
    }
    calculateScore();
}
/**
 * Calculate the sentiment score of the tweet
 */
void Tweet::calculateScore() {
     double totalScore = 0;
    for(auto const& word : this->words){ // if word exists in lexicon
        if(Util::Lexicon.find(word) != Util::Lexicon.end()){
            totalScore += Util::Lexicon.at(word);
        }
        else{ // check if it is coin
            auto it = std::find_if(std::begin(Util::CoinMap), std::end(Util::CoinMap),
                                   [&] (Coin * p) { return p->isCoin(word); }
            );
            if( it != end(Util::CoinMap)){ // it indeed is coin
                this->associatedCoins.push_back(it.operator*());
            }
        }
    }
    this->score = totalScore / sqrt( pow(totalScore,2) + 15 ) ;
}

string Tweet::GetTweetId() {
    return this->tweet_id;
}

vector<Coin *> Tweet::GetAssociatedCoins() {
    return associatedCoins;
}

double Tweet::GetScrore() {
    return score;
}

Tweet::~Tweet() {

}
