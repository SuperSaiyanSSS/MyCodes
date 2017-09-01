#include <iostream>
#include <queue>

using namespace std;

template <class T>
class binaryTreeNode{
public:
    T element;
    binaryTreeNode<T> *leftChild,
                        *rightChild;
    binaryTreeNode(){
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement){
        element = theElement;
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode<T> *theLeftChild, binaryTreeNode *theRightChind){
        element(theElement);
        leftChild = theLeftChild;
        rightChild = theRightChind;
    }
};


template <class T>
class binaryTree
{
public:
    virtual ~binaryTree(){}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void(*) (T *)) = 0;
    virtual void inOrder(void (*) (T *)) = 0;
    virtual void postOrder(void (*) (T *)) = 0;
    virtual void levelOrder(void (*) (T *)) = 0;
};

template <class E>
class linkedBinaryTree
{
public:
    linkedBinaryTree(){
        root = NULL;
        treeSize = 0;
    }
    ~linkedBinaryTree(){
        erase();
    }
    typedef void (*visitfun)(binaryTreeNode<E>*);
    static void (*visit) (binaryTreeNode<E>*);
    bool empty() const {
        return treeSize==0;
    }
    int size() const{
        return treeSize;
    }
    void preOrder(void(*theVisit)(binaryTreeNode<E>*)){
        visit = theVisit;
        preOrder(root);
    }
    void inOrder(void (*theVisit)(binaryTreeNode<E>*)){
        visit = theVisit;
        inOrder(root);
    }
    void postOrder(void (*theVisit)(binaryTreeNode<E>*)){
        visit = theVisit;
        postOrder(root);
    }
    void levelOrder(void(*)(binaryTreeNode<E>*));
    void erase(){
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() const{
        return height(root);
    }

    void preOrderOutput(){
        preOrder(output);
        cout<<endl;
    }

    binaryTreeNode<E>* makeTreeByPreOrder(binaryTreeNode<E>* t);
//private:
    binaryTreeNode<E>* root;
    int treeSize;

    static void preOrder(binaryTreeNode<E> *t);
    static void inOrder(binaryTreeNode<E> *t);
    static void postOrder(binaryTreeNode<E> *t);
    static void dispose(binaryTreeNode<E>* t){delete t;}

    static void output(binaryTreeNode<E>* t){
        if(t==NULL){
            cout<<"ha"<<endl;
            return;
        }
        cout<<t->element<<' ';
        cout<<"derftg"<<endl;
    }

    int height(binaryTreeNode<E>* t) const;
};

template <class E>
typename linkedBinaryTree<E>::visitfun linkedBinaryTree<E>::visit = nullptr;



template <class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t) {
   // linkedBinaryTree<E>::visit(t);
    if(t!=NULL){
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t) {
    if(t!=NULL){
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template <class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t) {
    if(t!=NULL){
        linkedBinaryTree<E>::visit(t);
        postOrder(t->leftChild);
        postOrder(t->rightChild);
    }
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void (*visit)(binaryTreeNode<E> *t)) {
    queue<binaryTreeNode<E>*> q;
    if(root==NULL){
        return;
    }
    q.push(root);
    while(!q.empty()){
        binaryTreeNode<E>* nowNode = q.front();
        visit(nowNode);
        if(nowNode->leftChild!=NULL)
            q.push((nowNode->leftChild));
        if(nowNode->rightChild!=NULL)
            q.push((nowNode->rightChild));
        q.pop();
    }
}

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) const {
    if(t==NULL)
        return 0;
    int h1 = height(t->leftChild);
    int h2 = height(t->rightChild);
    return h1>h2?++h1:++h2;
}


template <class E>
binaryTreeNode<E>* linkedBinaryTree<E>::makeTreeByPreOrder(binaryTreeNode<E>* t) {
    cout<<"please input the elements of the binary tree by pre-order!"<<endl;
    string newInput;
    cin>>newInput;
    if(newInput!="#"){
        t = new binaryTreeNode<E>();
        t->element = newInput;
        t->leftChild = makeTreeByPreOrder(t->leftChild);
        t->rightChild = makeTreeByPreOrder(t->rightChild);
    }
    else{
        return NULL;
    }
    return t;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    int(1);
    binaryTreeNode<int>* anode = new binaryTreeNode<int>(1);
    linkedBinaryTree<int>* a = new linkedBinaryTree<int>();
    a->root = anode;
// 0   a->visit = a->output;
    cout<<anode->element<<endl;
    linkedBinaryTree<string>* b = new linkedBinaryTree<string>();
    b->root = b->makeTreeByPreOrder(b->root);
    b->preOrderOutput();
    cout<<b->root->element<<endl;
    cout<<"333"<<endl;
    return 0;
}