#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int caozuoM[1020][5];
typedef struct node{
	//路径交叉点 0为无 1为有个路径 2为两个路径重合+ 
	int cross_flag;
	//该点内容 
	int id;
	
	//在队列中的下一个的指针
	struct node* next;
	//是否被访问过
	int visited;
	
	int zuobiaoi, zuobiaoj;
	 
}node;


node* front;
node* back;

//最外圈多一层路径（围墙） 
node M[1030][1030];

void initM(int n, int m){
	int i, j;
	for(i=0;i<=n+1;i++){
		for(j=0;j<=m+1;j++){
			M[i][j].id = '.';
			M[i][j].cross_flag = 0;
			M[i][j].zuobiaoi = i;
			M[i][j].zuobiaoj = j;
		} 
	}
	for(i=0;i<=n+1;i++){
		M[i][0].id = '|';
		M[i][0].cross_flag = 1;
		M[i][m+1].id = '|';
		M[i][m+1].cross_flag = 1;
	}
	for(i=0;i<=m+1;i++){
		M[0][i].id = '-';
		M[0][i].cross_flag = 1;
		M[n+1][i].id = '-';
		M[n+1][i].cross_flag = 1;
	}
	
}

void bfs(int n, int m, int x, int y, int zifu){
	int i, j;
		//清空visited信息 留待下次不同的字符继续调用
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			M[i][j].visited = 0;
			M[i][j].next = NULL;
		}
	}
	
	back = &M[x][y];
	while(back!=NULL){
		back->id = zifu;
		back->visited = 1; 
		if(M[x-1][y].cross_flag==0&&M[x-1][y].visited==0){
			M[x-1][y].next = back->next;
			back->next = &M[x-1][y];
			M[x-1][y].visited = 1;
			M[x-1][y].id = zifu;
		}
		if(M[x+1][y].cross_flag==0&&M[x+1][y].visited==0){
			M[x+1][y].next = back->next;
			back->next = &M[x+1][y];
			M[x+1][y].visited = 1;
			M[x+1][y].id = zifu;
		}
		if(M[x][y-1].cross_flag==0&&M[x][y-1].visited==0){
			M[x][y-1].next = back->next;
			back->next = &M[x][y-1];
			M[x][y-1].visited = 1;
			M[x][y-1].id = zifu;
		}
		if(M[x][y+1].cross_flag==0&&M[x][y+1].visited==0){
			M[x][y+1].next = back->next;
			back->next = &M[x][y+1];
			M[x][y+1].visited = 1;
			M[x][y+1].id = zifu;
		}
		back = back->next;
		if(back!=NULL){
		
			x = back->zuobiaoi;
			y = back->zuobiaoj;
		}
	}
	
	//清空visited信息 留待下次不同的字符继续调用
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			M[i][j].visited = 0;
		}
	}
}



int main() {
	int m, n, q;
	scanf("%d %d %d", &m, &n, &q);
	int i, j, k;
	int flag;
	for(i=0;i<q;i++){
		scanf("%d", &caozuoM[i][0]);
		if(caozuoM[i][0]==0){
			scanf("%d %d %d %d", &caozuoM[i][1], &caozuoM[i][2], &caozuoM[i][3], &caozuoM[i][4]);
		}
		else{
			scanf("%d %d %c", &caozuoM[i][1], &caozuoM[i][2], &caozuoM[i][3]);
		}
	}
	
	initM(n, m);
	for(k=0;k<q;k++){
		if(caozuoM[k][0]==0){
			//大坑：矩阵的[x][y]与坐标的[x][y]恰好相反！！！ 
			int y1 = caozuoM[k][1]+1;
			int x1 = caozuoM[k][2]+1;
			int y2 = caozuoM[k][3]+1;
			int x2 = caozuoM[k][4]+1;
			
			int t;
			if(y2<y1){
			
				t = y2;
				y2 = y1;
				y1 = t;
			}
			if(x2<x1){
				t = x2;
				x2 = x1;
				x1 = t;
			}
				
			
			if(x1==x2){
				for(j=y1;j<=y2;j++){
					if(M[x1][j].id=='|'||M[x1][j].id=='+'){
						M[x1][j].id = '+';
						M[x1][j].cross_flag = 2;
					}
					else{
						M[x1][j].id = '-';
						M[x1][j].cross_flag = 1;
					}
				}
			}
			else{
				for(i=x1;i<=x2;i++){
			//		printf("------0 %d %d\n", i, y1);
					if(M[i][y1].id=='-'||M[i][y1].id=='+'){
						M[i][y1].id = '+';
						M[i][y1].cross_flag = 2;
					}
					else{
						M[i][y1].id = '|';
						M[i][y1].cross_flag = 1; 
					}
				}
			}
		}
		else{
			int y = caozuoM[k][1]+1;
			int x = caozuoM[k][2]+1;
			int zifu = caozuoM[k][3];
			bfs(n, m, x, y, zifu);
		}
	}
	
	for(i=n;i>0;i--){
		for(j=1;j<=m;j++){
//			if(M[i][j].id!='.'&&M[i][j].id!='-'&&M[i][j].id!='|'&&M[i][j].id!='+'){
//				printf("%
//			}
			printf("%c", M[i][j].id);
			}
		printf("\n");
	}
	
	
	return 0;
}
