//
// Created by vassilis on 14/10/2018.
//

#ifndef EUCLEDIANHASHTABLE_H
#define EUCLEDIANHASHTABLE_H

#include <vector>
#include "../Item.h"
#include "hashFunction.h"
#include "HashNode.h"
#include "cosineHashfunction.h"
#include "AHashTable.h"

using namespace std;

class EucledianHashTable : public AHashTable {
private:
    vector<hashFunction *>H_vector;
    vector<int> r_vector;

public:
    EucledianHashTable(int k,int size);
    ~EucledianHashTable();
    void add(Item* item);
    vector<Item*>  findNcloserNeighbors(Item *item,double r) override;
    vector<int>* computeGVector(Item* item) override;
    int hash(Item*item) override;
    int size() override;
};


#endif //EUCLEDIANHASHTABLE_H
