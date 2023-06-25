#include<bits/stdc++.h>
using namespace std;
typedef unsigned short ushort;
const int maxSize = 25,inf=10000;
ushort rect[maxSize][maxSize];
//ushort rect2[maxSize][maxSize][maxSize][maxSize];
auto rect2=new ushort[maxSize][maxSize][maxSize][maxSize];

class Solution {
public:
    int tilingRectangle(int n, int m) {
        if (n > m)swap(n, m);
        if (rect[n][m])return rect[n][m];

        //方形情况
        if (n == m)return rect[n][m] = 1;

		int ans=inf;
        //分解为方形+矩形（方形顶满情况）
        //int ans = 1 + tilingRectangle(n, m - n);

        //分解为方形+L形，枚举方形的边长，其中加的1就是方形占用数量
        /*for (int i = n-1; i > 0; i--)
        {
            //L形的分解可以在横轴也可以在竖轴枚举，下面的Rect2只枚举横轴，竖轴通过旋转改为枚举横轴
            //L形枚举
            ans = min(ans, solveL(n - i, m, n, m - i) + 1);
        }*/
		
		// decompose into R+R
		for (int i=1;i<n;++i)ans=min(ans,tilingRectangle(i,m)+tilingRectangle(n-i,m));
		for (int i=1;i<m;++i)ans=min(ans,tilingRectangle(n,i)+tilingRectangle(n,m-i));
		
		// decompose into R+L
		for (int i=1;i<n;++i)
			for (int j=1;j<m;++j)
				ans=min(ans,tilingRectangle(i,j)+solveL(n-i,m,n,m-j));
		
		// decompose into L+L
		for (int I=0;I<2;++I){
			for (int i=1;i<n;++i)
				for (int j=i+1;j<n;++j)
					for (int k=1;k<m;++k)
						ans=min(ans,solveL(i,m,j,k)+solveL(n-j,m,n-i,m-k));
			swap(n,m);
		}
        return rect[n][m] = ans;
    }
	
	int solveL(int n1, int m1, int n2, int m2){
        if (rect2[n1][m1][n2][m2])return rect2[n1][m1][n2][m2];
		return rect2[n1][m1][n2][m2] = min(Rect2(n1,m1,n2,m2),Rect2(m2,n2,m1,n1));
	}

    //L-shape
    int Rect2(int n1, int m1, int n2, int m2)  //short1,long2,long1,short2
    {
        //恰好分为两个矩形（只需考虑一种，另一种已经在旋转中处理了）
        int ans = tilingRectangle(n1, m1 - m2) + tilingRectangle(n2, m2);

		//cut from a longer edge
		for (int i=1;i<n1;++i)
			ans=min(ans,tilingRectangle(i,m1)+solveL(n1-i,m1,n2-i,m2));
		
		//cut at another corner
		for (int i=1;i<n1;++i)
			ans=min(ans,tilingRectangle(i,m1-m2)+solveL(n1-i,m1,n2,m2));
		
        //枚举切分矩形的长度，注意旋转保证边长无负数
        for (int i = 1; i < m1; i++)
            if (m1 - i > m2)
                //注意L形的两种枚举
                ans = min(ans, tilingRectangle(n1, i) + solveL(n1, m1 - i, n2, m2));
            else if (m2 > m1 - i)
                ans = min(ans, tilingRectangle(n1, i) + solveL(n2 - n1, m2, n2, m1 - i));
        return ans;
    }
}A;

