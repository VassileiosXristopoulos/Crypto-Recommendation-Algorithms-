//
// Created by vassilis on 10/11/2018.
//

#include "../../header/clustering/Cluster.h"
#include "../../header/Util.h"

Cluster::Cluster() {
    Centroid = nullptr;
}

Cluster::~Cluster() {
    if(Centroid != nullptr && Centroid->getName() == "null")
        delete Centroid;
}
/**
 * Sets an Item as Centroid of the Cluster
 */
void Cluster::SetCentroid(Item * item) {
    if(Centroid != nullptr && Centroid->getName() == "null")
        delete Centroid;
    Centroid = item;
}



/**
 * Returns the Centroid of the Cluster
 */
Item *Cluster::GetCentroid() {
    return Centroid;
}



/**
 * Returns true if an Item is member of this Cluster
 */
bool Cluster::Contains(string item) {
    return Members.find(item) != Members.end();
}



/**
 * Delete a Member and return it
 */
void Cluster::DeleteMember(string item) {
    Members.erase(item);
}



/**
 * Add a new Member
 */
void Cluster::InsertMember(Item * item) {
    Members.insert(pair<string,Item*>(item->getName(),item));
}




/**
 * Update Members
 */
bool Cluster::Update(int algorithm) {
    bool ret;
    switch (algorithm){
        case 1:
            ret = kmeans();
            break;
        case 2:
            ret = PAM();
            break;
        default:
            cout<< "Error: No Update can be performed" <<endl;
            exit(0);
    }
    return ret;

}

int Cluster::size() {
    return (int)this->Members.size();
}

bool Cluster::PAM() {
    if(Members.empty()) return true;
    vector<pair<double,string>>distances;
    double min_sum = -1.0;
    Item *newCentroid;
    for(auto const& i : Members) { // for each element of Cluster
        Item * element_i = i.second;

        double sum =0; // sum of distances of items from element_i (to be centroid)
        for(auto const& j : Members){ // get every member of cluster
            Item * element_j = j.second;
            if(element_i->getName() != element_j->getName()) { // except itself
                sum += Util::EucledianDistance(element_i->getContent(), element_j->getContent());
            }
            if(min_sum != -1 && sum > min_sum) // if until now sum greater than min sum, stop searching
                break;
        }
        if(min_sum == -1.0){
            newCentroid = element_i;
            min_sum = sum;
        }
        else if(min_sum>sum){
            newCentroid = element_i;
            min_sum = sum;
        }
    }

    if(Centroid != nullptr) {
        for (unsigned int i = 0; i < Centroid->getContent().size(); i++) {
            // check if the centroid remains the same (condition checks if 2 contents are  equal)
            if (Centroid->getContent()[i] != newCentroid->getContent()[i]) {
                this->Centroid = newCentroid;
                return false;
            }
        }
    }


    return true;

}



/**
 * Update Members
 * K-Means
 */
bool Cluster::kmeans() {
    if(Members.empty()) return true;

    Item * newCentroid = new Item("null");
    int totalElements = static_cast<int>(Members.size());
    int dimensions = static_cast<int>(Members.begin()->second->getContent().size());
    vector<double>Points = vector<double>(dimensions,0); // set size to be the same with Item's content, init all with 0

    for(auto const& i : Members){ // for each element of Cluster
        Item * element_i = i.second;
        for(int j=0; j< dimensions ; j++){ // for each point of the element
            Points[j] += element_i->GetPoint(j);
        }
    }
    for (int l = 0; l < dimensions; ++l) {
        Points[l] /= totalElements;
    }

    newCentroid->SetContent(Points);

    if(Centroid != nullptr) {
        for(unsigned int i=0;i<Centroid->getContent().size();i++){
            // check if the centroid remains the same (condition checks if 2 contents are  equal)
            if (Centroid->getContent()[i] != newCentroid->getContent()[i]) {

                if ("null" == Centroid->getName())
                    delete Centroid;

                this->Centroid = newCentroid;
                return false;

            }
        }
    }

    delete newCentroid;

    return true;
}

void Cluster::FlushClusterMembers() {
    for(auto const & i : Members)
        i.second->SetCluster(-1); // item belongs to no cluster
    this->Members.clear();
}

map<string,Item*> Cluster::GetMembers() {
    return this->Members;
}




