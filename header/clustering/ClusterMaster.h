//
// Created by vassilis on 10/11/2018.
//

#ifndef CLUSTER_CLUSTERMASTER_H
#define CLUSTER_CLUSTERMASTER_H

// Lloyd's

#include <fstream>
#include "DataSetMap.h"
#include "Cluster.h"
#include "../lsh/AHashTable.h"
#include "../hypercube/AHypercube.h"
#include "../Util.h"
#include "../lsh/lsh.h"
#include "../hypercube/cube.h"

class ClusterMaster {
private:
    bool notFinished = true;
    bool canRepeat = false;
    DataSetMap* Dataset;
    vector<Cluster*> Clusters;
    vector<int>Choises;
    lsh * lsh_master;
    cube* hypercube_master;

    string metric;
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
    //void PrintResults(double);
    vector<double> Silhouette();
    void SetupParameters();
public:
    Config_info config_info; // TODO: place config info somewhere public
    ClusterMaster(vector<int>);
    ~ClusterMaster();
    void Clustering();
    vector<Cluster*> GetClusters();




};


#endif //CLUSTER_CLUSTERMASTER_H
