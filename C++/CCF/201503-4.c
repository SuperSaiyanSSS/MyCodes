#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


typedef struct treeNode{
	int father;
	int distence;
	int id;
	struct treeNode* firstChildNode;
	struct treeNode* nextBrotherNode;
	struct treeNode* nextStackNode;
	int visited;	
}treeNode;


typedef struct stack{
	treeNode *top;
	int size;
}stack;


treeNode M[40001];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int i, j;
	for(i=2;i<=m+n;i++){
		scanf("%d", &M[i].father); 
		M[i].id = i;
		M[i].distence = 0;
		M[i].nextBrotherNode = M[M[i].father].firstChildNode;		
		M[M[i].father].firstChildNode = &M[i];
	//	printf("ok"); 
	}
	stack* countStack = (stack*)malloc(sizeof(stack));
	M[1].distence = 0;
	M[1].id = 1;
	countStack->size = 1;
	countStack->top = &M[1];
	countStack->top->visited = 1;
	countStack->top->distence = 0;
	while(countStack->size!=0){

		treeNode* p = countStack->top->firstChildNode;
		while(p!=NULL){
			if(!p->visited){
				p->visited = 1;
				p->distence = countStack->top->distence + 1;
			//	printf("%d\n", &p->distence);
				//pushÈëÕ» 
				p->nextStackNode = countStack->top->nextStackNode;
				countStack->top->nextStackNode = p;
				countStack->size++;
			}
			p = p->nextBrotherNode;
		}
		treeNode* q_father = &M[countStack->top->father];
		if(!q_father->visited){
			q_father->visited = 1;
			q_father->distence = countStack->top->distence + 1;
			q_father->nextStackNode = countStack->top->nextStackNode;
			countStack->top->nextStackNode = q_father; 
			countStack->size++;
		}
		countStack->top = countStack->top->nextStackNode;
		countStack->size--;
	} 
	int maxDistence1 = 0;
	int maxI = 0;
	for(i=2;i<m+n+1;i++){
	//	printf("\n%d\n", M[i].distence);
		if(M[i].distence>maxDistence1){
			maxDistence1 = M[i].distence;
			maxI = i;
			
		}
		M[i].visited = 0;
		M[i].distence = 0;
	}
	M[1].visited = 0;
	M[1].distence = 0;
	
	M[maxI].distence = 0;
	M[maxI].id = maxI;
	M[maxI].nextStackNode = NULL;
	countStack->size = 1;
	countStack->top = &M[maxI];
	countStack->top->visited = 1;
	countStack->top->distence = 0;
	while(countStack->size!=0){
		treeNode* p = countStack->top->firstChildNode;
		while(p!=NULL){
			if(!p->visited){
				p->visited = 1;
				p->distence = countStack->top->distence + 1;
			//	printf("%d\n", &p->distence);
				//pushÈëÕ» 
				p->nextStackNode = countStack->top->nextStackNode;
				countStack->top->nextStackNode = p;
				countStack->size++;
			}
			p = p->nextBrotherNode;
		}
		treeNode* q_father = &M[countStack->top->father];
		if(!q_father->visited){
			q_father->visited = 1;
			q_father->distence = countStack->top->distence + 1;
			q_father->nextStackNode = countStack->top->nextStackNode;
			countStack->top->nextStackNode = q_father; 
			countStack->size++;
		}
		countStack->top = countStack->top->nextStackNode;
		countStack->size--;
	} 
	
	for(i=2;i<m+n+1;i++){
	//	printf("???\n");
		//printf("\n%d\n", M[i].distence);
		if(M[i].distence>maxDistence1){
			maxDistence1 = M[i].distence;
			maxI = i;
		}
	}
	printf("%d", maxDistence1);
	
	 
	return 0;
}
