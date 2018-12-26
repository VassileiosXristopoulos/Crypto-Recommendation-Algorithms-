//
// Created by vassilis on 23/12/2018.
//

#include <algorithm>
#include "../../header/recommendation/Predictor.h"

Predictor::Predictor(vector<User *> & persons, vector<User *> &representatives,Config_info configuration) {
    this->configuration = configuration;
    this->PersonUsers = persons;
    this->Representatives = representatives;
    this->clusteringChoise =  Util::GetUserChoise("Please set the clustering algorithm for recommendation");
    this->lsh_master = nullptr;
    this->clustermaster = nullptr;
}

void Predictor::PerfromPrediction(){
    //LshPrediction();
    ClusteringPrediction();
}

void Predictor::ClusteringPrediction() {
   // PredictPersonClustering();
    cout << "Completed PredictPersonClustering"<<endl;
    PredictRepresentClustering();
    cout << "Completed PredictRepresentClustering"<<endl;

}

void Predictor::LshPrediction() {
    PredictPersonLSH();
    cout << "Completed PredictPersonLSH"<<endl;

    PredictRepresentLSH();
    cout << "Completed PredictRepresentLSH"<<endl;

}

void Predictor::PredictPersonLSH() {
    int i=0;
    lsh_master = new lsh(configuration.lsh_L,configuration.lsh_L,configuration.w,PersonUsers);
   // for(auto const user : PersonUsers){ // for each user
   for(auto it = PersonUsers.begin(), end =PersonUsers.end(); it!= end; it++){
        vector<vector<double>> neighboors = lsh_master->FindNCloserNeighboors(it.operator*()); //find his neighboors
        vector<pair<double,Coin*>> bestpredictions = ComputePredictions(it.operator*(),neighboors,5);
        // here should probably print
        //TODO: implement print
        i++;
    }
    delete (lsh_master);
}

void Predictor::PredictRepresentLSH() {
    for(auto const user : PersonUsers) { // for each user
        vector<User*>allUsers = Representatives;
        allUsers.push_back(user);

        lsh_master = new lsh(configuration.lsh_L,configuration.lsh_L,configuration.w,allUsers);
        vector<vector<double>> neighboors = lsh_master->FindNCloserNeighboors(user); //find his neighboors
        vector<pair<double,Coin*>> bestpredictions = ComputePredictions(user,neighboors,2);
        // here should probably print
        //TODO: implement print

        delete (lsh_master);
    }
}


vector<pair<double, Coin *>> Predictor::ComputePredictions(User *user,vector<vector<double>>neighboors,int amountOfbestPreds) {
    map<double, Coin *> recommendations; // a vector with all the recomendations, we will keep the best
    vector<double> userSentiments = user->GetSentimentVector();
    vector<double>similarities;

    for(unsigned int i = 0;i < userSentiments.size() ; i++){
        if( userSentiments[i] ==0){
            double z =0;
            double multSum = 0;
            for( auto const neighboor :  neighboors){
                double similarity = Util::cosineSimilarity((vector<double> &)(neighboor), userSentiments);
                multSum +=  similarity * neighboor[i];
                z += abs(similarity);
            }
            if(z>0)
                z = 1/z;
            else
                continue;

            // find the coin associated with the recommendation that has been performed
            auto it = std::find_if(std::begin(Util::CoinMap), std::end(Util::CoinMap),
                                   [&] (Coin * p) { return p->GetCoinIndex() == i; }
            );
            if( it != end(Util::CoinMap))
                recommendations.insert(make_pair(z*multSum,it.operator*()));
        }
    }

    /*sort(recommendations.begin(),recommendations.end(),
         [](pair<double,Coin*> item1, pair<double,Coin*> item2) {
             return item1.first > item2.first;
         }); // sort with descending order
*/
    // keep "amountOfbestPreds" best recommendations

    vector<pair<double, Coin *>> returnVector;

    if(recommendations.size()>=amountOfbestPreds){ // get first (ordered) n elements
        int i =0;
        for(auto const& elem : recommendations) {
            returnVector.emplace_back(elem.first,elem.second);
            if(++i == amountOfbestPreds)
                break;
        }
    }
    else{
        for(auto const& elem: recommendations) {
            returnVector.emplace_back(elem.first,elem.second);
        }
    }
    return returnVector;
   /* if(recommendations.size() >= amountOfbestPreds) {
        return vector<pair<double, Coin *>>(recommendations.begin(), recommendations.begin() + amountOfbestPreds);
    }
    else{
        return recommendations;
    }*/
}

void Predictor::PredictPersonClustering() {
    clustermaster = new ClusterMaster(clusteringChoise,PersonUsers);
    clustermaster->Clustering();
    vector<Cluster*> clusters = clustermaster->GetClusters();
   clustermaster->ComputeVectorizedMembers();
    int k = 0;
    for(auto const & user: PersonUsers){

        // find the cluster in which is our user
        auto it = find_if(clusters.begin(),clusters.end(),
                [&](Cluster * mycluster){ return mycluster->Contains(user->GetUserId());});
        if(it == clusters.end()){
            continue;
        }

        //Cluster * myCluster = it.operator*(); // this cluster contains the user
        vector<vector<double>>neighboors = clustermaster->GetVectorizedCluster(it.operator*());
        /*for(auto const & member : myCluster->GetMembers()){ // get in the vector the content of each member of the
            // cluster (of each neighboor)
            if(member.first != user->GetUserId()) {
                neighboors.push_back(member.second->getContent());
            }
        }*/

        vector<pair<double,Coin*>> bestpredictions = ComputePredictions(user,neighboors,5);
        // here should probably print
        //TODO: implement print
        k++;
    }
}

void Predictor::PredictRepresentClustering() {
    for(auto const & user : PersonUsers){
        vector<User *> allUsers = Representatives;
        allUsers.push_back(user);
        clustermaster = new ClusterMaster(clusteringChoise,allUsers);
        clustermaster->Clustering();
        vector<Cluster*> clusters = clustermaster->GetClusters();

        // find the cluster in which is our user
        auto it = find_if(clusters.begin(),clusters.end(),
                          [&](Cluster * mycluster){ return mycluster->Contains(user->GetUserId());});
        if(it == clusters.end()){
            continue;
        }

        Cluster * myCluster = it.operator*(); // this cluster contains the user
        vector<vector<double>>neighboors;
        for(auto const & member : myCluster->GetMembers()){ // get in the vector the content of each member of the
            // cluster (of each neighboor)
            if(member.first != user->GetUserId()) {
                neighboors.push_back(member.second->getContent());
            }
        }

        vector<pair<double,Coin*>> bestpredictions = ComputePredictions(user,neighboors,5);
        // here should probably print
        //TODO: implement print

        delete(clustermaster);
    }
}

