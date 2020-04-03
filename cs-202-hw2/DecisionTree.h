/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 2
 */

#ifndef __DECISIONTREE_H
#define __DECISIONTREE_H

using namespace std;
#include "DecisionTreeNode.h";

class DecisionTree {
public:
    static double calculateEntropy(const int* classCounts, const int numClasses);
private:

};
#endif