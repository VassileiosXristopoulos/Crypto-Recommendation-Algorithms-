//
// Created by vassilis on 18/10/2018.
//

#include <random>
#include "../../header/lsh/cosineHashfunction.h"
#include "../../header/lsh/lsh.h"
#include "../../header/rangeSearch_consts.h"

extern default_random_engine generator;
extern normal_distribution<float> distribution;
cosineHashfunction::cosineHashfunction() {
    if(rangeSearch_consts::d<=0){
        cout << "d must be positive while constructing cosineHashFunction" << endl;
        exit(0);
    }

    for( int i=0; i<rangeSearch_consts::d ; i++){
        v.push_back(distribution(generator));
    }
}

cosineHashfunction::~cosineHashfunction() {

}

int cosineHashfunction::hash(Item *item) {
    vector<double>p_item = item->getContent();
    float sum=0;
    for(unsigned int i=0;i<p_item.size();i++){
        sum += p_item[i]*v[i];
    }
    return sum>=0;
}

int cosineHashfunction::size() {
    int size=0;
    for(unsigned int i=0;i<v.size(); i++){
        size+=sizeof(v[i]);
    }
    return size;
}
