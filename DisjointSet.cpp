//
// Created by Daniel Esemezie on 2024-03-03.
//

#include "DisjointSet.h"
#include "DisjointSet.h"
#include "iostream"


DisjointSet::DisjointSet(int n) : parent(n+1), rank(n+1, 0), setCount(n) {
    for(int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
}

void DisjointSet::make_set(int i) {
    if (i >= 1 && i < parent.size()) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int DisjointSet::find_set(int i) {
    if (i != parent[i]) {
        parent[i] = find_set(parent[i]); // Path compression
    }
    return parent[i];
}

void DisjointSet::union_sets(int i, int j) {
    int rootI = find_set(i);
    int rootJ = find_set(j);
    if (rootI != rootJ) {
        if (rank[rootI] < rank[rootJ]) {
            parent[rootI] = rootJ;
        } else if (rank[rootI] > rank[rootJ]) {
            parent[rootJ] = rootI;
        } else {
            parent[rootJ] = rootI;
            rank[rootI] += 1;
        }
        --setCount;
    }
}


int DisjointSet::final_sets() {
    std::vector<int> representative(parent.size(), 0);
    int label = 0;
    for (int i = 1; i <= parent.size(); ++i) {
        int root = find_set(i);
        if (representative[root] == 0) {
            representative[root] = ++label;
        }
    }
    for (int i = 0; i < parent.size(); ++i) {
        parent[i] = representative[find_set(i)];
    }

    return label; // Returns the total number of disjoint sets
}


void DisjointSet::print_sets() {
    for (int i = 0; i < parent.size(); ++i) {
        std::cout << "Element: " << i << ", Set Representative: " << find_set(i) << std::endl;
    }
}