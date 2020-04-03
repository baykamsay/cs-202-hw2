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
    double calculateInformationGain(const bool** data, const int* labels, 
        const int numSamples, const int numFeatures, const bool* usedSamples, 
        const int featureId);
private:

};
#endif