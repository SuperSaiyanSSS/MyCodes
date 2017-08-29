#include <iostream>

using namespace std;

//chapter9-9
//2
template <class T>
class deque<T>{
public:
    virtual deque() {}
    virtual ~deque() {}
    virtual bool empty() const = 0;
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
class arrayDeque<T> : public deque<T>{
public:
    int theFront;
    int theBack;
    int queueSize;
    T* queue;
    arrayDeque(){
        theBack = 0;
        theFront = 0;
        queue = new T[10];
        queueSize = 0;
    }
    bool empty () const{
        return theFront==theBack;
    }
    int size() const{
        return queueSize;
    }
    T& front(){
        if(queueSize!=0)
            return queue[(theFront+1)%queueSize];
        else
            return nullptr;
    }
    T& back(){
        if(queueSize!=0){
            return queue[theBack%queueSize];
        } else
            return nullptr;
    }

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}