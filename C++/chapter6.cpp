#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template <class T>
struct chainNode{
    T element;
    chainNode<T> *next;

    chainNode(){};
    chainNode(const T& element){
        this->element = element;
    }
    chainNode(const T& element, chainNode<T>* next){
        this->element = element;
        this->next = next;
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
    void output() const;
    void reverse();
    void circularShift(int i);

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

int main() {
    std::cout << "Hello, World!" << std::endl;
    srand((unsigned int)time(NULL));
    chain<int>* list1 = new chain<int>(10);
    time_t start, end;
    start = clock();
    //最好插入
    for(int i=0;i<10000;i++){
        list1->insert(0,1);
    }
    end = clock();
    cout<<"good "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
    //最坏插入
    start = clock();
    for(int i=0;i<10000;i++){
        list1->insert(list1->listSize, 1);
    }
    end = clock();
    cout<<"bad "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
    //平均插入
    start = clock();
    for(int i=0;i<10000;i++){
        list1->insert(rand()%10000, 1);
    }
    end = clock();
    cout<<"average "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;

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