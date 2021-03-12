#include "Graph.h"
#include <iostream>
using namespace std;


int main() {
    Graph h;
    h.InsertVertex(0);h.InsertVertex(1);h.InsertVertex(2);h.InsertVertex(3);h.InsertVertex(4);h.InsertVertex(5);
    // h.InsertEdge(0, 1, 20);h.InsertEdge(0, 2, 15);
    // h.InsertEdge(1, 0, 20);h.InsertEdge(1, 4, 10);h.InsertEdge(1, 5, 30);
    // h.InsertEdge(2, 0, 15);h.InsertEdge(2, 3, 4);h.InsertEdge(2, 5, 10);
    // h.InsertEdge(3, 2, 4);h.InsertEdge(3, 4, 15);h.InsertEdge(3, 5, 4);
    // h.InsertEdge(4, 1, 10);h.InsertEdge(4, 3, 15);h.InsertEdge(4, 5, 10);
    // h.InsertEdge(5, 1, 30);h.InsertEdge(5, 2, 10);h.InsertEdge(5, 3, 4);h.InsertEdge(5, 4, 10);
    // h.MinSpanTree();

    h.InsertEdge(0, 1, 20);h.InsertEdge(0, 2, 15);
    h.InsertEdge(1, 0, 2);h.InsertEdge(1, 4, 10);h.InsertEdge(1, 5, 30);
    h.InsertEdge(2, 3, 4);h.InsertEdge(2, 5, 10);
    h.InsertEdge(4, 3, 15);
    h.InsertEdge(5, 3, 4);h.InsertEdge(5, 4, 10);
    h.Shortestpath(0);
}