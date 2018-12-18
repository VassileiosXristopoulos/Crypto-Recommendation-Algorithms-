//
// Created by vassilis on 21/10/2018.
//

#ifndef CUBE_EUCLEDIANHYPERCUBE_H
#define CUBE_EUCLEDIANHYPERCUBE_H


#include "AHypercube.h"
#include "../lsh/hashFunction.h"

class EucledianHypercube : public AHypercube{
private:
    vector<hashFunction*>Hi;
public:
    explicit EucledianHypercube(int d);
    ~EucledianHypercube();
    vector<int> getBitVector(Item* item) override;
    double computeDistance(vector<double>&x,vector<double>&y) override;
    int size();
};


#endif //CUBE_EUCLEDIANHYPERCUBE_H
