//
// Created by vassilis on 10/11/2018.
//
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../header/clustering/DataSetMap.h"
#include "../header/clustering/ClusterMaster.h"
#include "../header/Util.h"
#include "../header/recommendation/TwitterUserFactory.h"

int k=0;
int main(int argv, char*argc[]){

    // TODO: add check for input parameters
    string input_file = argc[2];
    string output_file = argc[4];

    // TODO : add -validate parameter handling

    vector<int> Choises = Util::GetUserChoise();
    ClusterMaster* Clustermaster = new ClusterMaster(Choises);
    Clustermaster->Clustering();

    vector<Cluster*>clusters = Clustermaster->GetClusters();

    Util::Initialize();

    TwitterUserFactory * twitterUserFactory = new TwitterUserFactory(input_file,clusters);


    delete (Clustermaster);
}