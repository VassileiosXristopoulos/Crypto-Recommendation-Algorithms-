//
// Created by vassilis on 23/12/2018.
//

#ifndef RECOMMENDATION_PREDICTOR_H
#define RECOMMENDATION_PREDICTOR_H


#include "User.h"
#include "../lsh/lsh.h"
#include "../clustering/ClusterMaster.h"

class Predictor {
private:
    vector<User*>PersonUsers;
    vector<User*>Representatives;
    lsh * lsh_master;
    ClusterMaster * clustermaster;
    Config_info configuration;
    vector<int>clusteringChoise;
    void PredictPersonLSH();
    void PredictRepresentLSH();
    void PredictPersonClustering();
    void PredictRepresentClustering();
    void ClusteringPrediction();
    void LshPrediction();
    vector<pair<double,Coin*>> ComputePredictions(User *,vector<vector<double>>,int);

public:
    Predictor(vector<User*>&, vector<User*>&,Config_info);
    void PerfromPrediction();
};


#endif //RECOMMENDATION_PREDICTOR_H
