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
