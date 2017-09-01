#include <iostream>
#include <queue>

using namespace std;
//
//template <class T>
//struct binaryTreeNode
//{
//    T element;
//    binaryTreeNode<T> *leftChild,
//            *rightChild;
//
//    binaryTreeNode() {leftChild = rightChild = NULL;}
//    binaryTreeNode(const T& theElement):element(theElement)
//    {
//        leftChild = rightChild = NULL;
//    }
//    binaryTreeNode(const T& theElement,
//                   binaryTreeNode *theLeftChild,
//                   binaryTreeNode *theRightChild)
//            :element(theElement)
//    {
//        leftChild = theLeftChild;
//        rightChild = theRightChild;
//    }
//};
//
//template<class E>
//class linkedBinaryTree
//{
//public:
//    linkedBinaryTree()
//    {
//        root = NULL;
//        treeSize = 0;
//    }
//    typedef void (*visitfun)(binaryTreeNode<E>*);
//
//    bool empty() const
//    {
//        return treeSize == 0;
//    }
//    int size() const
//    {
//        return treeSize;
//    }
//
//    void makeTree(const E& element,
//                  linkedBinaryTree<E>&, linkedBinaryTree<E>&);
//
//    void preOrder(void(*theVisit)(binaryTreeNode<E>*))
//    {
//        visit = theVisit;
//        preOrder(root);
//    }
//
//    void preOrderOutput()
//    {
//        preOrder(output);
//        cout << endl;
//    }
//
//
//protected:
//    binaryTreeNode<E> *root;                // pointer to root
//    int treeSize;                           // number of nodes in tree
//
//    static void (*visit)(binaryTreeNode<E>*);      // visit function
//    static void preOrder(binaryTreeNode<E> *t);
//    static void output(binaryTreeNode<E> *t)
//    {
//        cout << t->element << " ";
//    }
//
//};
////void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
//
//template<class E>
//void linkedBinaryTree<E>::makeTree(const E& element,
//                                   linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
//{
//    // Combine left, right, and element to make new tree.
//    // left, right, and this must be different trees.
//    // create combined tree
//    root = new binaryTreeNode<E> (element, left.root, right.root);
//    treeSize = left.treeSize + right.treeSize + 1;
//
//    // deny access from trees left and right
//    left.root = right.root = NULL;
//    left.treeSize = right.treeSize = 0;
//}
//
//
//template<class E>
//void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
//{
//    // Previous order traversal.
//    if (t != NULL)
//    {
//        linkedBinaryTree::visit(t);
//        preOrder(t->leftChild);
//        preOrder(t->rightChild);
//    }
//}
//template<class E>
//typename linkedBinaryTree<E>::visitfun  linkedBinaryTree<E>::visit = nullptr;

//int main(void)
//{
//    linkedBinaryTree<int> a,x,y,z;
//    y.makeTree(1,a,a);
//    z.makeTree(2,a,a);
//    x.makeTree(3,y,z);
//    y.makeTree(4,x,a);
//    cout << "Number of nodes = ";
//    cout << y.size() << endl;
//
//    cout << "Preorder sequence is ";
//    y.preOrderOutput();
//
//    return 0;
//}


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

template <class F>
class haha{
public:
    int element;
    haha(){}
    haha(const F& e){
        element = e;
    }
    haha(int e){
        element = e;
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    int(1);
    binaryTreeNode<int>* anode = new binaryTreeNode<int>(1);
    linkedBinaryTree<int>* a = new linkedBinaryTree<int>();
    a->root = anode;
// 0   a->visit = a->output;
    cout<<anode->element<<endl;
    a->preOrderOutput();
    return 0;
}