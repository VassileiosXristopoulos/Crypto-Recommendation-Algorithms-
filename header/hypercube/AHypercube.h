//
// Created by vassilis on 21/10/2018.
//

#ifndef CUBE_AHYPERCUBE_H
#define CUBE_AHYPERCUBE_H


#include "../lsh/cosineHashfunction.h"
#include "BinaryMap.h"
#include "CubeEdge.h"

class AHypercube {
protected:
    BinaryMap binaryMap;
    vector<CubeEdge*>edges;
    int d;
public:
    explicit AHypercube(int d);
    virtual ~AHypercube();
    virtual  vector<int> getBitVector(Item* item) = 0;
    vector<CubeEdge*> getHamingCLose(int hammingDist,CubeEdge* edge);
    void add(Item* item);
    virtual double computeDistance(vector<double>&x,vector<double>&y) = 0;
    vector<Item*> findRCloser(Item *item,int max,int probes,double radius);
    virtual int size() = 0;
};


#endif //CUBE_AHYPERCUBE_H
