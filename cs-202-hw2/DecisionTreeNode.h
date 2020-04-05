/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 2
 */

#ifndef __DECISIONTREENODE_H
#define __DECISIONTREENODE_H

using namespace std;

class DecisionTreeNode {
private:
    DecisionTreeNode();
    DecisionTreeNode(const bool isLeaf, const int data);
    bool isLeaf;
    int data; // class decision if it is a leaf, feature index if it is not
    DecisionTreeNode* leftChildPtr;
    DecisionTreeNode* rightChildPtr;
    friend class DecisionTree;
};
#endif