#include <utility>

//
// Created by vassilis on 19/12/2018.
//

#include <fstream>
#include <algorithm>
#include "../../header/recommendation/TwitterUserFactory.h"
#include "../../header/Util.h"
#include "../../header/recommendation/Tweet.h"

TwitterUserFactory::TwitterUserFactory(string tweetsFile, vector<Cluster *>& clusters) {
    this->cluster_index = 0;
    ConstructPersonUsers(move(tweetsFile));
    ConstructRepresentatives(clusters);
}

void TwitterUserFactory::ConstructPersonUsers(string inputFile) {
    string FileLine;
    ifstream file(inputFile);

    while(getline( file, FileLine )) {
        vector<string> tweetContent = Util::SplitTabs(FileLine);
        if(tweetContent.size()<2){
            cout << "Tweet given not valid"<<endl;
            exit(0);
        }

        string user_id = tweetContent[0];
        auto * tweet = new Tweet(tweetContent);
        AddTweetToPersonUser(user_id,tweet);

        allTweets.push_back(tweet);
    }
    for(int i=0;i<PersonUsers.size();i++){ // finally, compute sentiment vector for each user
        PersonUsers[i]->ComputeSentiments();
        if(PersonUsers[i]->AllZero()){
          //  PersonUsers.erase(find(PersonUsers.begin(),PersonUsers.end(),user));
          delete(PersonUsers[i]);
          PersonUsers[i] = nullptr;
        }
    }
    PersonUsers.erase(remove_if(PersonUsers.begin(),PersonUsers.end(),[&](User * user)->bool{
        return user == nullptr;
    }), PersonUsers.end());

}

void TwitterUserFactory::ConstructRepresentatives(vector<Cluster*> clusters) {
    for(auto const& cluster: clusters){ // for each cluster make a Representative user
        string user_id = to_string(getClusterIndex()); //  user's name is constructed from ascending variable
        User* newUser = new User(user_id);
        for(auto const& tweet : cluster->GetMembers()){ // iterate all cluster members (tweets vectorized TFIDF)
            string itemName = tweet.first; // get tweet id from vectorized tweet
            for(auto const& storedTweet : allTweets){
                if(storedTweet->GetTweetId() == itemName){ // if found the corresponding tweet
                    AddTweetToRepresentativeUser(user_id, storedTweet);
                }
            }
        }
    }
    for(int i=0;i<RepresentativeUsers.size();i++){ // finally, compute sentiment vector for each user
        RepresentativeUsers[i]->ComputeSentiments();
        if(RepresentativeUsers[i]->AllZero()){
            //  PersonUsers.erase(find(PersonUsers.begin(),PersonUsers.end(),user));
            delete(RepresentativeUsers[i]);
            RepresentativeUsers[i] = nullptr;
        }
    }
    RepresentativeUsers.erase(remove_if(RepresentativeUsers.begin(),RepresentativeUsers.end(),[&](User * user)->bool{
        return user == nullptr;
    }), RepresentativeUsers.end());
}

void TwitterUserFactory::AddTweetToPersonUser(string user, Tweet * tweet) {

    User * tobeUser = new User(move(user));
    // check if user already exists in the vector
    auto it = std::find_if(std::begin(PersonUsers), std::end(PersonUsers),
                     [&] (User * p) { return p->GetUserId() == tobeUser->GetUserId(); }
                     );
    if(it != end(PersonUsers)){ // if user exists
        it.operator*()->addTweet(tweet);
        delete(tobeUser);
    }
    else{ // if not then add him
        tobeUser->addTweet(tweet);
        PersonUsers.push_back(tobeUser);
    }

}


void TwitterUserFactory::AddTweetToRepresentativeUser(string user, Tweet * tweet) {

    User * tobeUser = new User(move(user));
    auto it = std::find_if(std::begin(RepresentativeUsers), std::end(RepresentativeUsers),
                           [&] (User * p) { return p->GetUserId() == tobeUser->GetUserId(); }
    );
    if(it != end(RepresentativeUsers)){
        it.operator*()->addTweet(tweet);
        delete(tobeUser);
    }
    else{ // if not then add him
        tobeUser->addTweet(tweet);
        RepresentativeUsers.push_back(tobeUser);
    }

}

int TwitterUserFactory::getClusterIndex() {
    return cluster_index++;
}

vector<User *>& TwitterUserFactory::GetPersonUsers() {
    return PersonUsers;
}

vector<User *>& TwitterUserFactory::GetRepresentatives() {
    return RepresentativeUsers;
}


