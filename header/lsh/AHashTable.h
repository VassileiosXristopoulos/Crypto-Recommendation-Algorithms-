//
// Created by vassilis on 21/10/2018.
//

#ifndef CUBE_AHASHTABLE_H
#define CUBE_AHASHTABLE_H


#include "../Item.h"
#include "HashNode.h"

class AHashTable {
protected:
    int TableSize;
    vector< vector<HashNode*> >Table;
public:
    AHashTable(int size,int k);
    virtual ~AHashTable();
    virtual void add(Item* item) = 0;
    virtual int hash(Item*item) = 0;
    virtual vector<Item*>  findNcloserNeighbors(Item *item,double r) = 0;
    virtual vector<int>* computeGVector(Item* item) = 0;
    virtual int size() = 0;
};


#endif //CUBE_AHASHTABLE_H
