/*
��Ŀ���ݣ�
 С����ϰ������������Ƕ���Ρ�С����Ҫ֪���Ƿ����ж���Ρ�
��������
�����ж����������
��һ����n����ʾ���ӵĶ�������n<100
���n���ǰ��ӵİ�˳ʱ�뷽�򶥵����ꡣ
������һ����m����ʾ����ļ�����Ŀ m<1000
��m���Ǽ��䵽�����ꡣ

����(x,y)ֵ��С��1000

�������
һ��m�У������iֻ���������YES,�������NO.

��������
4
10 10
20 10
20 5
10 5
2
15 8
25 8

�������
YES
NO
*/ 

/*
����˼·һ(ֻ������͹�����):
�жϵ��Ƿ��ڸ����Ķ������:
	ת��Ϊ�жϵ��Ƿ�����������,������ڶ���ε�ĳһ����������,
	��ô�õ��һ���ڶ������. 
	
�жϵ��Ƿ�����������: 
	�����p����������abc��, ��ô�߶�ab,pc ����ac,pb ���� bc,paһ�������ཻ�����.
	
�ж������߶��ཻ(������һ����������һ���߶��ϵ����):
	����߶�ab,cd�ཻ,��ô��a,bһ�����߶�cd������,���ҵ�c,dҲһ�����߶�ab������,
	����ca������cb�ֱ�������cd�����࣬���ca��cb��cd�в�ͬ��ʱ�뷽��,�� 
	(cdxca) * (cdxcb) < 0  
	ͬʱ������ad������ac�ֱ�������ab������,�� 
	(ab*ac) * (ab*ad) < 0

��������߶�ab,cd�ཻ,����һ���߶ε�һ����������һ���߶��м�,�������½���:
	�����a�����߶�cd��, ������ca������cd�غ�,����Ϊ0,���ҵ�c,dһ�����߶�ab������,�� 
	(caxcd)==0 && (baxbc)*(baxbd)<0

����˼·��(ֻ������͹�����):
���ڶ����a[i]�ĵ��ǰ���˳�������(������˳ʱ�����),�����p�ڶ��������, 
�������pa[i]������pa[i+1]��Ϊ��ͬ��˳��,�������ǵĲ�˾�����ͬ��������.
���p�ڶ����a[i]������, ��һ������һ������pa[i],pa[i+1]��ǰ���pa[i-1]��pa[i]
˳��ͬ,�������ǵĲ�˾��в�ͬ��������.�ɴ˼����жϵ�p�Ƿ��ڶ������. 
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

//��������ab,ac�Ĳ��
double cross(Point& a, Point& b,Point& c){
	Vector ab(b.x - a.x, b.y - a.y);
	Vector ac(c.x - a.x, c.y - a.y);
	return cross(ab,ac);
}

//�ж��߶�ab,cd�Ƿ��ཻ,(������ĳһ����������һ���߶��ϵ����)
bool lineCross(Point& a,Point& b,Point& c, Point& d){
	return 
		dcmp( cross(a,b,c)*cross(a,b,d) ) < 0 &&  //c,d��ab���� 
		dcmp( cross(c,d,a)*cross(c,d,b) ) < 0 ; //a,b��cd���� 
}

//�жϵ�x�Ƿ���������abc��(�����ڱ���) 
bool inTriangle(Point& a,Point& b,Point& c, Point& x){
	if( lineCross(a,b,c,x) ) return false;
	if( lineCross(a,c,b,x) ) return false;
	if( lineCross(b,c,a,x) ) return false;
	return true;
}

//�жϵ�p�Ƿ��ڸ����Ķ������(ֻ��͹�������Ч)
//���жϵ��Ƿ�����n������ɵ�n-2����������
bool inPolygon1(Point p[], int n, Point &a){
	for(int i=1;i<n-1; ++i){
		if( inTriangle( p[0], p[i], p[i+1], a) ) return true;
	}
	return false;
}


//�жϵ�p�Ƿ��ڸ����Ķ������(ֻ��͹�������Ч)
bool inPolygon2(Point p[],int n,Point& a){
	//˳ʱ��,���ֵΪ��
	for(int i=0;i<n;++i){
		double tmp = cross(p[i] - a, p[(i+1)%n] - a);
		if( dcmp(tmp) > 0) return false;
		else if(tmp == 0) return true;
	}
	return true;
}

//�жϵ�p�Ƿ����߶�ab��
bool onLine(Point& a,Point& b, Point& p){
	return dcmp( cross(a-p, b-p) )==0 && dcmp( dot(a-p, b-p) )<=0;
}

//���߷��жϵ��Ƿ��ڶ������(��͹/������ζ���Ч)
//�����ǴӴ˵�������һ�����ߣ��ж϶���εı�˳ʱ����ʱ�봩�������ߴ����Ƿ���ȣ�����������档
bool inPolygon3(Point p[], int n, Point& a){
//	cout<<a.x << " " << a.y <<" ";
	int cnt=0;
	for(int i=0; i<n; ++i){
		if(onLine(p[i], p[(i+1)%n], a)) return 1; //���ڶ���εı���
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
