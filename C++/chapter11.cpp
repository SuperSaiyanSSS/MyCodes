#include <iostream>
#include <queue>
#include <stack>

using namespace std;

//chapter11-15
//层次 a be cfh dg
//后序 dcbgfhea

//chapter11-16
//层次 a b c dg eh fij k l
//后序 fedilkjhgba

//chapter11-17
//层次 h eg adf c b
//前序 headcbgf

//chapter11-19
//1
//层次 a be cfh dg
//中序 bcdagfeh
//2
//层次 a be cfh dg
//中序 dcbagfeh


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
    linkedBinaryTree(binaryTreeNode<E>* root){
        this->root = root;
    }
    ~linkedBinaryTree(){
        erase();
    }

    //左右子树里较低的那个树的高度
    static int test_h;

    typedef void (*visitfun)(binaryTreeNode<E>*);
    static void (*visit) (binaryTreeNode<E>*);

    typedef int (*visit2fun)(binaryTreeNode<E>*);
    static int (*visit2) (binaryTreeNode<E>*);

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
    void levelOrder(int(*)(binaryTreeNode<E>*));
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
    void inOrderOutput(){
        inOrder(output);
        cout<<endl;
    }
    void postOrderOutput(){
        postOrder(output);
        cout<<endl;
    }

    binaryTreeNode<E>* makeTreeByPreOrder(binaryTreeNode<E>* t);

    void makeTreeByPreOrder2(binaryTreeNode<E> **t);

    binaryTreeNode<E>* copyBinaryTreeByPreOrder(binaryTreeNode<E> *t);

    binaryTreeNode<E>* copyBinaryTreeByPostOrder(binaryTreeNode<E> *t);

    static void count(binaryTreeNode<E>* t){
        if(t==NULL)
            return;
        asize++;
    }

    void getSize(){
        preOrder(count);
       // preOrder(root);
        cout<<asize<<endl;
      //  return treeSize;
    }
    void getMaxSize(){
        levelOrder(levelCount);
        cout<<maxsize<<endl;
    }

    void inOrder2Output(){
        inOrder2(output);
        cout<<endl;
    }
    void preOrder2Output(){
        preOrder2(output);
        cout<<endl;
    }
    void postOrder2Output(){
        postOrder2(output);
        cout<<endl;
    }

    void inOrder2(void(*theVisit)(binaryTreeNode<E>* t)){
        visit = theVisit;
        inOrder2(root);
    }
    void preOrder2(void(*theVisit)(binaryTreeNode<E>* t)){
        visit = theVisit;
        preOrder2(root);
    }
    void postOrder2(void(*theVisit)(binaryTreeNode<E>* t)){
        visit = theVisit;
        postOrder2(root);
    }

    int ItemsNumber;

    void buildTreeByPreOrderAndInOrder(){
        cout<<"please input the preOrder items by space!"<<endl;
        vector<string> preItems;
        string item;
        while(cin>>item){
            if(cin.get()=='\n'){
                break;
            }
            preItems.push_back(item);
        }
        cout<<"please input the inOrder items by space!"<<endl;
        vector<string> inItems;
        while(cin>>item){
            if(cin.get()=='\n'){
                break;
            }
            inItems.push_back(item);
        }
        ItemsNumber = preItems.size();
        int inRoot = findAnotherVectorOrder(0, preItems, inItems);
        cout<<"inROOT is "<<inRoot<<endl;
        int inLeftStart = 0;
        int inLeftEnd = inRoot-1;
        int inRightStart = inRoot+1;
        int inRightEnd = ItemsNumber-1;
        root = new binaryTreeNode<string>(preItems[0]);
        cout<<inLeftStart<<" "<<inLeftEnd<<" "<<inRightStart<<" "<<inRightEnd<<endl;
        buildTreeByPreOrderAndInOrder(preItems, inItems, inLeftStart, inLeftEnd, 0, true, &root);
        buildTreeByPreOrderAndInOrder(preItems, inItems, inRightStart, inRightEnd, 0, false, &root);
    }

    void buildTreeByInOrderAndPostOrder(){
        cout<<"please input the inOrder items by space!"<<endl;
        string item;
        vector<string> inItems;
        while(cin>>item){
            if(cin.get()=='\n'){
                break;
            }
            inItems.push_back(item);
        }
        cout<<"please input the postOrder items by space!"<<endl;
        vector<string> postItems;
        while(cin>>item){
            if(cin.get()=='\n'){
                break;
            }
            postItems.push_back(item);
        }
        ItemsNumber = postItems.size();
        int postNewRoot = ItemsNumber-1;
        int inNewRoot = findAnotherVectorOrder(postNewRoot, postItems, inItems);
        int inLeftStart, inLeftEnd, inRightStart, inRightEnd;

        inLeftStart = 0;
        inLeftEnd = inNewRoot-1;
        inRightStart = inNewRoot+1;
        inRightEnd = ItemsNumber-1;
        root = new binaryTreeNode<E>(postItems[ItemsNumber-1]);
        binaryTreeNode<E>** root_pp = &root;
        buildTreeByInOrderAndPostOrder(inItems, postItems, inLeftStart, inLeftEnd, postNewRoot, true, &root);
        buildTreeByInOrderAndPostOrder(inItems, postItems, inRightStart, inRightEnd, postNewRoot, false, &root);

    }

    void buildTreeByInOrderAndPostOrder(vector<string> inItems, vector<string> postItems, int inStart, int inEnd,
                                            int postLastRoot, bool left, binaryTreeNode<E>** lastRoot_pp);

    void testVector(vector<string> A){
        for(vector<string>::iterator iter = A.begin();iter!=A.end();iter++){
            cout<<(*iter)<<endl;
        }
        cout<<"end"<<endl;
    }

    int findAnotherVectorOrder(int oldOrder, vector<string>A, vector<string>B){
        int count = 0;
        for(auto iter = B.begin();iter!=B.end();iter++){
            if(*iter==A[oldOrder]){
                return count;
            }
            count++;
        }
        return -1;
    }


    void buildTreeByPreOrderAndInOrder(vector<string> preItems, vector<string> inItems, int inStart, int inEnd,
            int preLastRoot, bool left, binaryTreeNode<string>** root_pp);

//private:
    binaryTreeNode<E>* root;
    int treeSize;
    static int asize;
    static int maxsize;
    static void preOrder(binaryTreeNode<E> *t);
    static void inOrder(binaryTreeNode<E> *t);
    static void postOrder(binaryTreeNode<E> *t);
    static void dispose(binaryTreeNode<E>* t){delete t;}

    static void inOrder2(binaryTreeNode<E> *t);
    static void preOrder2(binaryTreeNode<E> *t);
    static void postOrder2(binaryTreeNode<E> *t);

    static void output(binaryTreeNode<E>* t){
        if(t==NULL){
            cout<<"ha"<<endl;
            return;
        }
        cout<<t->element<<' ';
    }

    int height(binaryTreeNode<E>* t) const;

    static int levelCount(binaryTreeNode<E>* t){
        if(t==NULL){
            return 0;
        }
        return 1;
    }

};

template <class E>
typename linkedBinaryTree<E>::visitfun linkedBinaryTree<E>::visit = nullptr;


template <class E>
typename linkedBinaryTree<E>::visit2fun linkedBinaryTree<E>::visit2 = nullptr;

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

int maxLevelCount;
int maxLevel;

//chapter11-29
template <class E>
void linkedBinaryTree<E>::levelOrder(int (*visit2)(binaryTreeNode<E> *t)) {
    queue<binaryTreeNode<E>*> q;
    if(root==NULL){
        return;
    }
    q.push(root);
    maxsize = 0;
    this->visit2 = visit2;
    int nowLevelCount = 1;
    int nextLevelCount = 0;
    int nowLevel = 0;
    extern int maxLevelCount;
    extern int maxLevel;
    maxLevel = 1;
    maxLevelCount = 0;
    while(!q.empty()){
        binaryTreeNode<E>* nowNode = q.front();
        linkedBinaryTree<E>::visit2(nowNode);
        if(nowNode->leftChild!=NULL) {
            q.push((nowNode->leftChild));
            nextLevelCount++;
        }
        if(nowNode->rightChild!=NULL) {
            q.push((nowNode->rightChild));
            nextLevelCount++;
        }
        cout<<"now the nextlevelcount is "<<nextLevelCount<<endl;
        q.pop();
        nowLevelCount--;
        if(nowLevelCount==0){
            nowLevel++;
            maxLevelCount = nextLevelCount>maxLevelCount?nextLevelCount:maxLevelCount;
            maxLevel = nextLevelCount==maxLevelCount?nowLevel+1:maxLevel;
            maxsize = maxLevelCount;
            nowLevelCount = nextLevelCount;
            nextLevelCount = 0;
        }
    }

    cout<<"The max is "<<maxLevel<<" lou de "<<maxLevelCount<<endl;
}


template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) const {
    if(t==NULL)
        return 0;
    int h1 = height(t->leftChild);
    int h2 = height(t->rightChild);
    test_h = h2>h1?(h1+1):(h2+1);
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

template <class E>
void linkedBinaryTree<E>::makeTreeByPreOrder2(binaryTreeNode<E> **t) {
    cout<<"please input the elements of the binary tree by pre-order!"<<endl;
    string newInput;
    cin>>newInput;
    if(newInput!="#"){
        binaryTreeNode<E>* tt = new binaryTreeNode<E>();
        *t = tt;
        tt->element = newInput;
        makeTreeByPreOrder2(&(tt->leftChild));
        makeTreeByPreOrder2(&(tt->rightChild));
    } else{
        return;
    }
    return;
}

//chapter11-25
template <class E>
binaryTreeNode<E>* linkedBinaryTree<E>::copyBinaryTreeByPreOrder(binaryTreeNode<E> *t){
    if(t==NULL){
        return NULL;
    }
    binaryTreeNode<E>* newNode = new binaryTreeNode<E>(t->element);
    newNode->leftChild = copyBinaryTreeByPreOrder(t->leftChild);
    newNode->rightChild = copyBinaryTreeByPreOrder(t->rightChild);
    return newNode;
}

template <class E>
binaryTreeNode<E>* linkedBinaryTree<E>::copyBinaryTreeByPostOrder(binaryTreeNode<E> *t) {
    if(t==NULL){
        return NULL;
    }
    binaryTreeNode<E>* newNode = new binaryTreeNode<E>();
    newNode->leftChild = copyBinaryTreeByPostOrder(t->leftChild);
    newNode->rightChild = copyBinaryTreeByPostOrder(t->rightChild);
    newNode->element = t->element;
    return newNode;
}

//chapter11-26
template <typename T> int linkedBinaryTree<T>::asize;

//chapter11-27
template <typename T> int linkedBinaryTree<T>::maxsize;

//chapter11-30
template <typename E>
void linkedBinaryTree<E>::inOrder2(binaryTreeNode<E> *t) {
    stack<binaryTreeNode<E>*> myStack;
    if(t==NULL){
        return;
    }
    while(!myStack.empty()||t){
        while(t){
            myStack.push(t);
            t = t->leftChild;
        }
        if(!myStack.empty()) {
            t = myStack.top();
            myStack.pop();
            visit(t);
            t = t->rightChild;
        }
    }
//    while(!myStack.empty()){
//        while(t->leftChild){
//            t = myStack.top();
//            myStack.pop();
//            if(t->rightChild!=NULL){
//                myStack.push(t->rightChild);
//            }
//            myStack.push(t);
//            if(t->leftChild!=NULL){
//                myStack.push(t->leftChild);
//            }
//        }
//        visit(myStack.top());
//        myStack.pop();
//        t = myStack.top();
//    }

}

//chapter11-31
template <typename E>
void linkedBinaryTree<E>::preOrder2(binaryTreeNode<E> *t) {
    stack<binaryTreeNode<E>*> myStack;
    while(!myStack.empty()||t){
        while(t){
            visit(t);
            myStack.push(t);
            t = t->leftChild;
        }
        if(!myStack.empty()){
            t = myStack.top();
            myStack.pop();
            t = t->rightChild;
        }
    }
}

//chapter11-32
template <typename E>
void linkedBinaryTree<E>::postOrder2(binaryTreeNode<E> *t) {
    stack<binaryTreeNode<E>*> myStack;
    if(t==NULL)
        return;
    binaryTreeNode<E>* pnow, *plast;
    pnow = t;
    plast = NULL;
    while(pnow){
        myStack.push(pnow);
        pnow = pnow->leftChild;
    }
    while(!myStack.empty()){
        pnow = myStack.top();
        myStack.pop();
        if(!pnow->rightChild||pnow->rightChild==plast){
            visit(pnow);
            plast = pnow;
        }
        else{
            myStack.push(pnow);
            pnow = pnow->rightChild;
            while(pnow){
                myStack.push(pnow);
                pnow = pnow->leftChild;
            }
        }
    }
}

//chapter11-33
template <typename E>
void linkedBinaryTree<E>::buildTreeByPreOrderAndInOrder(vector<string> preItems, vector<string> inItems,
                                                        int inStart, int inEnd, int preLastRoot, bool left,
                                                        binaryTreeNode<string>** root_pp){
    if(inStart>inEnd){
        cout<<"inStart<inEnd"<<endl;
        cout<<inStart<<inEnd<<endl;
        return;
    }
    if(inStart==inEnd){
        if(left){
            (*root_pp)->leftChild = new binaryTreeNode<string>(inItems[inStart]);
        } else{
            (*root_pp)->rightChild = new binaryTreeNode<string>(inItems[inStart]);
        }
        cout<<"waht?"<<endl;
        return;
    }
    cout<<"1001"<<endl;
    int preNewRoot;
    if(left){
        preNewRoot =preLastRoot+1;
    }
    else{
        int break_flag = false;
        for(int i=preLastRoot+1;i<ItemsNumber;i++) {
            if(break_flag)
                break;
            for (int j = inStart; j <= inEnd; j++) {
                if (preItems[i] == inItems[j]) {
                    preNewRoot = i;
                    break_flag = true;
                    break;
                }
            }
        }
    }
    cout<<"1002"<<endl;
    if(preNewRoot==-1){
        throw "Cannot find newRoot in preOrder!";
    }
    int inNewRoot = findAnotherVectorOrder(preNewRoot, preItems, inItems);
    binaryTreeNode<string>* newRoot_p = new binaryTreeNode<string>(preItems[preNewRoot]);
    binaryTreeNode<string>** newRoot_pp = &(newRoot_p);
    if(left){
        (*root_pp)->leftChild = newRoot_p;
    } else{
        (*root_pp)->rightChild = newRoot_p;
    }
    int NewLeftInStart, NewLeftInEnd, NewRightInStart, NewRightInEnd;
    NewLeftInStart = inStart;
    NewLeftInEnd = inNewRoot-1;
    NewRightInStart = inNewRoot+1;
    NewRightInEnd = inEnd;
    cout<<"Now newROOT is "<<inNewRoot<<endl;
    cout<<NewLeftInStart<<", "<<NewLeftInEnd<<" ; "<<NewRightInStart<<", "<<NewRightInEnd<<endl;
    buildTreeByPreOrderAndInOrder(preItems, inItems, NewLeftInStart, NewLeftInEnd, preNewRoot, true, newRoot_pp);
    buildTreeByPreOrderAndInOrder(preItems, inItems, NewRightInStart, NewRightInEnd, preNewRoot, false, newRoot_pp);
    return;
}
//chapter11-34
//由于只有在每个节点的度数都为0或2的情况下，即完全二叉树，根据前序和后序才能唯一确定二叉树
//因此先判断输入的节点数是否满足完全二叉树（0，1，3，7.。。）
//若不满足 返回失败
//满足 则根据前序就可构建出该完全二叉树
//再后序遍历该二叉树，将所得序列与输入的后序进行比较
//若相同 则正确构造
//若不同 则给定的前序和后序无法构造出二叉树


//chapter11-35
template <typename E>
void linkedBinaryTree<E>::buildTreeByInOrderAndPostOrder(vector<string> inItems, vector<string> postItems,
                                                         int inStart, int inEnd,
                                    int postLastRoot, bool left, binaryTreeNode<E>** lastRoot_pp){
    if(inStart>inEnd){
        return;
    }
    if(inStart==inEnd){
        if(left){
            (*lastRoot_pp)->leftChild = new binaryTreeNode<E>(inItems[inStart]);
        } else{
            (*lastRoot_pp)->rightChild = new binaryTreeNode<E>(inItems[inStart]);
        }
        return;
    }
    int inNewRoot;
    int postNewRoot;
    if(!left){
        postNewRoot = postLastRoot-1;
        inNewRoot = findAnotherVectorOrder(postNewRoot, postItems, inItems);
    }
    else{
        postNewRoot = 0;
        bool findRoot = false;
        for(int i=ItemsNumber-1;i>=0;i--){
            if(findRoot){
                break;
            }
            for(int j=inStart;j<=inEnd;j++){
                if(postItems[i]==inItems[j]){
                    postNewRoot = i;
                    findRoot = true;
                    break;
                }
            }
        }
        inNewRoot = findAnotherVectorOrder(postNewRoot, postItems, inItems);
    }
    int inLeftNewStart, inLeftNewEnd, inRightNewStart, inRightNewEnd;
    inRightNewStart = inNewRoot+1;
    inRightNewEnd = inEnd;
    inLeftNewStart = inStart;
    inLeftNewEnd = inNewRoot-1;
    binaryTreeNode<E>* newRoot_p = new binaryTreeNode<E>(inItems[inNewRoot]);
    binaryTreeNode<E>** newRoot_pp = &newRoot_p;
    if(left){
        (*lastRoot_pp)->leftChild = newRoot_p;
    }
    else{
        (*lastRoot_pp)->rightChild = newRoot_p;
    }
    buildTreeByInOrderAndPostOrder(inItems, postItems, inLeftNewStart, inLeftNewEnd, postNewRoot, true, newRoot_pp);
    buildTreeByInOrderAndPostOrder(inItems, postItems, inRightNewStart, inRightNewEnd, postNewRoot, false, newRoot_pp);
    return;
}

//chapter11-45
//比较两个二叉树的前序中序序列是否相等即可
//时间复杂度O(n)

//chapter11-46
//顺序遍历时交换左右子树的指针即可
//时间复杂度O(n)

//chapter11-47
//对每一个节点都用height函数计算其较高子树的高度，利用test_h静态变量获取其较低字树的高度，取差值最大的那个节点的值即可
template <typename T> int linkedBinaryTree<T>::test_h;

int main() {
    std::cout << "Hello, World!" << std::endl;
    int(1);

    linkedBinaryTree<string> *atree = new linkedBinaryTree<string>();
//    atree->buildTreeByPreOrderAndInOrder();
//    atree->inOrder2Output();
//    atree->postOrder2Output();
    atree->buildTreeByInOrderAndPostOrder();
    atree->inOrder2Output();
    atree->preOrderOutput();
    cout<<atree->height()<<endl;
    cout<<atree->test_h<<endl;
   // cout<<atree->root->leftChild->element<<endl;
 //   binaryTreeNode<int>* anode = new binaryTreeNode<int>(1);
 //   linkedBinaryTree<int>* a = new linkedBinaryTree<int>();
 //   a->root = anode;
// 0   a->visit = a->output;
  //  cout<<anode->element<<endl;
//    linkedBinaryTree<string>* b = new linkedBinaryTree<string>();
////    b->root = b->makeTreeByPreOrder(b->root);
////    b->preOrderOutput();
////    cout<<b->root->element<<endl;
//    b->makeTreeByPreOrder2(&(b->root));
//    b->preOrderOutput();
//    cout<<"444"<<endl;
//
//    binaryTreeNode<string>* aaaa;
//    aaaa = b->copyBinaryTreeByPreOrder(b->root);
//    cout<<"???"<<endl;
//    linkedBinaryTree<string>* tree1 = new linkedBinaryTree<string>(aaaa);
//    tree1->preOrderOutput();
//    tree1->erase();
//    tree1->preOrderOutput();
//    cout<<"33333"<<endl;
//    tree1->preOrderOutput();
//    cout<<"11111111111"<<endl;
//    binaryTreeNode<string>* bbbb;
//    bbbb = b->copyBinaryTreeByPreOrder(b->root);
//    linkedBinaryTree<string>* tree2 = new linkedBinaryTree<string>(bbbb);
//    tree2->preOrderOutput();
//    tree2->getSize();
//    tree2->getMaxSize();
//    tree2->inOrder2Output();
//    tree2->preOrder2Output();
//    tree2->postOrder2Output();

    return 0;
}
