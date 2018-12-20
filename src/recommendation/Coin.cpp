//
// Created by vassilis on 19/12/2018.
//

#include "../../header/recommendation/Coin.h"
#include <algorithm>

Coin::Coin(vector<string> names) {
    for(auto const& i: names ){
        this->names.push_back(i);
    }
}

bool Coin::isCoin(string name) {
    return find(names.begin(), names.end(), name) != names.end();
}


