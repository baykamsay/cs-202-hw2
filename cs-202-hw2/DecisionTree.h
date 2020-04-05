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
    DecisionTree();
    ~DecisionTree();
    static double calculateEntropy(const int* classCounts, const int numClasses); // remove static
    double calculateInformationGain(const bool** data, const int* labels, 
        const int numSamples, const int numFeatures, const bool* usedSamples, 
        const int featureId);
    void train(const bool**, const int*, const int, const int);
    void train(const string, const int, const int);
    int predict(const bool*);
    void print();
private:
    DecisionTreeNode* root;
    int numFeatures;
    void destroyTree(DecisionTreeNode*& treePtr);
    // maybe fix numFeatures
    void train(const bool** data, const int* labels, const int numSamples,
        const int numFeatures, const bool* usedSamples, DecisionTreeNode*& currentNodePtr);
    void readFile(const string fileName, const int numSamples, const int numFeatures,
        bool**& data, int*& labels);
    int predict(const bool* data, const DecisionTreeNode* currentNodePtr);
    void print(const DecisionTreeNode* currentNodePtr, int level);
};
#endif