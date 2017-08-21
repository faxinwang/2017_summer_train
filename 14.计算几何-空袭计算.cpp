/*
题目内容：
轰炸机轰炸的目标区域是地面上一个n个顶点的多边形，现在三维坐标(x,y,h)处投一颗炸弹，飞行
速度是（vx,vy,0）,重力加速度是10。炸弹的爆炸半径是r, 现需要了解被炸的区域面积.

输入描述
第一行是x y h
第二行是vx vy
第三行是炸弹的爆炸半径r
第四行是n,代表目标区域的顶点数
下面是n行是目标多变形的顶点坐标，按顺时针给出

输出描述
被炸的区域面积（两位小数）

输入样例
0 0 2000
100 0
100 
4
1900 100
2000 100
2000 -100
1900 -100

输出样例
15707.96

之前在杭电OJ上一直提交不过, 找了老半天错误, 后来还是让徒弟给发现了
这题有多组测试数据, 但时题目没有说有多组测试数据,我之前是按照只有一组输入处理的,
所以一直提交不过,简直呵呵了. 被坑了好长时间. 

题目大意: 求多边形与圆的面积交.也就是重叠的部分的面积.其中多边形的顶点按顺时针或逆时针顺序给出. 
圆的位置也需要通过简单的平抛运动计算出来.  
解题思路:
本题的难点在于求重叠部分的面积, 从整体来看不好下手, 那么就要将问题分解成容易解决的多个小问题.
多边形的面积等于组成它的三角形的面积之和, 那么这些三角形的面积与圆的面积交之和就是多边形与圆的
面积交. 这样问题就分解成了计算多个三角形与圆的面积交.
分解方法是: 用圆心连接多边形所有的n个顶点, 组成n个三角形, 然后计算这些三角形与圆的面积交之和.
在每个三角形中,有两个顶点来自多边形, 另外一个顶点是圆心, 需要根据来自多边形的两个顶点p1,p2是否在
圆中分情况计算三角形与圆的面积交.
情况一: p1, p2都在圆中
	此时面积交就是三角形的面积(用叉乘计算,得出的是带正负号的面积)
情况二: p1在圆中, p2不在圆中(或者p1不在圆中,p2在圆中)
	此时需要计算线段P1p2与圆的交点, 该交点将三角形与圆的重叠部分分割成了一个三角形和一个扇形.
	计算交点的方法是联立圆和直线的方程.用求根公式直接计算出交点的坐标. 具体实现见代码部分. 
	这里需要注意两个问题: 
	1.三角形的面积我们都是用叉乘计算的,这样计算出来的面积是带有正负号的,可以同时处理圆心不在多
	边形内的情况,并且不用考虑多边形的点是按哪一种顺序给出.但时扇形的面积并不能用叉乘计算出来,而
	是用其他的扇形面积公式计算出来的,这样得出的面积都是正值,如果另外那个三角形的面积是负值的话,
	也需要让扇形的面积成为负值,才能保证最后计算出来的是正确的.所有需要把另外的那个三角形的面积的
	正负号赋给这个扇形的面积.
	2.在这种情况下,直线和圆可能有两个交点(或者一个交点,p1在圆上或者P2在圆上就只有一个交点,交点就是
	p1或p2),但我们要使用的是线段p1p2和圆的交点(另外一个交点在p1p2的延长线上),所以在使用交点的时候
	要注意判断一下. 
情况三: p1,p2都在圆外, 这时又要分两种情况考虑
 	a.如果线段p1p2与圆的交点个数小于等于1,则三角形Op1p2与圆O的面积交就是扇形Op1p2的面积
	b.如果交点个数为2,则这两个交点将重叠部分分割成了两个扇形和一个三角形. 
 	在第一种情况下,同样需要为扇形面积附上正负号,该正负号同三角形Op1p2面积的正负号 
 	在第二种情况下,还是联立圆和直线的方程计算出两个交点的坐标,然后用这两个交点计算两个小扇形和
	一个三角形的面积. 扇形面积的正负号同三角形面积的正负号. 
*/

#include<iostream> 
#include<cstdio>
#include<cmath>
#define maxn 100000
using namespace std;

typedef struct Point{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
}Vector;
Point p[maxn];

struct Circle{
	Point c;
	double r;
	Circle(Point p,double r):c(p.x, p.y),r(r){}
};
double eps = 1e-9; 

Vector operator - (const Vector& a,const Vector& b){return Vector(a.x - b.x, a.y - b.y);}

double dot(const Vector& a,const Vector& b){return a.x*b.x + a.y * b.y;}

double cross(const Vector& a,const Vector& b){return a.x*b.y - a.y * b.x;}

double length(const Vector& a){return sqrt(dot(a,a));}

double dist(const Point& a,const Point& b){return length(a - b);}

double angle(const Vector& a,const Vector& b){return acos(dot(a,b)/length(a)/length(b));}

int dcmp(double x){
	if(fabs(x) <= eps) return 0;
	else return x<0? -1:1;
}

int calc(Point&p1 ,Point& p2, Circle& ci,Point &x1, Point &x2){
	//将直线的两点试方程转化为斜截式方程
	//(y-y1)/(x-x1) = (y2-y1)/(x2-x1) ---> y=(y2-y1)/(x2-x1)*x + (x2y1-x1y2)/(x2-x1)
	//计算直线 y = kx + b 的 k 和 b 
	//首先处理斜率无穷大的情况 
	if( dcmp(p1.x-p2.x) == 0 ){ //垂直直线 
		double d = fabs(p1.x - ci.c.x);//直线与圆心的距离 
		if( dcmp(d - ci.r) == 0 ){ //有1个交点,直线与圆相切 
			x1.x = x2.x = p1.x;
			x1.y = x2.y = ci.c.y;
			return 1;
		}else if( dcmp(d - ci.r) < 0 ){
			x1.x = x2.x = p1.x;
			double tmp = sqrt(ci.r * ci.r - d*d);
			x1.y = ci.c.y - tmp;
			x2.y = ci.c.y + tmp;
			return 2;
		}else return 0; //有0个交点 
	}
	//处理斜率为0的情况
	if( dcmp(p1.y - p2.y) == 0 ){ //水平直线 
		double d = fabs(p1.y - ci.c.y);//直线到圆心的距离
		if( dcmp(d - ci.r) == 0 ){
			x1.y = x2.y = p1.y;
			x1.x = x2.x = ci.c.x;
			return 1;
		}else if( dcmp(d - ci.r) < 0 ){
			x1.y = x2.y = p1.y;
			double tmp = sqrt(ci.r*ci.r - d*d);
			x1.x = ci.c.x - tmp;
			x2.x = ci.c.x + tmp;
			return 2;
		}else return 0;
	}
	//处理斜率为其他值的情况 
	double k = (p2.y - p1.y)/(p2.x - p1.x); 
	double bb = (p2.x * p1.y - p1.x * p2.y)/(p2.x - p1.x);
	//计算方程 (k*k+1)x^2 + 2*k*b*x + b*b - R*R = 0的判别式的值
	//该方程由 x*x + y*y = R*R 和 y=kx + b 联立得到 
	double a = k*k+1;
	double b = 2 * k * bb; //b现在变成了方程 ax^2 + bx + c=0的系数
	double c = bb*bb - ci.r*ci.r;
	double delt = b*b - 4 * a * c;
	
	//delt > 0 ,有两个解 ,返回2 
	if( dcmp(delt) > 0){
		x1.x = (-b + sqrt(delt)) / 2/a;
		x1.y = k * x1.x + bb;
		x2.x = (-b - sqrt(delt)) / 2/a;
		x2.y = k * x2.x + bb;
		return 2;
	}
	else if(dcmp(delt) < 0) return 0; //无解,返回0
	else{ //delt为0,有一个解 ,返回1 
		x1.x = x2.x = -b / 2 / a;
		x1.y = k * x1.x + bb;
		return 1;
	}
}

double area(Point& p1, Point& p2, Circle& c){
	bool aInC = dcmp(dist(p1, c.c) - c.r) <= 0; 
	bool bInC = dcmp(dist(p2, c.c) - c.r) <= 0;
	Point x1,x2;
	double s = 0;
	if(aInC && bInC){ //点p1和p2都在圆c中 
		s =  cross(p1 - c.c, p2 - c.c) / 2; //返回三角形的面积
	}
	else if(aInC && !bInC){ //p1在圆c中,p2不在圆c中 
		int cnt = calc(p1,p2,c,x1,x2);
		if(cnt <= 1){
			if(cross(p1-c.c, p2 - c.c) < 0) s -= angle(x1-c.c, p2-c.c)/2*c.r*c.r; //扇形面积 
			else s += angle(x1-c.c, p2-c.c) / 2 * c.r * c.r;
		}else{
			if((p1.x <= x2.x && x2.x <= p2.x )||(p1.x >= x2.x && x2.x >= p2.x )) swap(x1,x2);
			s += cross(p1 - c.c, x1 - c.c) / 2; //三角形面积 
			if(cross(p1-c.c, p2 - c.c) < 0) s -= angle(x1-c.c, p2-c.c)/2*c.r*c.r; //扇形面积 
			else s += angle(x1-c.c, p2-c.c) / 2 * c.r * c.r;
		}
	}
	else if(!aInC && bInC){//p1不在圆c中, p2在圆c中 
		int cnt = calc(p1,p2,c,x1,x2);
		if(cnt <= 1){
			if(cross(p1 - c.c, p2-c.c) < 0) s -= angle(p1-c.c, x1-c.c)/2*c.r*c.r; //扇形面积 
			else s += angle(p1-c.c, x1-c.c) / 2 * c.r * c.r;
		}else{
			if((p1.x <= x2.x && x2.x <= p2.x )||(p1.x >= x2.x && x2.x >= p2.x )) swap(x1,x2);
			if(cross(p1 - c.c, p2-c.c) < 0) s -= angle(p1-c.c, x1-c.c)/2*c.r*c.r; //扇形面积 
			else s += angle(p1-c.c, x1-c.c) / 2 * c.r * c.r;
			s += cross(x1 - c.c, p2-c.c) / 2; //三角形面积 
		}
	}
	else{ //p1和p2都不在圆c中 
		int cnt  = calc(p1,p2,c,x1,x2);
		if(cnt <= 1){ //直线与圆的交点个数小于等于1,直接计算扇形的面积 
			if( cross(p1 - c.c, p2 - c.c) < 0 ) s -= angle(p1-c.c, p2-c.c)/2*c.r*c.r;
			else s += angle(p1-c.c, p2-c.c)/2*c.r*c.r;
		}else{ //有2个交点, 面积分解为两个扇形和一个三角形计算 
			if(dist(p1,x1) > dist(p1,x2)) swap(x1,x2);
			if(cross(p1-c.c, p2-c.c) < 0) s -= angle(p1-c.c,x1-c.c)/2*c.r*c.r;
			else s +=  angle(p1-c.c,x1-c.c)/2*c.r*c.r;
			
			s += cross(x1-c.c, x2-c.c) / 2;
			
			if(cross(p1-c.c, p2-c.c) < 0) s -= angle(x2-c.c, p2-c.c)/2*c.r*c.r;
			else s += angle(x2-c.c, p2-c.c)/2*c.r*c.r;
		}
	}
	return s;
}

double solve(int n,Circle c){
	double sum = 0;
	for(int i=0;i<n; ++i){
		sum += area(p[i], p[(i+1)%n], c);
	}
	return fabs(sum);
}

int main(){
#ifdef WFX
freopen("14 in.txt","r",stdin);
#endif
	ios::sync_with_stdio(false);
	double x,y,h,vx,vy,r;
	while(cin>>x>>y>>h>>vx>>vy>>r){
			double t = sqrt(2*h/10.0);
		x += vx * t;
		y += vy * t;
		Circle c(Point(x,y),r);
		int n;
		cin>>n;
		//将圆心平移到坐标原点(多边形也要做相应的平移),这样圆的方程会简单些:X*X + Y*Y = R*R 
		//否则圆的方程会稍微麻烦一些:(X-x0)^2 + (Y-y0)^2 = R^2
		for(int i=0;i<n;++i){
			 cin>>p[i].x>>p[i].y;
			 p[i].x -= c.c.x;
			 p[i].y -= c.c.y;
		}
		c.c.x = c.c.y = 0;
		printf("%.2lf\n",solve(n,c));
	}
	
	return 0;
}
