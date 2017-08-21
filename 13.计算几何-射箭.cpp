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
解题思路一(只适用于凸多边形):
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

解题思路二(只适用于凸多边形):
由于多边形a[i]的点是按照顺序给出的(本题是顺时针给出),如果点p在多边形里面, 
则从向量pa[i]到向量pa[i+1]均为相同的顺序,所以他们的叉乘具有相同的正负号.
如果p在多边形a[i]里外面, 则一定存在一对向量pa[i],pa[i+1]与前面的pa[i-1]和pa[i]
顺序不同,所以他们的叉乘具有不同的正负号.由此即可判断点p是否在多边形内. 
*/

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn = 100+5;
 
struct Point{
	double x,y;
	Point(double x,double y):x(x),y(y){}
	Point(){}
}p[maxn];
typedef Point Vector;
double eps = 1e-10;

Vector operator - (const Point& a,const Point& b){return Vector(a.x-b.x, a.y-b.y);}

double cross(const Vector& a,const Vector& b){return a.x*b.y - b.x*a.y;}

double dot(const Vector& a,const Vector& b){ return a.x*b.x + a.y*b.y;}


int dcmp(double x){
    if(fabs(x) < eps)  return 0;
    else  return x < 0 ? -1 : 1;
}

//返回向量ab,ac的叉乘
double cross(Point& a, Point& b,Point& c){
	Vector ab(b.x - a.x, b.y - a.y);
	Vector ac(c.x - a.x, c.y - a.y);
	return cross(ab,ac);
}

//判断线段ab,cd是否相交,(不包括某一个点落在另一条线段上的情况)
bool lineCross(Point& a,Point& b,Point& c, Point& d){
	return 
		dcmp( cross(a,b,c)*cross(a,b,d) ) < 0 &&  //c,d在ab两侧 
		dcmp( cross(c,d,a)*cross(c,d,b) ) < 0 ; //a,b在cd两侧 
}

//判断点x是否在三角形abc上(包括在边上) 
bool inTriangle(Point& a,Point& b,Point& c, Point& x){
	if( lineCross(a,b,c,x) ) return false;
	if( lineCross(a,c,b,x) ) return false;
	if( lineCross(b,c,a,x) ) return false;
	return true;
}

//判断点p是否在给定的多边形内(只对凸多边形有效)
//即判断点是否在由n个点组成的n-2个三角形内
bool inPolygon1(Point p[], int n, Point &a){
	for(int i=1;i<n-1; ++i){
		if( inTriangle( p[0], p[i], p[i+1], a) ) return true;
	}
	return false;
}


//判断点p是否在给定的多边形内(只对凸多边形有效)
bool inPolygon2(Point p[],int n,Point& a){
	//顺时针,叉乘值为负
	for(int i=0;i<n;++i){
		double tmp = cross(p[i] - a, p[(i+1)%n] - a);
		if( dcmp(tmp) > 0) return false;
		else if(tmp == 0) return true;
	}
	return true;
}

//判断点p是否在线段ab上
bool onLine(Point& a,Point& b, Point& p){
	return dcmp( cross(a-p, b-p) )==0 && dcmp( dot(a-p, b-p) )<=0;
}

//射线法判断点是否在多边形内(对凸/凹多边形都有效)
//方法是从此点向右引一条射线，判断多边形的边顺时针逆时针穿过此射线次数是否相等，相等则在外面。
bool inPolygon3(Point p[], int n, Point& a){
//	cout<<a.x << " " << a.y <<" ";
	int cnt=0;
	for(int i=0; i<n; ++i){
		if(onLine(p[i], p[(i+1)%n], a)) return 1; //点在多边形的边上
		int k = dcmp( cross(p[(i+1)%n] - p[i],  a - p[i]) );
		int d1 = dcmp(p[i].y - a.y);
		int d2 = dcmp(p[i+1].y - a.y);
		if(k > 0 && d1<=0 && d2>0) ++cnt;
		if(k < 0 && d2<=0 && d1>0) --cnt;
	}
	return cnt!=0;
}

int main(){
#ifdef WFX
//freopen("13 in.txt","r",stdin);
#endif 
	int n,m;
	Point a;
	while( scanf("%d",&n) != -1 ){
		for(int i=0;i<n;++i) scanf("%lf%lf",&p[i].x, &p[i].y);
		scanf("%d",&m);
		for(int i=0;i<m;++i){
			scanf("%lf%lf",&a.x, &a.y);
			printf("%s\n", inPolygon3( p, n , a )? "Yes":"No");
		}
	}
	
	return 0;
}
