//
// Created by vassilis on 21/10/2018.
//

#ifndef CUBE_COSINEHASHTABLE_H
#define CUBE_COSINEHASHTABLE_H


#include "AHashTable.h"
#include "cosineHashfunction.h"

class CosineHashTable : public AHashTable{
private:
    vector<cosineHashfunction *>cosine_vector;
    int k;
public:
    CosineHashTable(int size,int k);
    ~CosineHashTable() override;
    vector<int>* computeGVector(Item* item) override;
    int hash(Item*item) override;
    void add(Item* item) override;
    vector<Item*>  findNcloserNeighbors(Item *item,double r) override;
    int size() override;
};


#endif //CUBE_COSINEHASHTABLE_H
