/*
题目内容：
 数一堆硬币，x1个一拨，则余下y1个；
             x2个一拨，则余下y2个；
             。。。
             xn个一拨，则余下yn个；

问最少有几个硬币
输入描述
第一行输入整数n
第二行是x1 x2 .. xn
第三行是y1 y2 .. yn

输出描述
最少的硬币数目

输入样例
2
14 57
5 56

输出样例
341
*/ 

#include<iostream>
#include<cstdio>
using namespace std;
int M[10],R[10];
typedef long long LL;

LL gcd(LL a,LL b){
	while(a&&b) a>b?a=a%b:b=b%a;
	return a+b;
}

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
中国剩余定理求解多个同余方程(模不互质的情况):
	N = r1 (mod m1)
	N = r2 (mod m2)
	
	N = k1*m1 + r1 = k2*m2 + r2
	k1*m1 - k2*m2 = r2 - r1 = r 
令  a = m1, b = m2, x = k1, y = -k2
即  a*x + b*y = r;
 	d = ext_gcd(a,b,x0,y0) 扩展gcd计算a,b的最大公约数d和特解x0、y0,使得方程a*x0 + b*y0 = d成立 
 	if(r % d == 0) 有解,且有如下通解： 
		x = x0 + t * b / d
	  	y = y0 - t * b / d
两边同乘以r/d得： a * (x0 * r / d)  + b * (y0 * r / d) = r;
则原方程的解 x =  x0 * r / d;
又 有 
	N = m1 * k1 + r1 
	  = a * x + r1
	  = a * (x0 + t * b / d) + r1
	  = t * (a * b / d) + a * x0 + r1
	  = a * x0 + r1 ( mod (a * b / d) )   ----(1) 
	需要注意的是，这里的x0是a*x + b*y=d的解，而我们要求的是 a*x + b*y=r的解， 
	所以需要用 x = x0 * r / d 来替换式(1)中的 x0 
	这样就将两个同余方程合并为了一个同余方程，接下来继续同样的操作，最后剩下一个方程，
	即可求出N的值
	
*/


LL china_remain(int n){
	LL a = M[0], r1=R[0];
	LL x0,y0;
	for(int i=1; i<n; ++i){
		LL b=M[i],r2=R[i];
		LL r = r2 - r1;
		LL d = ext_gcd(a,b,x0,y0);
		if(r % d) return -1; //无解 
		LL x = x0 * r / d; //求原方程的解 
		LL t = b / d;
		//将x化为原方程的最小正整数解 
		x = ((x % t) + t) % t;
		r1 = a * x + r1; 
		a = a * b / d; //新的a 为 a和b的最小公倍数,LCM(a,b) = a*b/GCD(a,b)
	}
	
	if(r1 == 0){
		r1 = 1;
		for(int i=0;i<n;++i) r1 = r1 * M[i] / gcd(r1,M[i]);
	}
	return r1;
}

int main(){
#ifdef WFX
freopen("7 in.txt","r",stdin);
#endif
	int T,n;
	scanf("%d",&T);
	for(int t =1; t <= T; ++t){
		scanf("%d",&n);
		for(int i=0;i<n;++i) scanf("%lld",&M[i]);
		for(int i=0;i<n;++i) scanf("%lld",&R[i]);
		printf("Case %d: %lld\n", t, china_remain(n));
	}
	
	return 0;
}
