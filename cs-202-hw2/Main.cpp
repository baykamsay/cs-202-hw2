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
    DecisionTree* tree = new DecisionTree();

    tree->train("train_data.txt", 498, 21);

    bool* arr = new bool[21];
    for (int i = 0; i < 16; i++) {
        arr[i] = 0;
    }
    arr[16] = 1;
    arr[17] = 1;
    arr[18] = 0;
    arr[19] = 1;
    arr[20] = 1;

    tree->print();

    cout << tree->predict(arr);

    delete[] arr;
    delete tree;

    return 0;
}