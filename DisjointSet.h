



#ifndef ASSIGNMENT_2_DISJOINTSET_H
#define ASSIGNMENT_2_DISJOINTSET_H

#include <vector>

class DisjointSet {
private:
    std::vector<int> parent, rank;
    int setCount;

public:
    DisjointSet(int n);
    void make_set(int i);
    int find_set(int i);
    void union_sets(int i, int j);
    int final_sets();
    void print_sets();
};

#endif //ASSIGNMENT_2_DISJOINTSET_H
