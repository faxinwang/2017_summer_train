/*
��Ŀ���ݣ�

����ѭ������ִ��Ƶ�� for(i=A; i!=B ; i+=C) x+=1;
����A,B,C,i����kλ�޷���������
��������

A B C k, ����0<k<32


�������

���ִ��Ƶ���������������������forever��


��������

3 7 2 16


�������

2

*/

#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;

LL ext_gcd(LL a,LL b, LL& x,LL &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	LL g = ext_gcd(b, a%b, x, y);
	LL xt = x;
	x = y;
	y = xt - a/b*y;
	return g;
}

int main(){
#ifdef WFX
//freopen("6 in.txt","r",stdin);
#endif
	LL A,B,C,k,x=0;
	cin>>A>>B>>C>>k;
	if(!A && !B && !C){
		printf("forever");
		return 0;
	}
	//����ɵ÷��̣�A + Cx = B (mod 2^k) (���ܳ���)
	
	//1.���򷽳�Ϊ������ͬ�෽�̱�׼ʽ ax �� n (mod b);
	LL a = C;
	LL n = B-A;
	LL b = 1LL<<k; 
	LL x0,y0;
	
	//2.��չŷ������㷨�������ͬ�෽�� C*x �� B-A (mod 2^k);
	// ax + by = n
	LL g = ext_gcd(a,b, x0,y0);//�����a,b�����Լ��d���ؽ�x0,y0 
	if( n % g ){	//���g��������n���޽�
		printf("forever");
		return 0;
	}else{
		//3.���ݹ�ʽ x = x0 * n / g ���ԭ���̵Ľ�
		// a * x + b * y = n
		// a * x0 + b * y0 = g 
		// a * x0 * (n / g) + b * y0 * (n / g) = g * (n / g) = n 
		// x = x0 * (n / g)
		LL x = x0 * n / g; 
		//4.���������Ա仯����С�ķǸ������� ��ʽ: x1 = (x % (b/g) + (b/g) ) % (b/g);
		//x%Tʹ���䵽����(-T,T), x%T+Tʹ���䵽����(0,2T), 
		//(x%T+T)%Tʹ���䵽����(0,T),������С������ 
		LL T = b / g;
		LL x1 = (x % T + T) % T;
		printf("%lld",x1);
	}
	
	return 0;
}

/*
��չŷ������㷨Դ��ŷ������㷨��
ŷ������㷨��gcd��a��b��= gcd��b��a%b����
֤����a���Ա�ʾ��a = kb + r����r = a mod b����
          ����d��a,b��һ����Լ��������d|a, d|b��
          ��r = a - kb�����d|r�������d��(b,a mod b)�Ĺ�Լ������
          ����d ��(b,a mod b)�Ĺ�Լ������d | b , d |r ������a = kb +r����
          ���dҲ��(a,b)�Ĺ�Լ������
          ���(a,b)��(b,a mod b)�Ĺ�Լ����һ���ģ������Լ��Ҳ��Ȼ��ȣ���֤

��չŷ������㷨
�����㷨�����ڲ���ȫΪ 0 �ķǸ����� a��b��gcd��a��b����ʾ a��b �����Լ������Ȼ���������� x��y ��ʹ�� gcd��a��b��=ax+by��
֤������ a>b��
����1����Ȼ�� b=0��gcd��a��b��=a����ʱ x=1��y=0��
����2��ab!=0 ʱ
������ ax1+by1=gcd(a,b);
����bx2+(a mod b)y2=gcd(b,a mod b);
�����������ص�ŷ�����ԭ���� gcd(a,b)=gcd(b,a mod b);
������:ax1+by1=bx2+(a mod b)y2;
������:ax1+by1=bx2+(a-(a/b)*b)y2=ay2+bx2-(a/b)*by2;
�������ݺ�ȶ���ã�x1=y2; y1=x2-(a/b)*y2;
     �������Ǿ͵õ������ x1,y1 �ķ�����x1��y1 ��ֵ���� x2��y2.
��  �����˼�����Եݹ鶨��ģ���Ϊ gcd ���ϵĵݹ����һ�����и�ʱ�� b=0�����Եݹ���Խ�����

(1).��չŷ��������������Ԫһ�β�������a*x+b*y=gcd(a,b)��������
���������� ����a'=b, b'=a%b=a-(a/b*b),
 a*x+b*y=gcd(a,b)
a'*x0+b'*y0=gcd(a',b')=gcd(a,b)=a*x+b*y
b*x0+(a-a/b*b)y0=a*x+b*y
a*y0+b*(x0-a/b*y0)=a*x+b*y
���ԣ�  x=y0   ; y=x0-a/b*y0

��չŷ������㷨���£�
//d=ax+by,�������Լ��d=gcd(a,b)��x��yΪ����ϵ��������ֵΪd��x��y 
long long ext_gcd(long long a, long long b, long long & x, long long & y)  //ax+by=gcd(a,b)
{
    if(!b)
    {
        x=1;
        y=0;
        return a; //d=a��x=1,y=0,��ʱ��ʽd=ax+by���� 
    }
    long long d=ext_gcd(b,a%b,x,y);
    long long xt=x;
    x=y;
    y=xt-a/b*y;
    return d;      //������չ��ŷ������㷨�У�x=y0; y=x0-a/b*y0;
}
(2).��������a*x+b*y=n���̵�������

����ͨ����a*x+b*y=gcd(a,b)���̵���⣬ת����Ϊ���Ԫһ�β�������a*x+b*y=n
��gcd��a��b����������n����������������⣬��֮�������a*x+b*y=gcd(a,b)�Ľ�Ϊx0��y0��
�򷽳�����ͬ��n�ٳ���gcd��a��b����a*��n/gcd(a,b)*x0)+b*(n/gcd(a,b)*y0)=n
���Է��̽�Ϊx=n/gcd(a,b)*x0��y=n/gcd(a,b)*y0��
(3).��ͨ�����ǣ�������Ҫ��ⷽ�̵���С������
�������Ѿ����x0,y0Ϊ������x��һ���ؽ⣬��ô
x=x0+b/gcd(a,b)*t��y=y0-a/gcd(a,b)*t(tΪ����������ҲΪ���̵Ľ�
��b/gcd(a,b)��a/gcd(a,b)�ֱ�Ϊx��y�Ľ����С��࣬����x��0~b/gcd(a,b)�������ҽ���һ���⣬
ͬ��y��0~a/gcd(a,b)ͬ�����ҽ���һ���⣬����⼴Ϊ�������������С�������⡣

Ϊʲôb/gcd(a,b)��a/gcd(a,b)�ֱ�Ϊx��y�Ľ����С��ࣿ
�⣺����cΪx�Ľ����С��࣬��ʱdΪy�Ľ�ļ�࣬����x=x0+c*t��y=y0-d*t��x0��y0Ϊһ���ؽ⣬tΪ����������
      ���뷽�̵ã�a*x0+a*c*t+b*y0-b*d*t=n,��Ϊa*x0+b*y0=n������a*c*t-b*d*t=0��t������0ʱ��a*c=b*d
      ��Ϊa,b,c,d��Ϊ����������������С��c��d��ʹ�õ�ʽ������ac��bd��Ӧ�õ���a��b����С������a*b/gcd(a,b),
      ����c=b/gcd(a,b)��d�͵���a/gcd(a,b)��

���ԣ�����������Ҫ��xΪ��С��������ôx=(x0%��b/gcd(a,b))+b/gcd(a,b))%(b/gcd(a,b))��Ϊx����С�����⡣
x0%��b/gcd(a,b))ʹ���䵽����-b/gcd(a,b)~b/gcd(a,b)���ټ���b/gcd(a,b)ʹ��������0~2*b/gcd(a,b)��
��ģ��b/gcd(a,b)����õ���С�����⣨ע��b/gcd(a,b)Ϊ�����С���룬��Ҫ��
*/ 
