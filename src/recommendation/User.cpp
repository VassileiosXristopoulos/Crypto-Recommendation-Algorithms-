//
// Created by vassilis on 19/12/2018.
//

#include <cfloat>
#include "../../header/recommendation/User.h"

User::User(string userId) {
    this->user_id = userId;
    this->allZero = false;
}


User::User(string id, vector<Tweet *> tweets, vector<double> nonNormsentiments, vector<double> sentiments) {
    this->user_id = id;
    this->tweets = tweets;
    this->nonNormalizedsentiments = nonNormsentiments;
    this->sentiment = sentiments;
    this->allZero = false;
}


void User::addTweet(Tweet *tweet) {
    this->tweets.push_back(tweet);
}

string User::GetUserId() {
    return this->user_id;
}

void User::ComputeSentiments() {

    for (auto const &tweet : tweets) { // for each tweet of the user
        for (auto const &coin : tweet->GetAssociatedCoins()) { // for each coin of his tweet
            int index = coin->GetCoinIndex();

            if (!(index >= 0 && index < ((int) Util::amountOfCoins))) { // check if index is correct
                cout << "Unexpected error occured when computing sentiment vector for user " << this->user_id << endl;
                exit(0);
            }

            if (this->sentiment[coin->GetCoinIndex()] == INFINITY) // if the set that is to be set has not yet been set
                this->sentiment[coin->GetCoinIndex()] = 0;

            // add the sentiment of the tweet to the corresponding possition at the vector
            this->sentiment[coin->GetCoinIndex()] += tweet->GetScrore();
        }
    }
    for (auto const &i: sentiment) {
        this->nonNormalizedsentiments.push_back(i);
    }
    // now normalize the vector
    NormalizeVector();

}

vector<double> &User::GetSentimentVector() {
    return this->sentiment;
}

bool User::AllZero() {
    return this->allZero;
}

void User::NormalizeVector() {
    bool allZero = true, validation = false;
    double avg = 0; // this is the sum of sentiments
    for (auto const &i : sentiment) {
        if (i != INFINITY && i != DBL_MIN) {
            avg += i;
        }
        if (i == DBL_MIN)
            validation = true;
    }
    avg /= Util::amountOfCoins;
    for (auto &i : sentiment) {

        if (i != INFINITY && i != DBL_MIN) {
            i -= avg;
        } else if (i == DBL_MIN) {
            i = 0;
        } else if (i == INFINITY && !validation) { // if validation ignore it
            i = 0;
        }

        if (i != 0) {
            allZero = false;
        }
    }
    this->allZero = allZero;
}

vector<double> &User::GetNonNormalizedSentiments() {
    return nonNormalizedsentiments;
}

vector<Tweet *> User::GetTweets() {
    return this->tweets;
}

void User::SetSentimentVector(vector<double> vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        this->sentiment[i] = vec[i];
    }
}

User::~User() {

}

void User::deleteTweets() {
    for(auto tweet : tweets){
        delete tweet;
    }
}
