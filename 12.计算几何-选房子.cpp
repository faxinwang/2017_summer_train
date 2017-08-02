/*
��Ŀ���ݣ�
 ĳ����n�����ӣ���ī��Ǯ�����������������Ϸֲ���m���������������Ϊ���㹹�ɵ������ε���
�ϵĽ�󶼹鷨ī����īֻ��Ҫ�������������֪�����ж�����ѡ�� 
��������
�����ж������������
ÿ�����������ĵ�һ����n,m��Ȼ������n����n�����ӵ����꣬������m����m���������ꡣ
������Щ�����У�û���κ��������ǹ��ߵġ�

�������
ÿ�������������һ�У�����ī��ѡ�񷽰���

��������
4 4
-10 0
10 0
0 10
0 -10
1 1
1 2
-1 1
-1 -1

�������
2
*/

/*
����˼·:
���庯��f(ab)Ϊ�߶�ab����ĵ�ĸ���,��: 
����һ��������abc(˳ʱ�����), λ�����еĵ�ĸ�������f(ab)+f(bc)-f(ac)
����һ��������abc(��ʱ�����), λ�����еĵ�ĸ�������f(ac)-f(ab)-f(bc)
���������е�ĸ�������д��abs(f(ab)+f(bc)-f(ac)), 
����˼����,���f(ab)����Ϊ�߶�ab����ĵ�ĸ���,����ʽͬ�����Լ�����������е�ĸ���. 

�жϵ�c��ֱ��ab��λ�ù�ϵ: 
���a.x < b.x  �� a.x <= c.x <= b.x 
	��� ab�� ac �Ĳ�˴���0,˵�� ab �� ac��˳ʱ����ת, c��ab�·�
	��� ab�� ac �Ĳ��С��0,˵�� ab �� ac����ʱ����ת, c��ab�Ϸ�
	��� ab�� ac �Ĳ�˵���0,˵�� ab �� ac�غ�, c���߶�ab��. 
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
	return ab.cross(ac) < 0; //�˴�д�ɴ���0����С��0��Ӱ�� 
}

int main(){
#ifdef WFX
freopen("12 in.txt","r",stdin) ;
#endif
	int n,m,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%d%d",&p[i].x, &p[i].y);
	for(int i=n,nm=n+m; i<nm; ++i) scanf("%d%d",&p[i].x, &p[i].y);
	
	sort(p,p+n);//�����Ӱ�x�������� 
	
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

