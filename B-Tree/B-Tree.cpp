#include <iostream>
#include "BTree.h"
/// <summary>
/// vypise statistiky stromu do konzole
/// </summary>
/// <param name="tmp"></param>
void PrintStats(TreeStats tmp) {
    cout << "Height of tree:\t\t\t" << tmp.heigh << "\nNumber of keys:\t\t\t" << tmp.keysCount << "\nNumber of Nodes:\t\t"
        << tmp.nodesCount << "\nPercentage fill of tree:\t" << tmp.percentualFill * 100 << " %\n\n";
}

int main() {
    int y = 30;
    int keys[] =
    { 0,3,4,8,9,11,15,18,27,29,
    30,35,36,16,20,21,1,44,65,88,
    19,66,78,84,23,89,71,73,32,99 };

    BTree t(3);

    for (int i = 0; i < y; i++) {
        t.AddKey(keys[i]);
        t.PrintTree();
    }
    t.PrintTree();

    PrintStats(t.GetStats());

    t.IsKeyInBTree(22);
    t.IsKeyInBTree(11);
    t.IsKeyInBTree(35);
    t.IsKeyInBTree(21);
    t.IsKeyInBTree(101);

    t.RemoveKey(20);
    t.RemoveKey(27);
    t.RemoveKey(18);

    t.PrintTree();

    PrintStats(t.GetStats());

    return 0;
}

