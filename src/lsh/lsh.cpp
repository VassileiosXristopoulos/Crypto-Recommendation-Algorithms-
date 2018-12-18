//
// Created by vassilis on 13/11/2018.
//

#include <algorithm>
#include "../../header/lsh/lsh.h"
#include "../../header/lsh/EucledianHashTable.h"
#include "../../header/lsh/CosineHashTable.h"
#include "../../header/Util.h"
#include "../../header/rangeSearch_consts.h"

lsh::lsh(int k, int L, int w, string& metric,DataSetMap *set) {

    rangeSearch_consts::L = L;
    rangeSearch_consts::k = k;
    rangeSearch_consts::w = w;
    rangeSearch_consts::d = (int)set->at(0)->getContent().size();

    for (int i = 0; i < L; i++) { //construct the L HashTables
        if (metric == "eucledian") {
            this->LshHashTables.push_back(new EucledianHashTable(k, set->size() / 8));
        }
        else {
            this->LshHashTables.push_back(new CosineHashTable(set->size() / 2, k));
        }
        for (int j = 0; j < set->size(); j++) {
            LshHashTables[i]->add(set->at(j));
        }
    }

}

vector<Item*> lsh::FindItemsInRange(Item * centroid, double r) {
    vector<Item*> closerNneighboors=vector<Item*>();
    if(rangeSearch_consts::L == -1){
        cout <<"Cannot perform LSH" <<endl;
        exit(0);
    }
    for (int i = 0; i < rangeSearch_consts::L; i++) { //for each hashtable
        vector<Item*> Nneighboors = this->LshHashTables[i]->findNcloserNeighbors(centroid,r);

        for(unsigned int j=0; j<Nneighboors.size(); j++){
            if(Nneighboors[j]->GetCluster() != centroid->GetCluster()){ // return only those NOT already in the cluster
                closerNneighboors.push_back(Nneighboors[j]);
            }

        }

    }
    if(closerNneighboors.size()>0){
        sort(closerNneighboors.begin(), closerNneighboors.end());
        closerNneighboors.erase(unique(closerNneighboors.begin(), closerNneighboors.end()), closerNneighboors
                .end());
    }
    return closerNneighboors;
}

lsh::~lsh() {
    for (unsigned int i = 0; i < LshHashTables.size(); i++) {
        delete (LshHashTables[i]);
    }
}


