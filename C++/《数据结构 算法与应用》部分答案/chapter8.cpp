#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw ("new length must be >= 0");

    T* temp = new T[newLength];              // new array
    int number = min(oldLength, newLength);  // number to copy
    copy(a, a + number, temp);
    delete [] a;                             // deallocate old memory
    a = temp;
}

template<class T>
class stack
{
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    // return true iff stack is empty
    virtual int size() const = 0;
    // return number of elements in stack
    virtual T& top() = 0;
    // return reference to the top element
    virtual void pop() = 0;
    // remove the top element
    virtual void push(const T& theElement) = 0;
    // insert theElement at the top of the stack
};

template<class T>
class arrayStack : public stack<T>
{
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() {delete [] stack;}
    bool empty() const {return stackTop == -1;}
    int size() const
    {return stackTop + 1;}
    T& top()
    {
        if (stackTop == -1)
            throw "the stack is empty!";
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            throw "the stack is empty!";
        stack[stackTop--].~T();  // destructor for T
    }
    void push(const T& theElement);
private:
    int stackTop;         // current top of stack
    int arrayLength;      // stack capacity
    T *stack;           // element array
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{// Constructor.
    if (initialCapacity < 1)
    {ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw (s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{// Add theElement to stack.
    if (stackTop == arrayLength - 1)
    {// no space, double capacity
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // add at stack top
    stack[++stackTop] = theElement;
}

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
class linkedStack:public stack<T>
{
public:
    linkedStack(int initialCapacity=10){
        stackTop = NULL;
        stackSize = 0;
    }
    ~linkedStack();
    bool empty() const{
        return stackSize == 0;
    }
    int size() const{
        return stackSize;
    }
    T& top(){
        if(stackSize==0){
            throw "the Stack is empty!~";
        }
        return stackTop->element;
    }
    void pop();
    void push(const T& theElement){
        stackTop = new chainNode<T>(theElement, stackTop);
        stackSize++;
    }
private:
    chainNode<T>* stackTop;
    int stackSize;
};

template <class T>
linkedStack<T>::~linkedStack() {
    while(stackTop!=NULL){
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
    stackSize = 0;
}

template <class T>
void linkedStack<T>::pop() {
    if(stackSize==0){
        throw "the Stack is empty!";
    }
    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

void printMatchedParis(string expr){
    linkedStack<int>* saveChars = new linkedStack<int>();
    int stringSize = expr.size();
    for(int i=0;i<stringSize;i++){
        if(expr.at(i)=='{'){
            saveChars->push(1);
        }
        if(expr.at(i)=='}'){
            if(saveChars->size()>=1){
                saveChars->pop();
            } else{
                cout<<"no matched!"<<endl;
                return;
            }
        }
    }
    if(saveChars->size()==0){
        cout<<"match!"<<endl;
    }
    else{
        cout<<"no matched!"<<endl;
    }
}

//chapter8-15
//用一个int型的数即可 若减到负数则不匹配。若最后是0则匹配

//chapter8-17
void threeKindOfBrackets(string expr){
    linkedStack<int>* saveChars = new linkedStack<int>();
    int stringSize = expr.size();
    for(int i=0;i<stringSize;i++){
        if(expr.at(i)=='('){
            saveChars->push(1);
        }
        else if(expr.at(i)=='['){
            saveChars->push(2);
        }
        else if(expr.at(i)=='{'){
            saveChars->push(3);
        }
        else if(expr.at(i)==')'){
            if(saveChars->top()!=1){
                cout<<"no matched!"<<endl;
                return;
            }
            else{
                saveChars->pop();
            }
        }
        else if(expr.at(i)==']'){
            if(saveChars->top()!=2){
                cout<<"no matched!"<<endl;
                return;
            }
            else{
                saveChars->pop();
            }
        }
        else if(expr.at(i)=='}'){
            if(saveChars->top()!=3){
                cout<<"no matched!"<<endl;
                return;
            }
            else{
                saveChars->pop();
            }
        }
    }
    if(saveChars->size()==0){
        cout<<"matched!"<<endl;
    }
    else{
        cout<<"no matched!"<<endl;
    }

};

//chapter8-22
//由于没有大碟小碟之分，所以借助3塔直接两次倒置即可，移动2n-1次

//chapter8-23
//思路：若有n-1个中转塔，则移动时，只移动最上面的那一个碟子到最后一个中转塔，移动1次;
//下面的分散到每个中转塔加1个目标塔上，移动n-1次（最下面的那个碟子移动到目标塔）;
//然后按大小顺序，除了最大的那个碟子，逐个移动到目标塔上，移动n-1次;
//总共移动2n-1次;
//若有小于n-1个中转塔，假设有n-5个，则移动时，将最上面的5个碟子移动到最后一个中转塔（递归实现）,然后仿照之前做的即可

//chapter8-29
//思路：设置一个数组a，下标1~n对应着每个关系中的第一个元素（较小的元素，如（1，3）则是1）,初始值为0。
//当有新元素i进栈时，检测a[reflex[i]]是否为1，如果为1且栈顶不为reflex[i]，则返回不能布线
//如果为1且栈顶为reflex[i]，则出栈，继续
//如果为0，则置1，进栈

int main() {
    std::cout << "Hello, World!" << std::endl;
    printMatchedParis("s{}d{}");
    threeKindOfBrackets("sds{d[a+(a)}]");
    return 0;
}