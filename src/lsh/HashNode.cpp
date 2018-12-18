//
// Created by vassilis on 17/10/2018.
//

#include "../../header/lsh/HashNode.h"

HashNode::HashNode(Item *item,vector<int>* gvector) {
    my_item=item;
    for(unsigned int i=0;i<(*gvector).size();i++){
        this->gVector.push_back((*gvector)[i]);
    }
    delete gvector;
}

HashNode::~HashNode() {

}

vector<int> HashNode::getGvector(){
    return gVector;
}

string HashNode::getItemName(){
    return my_item->getName();
}

void HashNode::printGvector(){
    for(unsigned int i=0;i<gVector.size();i++){
        cout << gVector[i] << " ";
    }
}

Item *HashNode::getItem(){
    return my_item;
}

int HashNode::size() {
    int size=my_item->size();
    for(unsigned int i=0;i<gVector.size(); i++){
        size+=sizeof(gVector[i]);
    }
    return size;
}
