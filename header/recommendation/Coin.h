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
    int index;
public:
    Coin(vector<string>, int);
    bool isCoin(string);
    int GetCoinIndex();
    string getName();
};


#endif //RECOMMENDATION_COIN_H
