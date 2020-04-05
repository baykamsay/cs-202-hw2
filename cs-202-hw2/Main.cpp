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

    tree->train("train_data.txt", 498, 21); // train
    tree->print(); // print the tree
    cout << "Accuracy: " << tree->test("test_data.txt", 473) << endl; // print the accuracy

    delete tree;
    return 0;
}