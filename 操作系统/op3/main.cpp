#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
class PageTable;

PageTable* PageTableList;
vector<int> PhysicalBlockList;
vector<int> PageUsedSequence;
int oldest_point;
vector<int> RecordQueue;
int success_number;
int fail_number;

int PAGETABLENUM;
int PHYSICALBLOCKNUM;

class PageTable{
public:
    int page_sequence;
    int physical_block_sequence;
    bool in_mem;
    int used_times;
    bool has_changed;
    int disk_address;

    PageTable(){
        page_sequence = 0;
        physical_block_sequence = 0;
        in_mem = false;
        used_times = 0;
        has_changed = false;
        disk_address = 0;
    };
};

void init(){
    success_number = 0;
    fail_number = 0;

    PageTableList = new PageTable[PAGETABLENUM]();
    for(int i=0;i<PAGETABLENUM;i++){
        PageTableList[i].page_sequence = i;
    }

    for(int i=0;i<PHYSICALBLOCKNUM;i++){
        PhysicalBlockList.push_back(-1);
    }
//    PageUsedSequence.push_back(4);
//    PageUsedSequence.push_back(7);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(7);
//    PageUsedSequence.push_back(1);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(1);
//    PageUsedSequence.push_back(2);
//    PageUsedSequence.push_back(1);
//    PageUsedSequence.push_back(2);
//    PageUsedSequence.push_back(6);

    // ����趨�������е�ҳ�����
    int count = rand()%50+10;
    for(int i=0;i<count;i++){
        PageUsedSequence.push_back(rand()%PAGETABLENUM);
    }
//    PageUsedSequence.push_back(7);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(1);
//    PageUsedSequence.push_back(2);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(3);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(4);
//    PageUsedSequence.push_back(2);
//    PageUsedSequence.push_back(3);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(3);
//    PageUsedSequence.push_back(2);
//    PageUsedSequence.push_back(1);
//    PageUsedSequence.push_back(2);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(1);
//    PageUsedSequence.push_back(7);
//    PageUsedSequence.push_back(0);
//    PageUsedSequence.push_back(0);
}


void display_stack(){
    cout<<"====="<<endl;
    for(int i=0;i<PHYSICALBLOCKNUM;i++){
        cout<<PhysicalBlockList[i]<<endl;
    }
    cout<<"====="<<endl;
}


void LRU(){
    for(vector<int>::iterator iter = PageUsedSequence.begin();iter!=PageUsedSequence.end(); iter++){
        cout<<"�������� "<<*iter<<endl;
        // ����Ƿ��Ѿ���
        bool mem_full_flag = true;
        int stack_next_sequnce = 0;
        for(int i=0;i<PHYSICALBLOCKNUM;i++){
            if(PhysicalBlockList[i]==-1){
                stack_next_sequnce = i;
                mem_full_flag = false;
                break;
            }
        }

        // ����Ƿ��Ѿ���ջ��
        bool in_mem_flag = false;
        int old_sequence = 0;
        for(int i=0;i<PHYSICALBLOCKNUM;i++){
            if(PhysicalBlockList[i]==(*iter)){
                old_sequence = i;
                in_mem_flag = true;
                break;
            }
        }
        if(in_mem_flag){
            if(mem_full_flag){
                // �ƶ�Ŀ������ջ��
                for(int i=old_sequence+1;i<PHYSICALBLOCKNUM;i++){
                    PhysicalBlockList[i-1] = PhysicalBlockList[i];
                }
                PhysicalBlockList[PHYSICALBLOCKNUM-1] = *iter;
                display_stack();
                success_number++;
                continue;
            }
            else{
                // �ƶ�Ŀ����Ѿ�����ջ��
                for(int i=old_sequence+1;i<stack_next_sequnce;i++){
                    PhysicalBlockList[i-1] = PhysicalBlockList[i];
                }
                PhysicalBlockList[stack_next_sequnce-1] = *iter;
                display_stack();
                continue;
            }
        }
        else{
            if(mem_full_flag) {
                for (int i = 1; i < PHYSICALBLOCKNUM; i++) {
                    PhysicalBlockList[i - 1] = PhysicalBlockList[i];
                }
                PhysicalBlockList[PHYSICALBLOCKNUM - 1] = *iter;
                display_stack();
                fail_number++;
                continue;
            }
            else{
                PhysicalBlockList[stack_next_sequnce] = *iter;
                display_stack();
                continue;
            }
        }

    }
}


void FIFO(){
    for(vector<int>::iterator iter = PageUsedSequence.begin();iter!=PageUsedSequence.end(); iter++){
        cout<<"�������� "<<*iter<<endl;
        bool has_recorded = false;
        for(vector<int>::iterator iter2 = RecordQueue.begin();iter2!=RecordQueue.end(); iter2++){
            if(*iter2==*iter){
                has_recorded = true;
                break;
            }
        }
        if(!has_recorded){
            RecordQueue.push_back(*iter);
        }
        oldest_point = RecordQueue[0];
        cout<<"����ϵ�"<<oldest_point<<endl;
        for(vector<int>::iterator iter2 = RecordQueue.begin();iter2!=RecordQueue.end(); iter2++){
            cout<<"--- "<<*iter2;
        }
        cout<<endl;

        // ����Ƿ��Ѿ���ջ��
        bool in_mem_flag = false;
        int old_sequence = 0;
        for(int i=0;i<PHYSICALBLOCKNUM;i++){
            if(PhysicalBlockList[i]==(*iter)){
                old_sequence = i;
                in_mem_flag = true;
                break;
            }
        }


        // ����Ƿ��Ѿ���
        bool mem_full_flag = true;
        int stack_next_sequnce = 0;
        for(int i=0;i<PHYSICALBLOCKNUM;i++){
            if(PhysicalBlockList[i]==-1){
                stack_next_sequnce = i;
                mem_full_flag = false;
                break;
            }
        }

        if(in_mem_flag){
            display_stack();
            if(mem_full_flag)
                success_number++;
            continue;
        }


        if(mem_full_flag){
            // Ѱ�����ϵ�Ԫ�����ڵ�ջ��
            for(int i=0;i<PHYSICALBLOCKNUM;i++){
                if(PhysicalBlockList[i] == oldest_point){
                    PhysicalBlockList[i] = *iter;
                    RecordQueue.erase(RecordQueue.begin());
                    break;
                }
            }
            display_stack();
            fail_number++;
            continue;
        }
        else{
            PhysicalBlockList[stack_next_sequnce] = *iter;
            display_stack();
            continue;
        }
    }
}


int main() {
    std::cout << "===����洢������֮ҳ���û��㷨===" << std::endl;
    srand((unsigned)time(NULL));

    cout<<"���������ҳ�����Ŀ"<<endl;
    cin>>PAGETABLENUM;
    cout<<"�������ڴ���������"<<endl;
    cin>>PHYSICALBLOCKNUM;
    while(1) {
        init();
        cout<<"������Ҫѡ���ҳ���û��㷨"<<endl;
        cout<<"(0)�������"<<endl;
        cout<<"(1)�Ƚ��ȳ�ҳ���û��㷨"<<endl;
        cout<<"(2)������δʹ��ҳ���û��㷨"<<endl;
        int choose;
        cin>>choose;
        if(choose==1){
            FIFO();
        }
        else if(choose==2){
            LRU();
        }
        else if(choose==0){
            cout<<"���������"<<endl;
            break;
        }
        else{
            cout<<"�Ƿ����룡"<<endl;
            continue;
        }
        double f = (double) fail_number / ((double) success_number + (double) fail_number);
        cout << "ȱҳ��Ϊ " << f << endl;
    }
    return 0;
}