const int N=55,inf=~0u>>2;
struct query{
	int x1,x2,y1,y2,d;
	query(int _x1=0,int _x2=0,int _y1=0,int _y2=0):x1(_x1),x2(_x2),y1(_y1),y2(_y2){d=inf;}
}Q[N*N];
int d[N][N],qx[N*N],qy[N*N],Q1;
vector<vector<int>> A;
void SSSP(int x1,int x2,int y1,int y2,int sx,int sy){
	for (int i=x1;i<=x2;++i)
		for (int j=y1;j<=y2;++j)d[i][j]=inf;
	d[sx][sy]=0; qx[0]=sx; qy[0]=sy;
	int h=0,t=1;
	const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
	while (h<t){
		int x=qx[h],y=qy[h++],_d=d[x][y];
		for (int i=0;i<4;++i){
			int _x=x+dx[i],_y=y+dy[i];
			if (_x<x1||_x>x2||_y<y1||_y>y2)continue;
			if (A[_x][_y]&&d[_x][_y]==inf)d[_x][_y]=_d+1,qx[t]=_x,qy[t++]=_y;
		}
	}
}
void shortest_path(int x1,int x2,int y1,int y2,const vector<query*> &q){
	if (!q.size())return;
	vector<query*> q1,q2;
	if (x2-x1<=y2-y1){
		int mid=(y1+y2)/2;
		for (int i=x1;i<=x2;++i){
			if (!A[i][mid])continue;
			SSSP(x1,x2,y1,y2,i,mid);
			for (int j=0;j<q.size();++j){
				query *p=q[j]; p->d=min(p->d,d[p->x1][p->y1]+d[p->x2][p->y2]);
			}
		}
		for (int i=0;i<q.size();++i){
			if (q[i]->y1<mid&&q[i]->y2<mid)q1.push_back(q[i]);
			else if (q[i]->y1>mid&&q[i]->y2>mid)q2.push_back(q[i]);
		}
		shortest_path(x1,x2,y1,mid-1,q1);
		shortest_path(x1,x2,mid+1,y2,q2);
	}
	else {
		int mid=(x1+x2)/2;
		for (int i=y1;i<=y2;++i){
			if (!A[mid][i])continue;
			SSSP(x1,x2,y1,y2,mid,i);
			for (int j=0;j<q.size();++j){
				query *p=q[j]; p->d=min(p->d,d[p->x1][p->y1]+d[p->x2][p->y2]);
			}
		}
		for (int i=0;i<q.size();++i){
			if (q[i]->x1<mid&&q[i]->x2<mid)q1.push_back(q[i]);
			else if (q[i]->x1>mid&&q[i]->x2>mid)q2.push_back(q[i]);
		}
		shortest_path(x1,mid-1,y1,y2,q1);
		shortest_path(mid+1,x2,y1,y2,q2);
	}
}
class Solution {
public:
	int cutOffTree(vector<vector<int>>& a) {
		if (a.empty()||a[0].empty())return 0;
		int n=a.size(),m=a[0].size(),ans=0; A=a;
		vector<pair<int,int> > t;
		for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				if (a[i][j]>1)t.push_back(make_pair(a[i][j],i*m+j));
		t.push_back(make_pair(1,0));
		sort(t.begin(),t.end());
		vector<query*> q; Q1=0;
		for (int i=0;i+1<t.size();++i)Q[Q1]=query(t[i].second/m,t[i+1].second/m,t[i].second%m,t[i+1].second%m),q.push_back(Q+(Q1++));
		shortest_path(0,n-1,0,m-1,q);
		for (int i=0;i<Q1;++i)
			if (Q[i].d<inf)ans+=Q[i].d;
			else return -1;
		return ans;
	}
};


//IO
int _IO=[](){
	std::ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();


