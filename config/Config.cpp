#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <cstdlib>

using namespace std;

Config::Config(const string &filename) {
    readConfig(filename);
}

void Config::readConfig(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku konfiguracyjnego, upewnij się że nazwa pliku jest poprawna.\n";
        exit(1);
    }

    string line;
    map<string, string> configMap;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        istringstream iss(line);
        string key, value;
        if (getline(iss, key, '=') && getline(iss, value)) {
            configMap[key] = value;
        }
    }

    outputFile = configMap["outputFile"];
    inputFile = configMap["inputFile"];
    repetitions = stoi(configMap["repetitions"]);
    showProgressBar = configMap["showProgressBar"] == "1";
    distanceMin = stoi(configMap["distanceMin"]);
    distanceMax = stoi(configMap["distanceMax"]);
    isSymmetric = configMap["isSymmetric"] == "1";
    string nCitiesStr = configMap["NCities"];
    
    istringstream nCitiesStream(nCitiesStr);
    string nValue;
    while (getline(nCitiesStream, nValue, ',')) {
        NCities.push_back(stoi(nValue));
    }
}