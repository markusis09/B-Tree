#pragma once
#include <iostream>
#include "TreeStats.h"
using namespace std;
/// <summary>
/// Jeden uzel, obsahujici klice, rad, ukazatele na potomky, pocet klicu a zda je list.
/// </summary>
class Node {
    int* keys;
    int order;
    Node** childrens;
    int numOfKeys;
    bool leaf;

public:
    Node(int _t, bool _leaf);
    void DeleteNodes();
    
    TreeStats GetStats();
    Node* FindKey(int k);
    int FindKeyIndex(int k);
    void InsertNonFull(int k);
    void SplitChild(int i, Node* y);
    void RemoveKey(int k);
    void RemoveFromLeaf(int idx);
    void RemoveFromNonLeaf(int idx);
    int GetPredecessor(int idx);
    int GetSuccessor(int idx);
    void Fill(int idx);
    void BorrowFromPrev(int idx);
    void BorrowFromNext(int idx);
    void Merge(int idx);
    void Print(int tab);

    friend class BTree;
};


