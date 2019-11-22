#include "AVL.h"
#include <cmath>

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
    bool didInsert;
    
    //base case 1, we find where we want to insert
    if(tree == NULL){
        //cout << "adding " << val << endl;
        tree = new Node(val);
        return true; //we successfully added it
    }
    
    //base case 2, the value is already in the tree
    if(tree->value == val)
        return false; //can't add it, it's already there
        
    //RECURSION TIME    
    if(val < tree->value){
        didInsert = insert(tree->left, val);
    }
    else{
        didInsert = insert(tree->right, val);
    }
    
    //we've inserted it, now check if it's balanced
    updateHeight(tree);
    int balanceCase = isBalanced(tree, true); //true means it's our first time
                                              //entering the function
    if(balanceCase > 0){ //returns 0 if balanced
        balanceNode(tree, balanceCase);
        updateHeight(tree);
    }
    
    return didInsert;
}

///functions: isBalanced, updateHeight, getHeight, max, balanceNode, 
///rightRotate, leftRotate

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
    bool removed;
    
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
            
            //now we have to check and see if it's still balanced after 
            //these changes before going back and out through the recursion
            updateHeight(tree);
            int balanceCase = isBalanced(tree, true);//true=it's our first time 
                                                     //entering the function
            if(balanceCase > 0){ //returns 0 if it's balanced
            balanceNode(tree, balanceCase);
            updateHeight(tree);
            }

            return true; //Node was successfully deleted
        }
    }
    
    //RECURSION TIME
    //case 1: value is less than
    if(data < tree->value)
        removed = take_away(tree->left, data);
    //case 2: value is greater than
    else 
        removed = take_away(tree->right, data);
        
    //Balance it on it's way back up!
    updateHeight(tree);
    int balanceCase = isBalanced(tree, true);//true=it's our first time 
                                            //entering the function
    if(balanceCase > 0){ //returns 0 if it's balanced
        balanceNode(tree, balanceCase);
        updateHeight(tree);
    } 
    return removed;
    
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear(){
    clear_up(root);
    root = NULL;
}

void AVL::clear_up(Node *&tree){
    if(tree == NULL)
        return;
    clear_up(tree->left);
    clear_up(tree->right);
    delete tree;
}

//isBalanced @param
//@firstTime allows us to iterate through exactly once, passing
//"false" our second time
//@rightLeft tells us whether the imbalance of the first Node is 
//right or left. This helps with tie-breaking for the child Node

int AVL::isBalanced(Node *tree, bool firstTime, bool rightLeft){
    
    if(!firstTime){ //stops second time through, only recurses once, "base case"
        if((getHeight(tree->left) - getHeight(tree->right)) >= 1)//if it's balanced on the second tree
            return 1;
        else if((getHeight(tree->left) - getHeight(tree->right)) == 0){
            //this is the tie-breaker, when the child Node is balanced.
            //in this case we'll go with whatever imbalance the parent has,
            //as indicated by our "rightLeft" parameter, true being right
            //and false being left
            if(rightLeft)
                return 0;
            else
                return 1;
        }
        else
            return 0;
    }
    /**cout << "height of left tree: " << getHeight(tree->left) << endl;
    cout << "height of right tree: " << getHeight(tree->right) << endl;
    cout << "difference: " << getHeight(tree->left) - getHeight(tree->right) << endl;**/
    if((getHeight(tree->left) - getHeight(tree->right)) > 1) //left imbalanced
        return 1 + isBalanced(tree->left, false, false); //false = is not first time
                                                  //entering the function
    else if((getHeight(tree->left) - getHeight(tree->right)) < -1) //right imbalanced
        return 3 + isBalanced(tree->right, false, true);
    else
        return 0; //tree is balanced
        
    //return value key:
    // 0 = balanced
    // 1 = left-right imbalance
    // 2 = left-left imbalance
    // 3 = right-right imbalance
    // 4 = right-left imbalance
}

void AVL::updateHeight(Node *tree){
    if(tree == NULL)
        return; //narrow escape of a seg fault
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
}

int AVL::getHeight(Node *tree){
    if(tree == NULL)
        return -1;
    else
        return tree->height;
}

int AVL::max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

void AVL::balanceNode(Node *&tree, int imbalanceCase){
    switch(imbalanceCase){
        case 1: // left-right imbalance
            leftRotate(tree->left);
            rightRotate(tree);
            break;
        case 2: // left-left imbalance
            rightRotate(tree);
            break;
        case 3: // right-right imbalance
            leftRotate(tree);
            break;
        case 4: // right-left imbalance
            rightRotate(tree->right);
            leftRotate(tree);
            break;
    }
}

void AVL::rightRotate(Node *&tree){
    //cout << "rightRotate" << endl;
    //tree is the matriarch because it is passed by reference
    Node *dethroned = tree; //dethroned is a pointer to the Node tree points to
    Node *heir = tree->left; 
    tree = heir;
    dethroned->left = heir->right;
    heir->right = dethroned;
    updateHeight(tree);
    updateHeight(dethroned);
    updateHeight(dethroned->left);
}

void AVL::leftRotate(Node *&tree){
    //cout << "leftRotate" << endl;
    //cout << "tree value: " << tree->value << endl;
    //First establish the matriarch, dethroned, and heir pointers
    //tree is the matriarch because it is passed by reference
    Node *dethroned = tree; //dethroned is a pointer to the Node tree points to
    Node *heir = tree->right; //heir is to the right of the tree
    
    //now let's start rotating!
    tree = heir; //new king in town
    dethroned->right = heir->left;//******the problem line
    heir->left = dethroned;
    updateHeight(tree);
    updateHeight(dethroned);
    updateHeight(dethroned->right);
}