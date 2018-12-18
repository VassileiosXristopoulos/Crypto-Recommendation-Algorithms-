//
// Created by vassilis on 21/10/2018.
//

#include <cmath>
#include <algorithm>
#include "../../header/hypercube/EucledianHypercube.h"
#include "../../header/Util.h"

EucledianHypercube::EucledianHypercube(int d) : AHypercube(d) {
        for(  int i = 0 ;i< d ; i++){
            Hi.push_back(new hashFunction());
        }
}

EucledianHypercube::~EucledianHypercube() {
    for(int i=0;i<d;i++){
        delete(Hi[i]);
    }
    for(int i=0;i<pow(2,d);i++)
        delete(edges[i]);
}

vector<int> EucledianHypercube::getBitVector(Item *item) {
    int dimensions = (int)Hi.size();
    // we want the size of the vector to be power of 2, so as to get
    //  the right number off the conversion from vector to int
    int nextPowof2dimensions = static_cast<int>(Util::upper_power_of_two(dimensions));
    vector<int> bitVector((unsigned long)(nextPowof2dimensions));

    for(int i=0; i< dimensions ; i++){
        int key = Hi[i]->hash(item); //get the gey
        if(binaryMap.inMap(key)){ //if we have already generated a binary value for this key, get it
            bitVector[i] = binaryMap.get(key);
        }
        else{ // generate a default binary value for this key, add it to the map
            char val = static_cast<char>(rand() % 2);
            binaryMap.add(key,val);
            bitVector[i] = val;
        }
    }

    return  bitVector;
}

double EucledianHypercube::computeDistance(vector<double> &x, vector<double> &y) {
    return Util::EucledianDistance(x,y);
}

int EucledianHypercube::size() {
    int size = sizeof(d)+binaryMap.size();
    for(unsigned int i=0; i<edges.size(); i++){
        size+= edges[i]->size();
    }
    for(unsigned int i=0; i<Hi.size(); i++){
        size+=Hi[i]->size();
    }
    return size;
}
