#pragma once
#include "BTree.h"

/// <summary>
/// pridava klic do stromu, zaroven rozlisuje kam by mel byt klic zarazen
/// </summary>
/// <param name="k"></param>
void BTree::AddKey(int k) {
    if (root == NULL) {
        root = new Node(order, true);
        root->keys[0] = k;
        root->numOfKeys = 1;
    }
    else {
        if (root->numOfKeys == 2 * order - 1) {
            Node* s = new Node(order, false);

            s->childrens[0] = root;
            s->SplitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->childrens[i]->InsertNonFull(k);

            root = s;
        }
        else {
            root->InsertNonFull(k);
        }  
    }
}
/// <summary>
/// Vlozi klic do uzlu, kde je misto, popripade na spravnou pozici k potomkovi, nebo rozhodne o jeho rozdeleni
/// </summary>
/// <param name="k"></param>
void Node::InsertNonFull(int k) {
    int i = numOfKeys - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        numOfKeys = numOfKeys + 1;
    }
    else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
            
        if (childrens[i + 1]->numOfKeys == 2 * order - 1) {
            SplitChild(i + 1, childrens[i + 1]);

            if (keys[i + 1] < k) {
                i++;
            }            
        }
        childrens[i + 1]->InsertNonFull(k);
    }
}
/// <summary>
/// rozdeli potomka na dva nove uzly, protoze velikost potomka byla vetsi nez maximalni povolena
/// </summary>
/// <param name="i"></param>
/// <param name="y"></param>
void Node::SplitChild(int i, Node* y) {
    Node* z = new Node(y->order, y->leaf);
    z->numOfKeys = order - 1;

    for (int j = 0; j < order - 1; j++) {
        z->keys[j] = y->keys[j + order];
    }        

    if (y->leaf == false) {
        for (int j = 0; j < order; j++) {
            z->childrens[j] = y->childrens[j + order];
            y->childrens[j + order] = nullptr;
        }         
    }

    y->numOfKeys = order - 1;

    for (int j = numOfKeys; j >= i + 1; j--) {
        childrens[j + 1] = childrens[j];
    }
    childrens[i + 1] = z;

    for (int j = numOfKeys - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }
    keys[i] = y->keys[order - 1];

    numOfKeys = numOfKeys + 1;
}