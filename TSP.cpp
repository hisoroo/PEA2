#include "TSP.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <queue>
#include <stack>

using namespace std;

TSP::TSP(const Matrix &matrix) : matrix(matrix) {}

int TSP::calculateDistance(const vector<int> &route) const
{
    int totalDistance = 0;
    for (unsigned int i = 0; i < route.size() - 1; ++i)
    {
        totalDistance += matrix.getDistance(route[i], route[i + 1]);
    }
    totalDistance += matrix.getDistance(route.back(), route[0]);
    return totalDistance;
}

// int TSP::calculateLowerBound(const Node &node) const
// {
//     int bound = node.cost;
//     int n = matrix.getSize();

//     for (int i = 0; i < n; ++i)
//     {
//         if (!node.visited[i])
//         {
//             int minEdge = numeric_limits<int>::max();

//             for (int j = 0; j < n; ++j)
//             {
//                 if (i != j && matrix.getDistance(i, j) >= 0)
//                 {
//                     minEdge = min(minEdge, matrix.getDistance(i, j));
//                 }
//             }

//             if (minEdge == numeric_limits<int>::max())
//             {
//                 return numeric_limits<int>::max();
//             }

//             bound += minEdge;
//         }
//     }

//     return bound;
// }


int TSP::calculateLowerBound(const Node &node) const {
    int bound = node.cost;
    int n = matrix.getSize();

    for (int i = 0; i < n; ++i) {
        if (!node.visited[i]) {

            int minIncoming = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (i != j && matrix.getDistance(j, i) >= 0) {
                    minIncoming = min(minIncoming, matrix.getDistance(j, i));
                }
            }

            int minOutgoing = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (i != j && matrix.getDistance(i, j) >= 0) {
                    minOutgoing = min(minOutgoing, matrix.getDistance(i, j));
                }
            }

            if (minIncoming == numeric_limits<int>::max() || 
                minOutgoing == numeric_limits<int>::max()) {
                return numeric_limits<int>::max();
            }

            bound += (minIncoming + minOutgoing) / 2;
        }
    }

    return bound;
}


int TSP::branchAndBoundBFS() const
{
    int n = matrix.getSize();
    int minCost = numeric_limits<int>::max();

    priority_queue<Node, vector<Node>, CompareNode> pq;

    Node root(n);
    root.path.push_back(0);
    root.visited[0] = true;
    root.bound = calculateLowerBound(root);

    pq.push(root);

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        if (current.bound >= minCost)
        {
            continue;
        }

        if (current.path.size() == n)
        {
            int distToStart = matrix.getDistance(current.path.back(), 0);
            if (distToStart >= 0)
            {
                int totalCost = current.cost + distToStart;
                if (totalCost < minCost)
                {
                    minCost = totalCost;
                }
            }
            continue;
        }

        for (int i = 0; i < n; ++i)
        {
            if (!current.visited[i])
            {
                int dist = matrix.getDistance(current.path.back(), i);
                if (dist >= 0)
                {
                    Node newNode(n);
                    newNode.path = current.path;
                    newNode.visited = current.visited;
                    newNode.cost = current.cost + dist;

                    newNode.path.push_back(i);
                    newNode.visited[i] = true;

                    newNode.bound = calculateLowerBound(newNode);

                    if (newNode.bound < minCost)
                    {
                        pq.push(newNode);
                    }
                }
            }
        }
    }

    return minCost;
}

int TSP::depthFirstSearch()
{
    int n = matrix.getSize();
    int minCost = numeric_limits<int>::max();
    stack<Node> s;

    Node root(n);
    root.path.push_back(0);
    root.visited[0] = true;
    root.bound = calculateLowerBound(root);
    s.push(root);

    while (!s.empty())
    {
        Node current = s.top();
        s.pop();

        if (current.bound >= minCost)
        {
            continue;
        }

        if (current.path.size() == n)
        {
            int distToStart = matrix.getDistance(current.path.back(), 0);
            if (distToStart >= 0)
            {
                int totalCost = current.cost + distToStart;
                minCost = min(minCost, totalCost);
            }
            continue;
        }

        for (int i = n - 1; i >= 0; --i)
        {
            if (!current.visited[i])
            {
                int dist = matrix.getDistance(current.path.back(), i);
                if (dist >= 0)
                {
                    Node newNode = current;
                    newNode.cost += dist;
                    newNode.path.push_back(i);
                    newNode.visited[i] = true;
                    newNode.bound = calculateLowerBound(newNode);

                    if (newNode.bound < minCost)
                    {
                        s.push(newNode);
                    }
                }
            }
        }
    }

    return minCost;
}

int TSP::breadthFirstSearch() const
{
    int n = matrix.getSize();
    int minCost = numeric_limits<int>::max();
    queue<Node> q;

    Node root(n);
    root.path.push_back(0);
    root.visited[0] = true;
    root.bound = calculateLowerBound(root);
    q.push(root);

    while (!q.empty())
    {
        Node current = q.front();
        q.pop();

        if (current.bound >= minCost || current.cost >= minCost)
        {
            continue;
        }

        if (current.path.size() == n)
        {
            int distToStart = matrix.getDistance(current.path.back(), 0);
            if (distToStart >= 0)
            {
                int totalCost = current.cost + distToStart;
                minCost = min(minCost, totalCost);
            }
            continue;
        }

        for (int i = 0; i < n; ++i)
        {
            if (!current.visited[i])
            {
                int dist = matrix.getDistance(current.path.back(), i);
                if (dist >= 0)
                {
                    Node newNode = current;
                    newNode.cost += dist;
                    newNode.path.push_back(i);
                    newNode.visited[i] = true;
                    newNode.bound = calculateLowerBound(newNode);

                    if (newNode.bound < minCost)
                    {
                        q.push(newNode);
                    }
                }
            }
        }
    }

    return minCost;
}
