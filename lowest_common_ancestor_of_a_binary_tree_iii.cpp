// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
public:
    // essence is leetcode160: intersection of two linked lists: https://leetcode.com/problems/intersection-of-two-linked-lists/solution/
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* n1 = p, * n2 = q;
        while (n1 != n2) {
            n1 = n1->parent ? n1->parent : q;
            n2 = n2->parent ? n2->parent : p;
        }
        return n1;
    }
};