#include <iostream>

using namespace std;

//chapter9-9
//2
template <class T>
class deque{
public:
    virtual ~deque() {}
    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual void push_back(const T& theElement) = 0;
    virtual void push_front(const T& theElement) = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;

};
//3
template <class T>
class arrayDeque : public deque<T>{
public:
    int theFront;
    int theBack;
    int queueSize;
    int arrayLength;
    T* queue;
    arrayDeque(){
        theBack = 0;
        theFront = 0;
        queue = new T[10];
        queueSize = 0;
    }
    arrayDeque(int length){
        if(length<1){
            throw "Illegal length!";
        }
        theBack = 0;
        theFront = 0;
        queue = new T[length];
        queueSize = 0;
    }
    bool empty () const{
        return theFront==theBack;
    }
    bool full() const{
        return (theBack+1)%arrayLength == theFront;
    }
    int size() const{
        return queueSize;
    }
    T& front(){
        if(queueSize!=0)
            return queue[(theFront+1)%arrayLength];

    }
    T& back(){
        if(queueSize!=0){
            return queue[theBack%arrayLength];
        }
    }
    void pop_back(){
        if(empty()){
            throw "The queue is now empty!";
        }
        else{
            theBack = (theBack-1)%arrayLength;
            queueSize--;
        }
    }
    void pop_front(){
        if(empty()){
            throw "The queue is now empty!";
        }
        else{
            theFront = (theFront+1)%arrayLength;
            queueSize--;
        }
    }
    void push_back(const T& theElement){
        if(!full()){
            theBack = (theBack+1)%arrayLength;
            queue[theBack] = theElement;
            queueSize++;
        }
        else{
            changeArrayLength();
            theBack = (theBack+1)%arrayLength;
            queue[theBack] = theElement;
            queueSize++;
        }
    }
    void push_front(const T& theElement){
        if(!full()){
            queue[theFront] = theElement;
            theFront = (theFront-1)%arrayLength;
            queueSize++;
        }
        else{
            changeArrayLength();
            queue[theFront] = theElement;
            theFront = (theFront-1)%arrayLength;
            queueSize++;
        }
    }
    void output(){
        for(int i=(theFront+1)%arrayLength, count=1;count<=queueSize;count++, i = (i+1)%arrayLength){
            cout<<"->"<<queue[i];
        }
        cout<<endl;
    }

protected:
    void changeArrayLength(){
        T* newQueue = new T[arrayLength*2];
        int deviation = (theFront+1)%arrayLength;
        if(deviation==0||deviation==1){
            copy(queue+deviation, queue+deviation+queueSize, newQueue);
        }
        else{
            copy(queue+deviation, queue+arrayLength, newQueue);
            copy(queue, queue+deviation-1, newQueue+arrayLength-deviation);
        }
        // 注意偏移量究竟是0还是1还是2。。
        theFront = 2*arrayLength-1;
        theBack = arrayLength-2;
        arrayLength*=2;
        delete queue;
        queue = newQueue;
    }

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    arrayDeque<int>* a = new arrayDeque<int>(3);
    a->push_back(10);
    a->push_back(20);
    a->output();
    a->pop_front();
    for(int i=1000;i<1100;i++){
        a->push_front(i);
    }
    a->output();
    int i=100;
    while(i--){
        a->pop_front();
    }
    a->output();
    cout<<"????"<<endl;
    cout<<a->theFront<<endl;
    cout<<a->queue[1];
    return 0;
}