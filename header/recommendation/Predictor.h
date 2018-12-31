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
    ofstream *outfile;
    string output_file;
    void PredictPersonLSH();
    void PredictRepresentLSH();
    void PredictPersonClustering();
    void PredictRepresentClustering();
    void ClusteringPrediction();
    void LshPrediction();
    ofstream* GetOutputStream();
    bool isValidationInstance;
protected:
    lsh * lsh_master;
    ClusterMaster * clustermaster;
    vector<User*>PersonUsers;
    vector<User*>Representatives;
    Config_info configuration;
    vector<int>clusteringChoise;
    vector<pair<double,Coin*>> ComputePredictions(User *,vector<vector<double>>,int);
    void PrintPredictions(vector<pair<double,Coin*>>,User*);
public:
    Predictor(vector<User*>&, vector<User*>&,Config_info,string&);
    Predictor(vector<User*>&,vector<User*>&,Config_info,ofstream*);
    ~Predictor();
    void PerfromPrediction();
    void Validation();
};


#endif //RECOMMENDATION_PREDICTOR_H
