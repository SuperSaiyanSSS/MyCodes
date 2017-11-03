#include <iostream>
#define RESOURCE 3
#define PROCESS 5

using namespace std;

//int* Available;
//int** Max;
//int** Allocation;
//int** Need;
//bool* Finish;
//int* Work;
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

    //int Available[RESOURCE];
//    Available = new int[RESOURCE];
//    for(int i=0;i<PROCESS;i++){
//        Max[i] = new int[RESOURCE];
//    }
//    for(int i=0;i<PROCESS;i++){
//        Allocation[i] = new int[RESOURCE];
//    }
//    for(int i=0;i<PROCESS;i++){
//        Need[i] = new int[RESOURCE];
//    }
//    Finish = new bool[PROCESS];
//    Work = new int[RESOURCE];
//    int Max[PROCESS][RESOURCE] = {{7,5,3},
//    {3,2,2},
//    {9,0,2},
//     {2,2,2},
//    {4,3,3}
//    };
//    int Allocation[PROCESS][RESOURCE] = {
//            {0,1,0},
//            {2,0,0},
//            {3,0,2},
//            {2,1,1},
//            {0,0,2}
//    };

//    Allocation[0] = {0,1,0};
//    Allocation[1] = {2,0,0};
//    Allocation[2] = {3,0,2};
//    Allocation[3] = {2,1,1};
//    Allocation[4] = {0,0,2};
    //int Need[PROCESS][RESOURCE];

//    for(int i=0;i<PROCESS;i++){
//        for(int j=0;j<RESOURCE;j++){
//            Need[i][j] = Max[i][j] - Allocation[i][j];
//        }
//    }

   // int Available[PROCESS][RESOURCE] = {3,3,2};
//    Available[0] = 3;
//    Available[1] = 3;
//    Available[2] = 2;
}

int test_safe(){

    for(int i=0;i<RESOURCE;i++){
        Work[i] = Available[i];
        cout<<Work[i]<<endl;
    }

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

void request(int target_process, int *need_resource_list, int list_size){

    if(list_size!=RESOURCE){
        cout<<"输入非法！"<<endl;
        return;
    }
    bool can_flag = true;
    for(int i=0;i<list_size;i++){
        if(need_resource_list[i]>Need[target_process][i]||need_resource_list[i]>Available[i]){
            can_flag = false;
        }
    }
    if(!can_flag){
        cout<<"不安全！"<<endl;
        return;
    }
    for(int j=0;j<list_size;j++){
        Available[j] -= need_resource_list[j];
        Allocation[target_process][j] += need_resource_list[j];
        Need[target_process][j] -= need_resource_list[j];
    }

    int safe_flag = test_safe();
    if(safe_flag){
        cout<<"分配需要的成功12"<<endl;
    }
    else{
        cout<<"不好意思"<<endl;
    }
    return;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    init();
   // test_safe();
    int target_process = 1;
    int need_resource_list[RESOURCE] = {1,0,2};
    request(target_process, need_resource_list, RESOURCE);
    target_process = 0;

    need_resource_list[0] = 0;
    need_resource_list[1] = 2;
    need_resource_list[2] = 0;

    request(target_process, need_resource_list, RESOURCE);
    return 0;
}