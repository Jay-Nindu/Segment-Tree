#include <bits/stdc++.h>
using namespace std;

struct Node {
  int leftIndex, rightIndex, value;
  Node *leftNode, *rightNode;
};

vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

void update(int index, int newValue, Node &node) {  // move down the tree to find the node we want to update, and update it to it's new value
  if (node.rightIndex <= index || index < node.leftIndex) { // We're outisde, don't update anything
    return;
  }
  
  if(node.rightIndex - node.leftIndex == 1) { // We're at the node we want
    node.value = newValue;
    return;
  }
  
  // Otherwise, we're not at the bottom, keep going.
  update( index, newValue, *node.leftNode );
  update( index, newValue, *node.rightNode );
  
  node.value = min(node.leftNode->value, node.rightNode->value);
}

int query(int leftQuery, int rightQuery, Node &node) {
  if (leftQuery <= node.leftIndex && node.rightIndex <= rightQuery) {
    return node.value;
  }
  if (rightQuery <= node.leftIndex || node.rightIndex <= leftQuery) {
    return INT_MAX; // This would never be the minimum, we'd choose something else for another range query problem
  }
  return min( query(leftQuery, rightQuery, *node.leftNode), query(leftQuery, rightQuery, *node.rightNode) );
}

void build(Node &node) {
  if (node.rightIndex - node.leftIndex == 1) {
		node.value = numbers[ node.leftIndex ];
    return;
  }
  //Make left and right nodes
  Node *leftNode = new Node();
  Node *rightNode = new Node();
  
  leftNode->leftIndex = node.leftIndex;
  leftNode->rightIndex = (node.leftIndex + node.rightIndex) / 2;
  rightNode->leftIndex = leftNode->rightIndex;
  rightNode->rightIndex = node.rightIndex;
  
  node.leftNode = leftNode;
  node.rightNode = rightNode;
  build(leftNode);
  build(rightNode);
  
  node.value = min(leftNode->value, rightNode->value);
}

int main() {
  Node *root = new Node();
  build(*root);
  
  //read in input
  
  build(n);
  
  for(int i = 0; i < N; i++) {
  	scanf("%d", &q);
  	int result = query(0, N, q);
  }
}
