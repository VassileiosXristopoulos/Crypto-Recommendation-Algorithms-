//
// Created by vassilis on 17/10/2018.
//

#ifndef TEST_HASHNODE_H
#define TEST_HASHNODE_H


#include "../Item.h"

class HashNode {
private:
    Item* my_item;
    vector<int>gVector;
public:
    HashNode(Item *item,vector<int>* gvector);
    ~HashNode();
    vector<int>getGvector();
    string getItemName();
    void printGvector();
    Item* getItem();
    int size();
};


#endif //TEST_HASHNODE_H
