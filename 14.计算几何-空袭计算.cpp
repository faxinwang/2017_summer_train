/*
��Ŀ���ݣ�
��ը����ը��Ŀ�������ǵ�����һ��n������Ķ���Σ�������ά����(x,y,h)��Ͷһ��ը��������
�ٶ��ǣ�vx,vy,0��,�������ٶ���10��ը���ı�ը�뾶��r, ����Ҫ�˽ⱻը���������.

��������
��һ����x y h
�ڶ�����vx vy
��������ը���ı�ը�뾶r
��������n,����Ŀ������Ķ�����
������n����Ŀ�����εĶ������꣬��˳ʱ�����

�������
��ը�������������λС����

��������
0 0 2000
100 0
100 
4
1900 100
2000 100
2000 -100
1900 -100

�������
15707.96

�ں�������Ȼͨ����, ʵ�ڲ�֪���������������,  �ȴ�����, ������ʱ�����������. 

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
	//��ֱ�ߵ������Է���ת��Ϊб��ʽ����
	//(y-y1)/(x-x1) = (y2-y1)/(x2-x1) ---> y=(y2-y1)/(x2-x1)*x + (x2y1-x1y2)/(x2-x1)
	//����ֱ�� y = kx + b �� k �� b 
	//���ȴ���б����������� 
	if( fabs(p1.x-p2.x)<eps ){ //��ֱֱ�� 
		double d = fabs(p1.x - ci.c.x);//ֱ����Բ�ĵľ��� 
		if(fabs(d - ci.r) < eps){ //��1������,ֱ����Բ���� 
			x1.x = x2.x = p1.x;
			x1.y = x2.y = ci.c.y;
			return 1;
		}else if( d < ci.r ){
			x1.x = x2.x = p1.x;
			double tmp = sqrt(ci.r * ci.r - d*d);
			x1.y = ci.c.y - tmp;
			x2.y = ci.c.y + tmp;
			return 2;
		}else return 0; //��0������ 
	}
	//����б��Ϊ0�����
	if(fabs(p1.y - p2.y)<eps){ //ˮƽֱ�� 
		double d = fabs(p1.y - ci.c.y);//ֱ�ߵ�Բ�ĵľ���
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
	//����б��Ϊ����ֵ����� 
	double k = (p2.y - p1.y)/(p2.x - p1.x); 
	double bb = (p2.x * p1.y - p1.x * p2.y)/(p2.x - p1.x);
	//���㷽�� (k*k+1)x^2 + 2*k*b*x + b*b - R*R = 0���б�ʽ��ֵ
	//�÷����� x*x + y*y = R*R �� y=kx + b �����õ� 
	double a = k*k+1;
	double b = 2 * k * bb; //b���ڱ���˷��� ax^2 + bx + c=0��ϵ�� 
	double c = bb*bb - ci.r*ci.r;
	double delt = b*b - 4 * a * c;
	
	//delt > 0 ,�������� ,����2 
	if(delt > 0){
		x1.x = (-b + sqrt(delt)) / 2/a;
		x1.y = k * x1.x + bb;
		x2.x = (-b - sqrt(delt)) / 2/a;
		x2.y = k * x2.x + bb;
		return 2;
	}
	else if(delt < 0) return 0; //�޽�,����0
	else{ //deltΪ0,��һ���� ,����1 
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
	if(aInC && bInC){ //��p1��p2����Բc�� 
		s =  cross(p1 - c.c, p2 - c.c) / 2; //���������ε����
	}
	else if(aInC && !bInC){ //p1��Բc��,p2����Բc�� 
		calc(p1,p2,c,x1,x2);
		if((p1.x <= x2.x && x2.x <= p2.x )||(p1.x >= x2.x && x2.x >= p2.x )) swap(x1,x2);
		s += cross(p1 - c.c, x1 - c.c) / 2; //��������� 
		if(cross(x1-c.c, p2 - c.c) < 0) s -= angle(x1-c.c, p2-c.c)/2*c.r*c.r; //������� 
		else s += angle(x1-c.c, p2-c.c) / 2 * c.r * c.r;
	}
	else if(!aInC && bInC){//p1����Բc��, p2��Բc�� 
		calc(p1,p2,c,x1,x2);
		if((p1.x <= x2.x && x2.x <= p2.x )||(p1.x >= x2.x && x2.x >= p2.x )) swap(x1,x2);
		if(cross(p1 - c.c, x1-c.c) < 0) s -= angle(p1-c.c, x1-c.c)/2*c.r*c.r; //������� 
		else s += angle(p1-c.c, x1-c.c) / 2 * c.r * c.r;
		s += cross(x1 - c.c, p2-c.c) / 2; //��������� 
	}
	else{ //p1��p2������Բc�� 
		int cnt  = calc(p1,p2,c,x1,x2);
		if(cnt <= 1){ //ֱ����Բ�Ľ������С�ڵ���1,ֱ�Ӽ������ε���� 
			if( cross(p1 - c.c, p2 - c.c) < 0 ) s -= angle(p1-c.c, p2-c.c)/2*c.r*c.r;
			else s += angle(p1-c.c, p2-c.c)/2*c.r*c.r;
		}else{ //��2������, ����ֽ�Ϊ�������κ�һ�������μ��� 
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
