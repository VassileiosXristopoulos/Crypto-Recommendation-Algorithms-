//
// Created by vassilis on 16/11/2018.
//

#ifndef CLUSTER_CUBE_H
#define CLUSTER_CUBE_H


#include "AHypercube.h"
#include "../DataSetMap.h"

class cube {
private:
    AHypercube *hypercube;
public:
    cube(int k,int w,int probes,int M,string& metric,DataSetMap *set);
    ~cube();
    vector<Item*> FindItemsInRange(Item *, double);
};


#endif //CLUSTER_CUBE_H
