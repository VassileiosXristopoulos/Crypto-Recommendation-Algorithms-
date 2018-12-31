//
// Created by vassilis on 30/12/2018.
//

#include <algorithm>
#include <cfloat>
#include "../../header/recommendation/Validator.h"

Validator::Validator(vector<User *> &persons, vector<User *> &represents, Config_info info, ofstream *outfile)
        : Predictor(persons, represents, info, outfile) {


    this->outfile = outfile;
    // construct iconic users
    for (auto const &user : PersonUsers) {
        this->ValidationPersonUsers.push_back(
                new User(user->GetUserId(), user->GetTweets(), user->GetNonNormalizedSentiments(),
                         user->GetSentimentVector()));
    }

    MakeValidationSets();


}

void Validator::PredictRepresentLSH() {
    int i = 0;
    lsh_master = new lsh(configuration.lsh_L, configuration.lsh_L, configuration.w, PersonUsers);
    // for(auto const user : PersonUsers){ // for each user
    for (auto it = PersonUsers.begin(), end = PersonUsers.end(); it != end; it++) {
        User *user = it.operator*();
        vector<vector<double>> neighboors = lsh_master->FindNCloserNeighboors(user); //find his neighboors
        vector<pair<double, Coin *>> bestpredictions = ComputePredictions(user, neighboors, 5);

        PrintPredictions(bestpredictions, user);
        // I have the user, I have the coin, I have the prediction, I have the original prediction
        //compute MAE
        i++;
    }
    delete (lsh_master);
}

void Validator::PredictPersonClustering() {
    clustermaster = new ClusterMaster(clusteringChoise, PersonUsers);
    clustermaster->Clustering();
    vector<Cluster *> clusters = clustermaster->GetClusters();
    clustermaster->ComputeVectorizedMembers();
    int k = 0;
    for (auto const &user: ValidationPersonUsers) {

        // find the cluster in which is our user
        auto it = find_if(clusters.begin(), clusters.end(),
                          [&](Cluster *mycluster) { return mycluster->Contains(user->GetUserId()); });
        if (it == clusters.end()) {
            continue;
        }

        vector<vector<double>> neighboors = clustermaster->GetVectorizedCluster(it.operator*());

        vector<pair<double, Coin *>> bestpredictions = ComputePredictions(user, neighboors, 5);


        //compute MAE

        k++;
    }
}

void Validator::MakeValidationSets() {

    for (unsigned int i = 0; i < ValidationPersonUsers.size(); i++) { // count the amount of known sentiments
        int elementsTaken = (int) ceil(ValidationPersonUsers[i]->GetNonNormalizedSentiments().size() / 10);
        for (int j = 0; j < elementsTaken; j++) { // get 10% of the vector and place it to a set
            do {
                int random_element = (int) (rand() % ValidationPersonUsers[i]->GetNonNormalizedSentiments().size());
                if (ValidationPersonUsers[i]->GetNonNormalizedSentiments()[random_element] != INFINITY) {
                    int set_index = rand() % 10;
                    this->Sets[set_index].emplace_back(i, j); // save the pair
                    break;
                }
            }while(1);
        }
    }
}

void Validator::Validate() {

    for (int i = 0; i < 10; i++) { // each loop is a different (training sets,validation set) pair
        vector<pair<int, int>> mySet = Sets[i];
        map<int, User *> changedUsers;
        int k = 0;
        for (unsigned int j = 0; j < mySet.size(); j++) { // mark those that we want to validate, from Set[i]
            int user_index = mySet[j].first;
            int sentiment_index = mySet[j].second;
            ValidationPersonUsers[user_index]-> GetNonNormalizedSentiments()[sentiment_index] = DBL_MIN;
            changedUsers.insert(
                    make_pair(user_index, ValidationPersonUsers[user_index])); // keep the users that changed sentiments
            k++;
        }
        for (auto const &user : changedUsers) { // recompute sentiment vector because we deleted some sentiments
            // make the current sentiment vector the non normalized vector with the validation's unknown values
            user.second->SetSentimentVector(user.second->GetNonNormalizedSentiments());
            // normalize the vector again
            user.second->ComputeSentiments();
        }
        // make validation
         this->PredictRepresentLSH();
         this->PredictPersonClustering();

        for (auto const & changedUser : changedUsers) { // reset sentiment vector of each user
            changedUser.second->SetSentimentVector(PersonUsers[changedUser.first]->GetSentimentVector());
        }
    }

}

