
#include "BET.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <stack>
#include <vector>
#include <string>

using namespace std;

BET :: BET()
  :root(nullptr) {}

BET::BET(const string postfix)
    :root{nullptr} 
    {
      buildFromPostfix(postfix);
    }

BET::BET(const BET& other)
    :root{nullptr}
    {
      root=clone(other.root);
    }

BET::~BET() 
{
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string postfix)
{
  // Clear any existing tree
    makeEmpty(root);

    // Stack to hold BinaryNode pointers
    stack<BinaryNode*> nodeStack;
    istringstream inputStream(postfix);
    vector<string> tokens;
    string token;
    int operators = 0, operands = 0;

    while (inputStream >> token) {
        tokens.push_back(token);
        if (isalnum(token[0])) {
            // If the first character is alphanumeric, treat it as an operand
            ++operands;
        } else {
            // Otherwise, treat it as an operator
            ++operators;
        }
    }

    // Validate the expression structure
    if ((operands != operators + 1) || (tokens.size() > 1 && 
        (!isalnum(tokens[0][0]) || isalnum(tokens[tokens.size() - 1][0])))) {
        cout << "Error: Could not create tree.\n";
        return false;
    }

    // Build the tree using the postfix tokens
    for (size_t i = 0; i < tokens.size(); ++i) {
        BinaryNode* temp = new BinaryNode(tokens[i], nullptr, nullptr);

        if (isalnum(temp->element[0])) {
            // Operand: push to stack
            nodeStack.push(temp);
        } else {
            // Operator: pop two nodes for the right and left children
            if (nodeStack.size() < 2) {
                cout << "Error: Could not create tree.\n";
                delete temp; // Clean up allocated node
                return false;
            }
            temp->right = nodeStack.top();
            nodeStack.pop();
            temp->left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(temp);
        }
    }

    // Set the root to the last element in the stack
    if (!nodeStack.empty()) {
        root = nodeStack.top();
        nodeStack.pop();
    }

    return true;
}

const BET& BET:: operator= (const BET &rhs)
{
  if(this!=&rhs)
  {
    makeEmpty(root);

    root=clone(rhs.root);  
  }
  return *this;
}


//call the private version of the printPostfixExpression function
void BET::printInfixExpression()
{
  if(root!=nullptr) {
  printInfixExpression(root);
  cout << endl;
  } else {
    cout << "the tree is empty\n ";
  }
  
}

void BET::printPostfixExpression()
{
  if(root!=nullptr) {
  printPostfixExpression(root);
  cout << endl;
  } else {
    cout <<"the tree is empty\n";
  }
  
}

size_t BET::size()
{
  return size(root);
}

size_t BET::leaf_nodes() {
    return leaf_nodes(root);
}

bool BET::empty() {
    return root == nullptr;
}
 
//private member function implemented recursively 
void BET::printInfixExpression(BinaryNode* n) {
    if (!n) return;

    // Helper function to get the precedence of an operator
    auto getPrecedence = [](const string& op) -> int {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        return 0; // For operands (numbers/variables)
    };

    // Print left subexpression with parentheses if needed
    if (n->left != nullptr) {
        bool leftNeedsParens = !isalnum(n->left->element[0]) && (getPrecedence(n->element) > getPrecedence(n->left->element));
        if (leftNeedsParens) cout << "(";
        printInfixExpression(n->left);
        if (leftNeedsParens) cout << ")";
    }

    // Print the current node's operator or operand
    cout << n->element << " ";

    // Print right subexpression with parentheses if needed
    if (n->right != nullptr) {
        bool rightNeedsParens = !isalnum(n->right->element[0]) && 
                                (getPrecedence(n->element) > getPrecedence(n->right->element) ||
                                (getPrecedence(n->element) == getPrecedence(n->right->element) && !isalnum(n->element[0])));
        if (rightNeedsParens) cout << "(";
        printInfixExpression(n->right);
        if (rightNeedsParens) cout << ")";
    }
}
void BET::makeEmpty(BinaryNode *&t)
{
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }
}

BET::BinaryNode* BET::clone(BinaryNode *t) const
{
    if (t == nullptr) 
    return nullptr;
    else 
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode *n)
{
    if (n == nullptr) 
    return;

    // Recursively print the left subtree
    printPostfixExpression(n->left);

    // Recursively print the right subtree
    printPostfixExpression(n->right);

    // Print the current node's data (operator or operand)
    cout << n->element << " ";
}
size_t BET::size(BinaryNode *t)
{
  if (t == nullptr) return 0;  // Base case: empty subtree contributes 0
  return 1 + size(t->left) + size(t->right);  // 1 for the current node + left subtree + right subtree
}
size_t BET::leaf_nodes(BinaryNode *t)
{
  if (t == nullptr) 
    return 0;  // Base case: empty subtree has no leaves
  if (t->left == nullptr && t->right == nullptr) 
    return 1;  // Leaf node
  return leaf_nodes(t->left) + leaf_nodes(t->right);  // Recursively count leaf nodes in left and right subtrees
}



 
