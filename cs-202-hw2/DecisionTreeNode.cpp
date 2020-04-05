/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 2
 */

using namespace std;
#include <iostream>
#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode(const bool isLeaf, const int data) {
    this->isLeaf = isLeaf;
    this->data = data;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}