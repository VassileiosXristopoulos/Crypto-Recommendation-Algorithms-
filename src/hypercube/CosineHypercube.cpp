//
// Created by vassilis on 20/10/2018.
//

#include <cmath>
#include <algorithm>
#include "../../header/hypercube/CosineHypercube.h"
#include "../../header/Util.h"
#include "../../header/lsh/cosineHashfunction.h"
#include "../../header/hypercube/AHypercube.h"

CosineHypercube::CosineHypercube(int d) : AHypercube(d) {
    cosine_vector = vector<cosineHashfunction *>(d); //construct the hashfunction for hi()
    for( int i=0; i<d ;i++){
        cosine_vector[i] = new cosineHashfunction();
    }
}

CosineHypercube::~CosineHypercube(){
    for(int i=0;i<d;i++){
        delete(cosine_vector[i]);
    }
    for(int i=0;i<pow(2,d);i++)
        delete(edges[i]);
}
vector<int> CosineHypercube::getBitVector(Item*item){
    int dimensions = (int)cosine_vector.size();
    // we want the size of the vector to be power of 2, so as to get
    //  the right number off the conversion from vector to int
    int nextPowof2dimensions = static_cast<int>(Util::upper_power_of_two(dimensions));
    vector<int>ret(nextPowof2dimensions);
    for(int i=0; i<dimensions ;i++){
        ret[i] = cosine_vector[i]->hash(item);
    }
    return ret;

}


double CosineHypercube::computeDistance(vector<double>&x,vector<double>&y) {
    return Util::cosineDistance(x,y);
}

int CosineHypercube::size() {
    int size = sizeof(d)+binaryMap.size();
    for(unsigned int i=0; i<edges.size(); i++){
        size+= edges[i]->size();
    }
    for(unsigned int i=0;i<cosine_vector.size(); i++){
        size+=cosine_vector[i]->size();
    }
    return size;
}





