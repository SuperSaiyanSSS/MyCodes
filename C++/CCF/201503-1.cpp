#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int M[1000][1000];
int new_M[1000][1000];
int main() {
	int n, m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>M[i][j];
		}
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			new_M[1000-j-1][i] = M[i][j];
		}
	}
	
	for(int i=1000-m;i<1000;i++){
		for(int j=0;j<n;j++){
			cout<<new_M[i][j]<<" ";
		}
		cout<<endl;
	}
	
	return 0;
}
