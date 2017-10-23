#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#define MAX_HANDLING_TIME 1000000

using namespace std;

// �߳�1�����û����� �����ж�
DWORD WINAPI ThreadProc1(LPVOID lpParameter);
// �߳�2Ϊϵͳ�Զ�������̵��� ����ʱ���ж�
DWORD WINAPI ThreadProc2(LPVOID lpParameter);

// �ػ�
int power_off;

class PCB;
class RCB;
class IO;
// ȫ�ֱ���
// ���н����б�
vector<PCB*> PROCESS_LIST;
// ��ǰ���н���
PCB* NOW_PROCESS;
// ������Դ���б�
vector<RCB*> RESOURCE_LIST;
// IO�豸
IO* IO_RESOURCE;

// �������У�״ֵ̬Ϊ0��
vector<PCB*> READY_QUEUE;
// �������У�״ֵ̬Ϊ3��
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

// ��Դ���ƿ�
class RCB {
public:
    // Ψһ��ʶ
    int RID;
    // ״̬ ��Ϊfree��allocated
    string status;
    // �ȴ�����
    // ����Դ�����Ľ����б�
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


// ���̿��ƿ�
class PCB
{
public:
    string ID;
    // �ڴ���Դ
    int memory;
    // ������Դ
    vector<RCB*> other_resources;
    // ����״̬
    int status_code;
    // TODO..����ֻ��һ����Ҫ��RCB
    vector<RCB*> status_list;

    vector<PCB*> son_process_list;

    // ���ȼ�
    int priority;

    // ����ʱ��
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
            // ����һ��RCBָ��ָ�������Դ����
            insert(this, (*iter));
        }
        else{
            // ������Դ��ռ�� ��ý�������
            this->status_code = 3;
            this->status_list.push_back(*iter);
            cout<<" The process "<<this->ID<<" is blocked!!!"<<endl;
            // ���ý��̲������Դ�ĵȴ�����
            insert((*iter), this);

            // ������ �ͷ���request����Դ Ԥ������
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

            // ���̡������ܡ��ܶ����Դ������ ֱ�ӽ����������
            highest_process->other_resources.push_back((*iter));
            highest_process->status_list.pop_back();
            highest_process->status_code = 0;

            // ������Դ������������������ȼ��Ľ�����ȡ������������
            READY_QUEUE.push_back(highest_process);
            cout<<"���� "<<highest_process->ID<<" �Ѿ���"<<endl;


            // C++��BUG�� �����string���͵�ID�����뵼�±���
            // �����֮ǰ���ݵĲ������� ���ǰ�ֵ���� �൱��û���޸�
            // cout<<"��Դ "<<RID<<" ���ɺ� "<<(*highest_process_iter)->ID<<" ռ�У�"<<endl;
        }
        else{
            cout<<"��Դ "<<RID<<" ������"<<endl;
        }
        scheduler();

    }

    void request_IO(){

        if(IO_RESOURCE->status=="free"){
            IO_RESOURCE->status = "allocated";
            IO_RESOURCE->order = this;

        }
        else{
            // ������Դ��ռ�� ��ý���I/O����
            this->status_code = 3;
            cout<<" The process "<<this->ID<<" is I/O blocked!!!"<<endl;
            // ���ý��̲������Դ�ĵȴ�����
            PCB* this_p = this;
            IO_RESOURCE->waiting_list.push_back(this_p);

            // ������ �ͷ���request����Դ Ԥ������
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
            // ���̡������ܡ��ܶ����Դ������ ֱ�ӽ����������
            highest_process->status_code = 0;

            // ������Դ������������������ȼ��Ľ�����ȡ������������
            READY_QUEUE.push_back(highest_process);
            cout<<"���� "<<highest_process->ID<<" �Ѿ���"<<endl;

        }
        else{
            IO_RESOURCE->status = "free";
            cout<<"��Դ I/O ������"<<endl;
        }
        scheduler();
    }

};


PCB* createProcess(string ID, int priority) {
    PCB* newProcess = new PCB(ID, priority);
    PROCESS_LIST.push_back(newProcess);
    if(ID!="0") {
        cout<<"��ǰ�ĸ�����Ϊ"<<NOW_PROCESS->ID<<endl;
        NOW_PROCESS->son_process_list.push_back(newProcess);
    }
    return newProcess;
}

void deleteProcess(string ID) {
    vector<PCB*>::iterator iter;
    cout<<"ɾ��֮ǰ"<<endl;
    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        cout<<"-- "<<(*iter)->ID<<endl;
    }


    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();){
        if((*iter)->ID==ID){

            // �ͷ�I/O��Դ
            if(IO_RESOURCE->status=="allocated"&&IO_RESOURCE->order==(*iter)){
                (*iter)->release_IO();
            }

            cout<<ID<<endl;
            cout<<(*iter)->son_process_list.size()<<endl;
            cout<<"111���ڵݹ����"<<(*iter)->ID<<"���ӽ��̡�����"<<endl;
            for(int i=0;i<(*iter)->son_process_list.size();i++){
                cout<<"���ڵݹ����"<<(*iter)->son_process_list[i]->ID<<"���ӽ��̡�����"<<endl;
                deleteProcess((*iter)->son_process_list[i]->ID);
            }

            // ���ý���ռ����Դ ���ͷ�
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
    cout<<"ɾ��֮��"<<endl;
    for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        cout<<"-- "<<(*iter)->ID<<endl;
    }
    return;

  //  scheduler();
}


// ������赥����Դ
// ĳ������Ҫ����Դ
void insert(PCB* SELF, RCB* requested_resource) {
    SELF->other_resources.push_back(requested_resource);
}
// ĳ��Դ�ĵȴ�����
void insert(RCB* THAT, PCB* blocked_process){
    THAT->waiting_list.push_back(blocked_process);
}

// �����̴�ĳ������ɾ��
void remove(vector<PCB*>& list, PCB* SELF){
    vector<PCB*>::iterator iter;
    for(iter=list.begin();iter!=list.end();iter++){
        if((*iter)->ID==SELF->ID){
            break;
        }
    }
    list.erase(iter);
}

// ����Դ���ĳ������ɾ��
void remove(vector<RCB*>& list, RCB* SELF){
    vector<RCB*>::iterator iter;
    for(iter=list.begin();iter!=list.end();iter++){
        if((*iter)->RID==SELF->RID){
            break;
        }
    }
    cout<<"ɾ��֮ǰ "<<list.size()<<endl;
    list.erase(iter);
    cout<<"֮�� "<<list.size()<<endl;
    SELF->status = "free";
}

// ɾ��ĳ�������ȼ���ߵĽ��̣���������ָ��
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
        cout<<"-- "<<(*iter)->ID<<" �����ȼ�"<<(*iter)->priority<<endl;
    }
    cout<<"Ŀ��"<<target_PCB->ID<<endl;
    list.erase(target_iter);
    cout<<list.size()<<endl;
    cout<<"��Դ  ���ɺ� "<<target_PCB->ID<<" ռ�У�"<<endl;
    //cout<<(*target_PCB)->ID<<endl;
    return target_PCB;

}

void scheduler(){

    // �ҵ�������ȼ����� target_PCB;
    int max_priority;
    vector<PCB*>::iterator target_PCB = PROCESS_LIST.begin();

    max_priority = PROCESS_LIST[0]->priority;

    for(vector<PCB*>::iterator iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
        if((*iter)->priority>max_priority&&((*iter)->status_code==0)){
            target_PCB = iter;
            max_priority = (*iter)->priority;
        }
    }
    cout<<"�����С���"<<endl;

    // ����
    // ״̬�� 0Ϊ���� 1Ϊ���� 2Ϊ���� 3Ϊ������ -1Ϊ��ɾ��
    // TODO:��Ϊͬһ������ʱ����������� ����ҲҪ�������ѭ���м������Ƿ����������߹���״̬
    if(NOW_PROCESS->priority<max_priority&&NOW_PROCESS->status_code==2) {
        cout<<"1���ڸ��� "<<NOW_PROCESS->ID;
        NOW_PROCESS->status_code = 0;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" Ϊ"<<NOW_PROCESS->ID<<endl;

    }
        // �����ǰ���̱�ɾ�������� ��ֱ���滻
    else if(NOW_PROCESS->status_code==-1||NOW_PROCESS->status_code==3){
        cout<<"2���ڸ��� "<<NOW_PROCESS->ID;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" Ϊ"<<NOW_PROCESS->ID<<endl;
    }

}


void init(){

    // ����
    power_off = 0;
    // ����init����
    PCB* initPCB = createProcess("0", 0);
    NOW_PROCESS = initPCB;
    // ��initPCB�Ĵ���ʱ����Ϊ���ֵ
    initPCB->handling_time = MAX_HANDLING_TIME;

    // ��ʼ����Դ��
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
        // ÿ6�����һ��ϵͳʱ���ж�
        Sleep(6000);

        scheduler();

        vector<PCB *>::iterator iter;
        cout << "��ǰ�ڴ��е����н��̼������ȼ�Ϊ";
        for (iter = PROCESS_LIST.begin(); iter != PROCESS_LIST.end(); iter++) {
            cout << "-- " << (*iter)->ID << " ���ȼ� " << (*iter)->priority << " ״̬ " << (*iter)->status_code << endl;
        }

        // �������ʱ����� ��ôɾ���ý��� Ѱ����һ���ȵĽ���
        NOW_PROCESS->handling_time--;
        if (NOW_PROCESS->handling_time <= 0) {
            cout<<"WARNING!������"<<NOW_PROCESS->ID<<"�����������н�����"<<endl;
            deleteProcess(NOW_PROCESS->ID);
            // scheduler();
        }

        cout<<"��ǰ���н���: "<<NOW_PROCESS->ID<<endl;
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
        cout<<"��ǰ�ڴ��е����н��̼������ȼ�Ϊ";
        for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
            cout<<"-- "<<(*iter)->ID<<" ���ȼ� "<<(*iter)->priority<<" ״̬ "<<(*iter)->status_code<<endl;
        }

        // �������ʱ����� ��ôɾ���ý��� Ѱ����һ���ȵĽ���
        NOW_PROCESS->handling_time--;
        if(NOW_PROCESS->handling_time<=0){
            deleteProcess(NOW_PROCESS->ID);
            // scheduler();
        }

        cout<<"��ǰ���н��̣�"<<NOW_PROCESS->ID<<endl;
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
                cout<<"��ǰ���� "<<NOW_PROCESS->ID<<endl;
                cout<<"�Ƿ��������ý���û��ռ�ݸ���Դ"<<endl;
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
            cout<<"�Ƿ�������"<<endl;
            continue;
        }

        cout<<name<<endl;

        cout<<"��ǰ�ڴ��е����н��̼������ȼ�Ϊ";
        for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
            cout<<"-- "<<(*iter)->ID<<" ���ȼ� "<<(*iter)->priority<<" ״̬ "<<(*iter)->status_code<<endl;
        }

    }

    cout << "�ɹ��˳�" << endl;
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
    // TODO:  ���ֶ���
    cout<<"-------------------------------------------------"<<endl;
    cout<<"| ������Դ�飬���Ʒֱ�Ϊ1��2                      |"<<endl;
    cout<<"| ����I/O�豸������Ϊ10                          |"<<endl;
    cout<<"| ����cr a 10����ʾ������Ϊa�Ľ��̣����ȼ�Ϊ10     |"<<endl;
    cout<<"| ����rq 1����ʾ������Դ��1                       |"<<endl;
    cout<<"| ����rl 1����ʾ�ͷ���Դ��2                       |"<<endl;
    cout<<"| ����dl a����ʾɾ��a���̼����������              |"<<endl;
    cout<<"| ����bk����ʾ�˳���ǰ����                        |"<<endl;
    cout<<"| ÿ��6�룬ϵͳ������һ��ʱ���жϣ���ʱ��ƬΪ6��   |"<<endl;
    cout<<"| ��0�����⣬���̵Ĵ���ʱ��Ϊ20��ʱ��Ƭ����ʱ����  |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|                        ���� by SuperSaiyan Goku |"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    init();

    HANDLE handle1=CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
    HANDLE handle2=CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);
    CloseHandle(handle1);
    CloseHandle(handle2);

    // ��������������ʱ��
    while(1) {
        Sleep(2000);
        if(power_off==1){
            break;
        }
    }
    cout << "�ɹ��˳�" << endl;
    return 0;
}


// ��סҪ�������á�����
// erase���
// iter���
