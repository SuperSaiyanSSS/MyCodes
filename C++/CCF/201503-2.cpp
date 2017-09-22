#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct myNode{
	int value;
	int count;
	myNode* next;
};
myNode list[1000];	
int now_value_count=0;
void find_value(int value){
	for(int i=0;i<now_value_count;i++){
		if(list[i].value==value){
			list[i].count++;
			return;
		}
	}
	list[now_value_count].value = value;
	list[now_value_count].count = 1;
	now_value_count++;
	return;
}

int main() {
	int n;
	cin>>n;
	int x;
	for(int i=0;i<n;i++){
		cin>>x;
		find_value(x);
	}
	
	for(int i=0;i<now_value_count;i++){
		for(int j=i+1;j<now_value_count;j++){
			if(list[i].count<list[j].count){
				int temp_value = list[j].value;
				int temp_count = list[j].count;
				list[j].value = list[i].value;
				list[j].count = list[i].count;
				list[i].value = temp_value;
				list[i].count = temp_count;
			}
			else if(list[i].count==list[j].count){
				if(list[i].value>list[j].value){
					int temp_value = list[j].value;
					int temp_count = list[j].count;
					list[j].value = list[i].value;
					list[j].count = list[i].count;
					list[i].value = temp_value;
					list[i].count = temp_count;
				}
			}
		}
	} 
	
	for(int i=0;i<now_value_count;i++){
		cout<<list[i].value<<" "<<list[i].count<<endl;
	}
	return 0;
}
