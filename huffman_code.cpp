#include<stdio.h>
#include<malloc.h>
typedef struct node{
	int weight = 0;
	char value = '.';
	struct node* l_child = NULL;
	struct node* r_child = NULL;
	struct node* next = NULL;
}Node;
//int main(){
////	Node* a = (Node*)malloc(sizeof(Node));
////	printf("lalaaa");
////	scanf("%c",&(a->value));
////	printf("%c\n",a->value);
////	return 0;
////	int* arr = (int*)malloc(10*sizeof(int));
////	arr = {0};
////	printf("%d",arr[0]);
//}

int len(Node* head);
Node* find(Node* head, int num);
void sort(Node* ptr, int num);
void show(Node* ptr,int path,int* arr);

int main(){
	int num = 0;
	Node* head = NULL;//头结点，永远指向开始
	Node* current = NULL;//当前节点，用于寻找和排序
	printf("输入节点个数：");
	scanf("%d",&num);
	//int arr[num] = {0};
	int* arr = (int*)malloc(num*sizeof(int));
	for(int i = 0; i < num; i++){
		arr[i] = 100;
	}
	head = (Node*)malloc(sizeof(Node));//空指针
	head->weight = 0;
	head->value = '.';
	head->next = NULL;
	head->l_child = NULL;
	head->r_child = NULL;//初始化head
	//head = nodes;
	current = head;
	for(int i = 0; i < num; i++){
		current->next = (Node*)malloc(sizeof(Node));
	  current = current->next;
	  current->next = NULL;
	  current->l_child = NULL;
	  current->r_child = NULL;
	  printf("enter the value:");
	  scanf("%s",&(current->value));
	  printf("enter the weight:");
	  scanf("%d",&(current->weight));
	  //初始化新节点
	}//建立起一个链表，方便排序和查找
	while(len(head)+1 > 2){
		//printf("当前个数为%d个。",len(head));
		sort(head,num);
	  current = find(head,len(head) - 2);
		current->l_child = current->next;
		current->r_child = current->next->next;
		current->next->next = NULL;
  	current->next = (Node*)malloc(sizeof(Node));
  	current->next->l_child = current->l_child;
  	current->next->r_child = current->r_child;
  	current->l_child = NULL;
		current->r_child = NULL;
		current = current->next;
		current->weight = current->l_child->weight + current->r_child->weight;
		current->value = '.';//初始化
		current->next = NULL;
	}
  show(head->next,0,arr);//头指针、当前下标、编码数组
  return 0;
}
int len(Node* head){
	Node* current = head;
	int length = 0;
	while(current->next != NULL){
		//printf("%d",current->next != NULL);
		current = current->next;
		//printf("%s",current->value);
		length++;
		//printf("%d\n",length++);
	}
	return length;
}
Node* find(Node* head, int num){
	Node* current = head;
	for(int i = 0; i < num; i++){
		current = current->next;
	}
	return current;
}
void sort(Node* ptr, int num){
	printf("Begin sorting!\n");
	Node* temp = 0;
	Node* ps = NULL;
	Node* pc = NULL;
	Node* ss = NULL;
	Node* sc = NULL;
	Node* start = ptr->next;
	Node* current = NULL;
	while(start->next != NULL){
		//printf("The weight of start is %d.",start->weight);
		current = start->next;
		while(current != NULL){
			//printf("The weight of current is %d.",current->weight);
			if(current->weight > start->weight){
				ps = ptr;
				pc = ptr;
				ss = start->next;
				sc = current->next;
				while(ps->next != start){
					ps = ps->next;
				}
				while(pc->next != current){
					pc = pc->next;
				}
				if(start->next == current){
					ps->next = current;
					pc->next = sc;
					current->next = start;
				}else{
			  	ps->next = current;
			  	pc->next = start;
			  	start->next = sc;
			  	current->next = ss;
			  }
			  temp = current;
			  current = start;
			  start = temp;
			}
			current = current->next;
		}
		start = start->next;
	}
	printf("End sorting.\n");
}
void show(Node* ptr,int path,int* arr){
	Node* current = ptr;
	if(current->l_child != NULL){ //not leaf
		for(int i = 0; i < 2; i++){
			arr[path] = i;
			if(i == 0){
				//printf("l_child = %d\n",current->weight);
				show(current->l_child,path+1,arr);
			}else{
				//printf("r_child = %d\n",current->weight);
				show(current->r_child,path+1,arr);
			}
		}
		arr[path] = 100;//恢复现场
	}else{
		int k = 0;
		while(arr[k] != 100){
			printf("%d",arr[k]);
			k++;
		}
		printf("=>%c\n",current->value);
  }
}