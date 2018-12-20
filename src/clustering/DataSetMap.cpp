//
// Created by vassilis on 13/10/2018.
//

#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "../../header/clustering/DataSetMap.h"
#include "../../header/Util.h"
#include "../../header/lsh/lsh.h"
#include "../../header/clustering/rangeSearch_consts.h"

int n;


DataSetMap::~DataSetMap() {
    for(unsigned int i=0; i<Map.size(); i++){
        if(Map[i] != nullptr) {
            delete (Map[i]);
        }
    }
}


void DataSetMap::append(Item * item) {
    Map.push_back(item);
}



double DataSetMap::TrueDistance(Item *item,string mode) {
    double min=-1;
    for (auto &i : Map) {
        double dist;
        if(mode == "eucledian"){
            dist= Util::EucledianDistance(item->getContent(), i->getContent());
        }
        else if(mode == "cosine"){
            dist=Util::cosineDistance(item->getContent(), i->getContent());
        }
        if(min==-1 || dist<min)
            min = dist;
    }
    return min;
}

int DataSetMap::size(){
    return static_cast<int>(Map.size());
}

Item *DataSetMap::at(int index) {
    return Map[index];
}

void DataSetMap::InsertFile(const string inputFile) {
    string FileLine;
    ifstream file(inputFile);

    //count lines of file -- if k = default then k = log2(n) -- for hypercube
    n = (int)std::count(std::istreambuf_iterator<char>(file),
               std::istreambuf_iterator<char>(), '\n') - 1;
    if(rangeSearch_consts::k==-1) rangeSearch_consts::k = (int)log2(n);
    file.close();

    ifstream input(inputFile);

    for( std::string line; getline( input, FileLine ); ) {

        line = FileLine.substr(0, FileLine.size() - 1);
        vector<string> element = Util::SplitCommas(line);
        Item *item = new Item(element);

        if(element.size()<=0){
            cout <<"element empty!!"<<endl;
            continue;
        }
        Map.push_back(item);

    }

}

DataSetMap::DataSetMap(DataSetMap & Map) {
    for(int i=0;i<Map.size(); i++){
        this->Map.push_back(Map.at(i));
    }
}

void DataSetMap::erase(Item *item) {
    unsigned int pos = (unsigned int)(find(Map.begin(), Map.end(), item) - Map.begin());
    if(pos<Map.size()){
        Map.erase(Map.begin()+pos);
    }
}

void DataSetMap::clean() {
    for(unsigned int i=0;i<Map.size();i++){
        Map[i] = nullptr;
    }
}






