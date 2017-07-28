#include<iostream>
#include<cstdio>
using namespace std;
int M[10],R[10];
typedef long long LL;

LL ext_gcd(LL a,LL b, LL& x, LL& y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	LL d = ext_gcd(b, a%b, x, y);
	LL tx = x;
	x = y;
	y = tx - a / b * y;
	return d;
}
/*
�й�ʣ�ඨ�������ͬ�෽��(ģ�����ʵ����):
	N = r1 (mod m1)
	N = r2 (mod m2)
	
	N = k1*m1 + r1 = k2*m2 + r2
	k1*m1 - k2*m2 = r2 - r1 = r 
��  a = m1, b = m2, x = k1, y = -k2
��  a*x + b*y = r;
 	d = ext_gcd(a,b,x0,y0) ��չgcd����a,b�����Լ��d���ؽ�x0��y0,ʹ�÷���a*x0 + b*y0 = d���� 
 	if(r % d == 0) �н�,��������ͨ�⣺ 
		x = x0 + t * b / d
	  	y = y0 - t * b / d
����ͬ����r/d�ã� a * (x0 * r / d)  + b * (y0 * r / d) = r;
��ԭ���̵Ľ� x =  x0 * r / d;
�� �� 
	N = m1 * k1 + r1 
	  = a * x + r1
	  = a * (x0 + t * b / d) + r1
	  = t * (a * b / d) + a * x0 + r1
	  = a * x0 + r1 ( mod (a * b / d) )   ----(1) 
	��Ҫע����ǣ������x0��a*x + b*y=d�Ľ⣬������Ҫ����� a*r + b*y=r�Ľ⣬ 
	������Ҫ�� x = x0 * r / d ���滻ʽ(1)�е� x0 
	�����ͽ�����ͬ�෽�̺ϲ�Ϊ��һ��ͬ�෽�̣�����������ͬ���Ĳ��������ʣ��һ�����̣�
	�������N��ֵ
	
*/


LL china_remain(int n){
	LL a = M[0], r1=R[0];
	LL x0,y0;
	for(int i=1; i<n; ++i){
		LL b=M[i],r2=R[i];
		LL r = r2 - r1;
		LL d = ext_gcd(a,b,x0,y0);
		if(r % d) return -1; //�޽� 
		LL x = x0 * r / d; //��ԭ���̵Ľ� 
		LL t = b / d;
		//��x��Ϊԭ���̵���С�������� 
		x = ((x % t) + t) % t;
		r1 = a * x + r1; 
		a = a * b / d; //�µ�a Ϊ a��b����С������,LCM(a,b) = a*b/GCD(a,b)
	}
	if(r1 == 0){
		r1 = 1;
		for(int i=0;i<n;++i) r1*= M[i];
	}
	return r1;
}

int main(){
#ifdef WFX
freopen("7 in.txt","r",stdin);
#endif
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%lld",&M[i]);
	for(int i=0;i<n;++i) scanf("%lld",&R[i]);
	printf("%lld",china_remain(n));
	
	return 0;
}
