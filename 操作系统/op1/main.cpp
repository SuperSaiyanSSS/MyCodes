#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

class PCB;
class RCB;
// ȫ�ֱ���
vector<PCB*> PROCESS_LIST;
PCB* NOW_PROCESS;


// ��Դ���ƿ�
class RCB {
public:
    // Ψһ��ʶ
    int RID;
    // ״̬ ��Ϊfree��allocated
    string status;
    // �ȴ�����
    // ����Դ�����Ľ����б�
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


// ���̿��ƿ�
class PCB
{
public:
    string ID;
    // �ڴ���Դ
    int memory;
    // ������Դ
    RCB* other_resources;
    // ����״̬
    int status_code;
    // TODO..
    int zhuangtaiduilie;

    // ������
    PCB* father;
    // �ӽ��������Ķ���
    PCB* bigson;
    // �ֵܽ���
    PCB* brother;

    // ���ȼ�
    int priority;

    // ����ʱ��
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

// ����һ��RCBָ��ָ�������Դ����
// ������赥����Դ
void insert(PCB* SELF, RCB* requested_resource) {
    SELF->other_resources = requested_resource;
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
    cout<<"????????"<<endl;

    // ����
    // ״̬�� 0Ϊ���� 1Ϊ���� 2Ϊ���� 3Ϊ������ -1Ϊ��ɾ��
    // TODO:��Ϊͬһ������ʱ����������� ����ҲҪ�������ѭ���м������Ƿ����������߹���״̬
    if(NOW_PROCESS->priority<max_priority&&NOW_PROCESS->status_code!=2) {
        cout<<"���ڸ��� "<<NOW_PROCESS->ID;
        NOW_PROCESS->status_code = 0;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" Ϊ"<<NOW_PROCESS->ID<<endl;

    }
        // �����ǰ���̱�ɾ�� ��ֱ���滻
    else if(NOW_PROCESS->status_code==-1){
        cout<<"���ڸ��� "<<NOW_PROCESS->ID;
        NOW_PROCESS = *target_PCB;
        NOW_PROCESS->status_code = 2;
        cout<<" Ϊ"<<NOW_PROCESS->ID<<endl;
    }
}



int main()
{
    PCB* initPCB = createProcess("0", 0);
    NOW_PROCESS = initPCB;
    // ��initPCB�Ĵ���ʱ����Ϊ���ֵ
    initPCB->handling_time = 10000;

    while(1){
        Sleep(500);
        string command;
        string name;
        int priority;

        scheduler();

        cin>>command;

        vector<PCB*>::iterator iter;
        cout<<"��ǰ�ڴ��е����н��̼������ȼ�Ϊ"
        for(iter=PROCESS_LIST.begin();iter!=PROCESS_LIST.end();iter++){
            cout<<"-- "<<(*iter)->ID<<" ���ȼ� "<<(*iter)->priority<<endl;
        }

        // ������н��� ��ôɾ���ý��� Ѱ����һ���ȵĽ���
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
            cout<<"�Ƿ�������"<<endl;
            continue;
        }


        cout<<name<<endl;


    }


    cout << "�ɹ��˳�" << endl;
    return 0;
}

