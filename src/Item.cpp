//
// Created by vassilis on 13/10/2018.
//

#include <cstdlib>
#include "../header/Item.h"
#include "../header/Util.h"

Item::Item(string name){
    this->name = name;
    this->cluster = -1;
}
Item::Item(vector<string> &element){

    name = element.at(0);
    element.erase(element.begin());

    for(unsigned int i=0;i<element.size();i++){
        content.push_back(stof(element[i]));
    }
    this->cluster = -1;

}


vector<double> &Item::getContent() {
    return content;
}
string Item::getName(){
    return name;
}
void Item::setGVector(vector<int>& h_i) {
    g_vector.clear();
    for(unsigned int i=0;i<h_i.size(); i++){
        g_vector.push_back(h_i[i]);
    }
}

Item::~Item() {}



vector<int>& Item::getGVector() {
    return g_vector;
}


int Item::size() {
    int size=(int)name.size();
    for(unsigned int i=0;i<content.size(); i++){
        size+=sizeof(content[i]);
    }
    for(unsigned int i=0; i<g_vector.size(); i++){
        size+=sizeof(g_vector[i]);
    }
    return size;
}

void Item::SetContent(vector<double>& content) {
    this->content = content;

}

double Item::GetPoint(int p) {
    return content[p];
}

void Item::SetCluster(int cluster) {
    this->cluster = cluster;
}

int Item::GetCluster() {
    return cluster;
}






