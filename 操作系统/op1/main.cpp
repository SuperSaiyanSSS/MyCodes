#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#define MAX_HANDLING_TIME 1000000

using namespace std;

// 线程1接收用户输入 产生中断
DWORD WINAPI ThreadProc1(LPVOID lpParameter);
// 线程2为系统自动处理进程调度 产生时钟中断
DWORD WINAPI ThreadProc2(LPVOID lpParameter);

// 关机
int power_off;

class PCB;
class RCB;
class IO;
// 全局变量
// 所有进程列表
vector<PCB*> PROCESS_LIST;
// 当前运行进程
PCB* NOW_PROCESS;
// 所有资源块列表
vector<RCB*> RESOURCE_LIST;
// IO设备
IO* IO_RESOURCE;

// 就绪队列（状态值为0）
vector<PCB*> READY_QUEUE;
// 阻塞队列（状态值为3）
vector<PCB*> BLOCKING_QUEUE;


void insert(PCB* , RCB* );
void insert(RCB* , PCB* );
void remove(vector<PCB*>& list, PCB* SELF);
void remove(vector<RCB*>& list, RCB* SELF);
void scheduler();
PCB* remove_highest_process_in_queue(vector<PCB*>& list);


class IO{
public:
    int name;
    string status;
    vector<PCB*> waiting_list;
    PCB* order;

    IO(){
        name = 10;
        status = "free";
    }
};

// 资源控制块
class RCB {
public:
    // 唯一标识
    int RID;
    // 状态 分为free和allocated
    string status;
    // 等待队列
    // 本资源阻塞的进程列表
    vector<PCB*> waiting_list;

    RCB(){
        RID = 0;
        status = "free";
//        waiting_list = NULL;
    }
    RCB(int RID) {
        this->RID = RID;
        status = "free";
 //       waiting_list = NULL;
    }

};


// 进程控制块
class PCB
{
public:
    string ID;
    // 内存资源
    int memory;
    // 其他资源
    vector<RCB*> other_resources;
    // 进程状态
    int status_code;
    // TODO..假设只有一个需要的RCB
    vector<RCB*> status_list;

    vector<PCB*> son_process_list;

    // 优先级
    int priority;

    // 处理时间
    int handling_time;

    PCB() {
        ID = "0";
        memory = 0;
        status_code = 0;
        priority = 0;
        handling_time = 30;
    }

    PCB(string ID, int priority) {
        this->ID = ID;
        memory = 0;
        status_code = 0;
        this->priority = priority;
        handling_time = 20;
    }

    static vector<RCB*>::iterator get_RCB(int RID){
        vector<RCB*>::iterator iter;
        for(iter=RESOURCE_LIST.begin();iter!=RESOURCE_LIST.end();iter++){
            if((*iter)->RID==RID){
                break;
            }
        }
        return iter;

    }

    void request(int RID){
        vector<RCB*>::iterator iter;
        iter = get_RCB(RID);
        if((*iter)->status=="free"){
            (*iter)->status = "allocated";
            // 插入一个RCB指针指向进程资源链表
            insert(this, (*iter));
        }
        else{
            // 若该资源被占用 则该进程阻塞
            this->status_code = 3;
            this->status_list.push_back(*iter);
            cout<<" The process "<<this->ID<<" is blocked!!!"<<endl;
            // 将该进程插入该资源的等待队列
            insert((*iter), this);

            // 阻塞后 释放已request的资源 预防死锁
            if(this->other_resources.size()!=0){
                for(int i=0;i<this->other_resources.size();i++){
                    release(this->other_resources[i]->RID);
                }
            }

        }
        scheduler();
    }

    void release(int RID){
        vector<RCB*>::iterator iter;
        iter = get_RCB(RID);
        remove(this->other_resources, (*iter));
        if((*iter)->waiting_list.size()!=0){
            (*iter)->status = "allocated";
            PCB* highest_process = remove_highest_process_in_queue((*iter)->waiting_list);

            // 进程【不可能】受多个资源的阻塞 直接将其就绪即可
            highest_process->other_resources.push_back((*iter));
            highest_process->status_list.pop_back();
            highest_process->status_code = 0;

            // 将该资源的阻塞队列中最高优先级的进程提取到就绪队列中
            READY_QUEUE.push_back(highest_process);
            cout<<"进程 "<<highest_process->ID<<" 已就绪"<<endl;


            // C++的BUG？ 传入的string类型的ID变乱码导致崩溃
            // 解决：之前传递的不是引用 而是按值传递 相当于没有修改
            // cout<<"资源 "<<RID<<" 自由后被 "<<(*highest_process_iter)->ID<<" 占有！"<<endl;
        }
        else{
            cout<<"资源 "<<RID<<" 已自由"<<endl;
        }
        scheduler();

    }

    void request_IO(){

        if(IO_RESOURCE->status=="free"){
            IO_RESOURCE->status = "allocated";
            IO_RESOURCE->order = this;

        }
        else{
            // 若该资源被占用 则该进程I/O阻塞
            this->status_code = 3;
            cout<<" The process "<<this->ID<<" is I/O blocked!!!"<<endl;
            // 将该进程插入该资源的等待队列
            PCB* this_p = this;
            IO_RESOURCE->waiting_list.push_back(this_p);

            // 阻塞后 释放已request的资源 预防死锁
            if(this->other_resources.size()!=0){
                for(int i=0;i<this->other_resources.size();i++){
                    release(this->other_resources[i]->RID);
                }
            }

        }
        scheduler();
    }

    void release_IO(){

        if(IO_RESOURCE->waiting_list.size()!=0){
            IO_RESOURCE->status = "allocated";
            PCB* highest_process = remove_highest_process_in_queue(IO_RESOURCE->waiting_list);
            IO_RESOURCE->order = highest_process;
            // 进程【不可能】受多个资源的阻塞 直接将其就绪即可
            highest_process->status_code = 0;

            // 将该资源的阻塞队列中最高优先级的进程提取到就绪队列中
            READY_QUEUE.push_back(highest_process);
            cout<<"进程 "<<highest_process->ID<<" 已就绪"<<endl;

        }
        else{
            IO_RESOURCE->status = "free";
            cout<<"资源 I/O 已自由"<<endl;
        }
        scheduler();
    }

};


PCB* createProcess(string ID, int priority) {
    PCB* newProcess = new PCB(ID, priority);
    PROCESS_LIST.push_back(newProcess);
    if(ID!="0") {
        cout<<"当前的父进程为"<<NOW_PROCESS->ID<<endl;
        NOW_PROCESS->son_process_list.push_back(newProcess);
    }
    return newProcess;
}

void deleteProcess(string ID) {
    vector<PCB*>::iterator iter;
    cout<<"删除之前"<<endl;
    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        cout<<"-- "<<(*iter)->ID<<endl;
    }


    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();){
        if((*iter)->ID==ID){

            // 释放I/O资源
            if(IO_RESOURCE->status=="allocated"&&IO_RESOURCE->order==(*iter)){
                (*iter)->release_IO();
            }

            cout<<ID<<endl;
            cout<<(*iter)->son_process_list.size()<<endl;
            cout<<"111正在递归查找"<<(*iter)->ID<<"的子进程。。。"<<endl;
            for(int i=0;i<(*iter)->son_process_list.size();i++){
                cout<<"正在递归查找"<<(*iter)->son_process_list[i]->ID<<"的子进程。。。"<<endl;
                deleteProcess((*iter)->son_process_list[i]->ID);
            }

            // 若该进程占据资源 则释放
            if((*iter)->other_resources.size()!=0){
                for(int i=0;i<(*iter)->other_resources.size();i++){
                    (*iter)->release((*iter)->other_resources[i]->RID);
                }
            }

            (*iter)->status_code = -1;
            PROCESS_LIST.erase(iter);
            cout<<"The process "<<ID<<" has been deleted!"<<endl;
            break;
        }
        else{
            ++iter;
        }
    }
    cout<<"删除之后"<<endl;
    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        cout<<"-- "<<(*iter)->ID<<endl;
    }
    return;

  //  scheduler();
}


// 假设仅需单个资源
// 某进程需要的资源
void insert(PCB* SELF, RCB* requested_resource) {
    SELF->other_resources.push_back(requested_resource);
}
// 某资源的等待队列
void insert(RCB* THAT, PCB* blocked_process){
    THAT->waiting_list.push_back(blocked_process);
}

// 将进程从某队列中删除
void remove(vector<PCB*>& list, PCB* SELF){
    vector<PCB*>::iterator iter;
    for(iter=list.begin();iter!=list.end();iter++){
        if((*iter)->ID==SELF->ID){
            break;
        }
    }
    list.erase(iter);
}

// 将资源块从某队列中删除
void remove(vector<RCB*>& list, RCB* SELF){
    vector<RCB*>::iterator iter;
    for(iter=list.begin();iter!=list.end();iter++){
        if((*iter)->RID==SELF->RID){
            break;
        }
    }
    cout<<"删除之前 "<<list.size()<<endl;
    list.erase(iter);
    cout<<"之后 "<<list.size()<<endl;
    SELF->status = "free";
}

// 删除某队列优先级最高的进程，并返回其指针
PCB* remove_highest_process_in_queue(vector<PCB*>& list){
    PCB* target_PCB = list[0];
    vector<PCB*>::iterator iter;
    vector<PCB*>::iterator target_iter;
    target_iter = list.begin();
    int highest = (target_PCB)->priority;
    for(iter=list.begin();iter!=list.end();iter++){
        if(highest<(*iter)->priority){
            highest = (*iter)->priority;
            target_PCB = *iter;
            target_iter = iter;
        }
        cout<<"-- "<<(*iter)->ID<<" 的优先级"<<(*iter)->priority<<endl;
    }
    cout<<"目标"<<target_PCB->ID<<endl;
    list.erase(target_iter);
    cout<<list.size()<<endl;
    cout<<"资源  自由后被 "<<target_PCB->ID<<" 占有！"<<endl;
    //cout<<(*target_PCB)->ID<<endl;
    return target_PCB;

}

void scheduler(){

    // 找到最高优先级进程 target_PCB;
    int max_priority;
    vector<PCB*>::iterator target_PCB = PROCESS_LIST.begin();

    max_priority = PROCESS_LIST[0]->priority;

    for(vector<PCB*>::iterator iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        if((*iter)->priority>max_priority&&((*iter)->status_code==0)){
            target_PCB = iter;
            max_priority = (*iter)->priority;
        }
    }
    cout<<"调度中。。"<<endl;

    // 调度
    // 状态码 0为就绪 1为阻塞 2为运行 3为被挂起 -1为被删除
    // TODO:当为同一个进程时不必引起调换 另外也要在上面的循环中监测进程是否是阻塞或者挂起状态
    if(NOW_PROCESS->priority<max_priority&&NOW_PROCESS->status_code==2) {
        cout<<"1现在更换 "<<NOW_PROCESS->ID;
        NOW_PROCESS->status_code = 0;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" 为"<<NOW_PROCESS->ID<<endl;

    }
        // 如果当前进程被删除或阻塞 则直接替换
    else if(NOW_PROCESS->status_code==-1||NOW_PROCESS->status_code==3){
        cout<<"2现在更换 "<<NOW_PROCESS->ID;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" 为"<<NOW_PROCESS->ID<<endl;
    }

}


void init(){

    // 开机
    power_off = 0;
    // 创建init进程
    PCB* initPCB = createProcess("0", 0);
    NOW_PROCESS = initPCB;
    // 将initPCB的处理时间设为最大值
    initPCB->handling_time = MAX_HANDLING_TIME;

    // 初始化资源块
    RCB* R1 = new RCB(1);
    RCB* R2 = new RCB(2);
    IO_RESOURCE = new IO();
    RESOURCE_LIST.push_back(R1);
    RESOURCE_LIST.push_back(R2);

}


void timeout(){

    while(1) {
        if(power_off==1) {
            break;
        }
        // 每6秒产生一次系统时钟中断
        Sleep(6000);

        scheduler();

        vector<PCB *>::iterator iter;
        cout << "当前内存中的所有进程及其优先级为";
        for (iter = PROCESS_LIST.begin(); iter != PROCESS_LIST.end(); iter++) {
            cout << "-- " << (*iter)->ID << " 优先级 " << (*iter)->priority << " 状态 " << (*iter)->status_code << endl;
        }

        // 如果运行时间结束 那么删除该进程 寻找下一优先的进程
        NOW_PROCESS->handling_time--;
        if (NOW_PROCESS->handling_time <= 0) {
            cout<<"WARNING!【【【"<<NOW_PROCESS->ID<<"】】】已运行结束！"<<endl;
            deleteProcess(NOW_PROCESS->ID);
            // scheduler();
        }

        cout<<"当前运行进程: "<<NOW_PROCESS->ID<<endl;
    }
}

void user_process(){

    while(1){
        Sleep(500);
        string command;
        string name;
        int priority;

        scheduler();

        vector<PCB*>::iterator iter;
        cout<<"当前内存中的所有进程及其优先级为";
        for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
            cout<<"-- "<<(*iter)->ID<<" 优先级 "<<(*iter)->priority<<" 状态 "<<(*iter)->status_code<<endl;
        }

        // 如果运行时间结束 那么删除该进程 寻找下一优先的进程
        NOW_PROCESS->handling_time--;
        if(NOW_PROCESS->handling_time<=0){
            deleteProcess(NOW_PROCESS->ID);
            // scheduler();
        }

        cout<<"当前运行进程："<<NOW_PROCESS->ID<<endl;
     //   cout<<">>";
        cin>>command;

        if(command=="cr"){
            cin>>name>>priority;
            PCB* newProcess = createProcess(name, priority);
            if(priority>NOW_PROCESS->priority){
                NOW_PROCESS->status_code = 0;
                NOW_PROCESS = newProcess;
            }
            NOW_PROCESS->status_code = 2;
            cout<<"The process "<<NOW_PROCESS->ID<<" is running"<<endl;
        }
        else if(command=="dl"){
            cin>>name;
            deleteProcess(name);
        }

        else if(command=="rq"){
            int RID;
            cin>>RID;
            if(RID==10){
                NOW_PROCESS->request_IO();
            }
            else {
                NOW_PROCESS->request(RID);
            }
        }
        else if(command=="rl"){
            int RID;
            cin>>RID;
            if(RID==10){
                NOW_PROCESS->release_IO();
            }
            else if(NOW_PROCESS->other_resources.size()!=0){
                NOW_PROCESS->release(RID);
            }
            else{
                cout<<"当前进程 "<<NOW_PROCESS->ID<<endl;
                cout<<"非法操作，该进程没有占据该资源"<<endl;
            }
        }
        else if(command=="bk"){
            power_off = 1;
            break;
        }
        else if(command=="timeout"){
            scheduler();
        }
        else{
            cout<<"非法操作！"<<endl;
            continue;
        }

        cout<<name<<endl;

        cout<<"当前内存中的所有进程及其优先级为";
        for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
            cout<<"-- "<<(*iter)->ID<<" 优先级 "<<(*iter)->priority<<" 状态 "<<(*iter)->status_code<<endl;
        }

    }

    cout << "成功退出" << endl;
}

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
    timeout();
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
    user_process();
    return 0;
}

int main()
{
    // TODO:  各种队列
    cout<<"-------------------------------------------------"<<endl;
    cout<<"| 现有资源块，名称分别为1，2                      |"<<endl;
    cout<<"| 现有I/O设备，名称为10                          |"<<endl;
    cout<<"| 输入cr a 10，表示创建名为a的进程，优先级为10     |"<<endl;
    cout<<"| 输入rq 1，表示申请资源块1                       |"<<endl;
    cout<<"| 输入rl 1，表示释放资源块2                       |"<<endl;
    cout<<"| 输入dl a，表示删除a进程及其子孙进程              |"<<endl;
    cout<<"| 输入bk，表示退出当前程序                        |"<<endl;
    cout<<"| 每隔6秒，系统将产生一次时钟中断，即时间片为6秒   |"<<endl;
    cout<<"| 除0进程外，进程的处理时间为20个时间片，到时结束  |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|                        —— by SuperSaiyan Goku |"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    init();

    HANDLE handle1=CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
    HANDLE handle2=CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);
    CloseHandle(handle1);
    CloseHandle(handle2);

    // 控制主进程运行时间
    while(1) {
        Sleep(2000);
        if(power_off==1){
            break;
        }
    }
    cout << "成功退出" << endl;
    return 0;
}


// 记住要传递引用。。。
// erase神坑
// iter神坑
