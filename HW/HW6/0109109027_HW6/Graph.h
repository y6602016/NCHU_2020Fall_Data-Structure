#pragma once
#include <iostream>
using namespace std;

class Graph {
    public:
        Graph();
        void InsertEdge(int v, int u, int cost);
        void InsertVertex(int v);
        void MinSpanTree();
        void Shortestpath(int start);
    private:
        void printPath(int parent[], int i);
        int length[20][20]; // to simplify and manipulate the graph, we assume the number of verteces < 20
        int n;
};