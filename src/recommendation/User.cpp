//
// Created by vassilis on 19/12/2018.
//

#include "../../header/recommendation/User.h"

User::User(string userId) {
    this->user_id = userId;
}

void User::addTweet(Tweet *tweet) {
    this->tweets.push_back(tweet);
}


string User::GetUserId() {
    return this->user_id;
}

void User::ComputeSentiments() {
    for(auto const & tweet : tweets){ // for each tweet of the user
        for(auto const & coin : tweet->GetAssociatedCoins()){ // for each coin of his tweet
            int index = coin->GetCoinIndex();

            if(!(index >=0 && index<Util::amountOfCoins)){ // check if index is correct
                cout << "Unexpected error occured when computing sentiment vector for user "<<this->user_id<<endl;
                exit(0);
            }

            if(this->sentiment[coin->GetCoinIndex()] == INFINITY) // if the set that is to be set has not yet been set
                this->sentiment[coin->GetCoinIndex()] = 0;

            // add the sentiment of the tweet to the corresponding possition at the vector
            this->sentiment[coin->GetCoinIndex()] += tweet->GetScrore();
        }
    }
    // now normalize the vector
    double avg = 0; // this is the sum of sentiments
    for(auto const& i : sentiment){
        if( i != INFINITY){
            avg += i;
        }
    }
    avg /= Util::amountOfCoins;
    for(auto & i : sentiment){
        if( i != INFINITY ){
            i -= avg;
        }
        else{
            i = 0;
        }
    }
}

vector<double>& User::GetSentimentVector() {
    return this->sentiment;
}
