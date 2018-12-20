//
// Created by vassilis on 19/12/2018.
//

#ifndef RECOMMENDATION_COIN_H
#define RECOMMENDATION_COIN_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;
class Coin {
private:
    vector<string>names;
public:
    Coin(vector<string>);
    bool isCoin(string);
};


#endif //RECOMMENDATION_COIN_H
