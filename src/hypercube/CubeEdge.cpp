#include <utility>

//
// Created by vassilis on 20/10/2018.
//

#include "../../header/hypercube/CubeEdge.h"
#include "../../header/Util.h"
CubeEdge::CubeEdge(vector<int> index) { //it has it's unique index, and a vector of items
    this->index = index;
}

CubeEdge::~CubeEdge() {

}

void CubeEdge::add(Item *item) {
    elements.push_back(item);
}

vector<Item *> CubeEdge::Elements() {
    return elements;
}

vector<int> CubeEdge::getIndex() {
    return index;
}

int CubeEdge::size() {
    int size=0;
    for(unsigned int i=0;i<index.size(); i++){
        size+=sizeof(index[i]);
    }
    for(unsigned int i=0;i<elements.size(); i++){
        size+=elements[i]->size();
    }
    return size;
}

