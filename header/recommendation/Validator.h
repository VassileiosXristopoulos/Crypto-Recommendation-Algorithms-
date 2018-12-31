//
// Created by vassilis on 30/12/2018.
//

#ifndef RECOMMENDATION_VALIDATOR_H
#define RECOMMENDATION_VALIDATOR_H


#include "Predictor.h"

class Validator : public Predictor {
private:
    ofstream *outfile;
    vector<User*>ValidationPersonUsers;
    double MAE;
    vector<pair<int,int>> Sets[10]; // pairs (string, indexOfSentiment)

    void MakeValidationSets();
public:
    Validator(vector<User*>&,vector<User*>&,Config_info,ofstream*);
    void PredictRepresentLSH();
    void PredictPersonClustering();
    void Validate();
};


#endif //RECOMMENDATION_VALIDATOR_H
