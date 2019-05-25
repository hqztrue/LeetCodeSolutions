#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<pthread.h>
using namespace std;
#define N 10005
#define NUM_THREADS 1
void *print_id(void *args){
	int id=*((int*)args);
	for (int i=0;i<1000000;++i);
	printf("id: %d\n",id);
	pthread_exit(NULL);
}
int mask[N],len[N];
struct thread_data{
	int l1,r1,l2,r2,id,ans;
	thread_data(int l1_,int r1_,int l2_,int r2_,int id_=0):l1(l1_),r1(r1_),l2(l2_),r2(r2_),id(id_){}
};
thread_data *d[NUM_THREADS];
void *calc(void *args){
	thread_data *d=(thread_data*)args;
	int ans=0;
	for (int i=d->l1;i<d->r1;++i)
		for (int j=d->l2;j<d->r2;++j)
			if ((mask[i]&mask[j])==0)ans=max(ans,len[i]*len[j]);
	d->ans=ans;
	pthread_exit(NULL);
}
class Solution {
public:
    int maxProduct(vector<string> &v){
        int n=v.size(),ans=0;
        for (int i=0;i<n;++i){
            int t=0;
            for (int j=0;j<v[i].size();++j)t|=1<<(v[i][j]-'a');
            mask[i]=t; len[i]=v[i].size();
        }
        pthread_t p[NUM_THREADS];
        for (int i=0;i<NUM_THREADS;++i){
            int l=n/NUM_THREADS*i,r;
            if (i==NUM_THREADS-1)r=n;
            else r=n/NUM_THREADS*(i+1);
            d[i]=new thread_data(l,r,0,n,i);
            int ret=pthread_create(&p[i],NULL,calc,(void*)d[i]);
            if (ret){
                printf("error\n");
                exit(-1);
            }
        }
        void *status;
        for (int i=0;i<NUM_THREADS;++i){
            pthread_join(p[i],&status);
            ans=max(ans,d[i]->ans);
        }
        return ans;
    }
};


