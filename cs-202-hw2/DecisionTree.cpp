/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 2
 */

using namespace std;
#include <iostream>
#include <math.h>
#include "DecisionTree.h"

double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses)
{
    double result = 0;
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
    const int featureId)
{   
    // calculate parent entropy
    int usedSampleSize = 0;

    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i]) {
            usedSampleSize++;
        }
    }
    int* usedLabels = new int[usedSampleSize];
    int j = 0;

    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i]) {
            usedLabels[j] = labels[i];
            j++;
        }
    }
    double parentEntropy = calculateEntropy(usedLabels, usedSampleSize);

    // calculate left entropy
    int leftSampleSize = 0;

    for (int i = 0; i < numSamples; i++) {
        if (!data[i][featureId] && labels) {
            leftSampleSize++;
        }
    }
    int* leftLabels = new int[leftSampleSize];
    j = 0;

    for (int i = 0; i < numSamples; i++) {
        if (!data[i][featureId] && labels) {
            leftLabels[j] = labels[i];
            j++;
        }
    }
    double leftEntropy = calculateEntropy(leftLabels, leftSampleSize);

    // calculate right entropy
    int rightSampleSize = 0;

    for (int i = 0; i < numSamples; i++) {
        if (data[i][featureId] && labels) {
            rightSampleSize++;
        }
    }
    int* rightLabels = new int[rightSampleSize];
    j = 0;

    for (int i = 0; i < numSamples; i++) {
        if (data[i][featureId] && labels) {
            rightLabels[j] = labels[i];
            j++;
        }
    }
    double rightEntropy = calculateEntropy(rightLabels, rightSampleSize);

    // calculate information gain
    double splitEntropy = ((double) leftSampleSize / usedSampleSize) * leftEntropy
        + ((double) rightSampleSize / usedSampleSize) * rightEntropy;
    double informationGain = parentEntropy - splitEntropy;

    delete[] rightLabels;
    delete[] leftLabels;
    delete[] usedLabels;
    return informationGain;
}