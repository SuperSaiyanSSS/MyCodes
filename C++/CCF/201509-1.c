#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int array[1000];

int main(int argc, char *argv[]) {
	int n;
	scanf("%d", &n);
	int i;
	for(i=0;i<n;i++){
		scanf("%d", &array[i]);
	} 
	int flag = array[0];
	int count = 1;
	for(i=1;i<n;i++){
		if(flag!=array[i]){
			flag = array[i];
			count++; 
		}
	}
	printf("%d\n", count);
	
	return 0;
}
