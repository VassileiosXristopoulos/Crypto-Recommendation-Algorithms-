//
// Created by vassilis on 18/10/2018.
//

#include <cmath>
#include <algorithm>
#include <bitset>
#include <regex>
#include <fstream>
#include "../header/Util.h"

int Util::my_mod(int x, int y) {
    return (x % y + y) % y;
}
double Util::EucledianDistance(vector<double> x, vector<double> y) {
    double distance=0;
    for (unsigned int j = 0; j < x.size(); j++) {
        distance += pow(x[j] - y[j], 2);
    }
    return sqrt(distance);
}

int Util::intVectortoInteger(vector<int> table) { //convert vector<int> to integer
    int retval = 0;
    int i =0;
    std::reverse(table.begin(),table.end());
    for (auto it = table.begin() ; it != table.end(); it++,i++){
        if(*it){
            retval |= 1<<i;
        }
    }
    return retval;
}

vector<int> Util::intToIntVector(int number, int d) { //convert int to vector<int>
    vector<int> ret = vector<int>((unsigned long)d);
    for ( int i = 0; i < d; i++) {
        ret[d - 1 - i] = (1 << i & number) != 0;
    }
    return ret;
}

unsigned long Util::upper_power_of_two(unsigned long v){ //find the closest upper power of 2 to v
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

void Util::getHammingCloseVectors( int changesLeft, vector<int>& str, const int i,
        vector<vector<int>>&res
) {                                 //get all the vectors with hamming distance up to "changesleft"
    if (changesLeft == 0) {
        res.push_back(str);
        return;
    }
    if (i < 0) return;

    str[i] ^= 1;
    getHammingCloseVectors(changesLeft-1,str, i-1,res);

    str[i] ^= 1;
    getHammingCloseVectors(changesLeft,str, i-1,res);
}

double Util::cosineDistance(vector<double> &x, vector<double> &y) {
    double sum=0,partial_sumX=0,partial_sumY=0;

    for(unsigned int i=0;i<x.size();i++){
        sum+=x[i]*y[i];
        partial_sumX+=pow(x[i],2);
        partial_sumY+=pow(y[i],2);
    }
    partial_sumX=sqrt(partial_sumX);
    partial_sumY=sqrt(partial_sumY);
    return 1 - sum/(partial_sumX*partial_sumY);
}

vector<string> Util::SplitBlanks(string &line) { //split a string by spaces and return a vector<string>
    vector<string> element;
    size_t pos = line.find(' ');
    size_t startPos = 0;
    while (pos != string::npos) {
        element.push_back(line.substr(startPos, pos - startPos));
        startPos = pos + 1;
        pos = line.find(' ', startPos);
    }
    element.push_back(line.substr(startPos, pos - startPos));

    return element;
}

vector<string> Util::SplitCommas(string &line) {
    vector<string> element;
    size_t pos = line.find(',');
    size_t startPos = 0;
    while (pos != string::npos) {
        element.push_back(line.substr(startPos, pos - startPos));
        startPos = pos + 1;
        pos = line.find(',', startPos);
    }
    element.push_back(line.substr(startPos, pos - startPos));

    return element;
}


int Util::safe_atoi(string input) {
    try {
        return stoi(input);
    }
    catch(std::exception const & e){
        cout << "Cannot parse string \"" << input << "\" to integer" << endl;
        exit(0);
    }

}

string Util::safe_getline(std::ifstream &config) {
    string temp;
    try{
        getline(config,temp);
        return  temp;
    }
    catch (ifstream::failure &e){
        cout <<"Cannot read file" <<endl;
        exit(0);
    }
}

vector<int> Util::GetUserChoise() {
    int* Choises = new int[3];
    Choises[0] = 0;
    Choises[1] = 0;
    Choises[2] = 0;
    int a;

    cout << "Please set the algorithm for clustering" << endl<<endl;

    cout << "Initialization" << endl;
    cout << "   1. Random selection of k points" << endl;
    cout << "   2. K-means++"<<endl;
    cin >> a;
    if( a == 1 || a ==2){
        Choises[0] = a;
    }
    else{
        cout << "Invalid value!" <<endl;
        exit(0);
    }

    cout << "Assignment" << endl;
    cout << "   1. Lloyd's Assignment" << endl;
    cout << "   2. Assignment by Range search with LSH"<<endl;
    cin >> a;
    if( a == 1 || a ==2 ||  a == 3){
        Choises[1] = a;
    }
    else{
        cout << "Invalid value!" <<endl;
        exit(0);
    }


    cout << "Update " << endl;
    cout << "   1. K-means" << endl;
    cout << "   2. Partitioning Around Medoids"<<endl;
    cin >> a;
    if( a == 1 || a ==2 ){
        Choises[2] = a;
    }
    else{
        cout << "Invalid value!" <<endl;
        exit(0);
    }

    vector<int>ret;
    for(int i=0;i<3;i++){
        ret.push_back(Choises[i]);
    }
    delete[] Choises;
    return ret;
}




