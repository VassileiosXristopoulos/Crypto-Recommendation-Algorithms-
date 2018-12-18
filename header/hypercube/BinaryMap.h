//
// Created by vassilis on 20/10/2018.
//

#ifndef TEST_BINARYMAP_H
#define TEST_BINARYMAP_H

#include <map>
#include <iostream>
using namespace std;
class BinaryMap {
private:
    map<int,char>Map;
public:
    void add(int num,char val);
    int get(int num);
    bool inMap(int num);
    int size();
};


#endif //TEST_BINARYMAP_H
