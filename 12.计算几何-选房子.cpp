/*
题目内容：
 某地有n个房子，法墨的钱可以买三栋。地面上分布着m个金矿，这三栋房子为顶点构成的三角形地面
上的金矿都归法墨。法墨只想要奇数个金矿。他想知道他有多少种选择。 
输入描述
可能有多个测试用例。
每个测试用例的第一行是n,m，然后下面n行是n个房子的坐标，再下面m行是m个金矿的坐标。
假设这些坐标中，没有任何三个点是共线的。

输出描述
每个测试用例输出一行，即法墨的选择方案数

输入样例
4 4
-10 0
10 0
0 10
0 -10
1 1
1 2
-1 1
-1 -1

输出样例
2
*/

/*
解题思路:
定义函数f(ab)为线段ab下面的点的个数,则: 
对于一个三角形abc(顺时针给出), 位于其中的点的个数等于f(ab)+f(bc)-f(ac)
对于一个三角形abc(逆时针给出), 位于其中的点的个数等于f(ac)-f(ab)-f(bc)
则三角形中点的个数可以写成abs(f(ab)+f(bc)-f(ac)), 
有意思的是,如果f(ab)定义为线段ab上面的点的个数,则上式同样可以计算出三角形中点的个数. 

判断点c在直线ab的位置关系: 
如果a.x < b.x  且 a.x <= c.x <= b.x 
	如果 ab与 ac 的叉乘大于0,说明 ab 到 ac是顺时针旋转, c在ab下方
	如果 ab与 ac 的叉乘小于0,说明 ab 到 ac是逆时针旋转, c在ab上方
	如果 ab与 ac 的叉乘等于0,说明 ab 与 ac重合, c在线段ab上. 
*/ 

#include<iostream> 
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e3+5;

int cnt[maxn][maxn];

struct Point{
	int x,y;
	Point(int x,int y):x(x),y(y){}
	Point(){}
	bool operator<(const Point& p)const{
		return x < p.x;
	}
	int cross(const Point& p){return x*p.y - y*p.x;}
}p[maxn*2];

int cross(Point& a, Point& b, Point& c){
	typedef Point Vector;
	Vector ab(b.x - a.x, b.y - a.y);
	Vector ac(c.x - a.x, c.y - a.y);
	return ab.cross(ac) < 0; //此处写成大于0或者小于0无影响 
}

int main(){
#ifdef WFX
freopen("12 in.txt","r",stdin) ;
#endif
	int n,m,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%d%d",&p[i].x, &p[i].y);
	for(int i=n,nm=n+m; i<nm; ++i) scanf("%d%d",&p[i].x, &p[i].y);
	
	sort(p,p+n);//将房子按x坐标排序 
	
	for(int i=0; i<n; ++i){
		for(int j=i+1; j<n; ++j){
			for(int k=n,nm=n+m; k<nm; ++k){
				if( p[i].x < p[k].x && p[k].x < p[j].x && cross(p[i],p[j],p[k]) ) ++cnt[i][j];
			}
		}
	}
	
	for(int i=0; i<n; ++i){
		for(int j=i+1; j<n; ++j){
			for(int k=j+1; k<n;++k){
				if(abs( cnt[i][j] + cnt[j][k] - cnt[i][k] ) & 1) ++ans; 
			}
		}
	}
	
	printf("%d",ans);
	
	return 0;
}

