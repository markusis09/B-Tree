#pragma once
#include "BTree.h"
/// <summary>
/// vyvola vyhledavani + basecase
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
Node* BTree::Search(int k)
{
    if (root == NULL) {
        return NULL;
    }
    else {
        return root->FindKey(k);
    }
}
/// <summary>
/// vyhleda index klice v danem uzlu
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
int Node::FindKeyIndex(int k) {
    int idx = 0;
    while (idx < numOfKeys && keys[idx] < k) {
        idx++;
    }   
    return idx;
}
/// <summary>
/// vyhleda cely uzel podle hodnoty jednoho klice
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
Node* Node::FindKey(int k)
{
    int i = 0;
    while (i < numOfKeys && k > keys[i]) {
        i++;
    }
    if (keys[i] == k) {
        return this;
    }
    if (leaf == true) {
        return NULL;
    }
    return childrens[i]->FindKey(k);
}
/// <summary>
/// vrati index predchoziho klice
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
int Node::GetPredecessor(int idx) {
    Node* cur = childrens[idx];

    while (!cur->leaf) {
        cur = cur->childrens[cur->numOfKeys];
    }   

    return cur->keys[cur->numOfKeys - 1];
}
/// <summary>
/// vrati index nasledujiciho klice
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
int Node::GetSuccessor(int idx) {
    Node* cur = childrens[idx + 1];

    while (!cur->leaf) {
        cur = cur->childrens[0];
    }

    return cur->keys[0];
}
