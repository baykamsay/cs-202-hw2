/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 2
 */

using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include "DecisionTree.h"

DecisionTree::DecisionTree() {
    root = NULL;
    numFeatures = 0;
}

DecisionTree::~DecisionTree() {
    destroyTree(root);
}

void DecisionTree::destroyTree(DecisionTreeNode*& treePtr) {
    if (treePtr != NULL) {
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
        treePtr = NULL;
    }
}

double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses) {
    double result = 0; // FIX CLASS COUNTS
    int sum = 0;

    for (int i = 0; i < numClasses; i++) {
        sum += classCounts[i];
    }
    
    for (int i = 0; i < numClasses; i++) {
        double prob = classCounts[i] / (double) sum;

        if (prob != 0) {
            result -= prob * log2(prob);
        }
    }

    return result;
}

double DecisionTree::calculateInformationGain(const bool** data, const int* labels, 
    const int numSamples, const int numFeatures, const bool* usedSamples, 
    const int featureId) {   
    // calculate parent entropy
    int totClass = 0;
    int parentClasses = 0;
    
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] && labels[i] > totClass) {
            totClass = labels[i];
        }
    }
    int* classCounts = new int[totClass];

    for (int i = 0; i < totClass; i++) {
        classCounts[i] = 0;
    }
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i]) {
            parentClasses++;
            classCounts[labels[i] - 1]++;
        }
    }

    double parentEntropy = calculateEntropy(classCounts, totClass);
    delete[] classCounts;

    // calculate left entropy
    totClass = 0;
    int leftClasses = 0;

    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] && !data[i][featureId] && labels[i] > totClass) {
            totClass = labels[i];
        }
    }
    int* leftClassCounts = new int[totClass];

    for (int i = 0; i < totClass; i++) {
        leftClassCounts[i] = 0;
    }
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] && !data[i][featureId]) {
            leftClasses++;
            leftClassCounts[labels[i] - 1]++;
        }
    }
    double leftEntropy = calculateEntropy(leftClassCounts, totClass);
    delete[] leftClassCounts;

    // calculate right entropy
    totClass = 0;
    int rightClasses = 0;

    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] && data[i][featureId] && labels[i] > totClass) {
            totClass = labels[i];
        }
    }
    int* rightClassCounts = new int[totClass];
    for (int i = 0; i < totClass; i++) {
        rightClassCounts[i] = 0;
    }
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] && data[i][featureId]) {
            rightClasses++;
            rightClassCounts[labels[i] - 1]++;
        }
    }
    double rightEntropy = calculateEntropy(rightClassCounts, totClass);
    delete[] rightClassCounts;

    // calculate information gain
    double splitEntropy = ((double) leftClasses / parentClasses) * leftEntropy
        + ((double) rightClasses / parentClasses) * rightEntropy;
    double informationGain = parentEntropy - splitEntropy;
    
    return informationGain;
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples,
    const int numFeatures) {

    this->numFeatures = numFeatures;
    bool* usedSamples = new bool[numSamples];
    
    for (int i = 0; i < numSamples; i++) {
        usedSamples[i] = true;
    }
    train(data, labels, numSamples, numFeatures, usedSamples, root);

    delete[] usedSamples;
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, 
    const int numFeatures, const bool* usedSamples, DecisionTreeNode*& currentNodePtr) {

    double max = 0; // base case if information gain max is 0
    int feature = 0;

    for (int i = 0; i < numFeatures; i++) {
        double currentInformationGain = calculateInformationGain(data, labels, numSamples,
            numFeatures, usedSamples, i);
        if (currentInformationGain > max) {
            max = currentInformationGain;
            feature = i;
        }
    }
    // base case
    if (max == 0) {
        int totClass = 0;

        for (int i = 0; i < numSamples; i++) {
            if (usedSamples[i] && labels[i] > totClass) {
                totClass = labels[i];
            }
        }
        int* classCounts = new int[totClass];

        for (int i = 0; i < totClass; i++) {
            classCounts[i] = 0;
        }
        for (int i = 0; i < numSamples; i++) {
            if (usedSamples[i]) {
                classCounts[labels[i] - 1]++;
            }
        }

        int maxClass = 0;
        int classDecision = 0;
        
        for (int i = 0; i < totClass; i++) {
            if (classCounts[i] > maxClass) {
                maxClass = classCounts[i];
                classDecision = i + 1;
            }
        }
        currentNodePtr = new DecisionTreeNode(true, classDecision);
        delete[] classCounts;
        return;
    }

    currentNodePtr = new DecisionTreeNode(false, feature);
    // for left child
    bool* leftUsedSamples = new bool[numSamples];
    for (int i = 0; i < numSamples; i++) {
        leftUsedSamples[i] = usedSamples[i];
        if (data[i][feature]) {
            leftUsedSamples[i] = false;
        }
    }
    train(data, labels, numSamples, numFeatures, leftUsedSamples, currentNodePtr->leftChildPtr);
    delete[] leftUsedSamples;
    
    // for right child
    bool* rightUsedSamples = new bool[numSamples];

    for (int i = 0; i < numSamples; i++) {
        rightUsedSamples[i] = usedSamples[i];
        if (!data[i][feature]) {
            rightUsedSamples[i] = false;
        }
    }
    train(data, labels, numSamples, numFeatures, rightUsedSamples, currentNodePtr->rightChildPtr);
    delete[] rightUsedSamples;
}

void DecisionTree::train(const string fileName, const int numSamples,
    const int numFeatures) {
    bool** data = new bool*[numSamples];
    for (int i = 0; i < numSamples; i++) {
        data[i] = new bool[numFeatures];
    }
    int* labels = new int[numSamples];

    readFile(fileName, numSamples, numFeatures, data, labels);
    train((const bool**) data, labels, numSamples, numFeatures);

    for (int i = 0; i < numSamples; i++) {
        delete[] data[i];
    }
    delete[] data;
    delete[] labels;
}

void DecisionTree::readFile(const string fileName, const int numSamples, const int numFeatures,
    bool**& data, int*& labels) {

    fstream file(fileName);
    char c;

    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numFeatures; j++) {
            file >> c;
            data[i][j] = c - '0';
        }
        file >> c;
        labels[i] = c - '0';
    }
}

int DecisionTree::predict(const bool* data) {
    if (root == NULL) { // if train is not called
        cout << "Train is not called" << endl;
        return -1;
    }

    return predict(data, root);
}

int DecisionTree::predict(const bool* data, const DecisionTreeNode* currentNodePtr) {
    if (currentNodePtr->isLeaf) {
        return currentNodePtr->data;
    }

    if (data[currentNodePtr->data]) {
        return predict(data, currentNodePtr->rightChildPtr);
    }
    else {
        return predict(data, currentNodePtr->leftChildPtr);
    }
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {
    
    int truePredictions = 0;

    for (int i = 0; i < numSamples; i++) {
        int prediction = predict(data[i]);

        if (prediction == labels[i]) {
            truePredictions++;
        }
    }

    return (double) truePredictions / numSamples;
}

double DecisionTree::test(const string fileName, const int numSamples) {
    bool** data = new bool* [numSamples];
    for (int i = 0; i < numSamples; i++) {
        data[i] = new bool[numFeatures];
    }
    int* labels = new int[numSamples];

    readFile(fileName, numSamples, numFeatures, data, labels);
    double result = test((const bool**)data, labels, numSamples);

    for (int i = 0; i < numSamples; i++) {
        delete[] data[i];
    }
    delete[] data;
    delete[] labels;
    return result;
}

void DecisionTree::print() {
    if (root == NULL) {
        cout << "Empty tree!" << endl;
        return;
    }
    print(root, 0);
}

void DecisionTree::print(const DecisionTreeNode* currentNodePtr, int level) {
    
    for (int i = 0; i < level; i++) {
        cout << "\t";
    }
    if (currentNodePtr->isLeaf) {
        cout << "class=" << currentNodePtr->data << endl;
        return;
    }

    cout << "feature=" << currentNodePtr->data << endl;

    print(currentNodePtr->leftChildPtr, level + 1);
    print(currentNodePtr->rightChildPtr, level + 1);
}