//
// Created by vassilis on 21/10/2018.
//

#include <algorithm>
#include "../../header/hypercube/AHypercube.h"
#include "../../header/Util.h"
AHypercube::AHypercube(int d) { //construct the common fields of every hypercube. The number of edges, and the edges.
    this->d = d;
    for( int i = 0 ;i< pow(2,d) ; i++){
        edges.push_back(new CubeEdge(Util::intToIntVector(i,d)));
    }
}

vector<CubeEdge *> AHypercube::getHamingCLose(int hammingDist, CubeEdge *edge) { //get all the close adges to an edge
    vector<int>index = edge->getIndex();
    size_t sizeOfIndex = index.size();
    vector<CubeEdge *> closeEdges;
    vector<vector<int>> indexes; //the indexes are stored correctly, not need to reverse
    Util::getHammingCloseVectors(hammingDist,index,sizeOfIndex-1,indexes); //given the index of the edge, return the
    // close indexes
    for(unsigned int i=0 ;i<indexes.size() ;i++){
        int upperPowof2 = Util::upper_power_of_two(indexes[i].size());
        vector<int>fullSize_vector(upperPowof2);
        /*-------- vector's size is not power of 2, make it ---------*/
        if(indexes[i].size()!= (unsigned int)upperPowof2){
            for(unsigned int j=0;j<indexes[i].size();j++){
                fullSize_vector[j] = indexes[i][j];
            }

        }
        else
            fullSize_vector = indexes[i];
        /*-----------------------------------------------------------*/
        std::reverse(fullSize_vector.begin(),fullSize_vector.end());//intVectortoInteger computes int with reversed bitVector
        closeEdges.push_back(edges[Util::intVectortoInteger(fullSize_vector)]); //get all the edges with the
        // indexes found and return them
        // push back the edge that has the index "fullsize_vector"
    }

    return closeEdges;
}



vector<Item*> AHypercube::findRCloser(Item *item, int max, int probes, double radius) {
    vector<int>bitVector = getBitVector(item); //getBitvector returns the right vector
    std::reverse(bitVector.begin(),bitVector.end());
    CubeEdge * currentEdge = edges[Util::intVectortoInteger(bitVector)];
    vector<Item*>elements = currentEdge->Elements();
    vector <Item*> rNearest;
    int elems_checked = 0;
    for(unsigned int i=0;i < elements.size() ;i++){
        if(elems_checked++ > max) return rNearest;
        double dist = computeDistance(item->getContent(),elements[i]->getContent());
        if(dist<radius){
            rNearest.push_back(elements[i]);
        }

    }
    int hamminDist = 1, probes_checked = 0;
    while(1){
        if(probes_checked==probes) break;
        vector<CubeEdge*> hamingClose = getHamingCLose(hamminDist,currentEdge);
        if(hamingClose.size()==0) return rNearest; // no other edge available

        for(unsigned int i=0 ; i<hamingClose.size(); i++){ //for each close edge

            vector<Item*> items = hamingClose[i]->Elements();
            for(unsigned int j=0 ; j<items.size() ; j++){ // for each element of close edge
                if(elems_checked++ > max) return rNearest;
                double dist = computeDistance(item->getContent(),items[j]->getContent());
                if(dist<radius)
                    rNearest.push_back(items[j]);
            }

            if(++probes_checked==probes) return rNearest;
        }

        hamminDist++;
    }
    return rNearest;


}

void AHypercube::add(Item *item) {
    vector<int>bitVector = getBitVector(item);
    std::reverse(bitVector.begin(),bitVector.end());
    edges[Util::intVectortoInteger(bitVector)]->add(item); //add to the hypercube depending on the bitset returned
}

AHypercube::~AHypercube() { //all deletions implemented by the concrete classes

}


