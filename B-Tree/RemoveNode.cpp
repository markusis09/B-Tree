#pragma once
#include "BTree.h"

/// <summary>
/// odstrani dany klic ze stromu
/// </summary>
/// <param name="k"></param>
void Node::RemoveKey(int k) {
    int idx = FindKeyIndex(k);

    if (idx < numOfKeys && keys[idx] == k) {
        if (leaf)
            RemoveFromLeaf(idx);
        else
            RemoveFromNonLeaf(idx);
    }
    else {
        if (leaf) {
            cout << "The key " << k << " does not exist in the tree\n";
            return;
        }

        bool flag = ((idx == numOfKeys) ? true : false);

        if (childrens[idx]->numOfKeys < order) {
            Fill(idx);
        }
        if (flag && idx > numOfKeys) {
            childrens[idx - 1]->RemoveKey(k);
        }           
        else {
            childrens[idx]->RemoveKey(k);
        }      
    }
    return;
}
/// <summary>
/// zavola metodu na odstraneni klice ze stromu a provede kontrolu pred a po odstraneni
/// </summary>
/// <param name="k"></param>
void BTree::RemoveKey(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->RemoveKey(k);

    if (root->numOfKeys == 0) {
        Node* tmp = root;
        if (root->leaf) {
            root = NULL;
        }    
        else {
            root = root->childrens[0];
        }
        delete tmp;
    }
    return;
}
/// <summary>
/// odstrani klic, kdyz je nalezen v listu stromu
/// </summary>
/// <param name="idx"></param>
void Node::RemoveFromLeaf(int idx) {
    for (int i = idx + 1; i < numOfKeys; ++i) {
        keys[i - 1] = keys[i];
    }
    numOfKeys--;

    return;
}
/// <summary>
/// odstrani klic, kdyz je nalezen mimo list stomu a nahradi ho jinym klicem
/// </summary>
/// <param name="idx"></param>
void Node::RemoveFromNonLeaf(int idx) {
    int k = keys[idx];

    if (childrens[idx]->numOfKeys >= order) {
        int pred = GetPredecessor(idx);
        keys[idx] = pred;
        childrens[idx]->RemoveKey(pred);
    }
    else if (childrens[idx + 1]->numOfKeys >= order) {
        int succ = GetSuccessor(idx);
        keys[idx] = succ;
        childrens[idx + 1]->RemoveKey(succ);
    }
    else {
        Merge(idx);
        childrens[idx]->RemoveKey(k);
    }
    return;
}
/// <summary>
/// Doplni daneho potomka pokud ma malo klicu
/// </summary>
/// <param name="idx"></param>
void Node::Fill(int idx) {
    if (idx != 0 && childrens[idx - 1]->numOfKeys >= order) {
        BorrowFromPrev(idx);
    }
    else if (idx != numOfKeys && childrens[idx + 1]->numOfKeys >= order) {
        BorrowFromNext(idx);
    }
    else {
        if (idx != numOfKeys) {
            Merge(idx);
        }
        else {
            Merge(idx - 1);
        }
    }
    return;
}
/// <summary>
/// potomek si prebere nyjvyssi klic od potomka vlevo
/// </summary>
/// <param name="idx"></param>
void Node::BorrowFromPrev(int idx) {
    Node* child = childrens[idx];
    Node* sibling = childrens[idx - 1];

    for (int i = child->numOfKeys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->leaf) {
        for (int i = child->numOfKeys; i >= 0; --i) {
            child->childrens[i + 1] = child->childrens[i];
        }
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf) {
        child->childrens[0] = sibling->childrens[sibling->numOfKeys];
    }
    keys[idx - 1] = sibling->keys[sibling->numOfKeys - 1];

    child->numOfKeys += 1;
    sibling->numOfKeys -= 1;

    return;
}

/// <summary>
/// potomek si prebere nejnizsi klic od potomka vpravo
/// </summary>
/// <param name="idx"></param>
void Node::BorrowFromNext(int idx) {
    Node* child = childrens[idx];
    Node* sibling = childrens[idx + 1];

    child->keys[(child->numOfKeys)] = keys[idx];

    if (!(child->leaf)) {
        child->childrens[(child->numOfKeys) + 1] = sibling->childrens[0];
    }
    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->numOfKeys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->numOfKeys; i++) {
            sibling->childrens[i - 1] = sibling->childrens[i];
        }
    }

    child->numOfKeys += 1;
    sibling->numOfKeys -= 1;

    return;
}

/// <summary>
/// Spoji dva potomky, kteri jsou vedle sebe
/// </summary>
/// <param name="idx"></param>
void Node::Merge(int idx) {
    Node* child = childrens[idx];
    Node* sibling = childrens[idx + 1];

    child->keys[order - 1] = keys[idx];

    for (int i = 0; i < sibling->numOfKeys; i++) {
        child->keys[i + order] = sibling->keys[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->numOfKeys; i++) {
            child->childrens[i + order] = sibling->childrens[i];
        }
    }

    for (int i = idx + 1; i < numOfKeys; i++) {
        keys[i - 1] = keys[i];
    }
    for (int i = idx + 2; i <= numOfKeys; i++) {
        childrens[i - 1] = childrens[i];
    }

    child->numOfKeys += sibling->numOfKeys + 1;
    numOfKeys--;

    delete (sibling);
    return;
}