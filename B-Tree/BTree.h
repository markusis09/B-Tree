#pragma once
#include "Node.h"
/// <summary>
/// Drzi ukazatel na koren stromu a hodnotu radu stromu
/// </summary>
/// kod pro odebrani klice (RemoveNode.cpp) byl z velke casti prevzat ze stranky: https://www.programiz.com/dsa/deletion-from-a-b-tree
/// kod pro pridavani klice (AddNode.cpp) byl z velke casti prevzat ze stranky: https://www.programiz.com/dsa/insertion-into-a-b-tree
class BTree {
    Node* root;
    int order;

public:
    BTree(int _t);
    ~BTree();

    TreeStats GetStats();
    void PrintTree();
    Node* Search(int k);
    void AddKey(int k);
    void RemoveKey(int k);

    bool IsKeyInBTree(int k);
};

