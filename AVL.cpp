#include "AVL.h"

using namespace std;


AVL::AVL() {
    root = NULL;
}
AVL::~AVL() {
    clear();
}

//Please note that the class that implements this  must be made
//of objects which implement the Node

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
AVL::Node * AVL::getRootNode() const {
    return root;
}

/*
* Attempts to add the given int to the AVL tree
* Rebalances the tree if data is successfully added
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data){
    return insert(root, data);
}

bool AVL::insert(Node *&tree, int val){
    
    
    return true;
}

/*
* Attempts to remove the given int from the AVL tree
* Rebalances the tree if data is successfully removed
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data){
    return take_away(root, data);
}

bool AVL::take_away(Node *&tree, int data){
    //base case 1
    if(tree == NULL) //couldn't find it
        return false; 
        
    //base case 2
    if(tree->value == data){ //found it!
        if(tree->left == NULL){ //if it has one or no children
            Node *tempNode = tree;
            tree = tree->right;
            delete tempNode;
            tempNode = NULL;
            return true; //the Node was deleted
        } else if(tree->right == NULL){ //the other way of only having one child
            Node *tempNode = tree;
            tree = tree->left;
            delete tempNode;
            tempNode = NULL;
            return true; //the Node was successfully deleted
        } else { //this tree has two children
            //first, iterate to find the in order predecessor
            Node *inorderPredecessor = tree->left;
            while(inorderPredecessor->right != NULL)
                inorderPredecessor = inorderPredecessor->right;
            
            //now take the value of the inorder 
            //predecessor and put it at the top
            int newKing = inorderPredecessor->value;
            tree->value = newKing;
            
            //lastly, delete the old location of the in order predecessor
            take_away(tree->left, newKing);
            return true; //Node was successfully deleted
        }
    }
    
    //RECURSION TIME
    //case 1: value is less than
    if(data < tree->value)
        return take_away(tree->left, data);
    //case 2: value is greater than
    else 
        return take_away(tree->right, data);
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear(){
    clear_up(root);
}

void AVL::clear_up(Node *&tree){
    if(tree == NULL)
        return;
    clear_up(tree->left);
    clear_up(tree->right);
    delete tree;
}
