//
// Created by vassilis on 23/12/2018.
//

#include <algorithm>
#include "../../header/recommendation/Predictor.h"
#include "../../header/recommendation/Validator.h"

// constructor for prediction instance
Predictor::Predictor(vector<User *> &persons, vector<User *> &representatives, Config_info configuration,string& output_file) {
    this->configuration = configuration;
    this->PersonUsers = persons;
    this->Representatives = representatives;
    this->clusteringChoise = {1, 1, 1};
    this->lsh_master = nullptr;
    this->clustermaster = nullptr;
    this->outfile = new ofstream();
    this->outfile->open(output_file);
    this->isValidationInstance = false;
}

// constructor for validation instance
Predictor::Predictor(vector<User *> &persons,vector<User *> &represents, Config_info configuration, ofstream* outfile) {
    this->configuration = configuration;
    this->PersonUsers = persons;
    this->Representatives = represents;
    this->clusteringChoise = {1, 1, 1};
    this->lsh_master = nullptr;
    this->clustermaster = nullptr;
    this->outfile = outfile;
    this->isValidationInstance = true;
}


Predictor::~Predictor() {
    outfile->close();
    delete (outfile);
}

void Predictor::PerfromPrediction() {
    LshPrediction();
    ClusteringPrediction();
}

void Predictor::ClusteringPrediction() {
    PredictPersonClustering();
    cout << "Completed PredictPersonClustering" << endl;
    PredictRepresentClustering();
    cout << "Completed PredictRepresentClustering" << endl;

}

void Predictor::LshPrediction() {
    PredictPersonLSH();
    cout << "Completed PredictPersonLSH" << endl;

    PredictRepresentLSH();
    cout << "Completed PredictRepresentLSH" << endl;

}


void Predictor::PredictPersonLSH() {
    int i = 0;
    lsh_master = new lsh(configuration.lsh_L, configuration.lsh_L, configuration.w, PersonUsers);
    // for(auto const user : PersonUsers){ // for each user
    for (auto it = PersonUsers.begin(), end = PersonUsers.end(); it != end; it++) {
        User* user = it.operator*();
        vector<vector<double>> neighboors = lsh_master->FindNCloserNeighboors(user); //find his neighboors
        vector<pair<double, Coin *>> bestpredictions = ComputePredictions(user, neighboors, 5);

      //  if(!isValidationInstance)
        PrintPredictions(bestpredictions,user);
       /* else{
            // I have the user, I have the coin, I have the prediction
            //compute MAE
        }*/

        i++;
    }
    delete (lsh_master);
}

void Predictor::PredictRepresentLSH() {
    for (auto const user : PersonUsers) { // for each user
        vector<User *> allUsers = Representatives;
        allUsers.push_back(user);

        lsh_master = new lsh(configuration.lsh_L, configuration.lsh_L, configuration.w, allUsers);
        vector<vector<double>> neighboors = lsh_master->FindNCloserNeighboors(user); //find his neighboors
        vector<pair<double, Coin *>> bestpredictions = ComputePredictions(user, neighboors, 2);

        PrintPredictions(bestpredictions, user);


        delete (lsh_master);
    }
}

vector<pair<double, Coin *>>
Predictor::ComputePredictions(User *user, vector<vector<double>> neighboors, int amountOfbestPreds) {
    map<double, Coin *> recommendations; // a vector with all the recomendations, we will keep the best
    vector<double> userSentiments = user->GetSentimentVector();
    vector<double> similarities;

    for (unsigned int i = 0; i < userSentiments.size(); i++) {
        if (userSentiments[i] == 0) {
            double z = 0;
            double multSum = 0;
            for (auto const neighboor :  neighboors) {
                double similarity = Util::cosineSimilarity((vector<double> &) (neighboor), userSentiments);
                multSum += similarity * neighboor[i];
                z += abs(similarity);
            }
            if (z > 0)
                z = 1 / z;
            else
                continue;

            // find the coin associated with the recommendation that has been performed
            auto it = std::find_if(std::begin(Util::CoinMap), std::end(Util::CoinMap),
                                   [&](Coin *p) { return p->GetCoinIndex() == (int)i; }
            );
            if (it != end(Util::CoinMap))
                recommendations.insert(make_pair(z * multSum, it.operator*()));
        }
    }

    map<double, Coin *>::reverse_iterator it = recommendations.rbegin();

    vector<pair<double, Coin *>> returnVector;
    if ((int)recommendations.size() >= amountOfbestPreds) { // get first (ordered) n elements
        int i = 0;
        while (it != recommendations.rend()) {
            returnVector.emplace_back(it.operator*().first, it.operator*().second);
            if (++i == amountOfbestPreds)
                break;
            it++;
        }
    } else {
        while (it != recommendations.rend()) {
            returnVector.emplace_back(it.operator*().first, it.operator*().second);
            it++;
        }
    }

    return returnVector;

}

void Predictor::PredictPersonClustering() {
    clustermaster = new ClusterMaster(clusteringChoise, PersonUsers);
    clustermaster->Clustering();
    vector<Cluster *> clusters = clustermaster->GetClusters();
    clustermaster->ComputeVectorizedMembers();
    int k = 0;
    for (auto const &user: PersonUsers) {

        // find the cluster in which is our user
        auto it = find_if(clusters.begin(), clusters.end(),
                          [&](Cluster *mycluster) { return mycluster->Contains(user->GetUserId()); });
        if (it == clusters.end()) {
            continue;
        }

        vector<vector<double>> neighboors = clustermaster->GetVectorizedCluster(it.operator*());

        vector<pair<double, Coin *>> bestpredictions = ComputePredictions(user, neighboors, 5);

       // if(!isValidationInstance)
        PrintPredictions(bestpredictions,user);
     /*   else{
            //compute MAE
        }
*/
        k++;
    }
    delete (clustermaster);
}

void Predictor::PredictRepresentClustering() {
    for (auto const &user : PersonUsers) {
        vector<User *> allUsers = Representatives;
        allUsers.push_back(user);
        clustermaster = new ClusterMaster(clusteringChoise, allUsers);
        clustermaster->Clustering();
        vector<Cluster *> clusters = clustermaster->GetClusters();

        // find the cluster in which is our user
        auto it = find_if(clusters.begin(), clusters.end(),
                          [&](Cluster *mycluster) { return mycluster->Contains(user->GetUserId()); });
        if (it == clusters.end()) {
            continue;
        }

        Cluster *myCluster = it.operator*(); // this cluster contains the user
        vector<vector<double>> neighboors;
        for (auto const &member : myCluster->GetMembers()) { // get in the vector the content of each member of the
            // cluster (of each neighboor)
            if (member.first != user->GetUserId()) {
                neighboors.push_back(member.second->getContent());
            }
        }

        vector<pair<double, Coin *>> bestpredictions = ComputePredictions(user, neighboors, 5);

        PrintPredictions(bestpredictions, user);

        cout << "Shilouette: "<< clustermaster->Silhouette()<<endl;
        delete (clustermaster);
    }
}

void Predictor::PrintPredictions(vector<pair<double, Coin *>> predictions, User * user) {
    *outfile << user->GetUserId() << ": ";
    for ( auto const & prediction : predictions){
        *outfile << prediction.second->getName() << " ";
    }
    *outfile<<endl;
}

void Predictor::Validation() {
    // need to modify users before doing anything
    auto * validator = new Validator(PersonUsers,Representatives,configuration,outfile);
    validator->Validate();
}

ofstream *Predictor::GetOutputStream() {
    return outfile;
}

