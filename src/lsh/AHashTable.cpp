//
// Created by vassilis on 21/10/2018.
//

#include "../../header/lsh/AHashTable.h"

AHashTable::AHashTable(int size, int k) {
    TableSize = size;
    Table = vector<vector<HashNode*>>(TableSize);
}

AHashTable::~AHashTable() {

}
