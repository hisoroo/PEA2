#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

using namespace std;

class Config {
public:
    string outputFile;
    string inputFile;
    int repetitions;
    bool showProgressBar;
    int distanceMin;
    int distanceMax;
    bool isSymmetric;
    vector<int> NCities;

    Config(const string &filename);

private:
    void readConfig(const string &filename);
};

#endif