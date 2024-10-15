#include "Node.h"
/// <summary>
/// konstruktor pro jeden uzel
/// </summary>
/// <param name="t1"></param>
/// <param name="leaf1"></param>
Node::Node(int t1, bool leaf1) {
    order = t1;
    leaf = leaf1;
    keys = new int[2 * order - 1];
    childrens = new Node * [2 * order];
    numOfKeys = 0;
}
/// <summary>
/// Odstrani vsechny nasledujici uzly od uzlu, na kterem byla zavolana. Vcetne daneho uzlu.
/// </summary>
void Node::DeleteNodes() {
    delete[] keys;
    for (int i = 0; i < numOfKeys+1; ++i) {
        if (!this->leaf) {
            childrens[i]->DeleteNodes();
            delete childrens[i];
        }
            
    }
    delete[] childrens;
}
/// <summary>
/// ziska statistiky celeho stromu/podstromu od kuzlu na kterem je zavolana.
/// </summary>
/// <returns></returns>
TreeStats Node::GetStats() {
    TreeStats ts = { 0,0,0,0 };
    ts.nodesCount++;
    int i;
    for (i = 0; i < numOfKeys; i++) {
        if (!leaf) {
            TreeStats tmp = childrens[i]->GetStats();
            ts.keysCount += tmp.keysCount;
            ts.nodesCount += tmp.nodesCount;
        }            
        ts.keysCount++;
    }
    if (!leaf) {
        ts.heigh++;
        TreeStats tmp = childrens[i]->GetStats();
        ts.keysCount += tmp.keysCount;
        ts.nodesCount += tmp.nodesCount;     
        ts.heigh += tmp.heigh;
    }
    return ts;
}