//
// Created by vassilis on 13/11/2018.
//

#ifndef CLUSTER_LSH_H
#define CLUSTER_LSH_H


#include "AHashTable.h"
#include "../DataSetMap.h"



class lsh {
private:
    vector<AHashTable*> LshHashTables;

public:
    lsh(int k,int L,int w,string& metric,DataSetMap *set);
    ~lsh();
    vector<Item*> FindItemsInRange(Item * item, double r);
};


#endif //CLUSTER_LSH_H
