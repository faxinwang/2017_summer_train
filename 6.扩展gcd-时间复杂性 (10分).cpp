/*
题目内容：

计算循环语句的执行频次 for(i=A; i!=B ; i+=C) x+=1;
其中A,B,C,i都是k位无符号整数。
输入描述

A B C k, 其中0<k<32


输出描述

输出执行频次数，如果是无穷，则输出“forever”


输入样例

3 7 2 16


输出样例

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
	//由题可得方程：A + Cx ?= B (mod 2^k) (可能等于)
	
	//1.化简方程为求线性同余方程标准式 ax ≡ n (mod b);
	LL a = C;
	LL n = B-A;
	LL b = 1LL<<k; 
	LL x0,y0;
	
	//2.扩展欧几里德算法求解线性同余方程 C*x ≡ B-A (mod 2^k);
	// ax + by = n
	LL g = ext_gcd(a,b, x0,y0);//计算出a,b的最大公约数d和特解x0,y0 
	if( n % g ){	//如果g不能整除n则无解
		printf("forever");
		return 0;
	}else{
		//3.根据公式 x = x0 * n / g 算出原方程的解
		// a * x + b * y = n
		// a * x0 + b * y0 = g 
		// a * x0(n / g) + b * y0(n / g) = g(n/g) = n 
		// x = x0(n / g)
		LL x = x0 * n / g; 
		//4.利用周期性变化求最小的非负整数解 公式: x1 = (x % (b/g) + (b/g) ) % (b/g);
		//x%T使解落到区间(-T,T), x%T+T使解落到区间(0,2T), 
		//(x%T+T)%T使解落到区间(0,T),即得最小整数解 
		LL T = b / g;
		LL x1 = (x % T + T) % T;
		printf("%lld",x1);
	}
	
	return 0;
}

/*
扩展欧几里德算法源于欧几里德算法。
欧几里德算法：gcd（a，b）= gcd（b，a%b）。
证明：a可以表示成a = kb + r，则r = a mod b　　
          假设d是a,b的一个公约数，则有d|a, d|b，
          而r = a - kb，因此d|r　　因此d是(b,a mod b)的公约数　　
          假设d 是(b,a mod b)的公约数，则d | b , d |r ，但是a = kb +r　　
          因此d也是(a,b)的公约数　　
          因此(a,b)和(b,a mod b)的公约数是一样的，其最大公约数也必然相等，得证

扩展欧几里德算法
基本算法：对于不完全为 0 的非负整数 a，b，gcd（a，b）表示 a，b 的最大公约数，必然存在整数对 x，y ，使得 gcd（a，b）=ax+by。
证明：设 a>b。
　　1，显然当 b=0，gcd（a，b）=a。此时 x=1，y=0；
　　2，ab!=0 时
　　设 ax1+by1=gcd(a,b);
　　bx2+(a mod b)y2=gcd(b,a mod b);
　　根据朴素的欧几里德原理有 gcd(a,b)=gcd(b,a mod b);
　　则:ax1+by1=bx2+(a mod b)y2;
　　即:ax1+by1=bx2+(a-(a/b)*b)y2=ay2+bx2-(a/b)*by2;
　　根据恒等定理得：x1=y2; y1=x2-(a/b)*y2;
     这样我们就得到了求解 x1,y1 的方法：x1，y1 的值基于 x2，y2.
　  上面的思想是以递归定义的，因为 gcd 不断的递归求解一定会有个时候 b=0，所以递归可以结束。

(1).拓展欧几里德是用来求二元一次不定方程a*x+b*y=gcd(a,b)的整数解
我们这样想 对于a'=b, b'=a%b=a-(a/b*b),
 a*x+b*y=gcd(a,b)
a'*x0+b'*y0=gcd(a',b')=gcd(a,b)=a*x+b*y
b*x0+(a-a/b*b)y0=a*x+b*y
a*y0+b*(x0-a/b*y0)=a*x+b*y
所以：  x=y0   ; y=x0-a/b*y0

扩展欧几里德算法如下：
//d=ax+by,其中最大公约数d=gcd(a,b)，x、y为方程系数，返回值为d、x、y 
long long ext_gcd(long long a, long long b, long long & x, long long & y)  //ax+by=gcd(a,b)
{
    if(!b)
    {
        x=1;
        y=0;
        return a; //d=a，x=1,y=0,此时等式d=ax+by成立 
    }
    long long d=ext_gcd(b,a%b,x,y);
    long long xt=x;
    x=y;
    y=xt-a/b*y;
    return d;      //对于拓展的欧几里德算法有：x=y0; y=x0-a/b*y0;
}
(2).求更常规的a*x+b*y=n方程的整数解

可以通过对a*x+b*y=gcd(a,b)方程的求解，转化成为求二元一次不定方程a*x+b*y=n
若gcd（a，b）不能整除n，这个方程无整数解，反之，若解得a*x+b*y=gcd(a,b)的解为x0，y0，
则方程两边同乘n再除以gcd（a，b）得a*（n/gcd(a,b)*x0)+b*(n/gcd(a,b)*y0)=n
所以方程解为x=n/gcd(a,b)*x0，y=n/gcd(a,b)*y0。
(3).更通常的是：我们需要求解方程的最小整数解
若我们已经求得x0,y0为方程中x的一组特解，那么
x=x0+b/gcd(a,b)*t，y=y0-a/gcd(a,b)*t(t为任意整数）也为方程的解
且b/gcd(a,b)，a/gcd(a,b)分别为x，y的解的最小间距，所以x在0~b/gcd(a,b)区间有且仅有一个解，
同理y在0~a/gcd(a,b)同样有且仅有一个解，这个解即为我们所需求的最小正整数解。

为什么b/gcd(a,b)，a/gcd(a,b)分别为x，y的解的最小间距？
解：假设c为x的解的最小间距，此时d为y的解的间距，所以x=x0+c*t，y=y0-d*t（x0，y0为一组特解，t为任意整数）
      带入方程得：a*x0+a*c*t+b*y0-b*d*t=n,因为a*x0+b*y0=n，所以a*c*t-b*d*t=0，t不等于0时，a*c=b*d
      因为a,b,c,d都为正整数，所以用最小的c，d，使得等式成立，ac，bd就应该等于a，b的最小公倍数a*b/gcd(a,b),
      所以c=b/gcd(a,b)，d就等于a/gcd(a,b)。

所以，若最后所求解要求x为最小整数，那么x=(x0%（b/gcd(a,b))+b/gcd(a,b))%(b/gcd(a,b))即为x的最小整数解。
x0%（b/gcd(a,b))使解落到区间-b/gcd(a,b)~b/gcd(a,b)，再加上b/gcd(a,b)使解在区间0~2*b/gcd(a,b)，
再模上b/gcd(a,b)，则得到最小整数解（注意b/gcd(a,b)为解的最小距离，重要）
*/ 
