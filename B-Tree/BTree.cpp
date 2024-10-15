#pragma once
#include "BTree.h"
/// <summary>
/// konstruktor B stromu
/// </summary>
/// <param name="_t"></param>
BTree::BTree(int _t)
{
    root = NULL;
    order = _t;
}
/// <summary>
/// Destruktor B stromu
/// </summary>
BTree::~BTree()
{
    root->DeleteNodes();
}
/// <summary>
/// ziska potrebne statistiky o danem stromu
/// </summary>
/// <returns></returns>
TreeStats BTree::GetStats()
{
    if (root != NULL) {
        TreeStats res = root->GetStats();
        res.heigh++;
        res.percentualFill = (double)res.keysCount / (double)((2 * order - 1) * res.nodesCount);
        return res;
    }
    else {
        TreeStats ts = { 0,0,0,0 };
        return ts;
    }
    
}
/// <summary>
/// Zjisti, zda je klic soucasti stromu nebo ne
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
bool BTree::IsKeyInBTree(int k) {
    if (this->Search(k) != NULL) {
        cout << "Key "<< k << " is located in tree.\n\n";
        return true;
    }
    else {
        cout << "Key " << k << " is not located in tree.\n\n";
        return false;
    }
}