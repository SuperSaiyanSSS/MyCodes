#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



typedef struct node{
	int hang;
	int i1, i2, i3, i4;
	char s[200];
	int s_count;
	struct node* next;
}node;


char moban[100][200];
char name[100][200];
char value[100][200];

int main(int argc, char *argv[]) {
	int m, n;
	node* fnode=NULL; 
	int find_flag = 0;
	int next_flag = 1; 
	
	scanf("%d %d", &m, &n);
	//清空scanf的缓存区！ 
	fflush(stdin);
	int i, j, k;
	for(i=0;i<m;i++){
		scanf("%[^\n]", &moban[i]); 
		fflush(stdin);
//		printf("%s ------- %d\n", moban[i], i); 
	//	gets(moban[i]);
	}
	for(i=0;i<n;i++){
		scanf("%s ",&name[i]);
	//	gets(value[i]);
		scanf("%[^\n]", &value[i]);
	//	printf("name[%d]----%s----%s\n", i, name[i], value[i]);
	}
	
	
	
	while(next_flag!=0){
		next_flag = 0;
		
		for(i=0;i<m;i++){
			int zishu = strlen(moban[i]);
			for(j=0;j<zishu-6;j++){
				if(moban[i][j]=='{'&&moban[i][j+1]=='{'&&moban[i][j+2]==' '){
					for(k=j+3;k<zishu-3;k++){
						if(moban[i][k]==' '&&moban[i][k+1]=='}'&&moban[i][k+2]=='}'){
							node* myNode = (node*)malloc(sizeof(node));
							myNode->i1 = j;
							myNode->i2 = j+3;
							myNode->i3 = k-1;
							myNode->i4 = k;
							myNode->s_count = k-j-3;
							myNode->next = NULL;
							
							int s_i;
							int ss_i = myNode->i2;
							for(s_i = 0;s_i<k-j-3;s_i++){
								(myNode->s)[s_i] = moban[i][ss_i];
								ss_i++;
							} 
							
							myNode->hang = i;
							if(fnode==NULL){
								fnode = myNode;
							}	
							else{
								myNode->next = fnode;
								fnode = myNode;
							}
							find_flag = 1;
							break;
						}
					}
					
					if(find_flag==1){
						find_flag = 0;
						next_flag = 1;
						j = j+2+fnode->s_count+2;
						//每一行只找到一个就可以了 找多了会覆盖i 
						break;
					}
					
				}
			}
		}
		
		while(fnode!=NULL){
			int nowhang = fnode->hang;
			int nownamehang;
			
			for(i=0;i<n;i++){

				if(strncmp(name[i], fnode->s, fnode->s_count)==0){
					nownamehang = i;
					break;
				}

			}
			if(i==n){
				char front[200];
				strncpy(front, moban[nowhang], fnode->i1);
				strncpy(front+fnode->i1, moban[nowhang]+fnode->i4+3, strlen(moban[nowhang])-fnode->i4-2);
				strcpy(moban[nowhang], front);
				fnode = fnode->next;
				continue;	
			}
			
			char front[200];
			//三段拼凑 
			strncpy(front, moban[nowhang], fnode->i1);

			// +1 -2是因为去除两个双引号 
			strncpy(front+fnode->i1, value[nownamehang]+1, strlen(value[nownamehang])-2);  

			//+3 是因为跨过空格/}/} 
			strncpy(front+(fnode->i1+ strlen(value[nownamehang])-2), moban[nowhang]+fnode->i4+3, strlen(moban[nowhang])-fnode->i4-2);

			
			strcpy(moban[nowhang], front);
			fnode = fnode->next;
		}
	}
	for(i=0;i<m-1;i++){
		printf("%s", moban[i]);
		printf("\n");
	}
	printf("%s", moban[m-1]);


	return 0;
}
