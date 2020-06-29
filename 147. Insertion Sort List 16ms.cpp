#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 10005
/*inline int Rand(){
#ifdef _WIN32  //30 bits
	assert(RAND_MAX==32767);
	return rand()*(RAND_MAX+1)+rand();
#else  //31 bits
	assert(RAND_MAX==2147483647);
	return rand();
#endif
}*/
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}  //x+=(x<<4)+(x<<21)+1;
int s1;
struct List{
	struct node{
		node *pre,*next;int key;
	}a[N],*head;int a1;
	void clear(){head=a; a1=0; head->pre=head->next=0; head->key=-(1<<30);} 
	List(){clear();}
	void insert(node *x,int key){
		node *y=a+(++a1);y->key=key;
		y->pre=x;y->next=x->next;
		if (x->next)x->next->pre=y;x->next=y;
	}
	node* search(int key){
		if (!a1)return head;
		node *x=head;
		if (4*s1*s1<a1)++s1; int s=s1;  //s=int(sqrt(a1)/2);
		while (s--){
			node *y=a+_rand()%a1+1;
			if (y->key<key&&y->key>x->key)x=y;
		}
		for (;;x=x->next)if (!x->next||x->next->key>=key)return x;
	}
	void erase(node *x){
		x->pre->next=x->next;if (x->next)x->next->pre=x->pre;
		if (x!=a+a1){
			*x=a[a1];x->pre->next=x;
			if (x->next)x->next->pre=x;
		}
		--a1;
	}
	void insert(int key){node *x=search(key);insert(x,key);}
	void erase(int key){node *x=search(key)->next;if (x&&x->key==key)erase(x);}
	void print(){
		int s=0;for (node *x=head->next;x;x=x->next)printf("%d %d\n",++s,x->key);
		puts("---------");
	}
}l;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *	   int val;
 *	   ListNode *next;
 *	   ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		l.clear(); s1=1;
		for (ListNode *p=head;p;p=p->next)l.insert(p->val);
		List::node *p1=l.head->next;
		for (ListNode *p=head;p;p=p->next,p1=p1->next)p->val=p1->key;
		return head;
	}
};


