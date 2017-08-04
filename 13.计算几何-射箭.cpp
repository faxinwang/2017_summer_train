/*
题目内容：
 小明练习射箭，但靶子是多边形。小明需要知道是否射中多边形。
输入描述
可能有多组测试用例
第一行是n，表示靶子的顶点数，n<100
随后n行是靶子的按顺时针方向顶点坐标。
接下来一行是m，表示射出的箭的数目 m<1000
再m行是箭射到的坐标。

坐标(x,y)值都小于1000

输出描述
一共m行，如果第i只箭射中输出YES,否则输出NO.

输入样例
4
10 10
20 10
20 5
10 5
2
15 8
25 8

输出样例
YES
NO
*/ 

/*
解题思路:
判断点是否在给定的多边形上:
	转换为判断点是否在三角形上,如果点在多边形的某一个三角形上,
	那么该点就一定在多边形上. 
	
判断点是否在三角形上: 
	如果点p不在三角形abc上, 那么线段ab,pc 或者ac,pb 或者 bc,pa一定存在相交的情况.
	
判断两条线段相交(不包括一个点落在另一条线段上的情况):
	如果线段ab,cd相交,那么点a,b一定在线段cd的两侧,并且点c,d也一定在线段ab的两侧,
	向量ca和向量cb分别在向量cd的两侧，因而ca和cb对cd有不同的时针方向,即 
	(cdxca) * (cdxcb) < 0  
	同时，向量ad和向量ac分别在向量ab的两侧,即 
	(ab*ac) * (ab*ad) < 0

如果两条线段ab,cd相交,并且一条线段的一个点落在另一条线段中间,则有如下结论:
	如果点a落在线段cd上, 则向量ca与向量cd重合,其叉积为0,并且点c,d一定在线段ab的两侧,即 
	(caxcd)==0 && (baxbc)*(baxbd)<0

解题思路二:
由于多边形a[i]的点是按照顺序给出的(本题是顺时针给出),如果点p在多边形里面, 
则从向量pa[i]到向量pa[i+1]均为相同的顺序,所以他们的叉乘具有相同的正负号.
如果p在多边形a[i]里外面, 则一定存在一对向量pa[i],pa[i+1]与前面的pa[i-1]和pa[i]
顺序不同,所以他们的叉乘具有不同的正负号.由此即可判断点p是否在多边形内. 
*/

#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 100+5;

struct Point{
	int x,y;
	Point(int x,int y):x(x),y(y){}
	Point(){}
	int cross(Point& p){return x*p.y - y*p.x;}
}p[maxn];
typedef Point Vector;

Vector operator - (const Point& a,const Point& b){return Vector(b.x-a.x, b.y-a.y);}

double cross(const Vector& a,const Vector& b){return a.x*b.y - b.x*a.y;}

/*
//返回向量ab,ac的叉乘
int cross(Point& a, Point& b,Point& c){
	Vector ab(b.x - a.x, b.y - a.y);
	Vector ac(c.x - a.x, c.y - a.y);
	return ab.cross(ac);
}

//判断线段ab,cd是否相交,(不包括某一个点落在另一条线段上的情况)
bool lineCross(Point& a,Point& b,Point& c, Point& d){
	return 
		cross(a,b,c)*cross(a,b,d) < 0 &&  //c,d在ab两侧 
		cross(c,d,a)*cross(c,d,b) < 0 ; //a,b在cd两侧 
}

//判断点x是否在三角形abc上(包括在边上) 
bool inTriangle(Point& a,Point& b,Point& c, Point& x){
	if(lineCross(a,b,c,x)) return false;
	if(lineCross(a,c,b,x)) return false;
	if(lineCross(b,c,a,x)) return false;
	return true;
}

//判断点p是否在给定的多边形内 
bool inPolygon(Point p[], int n, Point &a){
	for(int i=0;i<n-2; ++i){
		if( inTriangle( p[i],p[i+1],p[i+2], a) ) return true;
	}
	return false;
}
*/

//判断点p是否在给定的多边形内(解法二)
bool inPolygon2(Point p[],int n,Point& a){
	//顺时针,叉乘值为负 
	for(int i=0;i<n;++i){
		if(cross(p[i] - a, p[(i+1)%n]-a) > 0) return false;
	}
	return true;
}

int main(){
#ifdef WFX
freopen("13 in.txt","r",stdin);
#endif 
	int n,m;
	Point a;
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d%d",&p[i].x, &p[i].y);
	scanf("%d",&m);
	for(int i=0;i<m;++i){
		scanf("%d%d",&a.x, &a.y);
		if( inPolygon2( p, n , a ) ) printf("YES\n");
		else printf("NO\n"); 
	}
	
	return 0;
}
