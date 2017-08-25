#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#define PI 3.14159

using namespace std;

template <class T>
struct chainNode{
    T element;
    string name;
    chainNode<T> *next;

    chainNode(){};
    chainNode(const T& element){
        this->element = element;
    }
    chainNode(const T& element, chainNode<T>* next){
        this->element = element;
        this->next = next;
    }
    chainNode(const T& element, chainNode<T>* next, const string name){
        this->element = element;
        this->next = next;
        this->name = name;
    }
};

template <class T>
class chain{
public:
    chain(int initialCapacity = 10);
    chain(const chain<T>&);
    chain();
    ~chain();

    bool empty() const {return listSize==0;};
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void insert(int theIndex, const T& theElement, const string name);
    void output() const;
    void reverse();
    void circularShift(int i);
    void binSort(int range);
    void radixSort(int range, int c);
    int getRadix(int x, int r, int count);

//protected:
    void checkIndex(int theIndex) const ;
    chainNode<T>* firstNode;
    int listSize;
};

template <class T>
chain<T>::chain(int initialCapacity) {
    if(initialCapacity<1)
        throw "the size of linearList cannot < 1";
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T> &theList) {
    listSize = theList.listSize;
    if(listSize==0){
        firstNode = NULL;
        return;
    }
    chainNode<T>* newFirstNode = new chainNode<T>();
    chainNode<T>* pointerOfNode = theList.firstNode;
    chainNode<T>* pointerOfNewNode = newFirstNode;
    while(pointerOfNode->next!=NULL){
        pointerOfNewNode->element = pointerOfNode->element;
        pointerOfNewNode->next = new chainNode<T>();
        pointerOfNewNode = pointerOfNewNode->next;
        pointerOfNode = pointerOfNode->next;
    }
    pointerOfNewNode->element = pointerOfNode;
    pointerOfNewNode->next = NULL;
}

template <class T>
chain<T>::chain() {
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::~chain() {
    if(listSize==0){
        return;
    }
    chainNode<T>* p = firstNode->next;
    delete firstNode;
    while(p!=NULL){
        firstNode = p;
        p = p->next;
        delete firstNode;
    }
}

template <class T>
T& chain<T>::get(int theIndex) const {
    checkIndex(theIndex);
    int count_ = 0;
    chainNode<T>* p = firstNode;
    while(p!=NULL){
        if(theIndex==count_)
            break;
        count_++;
        p=p->next;
    }
    return p->element;
}

template <class T>
int chain<T>::indexOf(const T &theElement) const {
    chainNode<T>* p = firstNode;
    int count_ = 0;
    while(p!=NULL){
        if(p->element==theElement)
            return count_;
        count_++;
        p = p->next;
    }
    return -1;
}

template <class T>
void chain<T>::erase(int theIndex) {
    checkIndex(theIndex);
    if(theIndex==0){
        chainNode<T>*p = firstNode->next;
        delete firstNode;
        firstNode = p;
    }
    else{
        chainNode<T>* p = firstNode;
        int count_ = 0;
        while(p!=NULL){
            if(count_+1==theIndex){
                chainNode<T>* p_d = p->next;
                p->next = p->next->next;
                delete p_d;
                break;
            }
            count_++;
            p = p->next;
        }
    }
    listSize--;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement) {
    if(theIndex==0){
        firstNode = new chainNode<T>(theElement, firstNode);
    }
    else{
        int count_ = 0;
        chainNode<T>* p = firstNode;
        while(p!=NULL){
            if(count_+1==theIndex){
                p->next = new chainNode<T>(theElement, p->next);
            }
            count_++;
            p = p->next;
        }
    }
    listSize++;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement, const string name) {
    if(theIndex==0){
        firstNode = new chainNode<T>(theElement, firstNode, name);
    }
    else{
        int count_ = 0;
        chainNode<T>* p = firstNode;
        while(p!=NULL){
            if(count_+1==theIndex){
                p->next = new chainNode<T>(theElement, p->next, name);
            }
            count_++;
            p = p->next;
        }
    }
    listSize++;
}


template <class T>
void chain<T>::output() const {
    chainNode<T>* p = firstNode;
    for(int i=0;i<listSize;i++){
        cout<<" "<<p->element;
        p = p->next;
    }
    cout<<endl;
//    for(int i=0,chainNode<T>* p = firstNode;i<listSize;i++, p=p->next){
//
//    }
}

template <class T>
void chain<T>::checkIndex(int theIndex) const {
    if(theIndex<0||theIndex>=listSize){
        throw "the index is illegal";
    }
}

//chapter6-15
template <class T>
void chain<T>::reverse(){
    chainNode<T>* first = firstNode;
    chainNode<T>* second = firstNode->next;
    first->next = second->next;
    second->next = first;
    chainNode<T>* temp = second;
    second = first;
    first = temp;
    cout<<first->element<<endl;
    while(first!=NULL&&second->next!=NULL){
        cout<<first->element<<endl;
        chainNode<T>* newfirst;
        newfirst = second->next;
        second->next = second->next->next;
        newfirst->next = first;
        first = newfirst;
        firstNode = first;
    }
}

//chapter6-23
template <class T>
void chain<T>::circularShift(int i){
    if(i<0){
        throw "cannot < 0";
    }
    i = i%listSize;
    chainNode<T>* oldFirst = firstNode;
    chainNode<T>* newEnd = firstNode;
    for(int j=0;j<i-1;j++){
        newEnd = newEnd->next;
        firstNode = firstNode->next;
    }
    firstNode = firstNode->next;
    newEnd->next = NULL;
    chainNode<T>* oldEnd = firstNode;
    while(oldEnd->next!=NULL){
        oldEnd = oldEnd->next;
    }
    oldEnd->next = oldFirst;

}

//chapter6-30
class Point2D{
public:
    double x;
    double y;
    bool ni;
    double cosTheta;
    double realTheta;
    bool relativeNi;
    double relativeCosTheta;
    double relativeTheta;
    Point2D* right;
    Point2D* left;
    Point2D(){};
    Point2D(double x, double y){
        this->x = x;
        this->y = y;
    }
};
template <class T>
class circularList{
public:
    Point2D* headerNode;
    int listSize;
    circularList(){
//        headerNode = new Point2D();
//        headerNode->right = headerNode;
//        headerNode->left = headerNode;
        listSize = 0;
    }
    void push_back(Point2D* newNode){
        if(listSize==0){
            headerNode = newNode;
            headerNode->right = headerNode;
            headerNode->left = headerNode;
            listSize++;
        }
        else{
            headerNode->left->right = newNode;
            newNode->left = headerNode->left;
            newNode->right = headerNode;
            listSize++;
        }
    }
    void erase(int number){
        if(number<0){
            throw "Cannot erase element which < 0";
        }
        if(listSize==0){
            throw "Cannot erase null list";
        }
        if(number>listSize){
            throw "Too large number to cover listSize";
        }
        if(number==0&&listSize>2){
            headerNode->left->right = headerNode->right;
            headerNode->right->left = headerNode->left;
            Point2D* oldHeaderNode = headerNode;
            headerNode = headerNode->right;
            delete oldHeaderNode;
            listSize--;
        }
        else if(number==0&&listSize==1){
            delete headerNode;
            listSize--;
        }
        else if(number==0&&listSize==2){
            headerNode->right->left = NULL;
            headerNode->right->right = NULL;
            Point2D* oldHeaderNode = headerNode;
            headerNode = headerNode->right;
            delete oldHeaderNode;
            listSize--;
        }
        else if(listSize==2){
            delete headerNode->right;
            headerNode->left = headerNode->right = NULL;
            listSize--;
        }
        else if(listSize>2){
            Point2D* p = headerNode;
            for(int i=0;i<number;i++){
                p = p->right;
            }
            p->left->right = p->right;
            p->right->left = p->left;
            delete p;
            listSize--;
        }
    }
    void output(){
        Point2D* p = headerNode;
        for(int i=0;i<listSize;i++){
            cout<<" ("<<p->x<<","<<p->y<<") ";
            p = p->right;
        }
        cout<<endl;
    }
    void insert(int number, Point2D* newNode){
        if(listSize<number){
            throw "the number is too large!";
        }
        if(number==0&&listSize==0){
            headerNode = newNode;
            headerNode->left = newNode;
            headerNode->right = newNode;
            listSize++;
        }
        else if(number==0&&listSize==1){
            headerNode->left = newNode;
            headerNode->right = newNode;
            newNode->right = headerNode;
            newNode->left = headerNode;
            headerNode = newNode;
            cout<<headerNode->x<<endl;
            cout<<headerNode->right->x<<endl;
            listSize++;
        }
        else if(number==0&&listSize>1){
            newNode->left = headerNode->left;
            newNode->right = headerNode;
            headerNode->left->right = newNode;
            headerNode->left = newNode;
            headerNode = newNode;
            listSize++;
        }
        else if(number==1&&listSize==1){
            newNode->left = headerNode;
            newNode->right = headerNode;
            headerNode->left = newNode;
            headerNode->right = newNode;
            listSize++;
        }
        else if(number==listSize){
            Point2D* p = headerNode->left;
            newNode->left = p;
            p->right = newNode;
            headerNode->left = newNode;
            newNode->right = headerNode;
            listSize++;
        }
        else{
            Point2D* p = headerNode;
            for(int i=0;i<number;i++){
                p = p->right;
            }
            p->left->right = newNode;
            newNode->left = p->left;
            newNode->right = p;
            p->left = newNode;
            listSize++;
        }

    }
    int indexOf(Point2D* targetNode){
        Point2D* p = headerNode;
        for(int i=0;i<listSize;i++){
            if(p->x==targetNode->x&&p->y==targetNode->y){
                return i;
            }
            p = p->right;
        }
        return -1;
    }

};

//chapter6-39
template <class T>
class circularListWithHeader{
public:
    circularListWithHeader(){
        headerNode = new chainNode<T>();
        headerNode->next = headerNode;
        listSize = 0;
    }
    void push_back(T element){
        chainNode<T>* p = headerNode;
        chainNode<T>* newNode = new chainNode<T>(element);
        for(int i=0;i<listSize;i++){
            p = p->next;
        }
        p->next = newNode;
        newNode->next = headerNode;
        listSize++;

    }
    void output(){
        chainNode<T>* p = headerNode;
        for(int i=0;i<listSize;i++) {
            p = p->next;
            cout << p->element << " ";
        }
        cout<<endl;
    }
    void reverse(){
        chainNode<T>* first = headerNode->next;
        chainNode<T>* second = first->next;
        first->next = second->next;
        second->next = first;
        chainNode<T>* temp = second;
        second = first;
        first = temp;
        headerNode->next = first;
        while(first&&second->next!=headerNode){
            chainNode<T>* newFirst = second->next;
            second->next = second->next->next;
            newFirst->next = first;
            first = newFirst;
            headerNode->next = first;
        }

        output();
    }


protected:
    chainNode<T>* headerNode;
    int listSize;
};

//bin sort
template <class T>
void chain<T>::binSort(int range){
    range++;
    chainNode<T> **bottom = new chainNode<T>*[range];
    chainNode<T> **top = new chainNode<T>*[range];
    for(int i=0;i<range;i++){
        bottom[i] = NULL;
        top[i]=NULL;
    }
    for(;firstNode!=NULL;firstNode=firstNode->next){
        if(bottom[firstNode->element]==NULL){
            top[firstNode->element] = bottom[firstNode->element] = firstNode;
        }
        else{
            top[firstNode->element]->next = firstNode;
            top[firstNode->element] = firstNode;
        }
    }
    bool firstFlag = true;
    chainNode<T>* newFirst, *p;
    for(int i=0;i<range;i++){
        if(bottom[i]!=NULL){
            if(firstFlag){
                firstFlag = false;
                newFirst = bottom[i];
                p = top[i];
            }
            else{
                p->next = bottom[i];
                p = top[i];
            }
        }
    }
    if(p!=NULL){
        p->next = NULL;
    }
    p = newFirst;
    while(p!=NULL){
        cout<<p->element<<":"<<p->name<<" -> ";
        p = p->next;
    }
    cout<<endl;
}

//chapter6-65
//cmath中的pow函数有很大误差
int powKai(int x, int n){
    int result = 1;
    while(n--){
        result = x*result;
    }
    return result;
}

template <class T>
int chain<T>::getRadix(int x, int r, int count) {
//    cout<<x<<endl;
//    cout<<pow(r, (double)count)<<endl;
//    cout<<(int)pow(r, (double)(count-1))<<endl;
//    cout<<x%(int)pow(r, (double)count)/(int)pow(r, (double)(count-1))<<endl;
    return (x%(int)powKai(r, count)/(int)powKai(r, (count-1)));
}

template <class T>
void chain<T>::radixSort(int range, int c){
    range++;
    int count =  (int)(log(range)/log(c));
    for(int j=1;j<=count+1;j++)
    {
        chainNode<T> **bottom = new chainNode<T> *[c+1];
        chainNode<T> **top = new chainNode<T> *[c+1];
        for (int i = 0; i < c+1; i++) {
            bottom[i] = NULL;
            top[i] = NULL;
        }
        for (; firstNode != NULL; firstNode = firstNode->next) {
            cout<<"now "<<firstNode->element<<"is changed to "<<getRadix(firstNode->element, c, j)<<endl;
            if (bottom[getRadix(firstNode->element, c, j)] == NULL) {
                top[getRadix(firstNode->element, c, j)] = bottom[getRadix(firstNode->element, c, j)] = firstNode;
            } else {
                top[getRadix(firstNode->element, c, j)]->next = firstNode;
                top[getRadix(firstNode->element, c, j)] = firstNode;
            }
        }
        bool firstFlag = true;
        chainNode<T> *newFirst, *p;
        for (int i = 0; i < c+1; i++) {
            if (bottom[i] != NULL) {
                if (firstFlag) {
                    firstFlag = false;
                    newFirst = bottom[i];
                    p = top[i];
                } else {
                    p->next = bottom[i];
                    p = top[i];
                }
            }
        }
        if (p != NULL) {
            p->next = NULL;
        }
        p = newFirst;
        while (p != NULL) {
            cout << p->element << ":" << p->name << " -> ";
            p = p->next;
        }
        firstNode = newFirst;
        cout << endl;
    }
}



//chapter6-67
//1
//typedef struct Point2D{
//    double x;
//    double y;
//    Point2D* right;
//    Point2D* left;
//};
Point2D* getPointInTriangle(const Point2D& u, const Point2D& v, const Point2D& w){
    Point2D* pointInTriangle = new Point2D();
    pointInTriangle->x = (u.x+v.x+w.x)/3.0;
    pointInTriangle->y = (u.y+v.y+w.y)/3.0;
    return pointInTriangle;
}
//2
int getPointNumberOfMinY(Point2D* listOfPoint, int numberOfPoint){
    if(numberOfPoint<2){
        throw "Cannot < 2";
    }
    double minY = listOfPoint[0].y;
    int minP = 0;
    for(int i=0;i<numberOfPoint;i++){
        if(listOfPoint[i].y<minY){
            minY = listOfPoint[i].y;
            minP = i;
        }
    }
    return minP;
}
int getPointNumberOfMaxY(Point2D* listOfPoint, int numberOfPoint){
    if(numberOfPoint<2){
        throw "Cannot < 2";
    }
    double maxY = listOfPoint[0].y;
    int maxP = 0;
    for(int i=0;i<numberOfPoint;i++){
        if(listOfPoint[i].y>maxY){
            maxY = listOfPoint[i].y;
            maxP = i;
        }
    }
    return maxP;
}

int checkIfCollinear(Point2D* listOfPoint, int numberOfPoint){
    if(numberOfPoint==2){
        return -1;
    }
    double k1 = (listOfPoint[1].y-listOfPoint[0].y)/(listOfPoint[1].x-listOfPoint[0].x);
    for(int i=2;i<numberOfPoint;i++){
        if((listOfPoint[i].y-listOfPoint[0].y)/(listOfPoint[i].x-listOfPoint[0].x)!=k1){
            return i;
        }
    }
    return -1;
}

Point2D* getX(Point2D* listOfPoint, int numberOfPoint){
    int targetPointNumber = checkIfCollinear(listOfPoint, numberOfPoint);
    if(targetPointNumber==-1){
        return nullptr;
    }
    return getPointInTriangle(listOfPoint[0], listOfPoint[1], listOfPoint[targetPointNumber]);
}
//3
double multiplicationCross(Point2D* X, Point2D* Y){
    return X->x*Y->y - X->y*Y->x;
}

Point2D* transToVector(Point2D* X, Point2D* Y){
    Point2D* vector = new Point2D(Y->x - X->x, Y->y - X->y);
    return vector;
}

double getCosTheta(Point2D* X, Point2D* Y){
    double XLength = sqrt((X->x)*(X->x)+(X->y)*(X->y));
    double YLength = sqrt((Y->x)*(Y->x)+(Y->y)*(Y->y));
    double dotProduct = X->x*Y->x + X->y*Y->y;
    return dotProduct/abs(XLength*YLength);
}

double getRelativeTheta(Point2D* x, Point2D* rx, Point2D* rrx){
    Point2D* vectorX1 = new Point2D(x->x - rx->x, x->y - rx->y);
    Point2D* vectorX2 = new Point2D(rrx->x - rx->x, rrx->y - rx->y);
    rx->relativeNi = multiplicationCross(vectorX1, vectorX2)>0;
    rx->relativeCosTheta = getCosTheta(vectorX1, vectorX2);
    if(rx->relativeNi){
        rx->relativeTheta = acos(rx->relativeCosTheta);
    }
    else{
        rx->relativeCosTheta = PI + PI - acos(rx->relativeCosTheta);
    }
    return rx->relativeCosTheta;
}

circularList<int>* getConvexHull(Point2D* listOfPoint, int numberOfPoint){
    //退化情况。如果S的点少于3个，则返回S
    if(numberOfPoint<3){
        circularList<int>* S = new circularList<int>();
        for(int i=0;i<numberOfPoint;i++){
            S->insert(i, &listOfPoint[i]);
        }
        return S;
    }
    Point2D* X = getX(listOfPoint, numberOfPoint);
    //如果S所有点共线，则返回最远的两个端点
    if(X == nullptr){
        circularList<int> *S = new circularList<int>();
        S->insert(0, &listOfPoint[getPointNumberOfMinY(listOfPoint, numberOfPoint)]);
        S->insert(1, &listOfPoint[getPointNumberOfMaxY(listOfPoint, numberOfPoint)]);
        return S;
    }
    //按极角排序
    //先根据向量叉乘x1y2-x2y1 判断是逆时针夹角还是顺时针夹角
    //若叉乘结果为正 则为逆时针夹角 否则为顺时针，需要做相应变换
    Point2D* XVector = transToVector(X, new Point2D(X->x, X->y-1));
    for(int i=0;i<numberOfPoint;i++){
        Point2D* vector = transToVector(X, &listOfPoint[i]);
        listOfPoint[i].ni = multiplicationCross(XVector, vector)>0;
        listOfPoint[i].cosTheta = getCosTheta(XVector, vector);
        if(listOfPoint[i].ni){
            listOfPoint[i].realTheta = acos(listOfPoint[i].cosTheta);
        }
        else{
            listOfPoint[i].realTheta = PI + PI - acos(listOfPoint[i].cosTheta);
        }
    }
    //后冒泡排序
    for(int i=0;i<numberOfPoint;i++){
        for(int j=i+1;j<numberOfPoint;j++){
            if(listOfPoint[i].realTheta>listOfPoint[j].realTheta){
                swap(listOfPoint[i], listOfPoint[j]);
            }
        }
    }
//    for(int i=0;i<numberOfPoint;i++){
//        cout<<listOfPoint[i].realTheta<<" "<<listOfPoint[i].x<<endl;
//    }
    circularList<int>* targetList = new circularList<int>();
    //插入至双向链表
    for(int i=0;i<numberOfPoint;i++){
        targetList->insert(i, &listOfPoint[i]);
    }
    //删除非极点的点
    int minp = getPointNumberOfMinY(listOfPoint, numberOfPoint);
    Point2D* p = &listOfPoint[minp];
    Point2D* x, *rx;
    //自己尝试的正确解法
    for(x=p, rx=x->right;p!=rx;){
        Point2D* rrx = rx->right;
        if(getRelativeTheta(x, rx, rrx)<=PI/2){
            targetList->erase(targetList->indexOf(rx));
            x = rrx;
            rx = x->right;
        }
        else{
            x = rx;
            rx = rrx;
        }
    }
//    //书本里提到的解法，但对(0,0)  (4,4)  (-1,6)  (-2,3)  (-5,0) (1,2)
//    //会多出(-2,3)导致错误
//    for(x=p, rx = x->right;p!=rx;){
//        Point2D* rrx = rx->right;
//        if(getRelativeTheta(x, rx, rrx)<=PI/2){
//            targetList->erase(targetList->indexOf(rx));
//            rx = x;
//            x = rx->left;
//        }
//        else{
//            x = rx;
//            rx = rrx;
//        }
//    }
    Point2D* p1;
    p1 = targetList->headerNode;
    cout<<"the extreme points of S are ";
    for(int i=0;i<targetList->listSize;i++){
        cout<<" ("<<p1->x<<","<<p1->y<<") ";
        p1 = p1->right;
    }
    cout<<endl;
    return targetList;

}

//chapter6-73
typedef struct equiveNode{
    int equiveClass;
    int next;
    int size;
};

equiveNode* nodeArray;

void initialize(int numberOfElements){
    nodeArray = new equiveNode[numberOfElements+1];
    for(int i=1;i<numberOfElements+1;i++){
        nodeArray[i].equiveClass = i;
        nodeArray[i].next = NULL;
        nodeArray[i].size = 1;
    }
}

void unite(int classA, int classB){
    if(nodeArray[classA].size>nodeArray[classB].size) {
        swap(classA, classB);
    }
    int i = classA;
    nodeArray[i].equiveClass = classB;
    while(nodeArray[i].next!=NULL){
        nodeArray[i].equiveClass = classB;
        i = nodeArray[i].next;
    }
    nodeArray[i].equiveClass = classB;
    nodeArray[i].next = nodeArray[classB].next;
    nodeArray[classB].next = classA;
    nodeArray[classB].size += nodeArray[classA].size;
    nodeArray[classA].size = 0;
}

int find(int theElement){
    return nodeArray[theElement].equiveClass;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    srand((unsigned int)time(NULL));
//    chain<int>* list1 = new chain<int>(10);
//    time_t start, end;
//    start = clock();
//    //最好插入
//    for(int i=0;i<10000;i++){
//        list1->insert(0,1);
//    }
//    end = clock();
//    cout<<"good "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
//    //最坏插入
//    start = clock();
//    for(int i=0;i<10000;i++){
//        list1->insert(list1->listSize, 1);
//    }
//    end = clock();
//    cout<<"bad "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
//    //平均插入
//    start = clock();
//    for(int i=0;i<10000;i++){
//        list1->insert(rand()%10000, 1);
//    }
//    end = clock();
//    cout<<"average "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
//    chain<int>* list2 = new chain<int>(10);
//    for(int i=0;i<9;i++){
//        list2->insert(0, i+1, "ez");
//    }
//    list2->insert(list2->listSize, 3, "gl");
//    list2->insert(0, 4, "sd");
//    list2->insert(0, 3, "haha");
//    list2->binSort(10);
//
    //chapter6-65
    chain<int>* list5 = new chain<int>(10);
    for(int i=0;i<10000;i++){
        list5->insert(0, i+1, "name");
    }
    list5->radixSort(10000, 100);
    cout<<list5->getRadix(99, 10, 2)<<" jishu"<<endl;
 //   list5->binSort(100);
//    circularList<int>* list3 = new circularList<int>();
//    cout<<list3->listSize<<endl;
//    Point2D* p1 = new Point2D(1,2);
//    Point2D* p2 = new Point2D(3.3,5.5);
//    Point2D* p3 = new Point2D(8,8);
//    list3->insert(0,p1);
//    cout<<list3->listSize<<endl;
//    list3->output();
//    list3->insert(0,p2);
//    list3->output();
//    list3->insert(0,p3);
//    list3->output();
//    list3->insert(3, new Point2D(5,5));
//    list3->insert(0, new Point2D(5,7));
//    list3->output();
//    cout<<list3->listSize<<endl;
//    cout<<acos(-1)<<endl;
//    cout<<PI/2<<endl;
//    int a[5] = {2,4,6,1,3};
//    for(int i=0;i<5;i++){
//        for(int j=i+1;j<5;j++){
//            if(a[i]>a[j]){
//                swap(a[i], a[j]);
//            }
//        }
//    }
//    for(int i=0;i<5;i++){
//        cout<<a[i]<<endl;
//    }
//    cout<<endl;
//    Point2D* aa = new Point2D(-5,5);
//    Point2D* bb = new Point2D(5,5);
//    Point2D* cc = new Point2D(-5,0);
//    Point2D* dd = new Point2D(5,0);
//    Point2D* ee = new Point2D(-2, 3);
//    Point2D* ff = new Point2D(100, 2);
//    Point2D* ss = new Point2D[6];
//    ss[0] = *aa;
//    ss[1] = *bb;
//    ss[2] = *cc;
//    ss[3] = *dd;
//    ss[4] = *ee;
//    ss[5] = *ff;
//    getConvexHull(ss, 6);

    initialize(14);
    unite(find(1), find(11));
    unite(find(7), find(11));
    unite(find(2), find(12));
    unite(find(12), find(8));
    unite(find(11), find(12));
    unite(find(3), find(13));
    unite(find(4), find(13));
    unite(find(13), find(14));
    unite(find(14), find(9));
    unite(find(5), find(14));
    unite(find(6), find(10));

    for(int i=1;i<=14;i++){
        cout<<find(i)<<"->";
    }
    cout<<endl;


//    circularListWithHeader<int>* h = new circularListWithHeader<int>();
//    for(int i=0;i<100;i++){
//        h->push_back(i+100);
//    }
//    h->output();
//    h->reverse();
//    chain<int> h(10);
//    for(int i=0;i<100;i++){
//        h.insert(i, i+100);
//    }
//    h.output();
//    h.reverse();
//    h.output();
//    h.circularShift(5);
//    h.output();
    return 0;
}