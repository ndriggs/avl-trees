//YOU MAY NOT MODIFY THIS DOCUMENT
/*
*/
#pragma once
#include "AVLInterface.h"
#include "NodeInterface.h"
#include <iostream>
using namespace std;

class AVL : public AVLInterface {
public:
    struct Node : public NodeInterface {
        Node(int data){
            value = data;
            left = NULL;
            right = NULL;
            height = 0;
        }
        int value;
        Node *left, *right;
        int height;
        
        ~Node(){}
        int getData() const {
            return value;
        }
        Node* getLeftChild() const {
            return left;
        }
        Node* getRightChild() const {
            return right;
        }
        int getHeight() {
            return height;
        }
        
    };
    
	AVL();
	~AVL();

	//Please note that the class that implements this  must be made
	//of objects which implement the Node

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	Node * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);
    bool insert(Node *&tree, int val);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);
    bool take_away(Node *&tree, int data);
	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
	void clear_up(Node *&tree);
//private:
    Node *root;
    //isBalanced @param
    //@firstTime allows us to iterate through exactly once, passing
    //"false" our second time
    //@rightLeft tells us whether the imbalance of the first Node is 
    //right or left. This helps with tie-breaking for the child Node
    int isBalanced(Node *tree, bool firstTime, bool rightLeft = true);
    void updateHeight(Node *tree);
    int getHeight(Node *tree);
    int max(int a, int b);
    void balanceNode(Node *&tree, int imbalanceCase);
    void rightRotate(Node *&tree);
    void leftRotate(Node *&tree);
};
