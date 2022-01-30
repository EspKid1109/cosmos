//
// Created by Alex Chase on 7/26/21.
//
using namespace std;
#ifndef DATASTRUCTURESEARCHENGINEP3_BST_H
#define DATASTRUCTURESEARCHENGINEP3_BST_H
template <typename T>
struct BSTnode{
    T val;
    BSTnode* left;
    BSTnode* right;
    BSTnode(const T &v){//Create node, Timing O(1)
        this->val = v;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class BST{
private:
    int levelCount(BSTnode<T>* root){ //returns the height of a given branch, Timing O(n)
        if(root != nullptr){ //if node is found
            return max(levelCount(root->left), levelCount(root->right)) + 1;
        }
        return -1; //no node available
    }
    int getBalance(BSTnode<T>* root){ //Gets the balance factor of a branch, Timing O(n)
        if(root != nullptr){//If node is found
            return levelCount(root->left) - levelCount(root->right);
        }
        return 0; // no node available
    }
    BSTnode<T>* rotateLeft(BSTnode<T>* root){// rotate left, Timing O(1)
        BSTnode<T>* rootR = root->right;
        root->right = rootR->left;
        rootR->left = root;
        return rootR;
    }
    BSTnode<T>* rotateRight(BSTnode<T>* root){// rotate right, Timing O(1)
        BSTnode<T>* rootL = root->left;
        root->left = rootL->right;
        rootL->right = root;
        return rootL;
    }
    BSTnode<T>* balanceTree(BSTnode<T>* root, const T &v){// performs balancing function, Timing O(n^2)
        int balance = getBalance(root);
        if(balance > 1){ // left branch imbalance
            if(v < root->left->val){ //fix LL imbalance
                return rotateRight(root);
            }
            if(v > root->left->val){// fix LR imbalance
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        else if(balance < -1){// right branch imbalance
            if(v > root->right->val){// fix RR imbalance
                return rotateLeft(root);
            }
            if(v  < root->right->val){// fix RL imbalance
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }
        return root; //no imbalances
    }
public:
    BSTnode<T>* curRoot;
    BST<T>(){curRoot = nullptr;}
    BSTnode<T>* insert(BSTnode<T>* root,const T &v){//insert data, Timing O(log n) * O(n^2) for balancing
        if(root == nullptr){//no root, create one
            return new BSTnode<T>(v);
        }
        else if(v < root->val){ //go left
            root->left = insert(root->left, v);
        }
        else if(v > root->val){ //go right
            root->right = insert(root->right, v);
        }
        else {//node already exists, ignore input
            return root;
        }
        //balance tree
        return balanceTree(root, v);
    }
    bool getVal(BSTnode<T>* root, const T &v){//will simulate timing to access a node, Timing O(log n)
        bool found = false;
        if(root != nullptr){
            if(v == root->val){
                found = true;
            }
            else if(v < root->val){//go left
                found = getVal(root->left, v);
            }
            else if(v > root->val){//go right
                found = getVal(root->right, v);
            }
        }
        return found; //if no value is found, false is returned
    }
};
#endif //DATASTRUCTURESEARCHENGINEP3_BST_H
/*Links for websites used as reference for BST
 *Template Handling http://users.cis.fiu.edu/~weiss/Deltoid/vcstl/templates
 *Typename: https://en.cppreference.com/w/cpp/language/type_alias
 */