//
// Created by vassilis on 10/11/2018.
//

#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H


#include <map>
#include "Item.h"

class Cluster {
private:
    Item * Centroid;
    map<string,Item*>Members;
    bool PAM();
    bool kmeans();
public:
    Cluster();
    ~Cluster();
    void SetCentroid(Item*);
    Item* GetCentroid();
    bool Contains(string item);
    void DeleteMember(string);
    void InsertMember(Item*);
    map<string,Item*> GetMembers();
    bool Update(int);
    void FlushClusterMembers();
    int size();
};


#endif //CLUSTER_CLUSTER_H
