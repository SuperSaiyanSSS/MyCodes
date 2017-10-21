#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>

#define MMSIZE 2000
#define MINSIZE 2

using namespace std;


char mm[MMSIZE];

class BlankPartitionTable{
public:
    vector<int> number;
    vector<int> size;
    vector<int> start_address;
    vector<int> status;

    void reset_number(){
        for(int i=0;i<number.size();i++){
            number[i] = i;
        }
    }


    void erase(int i){
        int count = 0;
        vector<int>::iterator iter;
        for(iter=size.begin();iter<size.end();iter++){
            if(count==i){
                size.erase(iter);
                break;
            }
            count++;
        }
        count = 0;
        for(iter=start_address.begin();iter<start_address.end();iter++){
            if(count==i){
                start_address.erase(iter);
                break;
            }
            count++;
        }
        status.pop_back();
        number.pop_back();
        reset_number();
    }

    void display(){
        cout<<"空闲表如下"<<endl;
        for(int i=0;i<size.size();i++){
            cout<<number[i]<<" "<<start_address[i]<<" "<<size[i]<<endl;
        }
    }

    vector<int>::iterator get_iter_of_size(int num){
        int count = 0;
        vector<int>::iterator iter;
        for(iter = size.begin();iter<size.end();iter++){
            if(count==num){
                return iter;
            }
            count++;
        }
    }

    vector<int>::iterator get_iter_of_start_address(int num){
        int count = 0;
        vector<int>::iterator iter;
        for(iter = start_address.begin();iter<start_address.end();iter++){
            if(count==num){
                return iter;
            }
            count++;
        }
    }
};

BlankPartitionTable* blank_table;

class HasRequestedTable{
public:
    vector<int> number;
    vector<int> size;
    vector<int> start_address;
    vector<int> status;

    void reset_number(){
        for(int i=0;i<number.size();i++){
            number[i] = i;
        }
    }

    void erase(int i){
        int count = 0;
        vector<int>::iterator iter;
        for(iter=size.begin();iter<size.end();iter++){
            if(count==i){
                size.erase(iter);
                break;
            }
            count++;
        }
        count = 0;
        for(iter=start_address.begin();iter<start_address.end();iter++){
            if(count==i){
                start_address.erase(iter);
                break;
            }
            count++;
        }
        status.pop_back();
        number.pop_back();
        reset_number();
    }

    void display(){
        cout<<"忙碌表如下"<<endl;
        for(int i=0;i<size.size();i++){
            cout<<number[i]<<" "<<start_address[i]<<" "<<size[i]<<endl;
        }
    }

    void insert(int start_address, int size){
        status.push_back(1);
        this->start_address.push_back(start_address);
        this->size.push_back(size);
        reset_number();
    }

    vector<int>::iterator get_iter_of_size(int num){
        int count = 0;
        vector<int>::iterator iter;
        for(iter = size.begin();iter<size.end();iter++){
            if(count==num){
                return iter;
            }
            count++;
        }
    }

    vector<int>::iterator get_iter_of_start_address(int num){
        int count = 0;
        vector<int>::iterator iter;
        for(iter = start_address.begin();iter<start_address.end();iter++){
            if(count==num){
                return iter;
            }
            count++;
        }
    }
};

HasRequestedTable* busy_table;

class AllMMTable{
public:
    vector<int> number;
    vector<int> size;
    vector<int> start_address;
    vector<int> status;

    AllMMTable(){
        ;
    }

    void reset_number(){
        for(int i=0;i<number.size();i++){
            number[i] = i;
        }
    }

    void erase(int i){
        int count = 0;
        vector<int>::iterator iter;
        for(iter=size.begin();iter<size.end();iter++){
            if(count==i){
                size.erase(iter);
                break;
            }
            count++;
        }
        count = 0;
        for(iter=start_address.begin();iter<start_address.end();iter++){
            if(count==i){
                start_address.erase(iter);
                break;
            }
            count++;
        }
        status.pop_back();
        number.pop_back();
        reset_number();
    }

    void display(){
        cout<<"所有表如下"<<endl;
        for(int i=0;i<size.size();i++){
            cout<<number[i]<<" "<<start_address[i]<<" "<<size[i]<<" "<<status[i]<<endl;
        }
    }

    vector<int>::iterator get_iter_of_size(int num){
        int count = 0;
        vector<int>::iterator iter;
        for(iter = size.begin();iter<size.end();iter++){
            if(count==num){
                return iter;
            }
            count++;
        }
    }

    vector<int>::iterator get_iter_of_start_address(int num){
        int count = 0;
        vector<int>::iterator iter;
        for(iter = start_address.begin();iter<start_address.end();iter++){
            if(count==num){
                return iter;
            }
            count++;
        }
    }
};

AllMMTable* all_table;


void* mem_init(){
    int start_i = 0;
    int count = 0;
    int blank_count = 0;
    int busy_count = 0;

    while(count<20){
        int now_size = (rand() % (MMSIZE));
        if(now_size>100||now_size<MINSIZE)
            continue;
        if(now_size+start_i>MMSIZE){
            if(count>10)
                break;
            else
                continue;
        }
        else{
            if(count%2==1) {
                busy_table->number.push_back(busy_count);
                busy_table->size.push_back(now_size);
                busy_table->start_address.push_back(start_i);
                busy_table->status.push_back(1);

                all_table->number.push_back(count);
                all_table->size.push_back(now_size);
                all_table->start_address.push_back(start_i);
                all_table->status.push_back(1);

                start_i += now_size;
                busy_count++;
            }
            else{
                blank_table->number.push_back(blank_count);
                blank_table->size.push_back(now_size);
                blank_table->start_address.push_back(start_i);
                blank_table->status.push_back(0);

                all_table->number.push_back(count);
                all_table->size.push_back(now_size);
                all_table->start_address.push_back(start_i);
                all_table->status.push_back(0);

                start_i += now_size;
                blank_count++;
            }
        }
        count++;
    }

    if(start_i<MMSIZE){
        blank_table->number.push_back(blank_count);
        blank_table->size.push_back(MMSIZE-all_table->start_address[--count]-all_table->size[count]);
        blank_table->start_address.push_back(start_i);
        blank_table->status.push_back(0);

        all_table->number.push_back(blank_count);
        all_table->size.push_back(MMSIZE-all_table->start_address[count]-all_table->size[count]);
        all_table->start_address.push_back(start_i);
        all_table->status.push_back(0);
    }

    cout<<"空闲区如下"<<endl;
    for(int i=0;i<blank_table->number.size();i++){
        cout<<blank_table->number[i]<<" "<<blank_table->start_address[i]<<" "<<blank_table->size[i]<<endl;
    }

    cout<<"忙碌区如下"<<endl;
    for(int i=0;i<busy_table->number.size();i++){
        cout<<busy_table->number[i]<<" "<<busy_table->start_address[i]<<" "<<busy_table->size[i]<<endl;
    }

    cout<<"所有区如下"<<endl;
    for(int i=0;i<all_table->number.size();i++){
        cout<<all_table->number[i]<<" "<<all_table->start_address[i]<<" "<<all_table->size[i]<<" "<<all_table->status[i]<<endl;
    }
}


// 最先适应申请
int mm_request_FF(int n){

    int loss_start = -1;
    //检查第一个大于等于该大小的空闲区
    int i;
    for(i=0;i<blank_table->size.size();i++){
        if(blank_table->size[i]>=n){

            loss_start = blank_table->start_address[i];
            // 若分割后的区域小于最小区域，则把整个空闲区都分出去
            if(blank_table->size[i]-n <= MINSIZE){
                blank_table->erase(i);
            }
            // 否则 剩下的仍然留在空闲表中
            else{
                blank_table->size[i] = blank_table->size[i]- n;
                blank_table->start_address[i] += n;
            }
            break;
        }
    }
    if(loss_start!=-1){
        cout<<"首次适应算法分配出去的起始地址为"<<loss_start<<" 大小为"<<n<<endl;
        blank_table->display();
        // 插入忙碌表中
        busy_table->insert(loss_start, n);

       // busy_table->display();
    }
    return loss_start;
}

int mm_request_BF(int n){
    int loss_start = -1;
    //检查第一个大于等于该大小的空闲区
    int i;
    int min_surplus = MMSIZE;
    int min_pos = 0;
    for(i=0;i<blank_table->size.size();i++){
        if(blank_table->size[i]>=n){
            if(blank_table->size[i] - n < min_surplus){
                min_pos = i;
                min_surplus = blank_table->size[i] - n;
            }
        }
    }
    if(min_surplus!=MMSIZE){
        loss_start = blank_table->start_address[min_pos];
        // 若分割后的区域小于最小区域，则把整个空闲区都分出去
        if(blank_table->size[min_pos]-n <= MINSIZE){
            blank_table->erase(min_pos);
        }// 否则 剩下的仍然留在空闲表中
        else{
            blank_table->size[min_pos] = blank_table->size[min_pos]- n;
            blank_table->start_address[min_pos] += n;
        }
    }

    if(loss_start!=-1){
        cout<<"最佳适应算法分配出去的起始地址为"<<loss_start<<" 大小为"<<n<<endl;
        blank_table->display();
        // 插入忙碌表中
        busy_table->insert(loss_start, n);

        // busy_table->display();
    }
    return loss_start;
}

int mm_request_WF(int n){
    int loss_start = -1;
    //检查第一个大于等于该大小的空闲区
    int i;
    int max_surplus = 0;
    int max_pos = 0;
    for(i=0;i<blank_table->size.size();i++){
        if(blank_table->size[i]>=n){
            if(blank_table->size[i] - n > max_surplus){
                max_pos = i;
                max_surplus = blank_table->size[i] - n;
            }
        }
    }
    if(max_surplus!=0){
        loss_start = blank_table->start_address[max_pos];
        // 若分割后的区域小于最小区域，则把整个空闲区都分出去
        if(blank_table->size[max_pos]-n <= MINSIZE){
            blank_table->erase(max_pos);
        }// 否则 剩下的仍然留在空闲表中
        else{
            blank_table->size[max_pos] = blank_table->size[max_pos]- n;
            blank_table->start_address[max_pos] += n;
        }
    }

    if(loss_start!=-1){
        cout<<"最坏适应算法分配出去的起始地址为"<<loss_start<<" 大小为"<<n<<endl;
        blank_table->display();
        // 插入忙碌表中
        busy_table->insert(loss_start, n);

    }
    return loss_start;
}
// 用于随机归还
int mm_release(int p){
    // 删除忙碌表中的
    int start_address = busy_table->start_address[p];
    int size = busy_table->size[p];

    busy_table->erase(p);

    // 补充到空闲表中
    // 顺序次检索空闲表
    for(int i=0;i<blank_table->size.size();i++){
        if(blank_table->start_address[i]>start_address){
            cout<<"now "<<i<<endl;
            // 不是第一个表且与前一个可用区相邻
            if(i!=0 && start_address == blank_table->start_address[i-1] + blank_table->size[i-1]){
                // 把所释放的可用区与前一分区合并
                blank_table->size[i-1] += size;

                // 与后一可用区相邻？
                if(i!=blank_table->size.size()-1 && blank_table->start_address[i-1]+blank_table->size[i-1] == blank_table->start_address[i]){
                    // 与后一个可用区合并
                    blank_table->size[i-1] += blank_table->size[i];
                    blank_table->erase(i);
                }
            }
            else{
                // 与后一个可用分区相邻？
                if(start_address+size == blank_table->start_address[i]){
                    // 合并
                    blank_table->size[i] += size;
                    blank_table->start_address[i] = start_address;
                   // blank_table->erase(i+1);
                }
                else{
                    vector<int>::iterator iter;
                    iter = blank_table->get_iter_of_start_address(i);
                    blank_table->start_address.insert(iter, start_address);
                    iter = blank_table->get_iter_of_size(i);
                    blank_table->size.insert(iter, size);
                    blank_table->status.push_back(0);
                    blank_table->number.push_back(blank_table->number.size());
                    blank_table->reset_number();
                }
            }
            break;
        }
    }
    cout<<"归还后， 空闲表变为如下："<<endl;
    blank_table->display();
}

double get_utilization_rate_of_memory(){
    double all_block_num = 0;
    for(int i=0;i<blank_table->size.size();i++){
        all_block_num += blank_table->size[i];
    }
    return (MMSIZE-all_block_num)/MMSIZE;
}

void manage(int sim_step, int type){

    for(int i=0;i<sim_step;i++) {
        int n;
        if(type==0) {
            do {
                // 获取请求空间的大小
                n = rand() % 30;

            } while (mm_request_FF(n) != -1);
        }
        if(type==1) {
            do {
                // 获取请求空间的大小
                n = rand() % 30;

            } while (mm_request_BF(n) != -1);
        }
        if(type==2) {
            do {
                // 获取请求空间的大小
                n = rand() % 30;

            } while (mm_request_WF(n) != -1);
        }

       // blank_table->display();
        mm_release(blank_table->size.size()-1);
    }

    cout<<get_utilization_rate_of_memory()<<endl;
}

int main() {
    blank_table = new BlankPartitionTable();
    busy_table = new HasRequestedTable();
    all_table = new AllMMTable();

    srand((unsigned)time(NULL));

    mem_init();
    blank_table->display();

    cout<<"----------------------------"<<endl;
    // 0为FF 1为BF 2为WF
    manage(5, 0);

    return 0;
}