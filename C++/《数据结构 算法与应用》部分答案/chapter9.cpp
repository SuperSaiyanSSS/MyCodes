#include <iostream>
#include <cstdio>

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



struct task{
    int machine;
    int time;
    task(int theMachine=0, int theTime=0){
        machine = theMachine;
        time = theTime;
    }
};

struct job{
    arrayDeque<task> taskQ;
    int length;
    int arrivalTime;
    int id;
    job(int theId=0){
        id = theId;
        length=0;
        arrivalTime=0;
    }

    void addTask(int theMachine, int theTime){
        task theTask(theMachine, theTime);
        taskQ.push_back(theTask);
    }

    int removeNextTask(){
        int theTime = taskQ.front().time;
        taskQ.pop_front();
        length+=theTime;
        return theTime;
    }
};

struct machine{
    arrayDeque<job*> jobQ;

    int changeTime;
    int totalWait;
    int numTasks;
    job* activeJob;

    machine(){
        totalWait = 0;
        numTasks = 0;
        activeJob = 0;
    };
};

class eventList{
public:
    eventList(int theNumMachines, int theLargeTime){
        if(theNumMachines<1){
            throw "Illegal nums";
        }
        numMachines = theNumMachines;
        finishTime = new int [theNumMachines+1];

        for(int i=1;i<=numMachines;i++){
            finishTime[i] = theLargeTime;
        }
    }
    int nextEventMachine(){
        int p=1;
        int t = finishTime[1];
        for(int i=2;i<=numMachines;i++){
            if(finishTime[i]<t){
                p = i;
                t = finishTime[i];
            }
        }
        return p;
    }
    int nextEventTime(int theMachine){
        return finishTime[theMachine];
    }
    void setFinishTime(int theMachine, int theTime){
        finishTime[theMachine] = theTime;
    }

private:
    int* finishTime;
    int numMachines;
};

int timeNow;
int numMachines;
int numJobs;
eventList* eList;
machine* mArray;
int largeTime = 100000;

void inputData(){
    cout<<"Enter number of machines and jobs"<<endl;
    cin>>numMachines>>numJobs;
    if(numMachines<1||numJobs<1){
        throw "illegal input";
    }
    eList = new eventList(numMachines, numJobs);
    mArray = new machine[numMachines+1];

    cout<<"Enter change-over times for machines!"<<endl;
    int ct;
    for(int j=1;j<=numMachines;j++){
        cin>>ct;
        if(ct<0){
            throw "illegal input";
        }
        mArray[j].changeTime = ct;
    }

    job* theJob;
    int numTasks, firstMachine, theMachine, theTaskTime;
    for(int i=1;i<=numJobs;i++){
        cout<<"Enter number of tasks for job"<<i<<endl;
        cin>>numTasks;
        firstMachine = 0;
        if(numTasks<1){
            throw "illegal num!";
        }
        theJob = new job(i);
        cout<<"Enter the tasks (machine, time)"<<endl;
        for(int j=1;j<=numTasks;j++){
            cin>>theMachine>>theTaskTime;
            if(j==1){
                firstMachine = theMachine;
            }
            theJob->addTask(theMachine, theTaskTime);
        }
        mArray[firstMachine].jobQ.push_back(theJob);
    }
}

void startShop(){
    extern changeState(int theMachine);
    for(int p=1;p<=numMachines;p++){
        changeState(p);
    }
}

job* changeState(int theMachine){
    job* lastJob;
    if(mArray[theMachine].activeJob==NULL){
        lastJob = NULL;
        if(mArray[theMachine].jobQ.empty()){
            eList->setFinishTime(theMachine, largeTime);
        }
        else{
            mArray[theMachine].activeJob = mArray[theMachine].jobQ.front();
            mArray[theMachine].jobQ.pop_front();
            mArray[theMachine].totalWait += timeNow - mArray[theMachine].activeJob->arrivalTime;
            mArray[theMachine].numTasks++;
            int t = mArray[theMachine].activeJob->removeNextTask();
            eList->setFinishTime(theMachine, timeNow+t);
        }
    }
    else{
        lastJob = mArray[theMachine].activeJob;
        mArray[theMachine].activeJob = NULL;
        eList->setFinishTime(theMachine, timeNow+=mArray[theMachine].changeTime);
    }
    return lastJob;
}

bool moveToNextMachine(job* theJob){
    if(theJob->taskQ.empty()){
        cout<<"Job "<<theJob->id<<" has completed at "<< timeNow<< " Total wait was "<<(timeNow-theJob->length)<<endl;
        return false;
    }
    else{
        int p = theJob->taskQ.front().machine;
        mArray[p].jobQ.push_back(theJob);
        theJob->arrivalTime = timeNow;
        if(eList->nextEventTime(p)==largeTime){
            changeState(p);
        }
    }
    return true;
}

void simulate(){
    while(numJobs>0){
        int nextToFinish = eList->nextEventMachine();
        timeNow = eList->nextEventTime(nextToFinish);
        job* theJob = changeState(nextToFinish);
        if(theJob!=NULL&&!moveToNextMachine(theJob)){
            numJobs--;
        }
    }
}

//TODO: 有问题 等待时间多2
void outputSatistics(){
    cout<<"Finish time = "<<timeNow<<endl;
    for(int p=1;p<=numMachines;p++){
        cout<<"Machine "<<p<<" completed "<<mArray[p].numTasks<<" tasks"<<endl;
        cout<<"The total wait time was"<< mArray[p].totalWait<<endl;
    }
    cout<<endl;
    getchar();
    getchar();
    getchar();

}



int main() {
//    std::cout << "Hello, World!" << std::endl;
//    arrayDeque<int>* a = new arrayDeque<int>(3);
//    a->push_back(10);
//    a->push_back(20);
//    a->output();
//    a->pop_front();
//    for(int i=1000;i<1100;i++){
//        a->push_front(i);
//    }
//    a->output();
//    int i=100;
//    while(i--){
//        a->pop_front();
//    }
//    a->output();
//    cout<<"????"<<endl;
//    cout<<a->theFront<<endl;
//    cout<<a->queue[1];
    inputData();
    startShop();
    simulate();
    outputSatistics();
    return 0;
}