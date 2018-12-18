//
// Created by vassilis on 13/10/2018.
//

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

#include "rangeSearch_consts.h"

using namespace std;

class Item {
private:
    string name;
    vector<double>content;
    vector<int>g_vector;
    int cluster;
public:
    Item(string);
    Item(vector<string>&element);
    ~Item();
    vector<double>& getContent();
    void SetContent(vector<double>&);
    string getName();
    void setGVector(vector<int>& h_i);
    vector<int>& getGVector();
    double GetPoint(int);
    int size();
    void SetCluster(int);
    int GetCluster();
};


#endif //TEST_ITEM_H
