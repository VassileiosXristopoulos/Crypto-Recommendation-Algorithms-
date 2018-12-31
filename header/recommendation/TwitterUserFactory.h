//
// Created by vassilis on 19/12/2018.
//

#ifndef RECOMMENDATION_TWITTERUSERFACTORY_H
#define RECOMMENDATION_TWITTERUSERFACTORY_H


#include "../clustering/Cluster.h"
#include "User.h"

class TwitterUserFactory {
private:
    vector<User*> PersonUsers; // vector with all the users with their tweets
    vector<User*> RepresentativeUsers; // vector with all the representative users with their tweets

    vector<Tweet*>allTweets;

    int cluster_index;

   void ConstructPersonUsers(string);
   void ConstructRepresentatives(vector<Cluster*>);

   void AddTweetToPersonUser(string, Tweet*);
   void AddTweetToRepresentativeUser(string, Tweet*);

   int getClusterIndex();

public:
    TwitterUserFactory(string,vector<Cluster*>&);
    ~TwitterUserFactory();
    vector<User*>& GetPersonUsers();
    vector<User*>& GetRepresentatives();
};


#endif //RECOMMENDATION_TWITTERUSERFACTORY_H
