//
// Created by vassilis on 13/11/2018.
//

#include <algorithm>
#include "../../header/lsh/lsh.h"
#include "../../header/lsh/EucledianHashTable.h"
#include "../../header/lsh/CosineHashTable.h"
#include "../../header/Util.h"
#include "../../header/clustering/rangeSearch_consts.h"
#include "../../header/Consts.h"

lsh::lsh(int k, int L, int w, string &metric, DataSetMap *set) {

    rangeSearch_consts::L = L;
    rangeSearch_consts::k = k;
    rangeSearch_consts::w = w;
    rangeSearch_consts::d = (int) set->at(0)->getContent().size();

    for (int i = 0; i < L; i++) { //construct the L HashTables
        if (metric == "eucledian") {
            this->LshHashTables.push_back(new EucledianHashTable(k, set->size() / 8));
        } else {
            this->LshHashTables.push_back(new CosineHashTable(set->size() / 2, k));
        }
        for (int j = 0; j < set->size(); j++) {
            LshHashTables[i]->add(set->at(j));
        }
    }

}

lsh::lsh(int k, int L, int w, vector<User *> set) {
    rangeSearch_consts::L = L;
    rangeSearch_consts::k = k;
    rangeSearch_consts::w = w;
    rangeSearch_consts::d = (int) set[0]->GetSentimentVector().size();
    for (int i = 0; i < L; i++) { //construct the L HashTables
        this->LshHashTables.push_back(new CosineHashTable((int) set.size() / 2, k));
        for (auto const &j: set) { // TODO : check this. All users are duplicates
            Item* newUser = new Item(j->GetUserId(), j->GetSentimentVector());
            this->Dataset.push_back(newUser);
            LshHashTables[i]->add(newUser);
        }
    }
}

lsh::~lsh() {
    if(!this->Dataset.empty()) {
        for (auto item : this->Dataset)
            delete item;
    }
    for (unsigned int i = 0; i < LshHashTables.size(); i++) {
        delete (LshHashTables[i]);
    }
}

vector<Item *> lsh::FindItemsInRange(Item *centroid, double r) {
    vector<Item *> closerNneighboors = vector<Item *>();
    if (rangeSearch_consts::L == -1) {
        cout << "Cannot perform LSH" << endl;
        exit(0);
    }
    for (int i = 0; i < rangeSearch_consts::L; i++) { //for each hashtable
        vector<Item *> Nneighboors = this->LshHashTables[i]->findCloserNeighbors(centroid, r);

        for (unsigned int j = 0; j < Nneighboors.size(); j++) {
            if (Nneighboors[j]->GetCluster() !=
                centroid->GetCluster()) { // return only those NOT already in the cluster
                closerNneighboors.push_back(Nneighboors[j]);
            }

        }

    }
    if (closerNneighboors.size() > 0) {
        sort(closerNneighboors.begin(), closerNneighboors.end());
        closerNneighboors.erase(unique(closerNneighboors.begin(), closerNneighboors.end()), closerNneighboors
                .end());
    }
    return closerNneighboors;
}

vector<vector<double>> lsh::FindNCloserNeighboors(User *user) {
    vector<vector<double>> closerNneighboors = vector<vector<double>>();
    if (rangeSearch_consts::L == -1) {
        cout << "Cannot perform LSH" << endl;
        exit(0);
    }

    for (int i = 0; i < rangeSearch_consts::L; i++) { //for each hashtable
        /* for (auto const &sent : user->GetSentimentVector()) {
             if (sent != 0) {
                 cout << "found it" << endl;
             }
         }*/
        Item *newItem = new Item(user->GetUserId(), user->GetSentimentVector());
        vector<Item *> Nneighboors = this->LshHashTables[i]->findNCloserNeighboors(newItem, Consts::amountOfNeighboors);
        delete(newItem);

        for (unsigned int j = 0; j < Nneighboors.size(); j++) {
            if (Nneighboors[j]->getName() != user->GetUserId()) { // return it if not same user
                closerNneighboors.push_back(Nneighboors[j]->getContent());
            }

        }


    }
    // TODO: check if "User *user" in lamda is the correct user
    // sort and get the 20-50 closer
    std::sort(closerNneighboors.begin(), closerNneighboors.end(),
              [&](std::vector<double> a, std::vector<double> b) {
                  return Util::cosineDistance(a, user->GetSentimentVector()) < Util::cosineDistance(b,
                                                                                                    user->GetSentimentVector());
              });
    closerNneighboors.erase(unique(closerNneighboors.begin(), closerNneighboors.end()), closerNneighboors
            .end());
    if (closerNneighboors.size() >= Consts::amountOfNeighboors) {

        return vector<vector<double>>(closerNneighboors.begin(),
                                      closerNneighboors.begin() + Consts::amountOfNeighboors);
    } else {
        return closerNneighboors;
    }
}


