#include <iostream>
#define RESOURCE 3
#define PROCESS 5

using namespace std;

int Max[PROCESS][RESOURCE] = {
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
};
int Allocation[PROCESS][RESOURCE] = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
};

int Need[PROCESS][RESOURCE] = {
        7,4,3,1,2,2,6,0,0,0,1,1,4,3,1
};

int Work[RESOURCE];

bool Finish[PROCESS] = {false, false, false};

int Available[RESOURCE] = {3,3,2};

void init(){
    for(int i=0;i<PROCESS;i++){
        for(int j=0;j<RESOURCE;j++){
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

int test_safe(){

    for(int i=0;i<PROCESS;i++){
        Finish[i] = false;
    }

    cout<<"现在拥有的资源1 2 3的数量分别为"<<endl;
    for(int i=0;i<RESOURCE;i++){
        Work[i] = Available[i];
        cout<<Work[i]<<" ";
    }
    cout<<endl;

    while(1) {
        bool ok_flag = false;
        int target_process = -1;
        for (int i = 0; i < PROCESS; i++) {
            if (!Finish[i]) {
                for (int j = 0; j < RESOURCE; j++) {
                    if (Need[i][j] > Work[j]) {
                        ok_flag = false;
                        break;
                    }
                    if (j == RESOURCE - 1 && Need[i][j] <= Work[j]) {
                        ok_flag = true;
                    }
                }
                if (ok_flag) {
                    target_process = i;
                    cout<<"现在运行的进程为    "<<i<<endl;
                    break;
                }
            }
        }
        if(!ok_flag){
            break;
        }
        for (int j = 0; j < RESOURCE; j++) {
            Work[j] += Allocation[target_process][j];
        }
        Finish[target_process] = true;
    }
    for(int i=0;i<PROCESS;i++){
        if(!Finish[i]){
            cout<<"fail"<<endl;
            return 0;
        }
    }
    cout<<"success"<<endl;
    return 1;

}

void request(int target_process, int *need_resource_list){

    bool can_flag = true;
    for(int i=0;i<RESOURCE;i++){
        if(need_resource_list[i]>Need[target_process][i]||need_resource_list[i]>Available[i]){
            can_flag = false;
        }
    }
    if(!can_flag){
        cout<<"不安全！"<<endl;
        return;
    }
    for(int j=0;j<RESOURCE;j++){
        Available[j] -= need_resource_list[j];
        Allocation[target_process][j] += need_resource_list[j];
        Need[target_process][j] -= need_resource_list[j];
    }

    int safe_flag = test_safe();
    if(safe_flag){
        cout<<"申请资源成功！"<<endl;
    }
    else{
        cout<<"申请资源失败，原因是将进入不安全状态"<<endl;
        for(int j=0;j<RESOURCE;j++){
            Available[j] += need_resource_list[j];
            Allocation[target_process][j] -= need_resource_list[j];
            Need[target_process][j] += need_resource_list[j];
        }
    }


    return;
}

void display(){
    cout<<"当前最大需求矩阵 Max 为"<<endl;
    for(int i=0;i<PROCESS;i++){
        for(int j=0;j<RESOURCE;j++){
            cout<<Max[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"当可利用资源向量 Available 为"<<endl;
    for(int j=0;j<RESOURCE;j++){
        cout<<Available[j]<<" ";
    }
    cout<<endl;
    cout<<"当前分配矩阵 Allocation 为"<<endl;
    for(int i=0;i<PROCESS;i++){
        for(int j=0;j<RESOURCE;j++){
            cout<<Allocation[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"当前需求矩阵 Need 为"<<endl;
    for(int i=0;i<PROCESS;i++){
        for(int j=0;j<RESOURCE;j++){
            cout<<Need[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    std::cout << "=======银行家算法========" << std::endl;
    init();
    display();
    cout<<"检查当前状态是否安全。。"<<endl;
    test_safe();
    int target_process;
    int need_resource_list[RESOURCE];

    target_process = 0;
    while(1) {

        display();

        cout << "请输入命令 格式为 request 0 0 2 0" << endl;
        cout << "示例为进程0请求资源1,2,3的数量分别为0,2,0" << endl;
        cout <<"如结束，则输入break"<<endl;

        string request2;
        cin >> request2;
        if (request2 == "break"){
            break;
        }
        if (request2 != "request") {
            cout << "非法输入！" << endl;
        }
        cin >> target_process;
        if (target_process < 0 || target_process >= PROCESS) {
            cout << "进程超出范围，范围为0到" << PROCESS << endl;
        }
        for (int i = 0; i < RESOURCE; i++) {
            cin >> need_resource_list[i];
        }
        request(target_process, need_resource_list);
    }
    return 0;
}