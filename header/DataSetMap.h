//
// Created by vassilis on 13/10/2018.
//

#ifndef DATASETMAP_H
#define DATASETMAP_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "Item.h"

using namespace std;
class DataSetMap {
private:
    vector<Item*>Map;
public:
    DataSetMap() = default;
    DataSetMap(DataSetMap&);
    ~DataSetMap();
    void append(Item *item);
    double TrueDistance(Item*item,string mode);
    int size();
    Item* at(int index);
    void InsertFile(string file);
    void erase(Item *);
    void clean();
};


#endif
