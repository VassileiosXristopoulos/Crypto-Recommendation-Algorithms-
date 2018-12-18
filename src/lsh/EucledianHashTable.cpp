//
// Created by vassilis on 14/10/2018.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "../../header/lsh/EucledianHashTable.h"
#include "../../header/Item.h"
#include "../../header/lsh/HashNode.h"
#include "../../header/Util.h"
#include "../../header/lsh/lsh.h"
#include "../../header/rangeSearch_consts.h"

using namespace std;

EucledianHashTable::EucledianHashTable(int k, int size): AHashTable(size,k) {

    for(  int a=0; a<k; a++){
       r_vector.push_back(rand()%10+1); //construct an array with constants r
       H_vector.push_back(new hashFunction()); //construct the h(i) hash functions
    }
}


EucledianHashTable::~EucledianHashTable() {
    for(unsigned int i=0;i<Table.size();i++){
        for(unsigned int j=0;j<Table[i].size();j++){
            delete(Table[i][j]);
        }
    }
    for(unsigned int i=0;i<r_vector.size();i++){
        delete(H_vector[i]);
    }
}
void EucledianHashTable::add(Item* item){
    int key = hash(item);
    Table[key].push_back(new HashNode(item,computeGVector(item)));
}




int EucledianHashTable::hash(Item *item) {
    int sum = 0;
    int M = (int)pow(2.0,32.0) -5;
    vector<int>*h_i=computeGVector(item);
    for(unsigned  int i=0; i< r_vector.size() ; i++){
       sum += Util::my_mod(((int)r_vector[i])*(*h_i)[i],M);
    }
    delete h_i;
    return Util::my_mod(sum,TableSize);
}



vector< Item* > EucledianHashTable::findNcloserNeighbors(Item *item,double r){
    int bucket = hash(item);
    vector<int>*item_gVector=computeGVector(item);
    item->setGVector(*item_gVector);
    delete item_gVector;
    vector< Item* >ret;
    for(unsigned int i=0; i<Table[bucket].size(); i++) {
        bool match = true;

        for (unsigned int j = 0; j < item->getGVector().size(); j++) {  //for each item of the bucket
            if (item->getGVector()[j] != Table[bucket][i]->getGvector()[j]) { //check if g(p)==g(q)
                match = false;
                break;
            }
        }
        if (match) { // if  g(p)==g(q)
            Item * datasetItem = Table[bucket][i]->getItem();

            double distance = Util::EucledianDistance(item->getContent(), Table[bucket][i]->getItem()
                    ->getContent()); //compute distance of items
            if (item->getName().compare(datasetItem->getName()) != 0) {
                if (distance < r ) { //if distance < radius
                    ret.push_back(datasetItem);
                }
            }
        }

    }
    return ret;
}



vector<int>* EucledianHashTable::computeGVector(Item* item){
    vector<int>* h_i= new vector<int>(rangeSearch_consts::k);
    for(unsigned  int i=0; i< h_i->size() ; i++) {
        (*h_i)[i] = H_vector[i]->hash(item);
    }

    return h_i;
}

int EucledianHashTable::size() {
    int size=TableSize;
    for(unsigned int i=0; i<H_vector.size(); i++){
        size+=H_vector[i]->size();
    }
    for(unsigned int i=0;i<r_vector.size(); i++){
        size+=sizeof(r_vector[i]);
    }
    for(unsigned int i=0;i<Table.size(); i++){
        for(unsigned int j=0; j<Table[i].size(); j++){
            size+= Table[i][j]->size();
        }
    }
    return size;
}





