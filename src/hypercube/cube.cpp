//
// Created by vassilis on 16/11/2018.
//

#include "../../header/hypercube/cube.h"
#include "../../header/hypercube/CosineHypercube.h"
#include "../../header/hypercube/EucledianHypercube.h"

cube::cube(int k, int w, int probes, int M, string &metric, DataSetMap *set) {

    rangeSearch_consts::k = k;
    rangeSearch_consts::w = w;
    rangeSearch_consts::probes = probes;
    rangeSearch_consts::M = M;
    rangeSearch_consts::d = (int)set->at(0)->getContent().size();

    if (metric == "eucledian") {
        hypercube = new EucledianHypercube(k);
    } else {
        hypercube = new CosineHypercube(k);
    }
    for (int i = 0; i < set->size(); i++) {
        hypercube->add(set->at(i));
    }
}

vector<Item *> cube::FindItemsInRange(Item *centroid, double r) {
    vector<Item*>ret;
    vector<Item*> items= hypercube->findRCloser(centroid,rangeSearch_consts::M,rangeSearch_consts::probes,r);
    for(unsigned int i=0;i<items.size();i++){
        if(centroid->GetCluster() != items[i]->GetCluster()){ // return only those NOT already in the cluster
            ret.push_back(items[i]);
        }
    }
    return ret;
}

cube::~cube() {
    delete (hypercube);
}
