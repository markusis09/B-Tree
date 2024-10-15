#pragma once
#include "BTree.h"
/// <summary>
/// Vypise cely strom do konzole
/// </summary>
void BTree::PrintTree() {
    cout << "Actual BTree:\n";
    root->Print(0);
    cout << endl;
}
/// <summary>
/// vypise podstrom daneho uzlu do konzole
/// </summary>
/// <param name="tab"></param>
void Node::Print(int tab) {
    for (unsigned i = 0; i < tab; i++) {
        printf("\t");
    }

    for (unsigned i = 0; i < this->numOfKeys; i++) {
        cout << this->keys[i];
        printf(" ");
    }
    printf("\n");

    if (!this->leaf) {
        tab++;
        for (unsigned i = 0; i <= this->numOfKeys; i++) {
            this->childrens[i]->Print(tab);
        }
    }
}