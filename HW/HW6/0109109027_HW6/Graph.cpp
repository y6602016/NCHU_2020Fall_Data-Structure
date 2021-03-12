#include "Graph.h"
#include <limits>

Graph::Graph() {
    n = 0;
    for (int i = 0; i < 20; i ++) {
        for (int j = 0; j < 20; j++) {
            length[i][j] = INT_MAX;
        }
    }
}

void Graph::InsertVertex(int v) {
    n++;
    if (v > 19) {
        cout << "Please give a number under 20" << endl;
    }
    else {
        length[v][v] = 0;
    }
}

void Graph::InsertEdge(int v, int u, int cost) {
    if (v > 19 || u > 19) {
        cout << "Please give a number under 20" << endl;
    }
    else {
        length[v][u] = cost;
    }
}

void Graph::MinSpanTree() { // find the minimum-cost spanning tree by the Prim's Algorithm
    int pre[n], key[n];
    bool visited[n];
    for (int i = 0; i < n; i ++) {
        pre[i] = -1;
        key[i] = INT_MAX; // initialize the value as Max
        visited[i] = false;
    }
    key[0] = 0; // start from vertex 0

    for(int i = 0; i < n; i ++) { 
        // find the smallest key number
        int min = INT_MAX, index = 0;
        for (int i = 0; i < n; i ++) {
            if (visited[i] == false && key[i] < min) {
                min = key[i];
                index = i;
            }
        }

        visited[index] = true; // set the smallest key as visited, which means add it into the spanning tree
        
        for (int i = 0; i < n; i ++) {// updated the value of the nodes associated with the current smallest key to explore the next node
            if (visited[i] == false && length[index][i] != 0 && length[index][i] < key[i]) {
                pre[i] = index;
                key[i] = length[index][i];
            }
        }
    }


    int i = 1, total = 0;
    cout << "Minimum-cost spanning tree:" << endl;
    while (i < n) {
        cout << pre[i] << " - " << i << " cost: " << length[pre[i]][i] << endl; 
        total += length[pre[i]][i];
        i++;
    }
    cout << "Total cost: " << total << endl;
}

void Graph::Shortestpath(int start) {
    int parent[n], dist[n];
    bool visited[n];
    for (int i = 0; i < n; i ++) {
        dist[i] = length[start][i];
        visited[i] = false;
        if (length[start][i] != INT_MAX) {
            parent[i] = start; // parent array to store the shortest path node
        }
    }

    visited[start] = true;
    dist[start] = 0;
    parent[start] = -1;

    for (int i = 0; i < n - 2; i ++) {

        int min = INT_MAX, u = -1;
        for (int i = 0; i < n; i ++) {
            if (visited[i] == false && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        visited[u] = true;

        for (int w = 0; w < n; w ++) {
            if (visited[w] == false && length[u][w] != INT_MAX && dist[u] + length[u][w] < dist[w]) {
                dist[w] = dist[u] + length[u][w];
                parent[w] = u; // set the u node as the w node parent
            }
        }
    }

    int cost = 0;
    for (int i = 0; i < n; i ++) { // print the path from the start node to every node
        cout << start << "->" << i << ":";
        printPath(parent, i);
        cout <<"  Total cost:" << dist[i] << endl;
    }
}

void Graph::printPath(int parent[], int i) { // recursive print function
    if (parent[i] == -1) {
        cout << i;
        return;
    }
    else {
        printPath(parent, parent[i]);
        cout << "," << i;
    }
}