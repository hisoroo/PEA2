#ifndef TSP_H
#define TSP_H

#include <vector>
#include "Matrix.h"

using namespace std;

class TSP {
private:
    const Matrix &matrix;

    struct Node {
        vector<int> path;    
        vector<bool> visited;
        int cost;             
        int bound;          
        
        Node(int n) : visited(n, false), cost(0), bound(0) {}
    };
    
    struct CompareNode {
        bool operator()(const Node& lhs, const Node& rhs) const {
            return lhs.bound > rhs.bound;
        }
    };
    
    int calculateLowerBound(const Node& node) const;

public:
    TSP(const Matrix &matrix);

    int calculateDistance(const vector<int> &route) const;
    int branchAndBoundBFS() const;
    int depthFirstSearch();
    int breadthFirstSearch() const;
};

#endif