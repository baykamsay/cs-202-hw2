/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 2
 */

using namespace std;
#include <iostream>
#include "DecisionTree.h"

int main() {
    const int arr[] = { 32, 0, 7 };

    cout << DecisionTree::calculateEntropy(arr, 3);
    return 0;
}