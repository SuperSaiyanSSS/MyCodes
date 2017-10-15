#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#define MAX_HANDLING_TIME 1000000

using namespace std;

class PCB;
class RCB;
// 全局变量
// 所有进程列表
vector<PCB*> PROCESS_LIST;
// 当前运行进程
PCB* NOW_PROCESS;
// 所有资源块列表
vector<RCB*> RESOURCE_LIST;

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
       // other_resources = NULL;
        status_code = 0;
       // status_list = NULL;

        father = NULL;
        bigson = NULL;
        brother = NULL;

        priority = 0;
        handling_time = 3;

    }

    PCB(string ID, int priority) {
        this->ID = ID;
        memory = 0;
     //   other_resources = NULL;
        status_code = 0;
       // status_list = NULL;

        father = NULL;
        bigson = NULL;
        brother = NULL;

        this->priority = priority;

        handling_time = 10;
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
            // TODO： 当进程需要多个资源时 需要修改此处逻辑！
            highest_process->status_code = 0;
            highest_process->status_list.pop_back();
            highest_process->other_resources.push_back((*iter));
            // 将该资源的阻塞队列中最高优先级的进程提取到就绪队列中
            READY_QUEUE.push_back(highest_process);

            // C++的BUG？ 传入的string类型的ID变乱码导致崩溃
            // 解决：之前传递的不是引用 而是按值传递 相当于没有修改
            // cout<<"资源 "<<RID<<" 自由后被 "<<(*highest_process_iter)->ID<<" 占有！"<<endl;
        }
        else{
            cout<<"资源 "<<RID<<" 已自由"<<endl;
        }
        scheduler();

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
            if((*iter)->other_resources.size()!=0)
                (*iter)->release((*iter)->other_resources[0]->RID);
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

    scheduler();
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

    // 创建init进程
    PCB* initPCB = createProcess("0", 0);
    NOW_PROCESS = initPCB;
    // 将initPCB的处理时间设为最大值
    initPCB->handling_time = MAX_HANDLING_TIME;

    // 初始化资源块
    RCB* R1 = new RCB(1);
    RCB* R2 = new RCB(2);
    RESOURCE_LIST.push_back(R1);
    RESOURCE_LIST.push_back(R2);

}

int main()
{
    init();

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
            deleteProcess(NOW_PROCESS->ID);
        }

        else if(command=="rq"){
            int RID;
            cin>>RID;
            NOW_PROCESS->request(RID);
        }
        else if(command=="rl"){
            int RID;
            cin>>RID;
            if(NOW_PROCESS->other_resources.size()!=0){
                NOW_PROCESS->release(RID);
            }
            else{
                cout<<"当前进程 "<<NOW_PROCESS->ID<<endl;
                cout<<"非法操作，该进程没有占据该资源"<<endl;
            }
        }
        else if(command=="bk"){
            break;
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
    return 0;
}


// 记住要传递引用。。。
// erase神坑
// iter神坑
