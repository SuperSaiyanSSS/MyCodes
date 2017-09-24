#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct linkNode{
	int id;
	struct linkNode* next;
}linkNode;

int arrayforprint[1000];
int arrayforprint_length;


linkNode points[1000];
int visited[1000][1000]; 

void pushNewNode(int p1, int p2){
	linkNode* newNode = (linkNode*)malloc(sizeof(linkNode));
	newNode->id = p2;
	newNode->next = NULL;
	
	linkNode* p = points[p1].next;
	linkNode* pnext;
	
	if(p==NULL){
		newNode->next = NULL;
		points[p1].next = newNode;
	}
	else{
		pnext = p->next;
		if(pnext==NULL){
			if(newNode->id>p->id){
				p->next = newNode;
				newNode->next = NULL;
				return;
			}
			else{
				//points[p1].next = newNode;
				newNode->next = p;
				points[p1].next = newNode;
				p->next = NULL;
				return;
			}
		}
		
		if(newNode->id<p->id){
			points[p1].next = newNode;
			newNode->next = p;
			p->next = NULL;
			return;
		}
		
		while(pnext!=NULL){
			if(newNode->id<pnext->id){
				p->next = newNode;
				newNode->next = pnext;
				
				return;
			}
			else{
				p = p->next;
				pnext = pnext->next;
			}
		}
		p->next = newNode;
	}
	
	

}

//�ж��Ƿ�Ϊ��ͨͼ
int n_nodes[1000];

int find(int number){
	if(number == n_nodes[number])
		return number;
	else{
		return find(n_nodes[number]);
	}
}

void _union(int p, int q){
	int p_root = find(p);
	int q_root = find(q);
	if(p_root == q_root){
		return;
	}
	else{
		n_nodes[q_root] = p_root;
		return;
	}
}

int is_unicom(int n){
	int root = n_nodes[1];
	int i;
	for(i=1;i<n;i++){
		if(find(i)!=root)
			return 0;
	} 
	return 1;
}

void dfs(int node){
	linkNode* p = points[node].next;
	while(p!=NULL){
		if(visited[node][p->id]==0){
			visited[node][p->id]=1;
			visited[p->id][node]=1;
			dfs(p->id);
		}

				p = p->next;
	}
		//	printf("--%d", node);
	
	arrayforprint[arrayforprint_length] = node;
	arrayforprint_length++;

}



int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int i;
	arrayforprint_length = 0; 
	
	//init unionform
	for(i=1;i<n+1;i++){
		n_nodes[i] = i;
	}	
	
	for(i=0;i<m;i++){
		int p1, p2;
		scanf("%d %d", &p1, &p2);
		pushNewNode(p1, p2);
		pushNewNode(p2, p1);
		_union(p1, p2);
	}
	
	int has_euler_path = 0;
	if(is_unicom(n)==1){
		has_euler_path = 1;
	} 
	
	if(has_euler_path==0){
		printf("-1\n");
		return 0;
	}


// һ��Ҫ��malloc ��������next��ΪNULL��������֪��ʲôԭ����next��Ȼ��ָ����ĳ���ص㣬���ӵ��Ǿ�Ȼ����id���ԡ������˹� 
//printf("now is %d %d\n", 1, points[1].next->id);

	
	//�ж��Ƿ�����ŷ��·�Ķ��� ��ÿ��������Ϊż���������ҽ�������������Ϊ������������һ����Ϊ��ڵ� 
	int count_ji = 0;
	int count = 0;
	int first_ji = 0; 
	int second_ji = 0;
	for(i=1;i<n+1;i++){
		linkNode* p = points[i].next;
		//���ã�p  ��������ĳ�!p�ͳ����ˡ���C�������汾̫�� ��Ϊ���������� 
		while(p!=NULL){
			count++;
			p = p->next;
		}
		if(count%2!=0){
			count_ji++;
			if(first_ji==0){
				first_ji = i;
			}
			else
				second_ji = i;
		}
		count = 0;
	}

	if(count_ji==0||(count_ji==2&&(first_ji==1)))
		 has_euler_path = 1;
	else
		 has_euler_path = 0;
		
	if(has_euler_path==0){
		printf("-1\n");
		return 0;
	}

	if(has_euler_path==1){
		dfs(1);
		for(i=arrayforprint_length-1;i>0;i--){
			printf("%d ", arrayforprint[i]);
		}
		printf("%d\n", arrayforprint[0]);
	 
	}
	
	return 0;
}
