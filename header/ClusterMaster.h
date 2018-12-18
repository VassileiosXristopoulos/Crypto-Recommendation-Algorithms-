//
// Created by vassilis on 10/11/2018.
//

#ifndef CLUSTER_CLUSTERMASTER_H
#define CLUSTER_CLUSTERMASTER_H

// Lloyd's

#include <fstream>
#include "DataSetMap.h"
#include "Cluster.h"
#include "lsh/AHashTable.h"
#include "hypercube/AHypercube.h"
#include "Util.h"
#include "lsh/lsh.h"
#include "hypercube/cube.h"

class ClusterMaster {
private:
    bool notFinished = true;
    bool canRepeat = false;
    bool complete;
    DataSetMap* Dataset;
    vector<Cluster*> Clusters;
    vector<int>Choises;
    lsh * lsh_master;
    cube* hypercube_master;
    Config_info config_info;
    string metric;
    string output_file;
    ofstream outfile;

    void Initialization();
    void RandomSelection();
    void kmeanspp();
    void Assignement();
    void LloydsAssignment();
    void RangeSearchAssignment(string&);
    vector<Item*> GenericFindinRange(string&,Item*,double);
    void Update();
    void SetNextChoise();
    void ResetDataset();
    void PrintResults(double);
    vector<double> Silhouette();
public:
    ClusterMaster(Config_info, DataSetMap*, vector<int>,string&,string&,bool);
    ~ClusterMaster();
    void Clustering();




};


#endif //CLUSTER_CLUSTERMASTER_H
