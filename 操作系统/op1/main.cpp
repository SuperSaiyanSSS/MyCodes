#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

class PCB;
class RCB;
// 全局变量
vector<PCB*> PROCESS_LIST;
PCB* NOW_PROCESS;


// 资源控制块
class RCB {
public:
    // 唯一标识
    int RID;
    // 状态 分为free和allocated
    string status;
    // 等待队列
    // 本资源阻塞的进程列表
    PCB* waiting_list;



    RCB(){
        RID = 0;
        status = "free";
        waiting_list = NULL;
    }
    RCB(int RID) {
        this->RID = RID;
        status = "free";
        waiting_list = NULL;
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
    RCB* other_resources;
    // 进程状态
    int status_code;
    // TODO..
    int zhuangtaiduilie;

    // 父进程
    PCB* father;
    // 子进程中最大的儿子
    PCB* bigson;
    // 兄弟进程
    PCB* brother;

    // 优先级
    int priority;

    // 处理时间
    int handling_time;

    PCB() {
        ID = "0";
        memory = 0;
        other_resources = NULL;
        status_code = 0;

        father = NULL;
        bigson = NULL;
        brother = NULL;

        priority = 0;
        handling_time = 3;

    }

    PCB(string ID, int priority) {
        this->ID = ID;
        memory = 0;
        other_resources = NULL;
        status_code = 0;

        father = NULL;
        bigson = NULL;
        brother = NULL;

        this->priority = priority;

        handling_time = 3;
    }

};


PCB* createProcess(string ID, int priority) {
    PCB* newProcess = new PCB(ID, priority);
    PROCESS_LIST.push_back(newProcess);
    return newProcess;
}

void deleteProcess(string ID) {
    vector<PCB*>::iterator iter;
    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        cout<<"-- "<<(*iter)->ID<<endl;
    }


    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();){
        if((*iter)->ID==ID){
            (*iter)->status_code = -1;
            PROCESS_LIST.erase(iter);
            cout<<"The process "<<ID<<" has been deleted!"<<endl;
            break;
        }
        else{
            ++iter;
        }
    }
    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        cout<<"-- "<<(*iter)->ID<<endl;
    }
}

// 插入一个RCB指针指向进程资源链表
// 假设仅需单个资源
void insert(PCB* SELF, RCB* requested_resource) {
    SELF->other_resources = requested_resource;
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
    cout<<"????????"<<endl;

    // 调度
    // 状态码 0为就绪 1为阻塞 2为运行 3为被挂起 -1为被删除
    // TODO:当为同一个进程时不必引起调换 另外也要在上面的循环中监测进程是否是阻塞或者挂起状态
    if(NOW_PROCESS->priority<max_priority&&NOW_PROCESS->status_code!=2) {
        cout<<"现在更换 "<<NOW_PROCESS->ID;
        NOW_PROCESS->status_code = 0;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" 为"<<NOW_PROCESS->ID<<endl;

    }
        // 如果当前进程被删除 则直接替换
    else if(NOW_PROCESS->status_code==-1){
        cout<<"现在更换 "<<NOW_PROCESS->ID;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" 为"<<NOW_PROCESS->ID<<endl;
    }
}



int main()
{
    PCB* initPCB = createProcess("0", 0);
    NOW_PROCESS = initPCB;
    // 将initPCB的处理时间设为最大值
    initPCB->handling_time = 10000;

    while(1){
        Sleep(500);
        string command;
        string name;
        int priority;

        scheduler();

        cin>>command;

        vector<PCB*>::iterator iter;
        cout<<"当前内存中的所有进程及其优先级为"
        for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
            cout<<"-- "<<(*iter)->ID<<" 优先级 "<<(*iter)->priority<<endl;
        }

        // 如果运行结束 那么删除该进程 寻找下一优先的进程
        NOW_PROCESS->handling_time--;
        if(NOW_PROCESS->handling_time==0){
            deleteProcess(NOW_PROCESS->ID);
            scheduler();
        }


        if(command=="cr"){
            cin>>name>>priority;
            PCB* newProcess = createProcess(name, priority);
            if(priority>NOW_PROCESS->priority){
                NOW_PROCESS = newProcess;
            }
            cout<<"The process "<<NOW_PROCESS->ID<<" is running"<<endl;

        }
        else if(command=="dl"){
            cin>>name;
            deleteProcess(NOW_PROCESS->ID);
        }

        else if(command=="bk"){
            break;
        }
        else{
            cout<<"非法操作！"<<endl;
            continue;
        }


        cout<<name<<endl;


    }


    cout << "成功退出" << endl;
    return 0;
}

