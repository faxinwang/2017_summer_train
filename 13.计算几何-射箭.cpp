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
����˼·:
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

//��������ab,ac�Ĳ��
int cross(Point& a, Point& b,Point& c){
	Vector ab(b.x - a.x, b.y - a.y);
	Vector ac(c.x - a.x, c.y - a.y);
	return ab.cross(ac);
}

//�ж��߶�ab,cd�Ƿ��ཻ,(������ĳһ����������һ���߶��ϵ����)
bool lineCross(Point& a,Point& b,Point& c, Point& d){
	return 
		cross(a,b,c)*cross(a,b,d) < 0 &&  //c,d��ab���� 
		cross(c,d,a)*cross(c,d,b) < 0 ; //a,b��cd���� 
}

//�жϵ�x�Ƿ���������abc��(�����ڱ���) 
bool inTriangle(Point& a,Point& b,Point& c, Point& x){
	if(lineCross(a,b,c,x)) return false;
	if(lineCross(a,c,b,x)) return false;
	if(lineCross(b,c,a,x)) return false;
	return true;
}

//�жϵ�p�Ƿ��ڸ����Ķ������ 
bool inPolygon(Point p[], int n, Point &a){
	for(int i=0;i<n-2; ++i){
		if( inTriangle( p[i],p[i+1],p[i+2], a) ) return true;
	}
	return false;
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
		if( inPolygon( p, n , a ) ) printf("YES\n");
		else printf("NO\n"); 
	}
	
	return 0;
}
