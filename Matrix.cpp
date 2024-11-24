#include "Matrix.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <cstdlib>

using namespace std;

Matrix::Matrix(int numCities, int minDistance, int maxDistance, bool isSymmetric) {
    size = numCities;
    matrix.resize(size, vector<int>(size, 0));
    generateMatrix(minDistance, maxDistance, isSymmetric);
}

Matrix::Matrix(const string &filename) {
    readMatrixFromFile(filename);
}


int Matrix::getDistance(int i, int j) const {
    return matrix[i][j];
}


int Matrix::getSize() const {
    return size;
}

void Matrix::generateMatrix(int minDistance, int maxDistance, bool isSymmetric) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minDistance, maxDistance);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                matrix[i][j] = -1;
            } else {
                if (isSymmetric) {
                    if (j > i) {
                        int distance = dist(gen);
                        matrix[i][j] = distance;
                        matrix[j][i] = distance;
                    }
                } else {
                    matrix[i][j] = dist(gen);
                }
            }
        }
    }
}

void Matrix::readMatrixFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku z macierzą.\n";
        exit(1);
    }

    file >> size;
    matrix.resize(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix[i][j];
        }
    }
}

// #include <iomanip>
// void Matrix::printMatrix() const {
//     for (int i = 0; i < size; ++i) {
//         for (int j = 0; j < size; ++j) {
//             std::cout << std::setw(5) << matrix[i][j] << " ";
//         }
//         std::cout << "\n";
//     }
// }