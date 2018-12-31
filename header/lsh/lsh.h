//
// Created by vassilis on 13/11/2018.
//

#ifndef CLUSTER_LSH_H
#define CLUSTER_LSH_H


#include "AHashTable.h"
#include "../clustering/DataSetMap.h"
#include "../recommendation/User.h"


class lsh {
private:
    vector<AHashTable*> LshHashTables;
    vector<Item*>Dataset=vector<Item*>();
public:
    lsh(int k,int L,int w,string& metric,DataSetMap *set);
    lsh(int k,int L,int w,vector<User *>set);
    ~lsh();
    vector<Item*> FindItemsInRange(Item * item, double r);
    vector<vector<double>> FindNCloserNeighboors(User *);
    //vector<vector<double>>
};


#endif //CLUSTER_LSH_H
