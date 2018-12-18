//
// Created by vassilis on 21/10/2018.
//

#include <algorithm>
#include "../../header/lsh/CosineHashTable.h"
#include "../../header/Util.h"

CosineHashTable::CosineHashTable(int size, int k) : AHashTable(size,k){
    for(  int a=0; a<k; a++){
        cosine_vector.push_back(new cosineHashfunction()); //construct the h(i) for the hashTable
    }
    this->k = k;
}

vector<int>* CosineHashTable::computeGVector(Item *item) {
    vector<int>*ret= new vector<int>(k);
    for( int i=0; i<k ;i++){
        (*ret)[i] = cosine_vector[i]->hash(item);
    }
    return ret;
}

int CosineHashTable::hash(Item *item) {
    vector<int>* table = computeGVector(item);
    std::reverse(table->begin(),table->end());
    int ret = Util::my_mod(Util::intVectortoInteger(*table),TableSize);
    delete table;
    return ret;
}

void CosineHashTable::add(Item *item) {
    int key = hash(item);
    Table[key].push_back(new HashNode(item,computeGVector(item)));
}

vector<Item*>  CosineHashTable::findNcloserNeighbors(Item *item,double r) {
    int bucket = hash(item);

    vector <Item*> ret;
    for(unsigned int i=0; i<Table[bucket].size(); i++) { //compute distance within all items of the same bucket
                                                        // because hashfunction returns bitset, so all g(i)'s are the
                                                        // same

        Item * datasetItem = Table[bucket][i]->getItem();
        double distance = Util::cosineDistance(item->getContent(), datasetItem->getContent());

        if (item->getName().compare(datasetItem->getName()) != 0) {
            if (distance < r ) {
                ret.push_back(datasetItem);
            }
        }


    }
    return ret;
}


CosineHashTable::~CosineHashTable()  {
    for(unsigned int i=0;i<Table.size();i++){
        for(unsigned int j=0;j<Table[i].size();j++){
            delete(Table[i][j]);
        }
    }
    for(int i = 0; i<k; i++){
        delete(cosine_vector[i]);
    }
}

int CosineHashTable::size() {
    int size=sizeof(k);
    for(unsigned int i=0; i<cosine_vector.size(); i++){
        size+=cosine_vector[i]->size();
    }
    for(unsigned int i=0;i<Table.size(); i++){
        for(unsigned int j=0; j<Table[i].size(); j++){
            size+= Table[i][j]->size();
        }
    }
    return size;
}

