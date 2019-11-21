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
    bool didInsert;
    
    //base case 1, we find where we want to insert
    if(tree == NULL){
        cout << "in the tree == NULL statement" << endl;
        tree = new Node(val);
        cout << "new Node created" << endl;
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
    cout << "about to check if balanced" << endl;
    //we've inserted it, now check if it's balanced
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

int AVL::isBalanced(Node *tree, bool firstTime){
    cout << "in is balanced function" << endl;
    bool leftNull, rightNull;
    
    //first we have to catch a few base cases where the children 
    //are NULL in order to avoid a seg fault
    cout << "a" << endl;
    if((tree->left == NULL) && (tree->right == NULL))
        return 0; //tree is balanced
    if(tree->left == NULL){
        if(tree->right->height > 0){
            if(firstTime)
                return 3 + isBalanced(tree->right, false);
            else
                return 0;
        }
    }
    cout << "b" << endl;
    if(tree->right == NULL){
        if(tree->left->height > 0){
            if(firstTime)
                return 1 + isBalanced(tree->left, false);
            else
                return 1;
        }
    }
    cout << "c" << endl;
    if(!firstTime){ //stops second time through, only recurses once, "base case"
        cout << "in isBalanced for the 2nd time" << endl;
        if((tree->left->height - tree->right->height) > 1)
            return 1;
        else
            return 0;
    }
     
    
        
    if((tree->left->height - tree->right->height) > 1) //left imbalanced
        return 1 + isBalanced(tree->left, false); //false = is not first time
                                                  //entering the function
    else if((tree->left->height - tree->right->height) < -1) //right imbalanced
        return 3 + isBalanced(tree->right, false);
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
    //tree is the matriarch because it is passed by reference
    Node *dethroned = tree; //dethroned is a pointer to the Node tree points to
    Node *heir = tree->right; 
    tree = heir; //new king in town
    dethroned->right = heir->left;
    heir->left = dethroned;
    updateHeight(tree);
    updateHeight(dethroned);
    updateHeight(dethroned->right);
}