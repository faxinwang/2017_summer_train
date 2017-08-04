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

在杭电上依然通不过, 实在不知道问题出在哪里了,  先存起来, 后面有时间再来解决吧. 

*/


#include<iostream> 
#include<cstdio>
#include<cmath>
using namespace std;

typedef struct Point{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
}Vector;
Point p[100];

struct Circle{
	Point c;
	double r;
	Circle(Point p,double r):c(p.x, p.y),r(r){}
};
double eps = 1e-6; 

Vector operator - (const Vector& a,const Vector& b){return Vector(a.x - b.x, a.y - b.y);}

double dot(const Vector& a,const Vector& b){return a.x*b.x + a.y * b.y;}

double cross(const Vector& a,const Vector& b){return a.x*b.y - a.y * b.x;}

double length(const Vector& a){return sqrt(dot(a,a));}

double dist(const Point& a,const Point& b){return length(a - b);}

double angle(const Vector& a,const Vector& b){return acos(dot(a,b)/length(a)/length(b));}

int calc(Point&p1 ,Point& p2, Circle& ci,Point &x1, Point &x2){
	//将直线的两点试方程转化为斜截式方程
	//(y-y1)/(x-x1) = (y2-y1)/(x2-x1) ---> y=(y2-y1)/(x2-x1)*x + (x2y1-x1y2)/(x2-x1)
	//计算直线 y = kx + b 的 k 和 b 
	//首先处理斜率无穷大的情况 
	if( fabs(p1.x-p2.x)<eps ){ //垂直直线 
		double d = fabs(p1.x - ci.c.x);//直线与圆心的距离 
		if(fabs(d - ci.r) < eps){ //有1个交点,直线与圆相切 
			x1.x = x2.x = p1.x;
			x1.y = x2.y = ci.c.y;
			return 1;
		}else if( d < ci.r ){
			x1.x = x2.x = p1.x;
			double tmp = sqrt(ci.r * ci.r - d*d);
			x1.y = ci.c.y - tmp;
			x2.y = ci.c.y + tmp;
			return 2;
		}else return 0; //有0个交点 
	}
	//处理斜率为0的情况
	if(fabs(p1.y - p2.y)<eps){ //水平直线 
		double d = fabs(p1.y - ci.c.y);//直线到圆心的距离
		if(fabs(d - ci.r)<eps){
			x1.y = x2.y = p1.y;
			x1.x = x2.x = ci.c.x;
			return 1;
		}else if(d < ci.r){
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
	if(delt > 0){
		x1.x = (-b + sqrt(delt)) / 2/a;
		x1.y = k * x1.x + bb;
		x2.x = (-b - sqrt(delt)) / 2/a;
		x2.y = k * x2.x + bb;
		return 2;
	}
	else if(delt < 0) return 0; //无解,返回0
	else{ //delt为0,有一个解 ,返回1 
		x1.x = x2.x = -b / 2 / a;
		x1.y = k * x1.x + bb;
		return 1;
	}
}

double area(Point& p1, Point& p2, Circle& c){
	bool aInC= dist(p1,c.c) - c.r <= eps;
	bool bInC = dist(p2,c.c) - c.r <= eps;
	Point x1,x2;
	double s = 0;
	if(aInC && bInC){ //点p1和p2都在圆c中 
		s =  cross(p1 - c.c, p2 - c.c) / 2; //返回三角形的面积
	}
	else if(aInC && !bInC){ //p1在圆c中,p2不在圆c中 
		calc(p1,p2,c,x1,x2);
		if((p1.x <= x2.x && x2.x <= p2.x )||(p1.x >= x2.x && x2.x >= p2.x )) swap(x1,x2);
		s += cross(p1 - c.c, x1 - c.c) / 2; //三角形面积 
		if(cross(x1-c.c, p2 - c.c) < 0) s -= angle(x1-c.c, p2-c.c)/2*c.r*c.r; //扇形面积 
		else s += angle(x1-c.c, p2-c.c) / 2 * c.r * c.r;
	}
	else if(!aInC && bInC){//p1不在圆c中, p2在圆c中 
		calc(p1,p2,c,x1,x2);
		if((p1.x <= x2.x && x2.x <= p2.x )||(p1.x >= x2.x && x2.x >= p2.x )) swap(x1,x2);
		if(cross(p1 - c.c, x1-c.c) < 0) s -= angle(p1-c.c, x1-c.c)/2*c.r*c.r; //扇形面积 
		else s += angle(p1-c.c, x1-c.c) / 2 * c.r * c.r;
		s += cross(x1 - c.c, p2-c.c) / 2; //三角形面积 
	}
	else{ //p1和p2都不在圆c中 
		int cnt  = calc(p1,p2,c,x1,x2);
		if(cnt <= 1){ //直线与圆的交点个数小于等于1,直接计算扇形的面积 
			if( cross(p1 - c.c, p2 - c.c) < 0 ) s -= angle(p1-c.c, p2-c.c)/2*c.r*c.r;
			else s += angle(p1-c.c, p2-c.c)/2*c.r*c.r;
		}else{ //有2个交点, 面积分解为两个扇形和一个三角形计算 
			if(dist(p1,x1) > dist(p1,x2)) swap(x1,x2);
			if(cross(p1-c.c, x1-c.c) < 0) s -= angle(p1-c.c,x1-c.c)/2*c.r*c.r;
			else s +=  angle(p1-c.c,x1-c.c)/2*c.r*c.r;
			
			s += cross(x1-c.c, x2-c.c) / 2;
			
			if(cross(x2-c.c, p2-c.c) < 0) s -= angle(x2-c.c, p2-c.c)/2*c.r*c.r;
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
	cin>>x>>y>>h>>vx>>vy>>r;
	double t = sqrt(2*h/10.0);
	x += vx * t;
	y += vy * t;
	Circle c(Point(x,y),r);
	int n;
	cin>>n;
	for(int i=0;i<n;++i) cin>>p[i].x>>p[i].y;
	printf("%.2lf\n",solve(n,c));
	
	return 0;
}
