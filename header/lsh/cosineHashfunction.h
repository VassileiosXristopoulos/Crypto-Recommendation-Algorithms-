//
// Created by vassilis on 18/10/2018.
//

#ifndef TEST_COSINEHASHFUNCTION_H
#define TEST_COSINEHASHFUNCTION_H


#include "../Item.h"

class cosineHashfunction {
private:
    vector<float>v;
public:
    cosineHashfunction();
    ~cosineHashfunction();
    int hash(Item* item);
    int size();
};


#endif //TEST_COSINEHASHFUNCTION_H
