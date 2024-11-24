#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

using namespace std;

class Matrix {
private:
    int size;
    vector<vector<int> > matrix;
    bool isSymmetric;

public:
    Matrix(int numCities, int minDistance, int maxDistance, bool isSymmetric);
    Matrix(const string &filename);
    Matrix(const Matrix& other);

    int getDistance(int i, int j) const;
    int getSize() const;

private:
    void generateMatrix(int minDistance, int maxDistance, bool isSymmetric);
    void readMatrixFromFile(const string &filename);
    //void printMatrix() const;
};

#endif