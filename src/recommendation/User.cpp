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

}
