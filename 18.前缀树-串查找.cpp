/*
题目内容：
给N个模式串，每个不超过500个字符，再给M个句子串，句子长度<=10000, 判断每个句子里是否包含模式串.
N<=100,M<=100 ,字符都是小写字母
输入描述
第一行是N, M. 随后N行模式串，以及M行句子

输出描述
每个句子的判断结果，如果句子包含某个串则输出1，否则输出0

输入样例
5 8
abcde
defg
cdke
ab
f
abcdkef
abkef
bcd
bca
add
ab
qab
f

输出样例
1
1
0
0
0
1
1
1
*/

#include<iostream>
#include<cstdio>
using namespace std;

char pat[505],sent[10005];
struct Node{
	bool end;
	Node *sub[26];
	Node(){
		end=false;
		for(int i=0;i<26;++i) sub[i] = 0;
	}
};

void insert(Node* rt, char* s, int k){
	if( rt->sub[s[k] - 'a'] == 0) rt->sub[s[k] - 'a'] = new Node();
	if(s[k+1] == 0){
		 rt->sub[s[k] - 'a']->end = true;
		 return;
	}
	insert(rt->sub[s[k]-'a'], s, k+1);
}

//查看那些点上标记了结束符 
void dfs(Node* rt,char ch){
	if(rt->end) printf("%c\n",ch);
	for(int i=0; i<26; ++i) if(rt->sub[i]) dfs(rt->sub[i],'a'+i);
}

bool find(Node* rt, char* s){
	bool found = false;
	for(int k=0; !found && s[k]; ++k){
		Node* p = rt;
		for(int j=k; !found && s[j] && p; ++j){
			if( p->sub[ s[j] - 'a' ] ){
				p = p->sub[s[j] - 'a'];
				found = p->end;
			}else break;
		}
	}
	return found;
}

int main(){
#ifdef WFX
freopen("18 in.txt","r",stdin);
#endif
	int T,n,m;
	Node *Head = new Node();
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		scanf("%s",pat);
		insert(Head, pat, 0);
	}
	
	for(int i=0;i<m;++i){
		scanf("%s",sent);
		printf("%d\n", find(Head, sent));
	}
	
	return 0;
}
