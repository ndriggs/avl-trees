#include "AVL.h"

using namespace std;


AVL::AVL() {}
AVL::~AVL() {}

//Please note that the class that implements this  must be made
//of objects which implement the Node

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
AVL::Node * AVL::getRootNode() const {
    
}

/*
* Attempts to add the given int to the AVL tree
* Rebalances the tree if data is successfully added
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data){
    
}

/*
* Attempts to remove the given int from the AVL tree
* Rebalances the tree if data is successfully removed
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data){
    
}

bool AVL::take_away(Node *&tree, int data){
    //base case 1
    if(tree == NULL)
        return false; //couldn't find it
        
    //base case 2
    if(tree->value == data){ //found it!
        if(tree->left == NULL){ //it only has one child
            
        } else if(tree->right == NULL) //the other way of only having one child
    }
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
