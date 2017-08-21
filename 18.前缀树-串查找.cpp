/*
��Ŀ���ݣ�
��N��ģʽ����ÿ��������500���ַ����ٸ�M�����Ӵ������ӳ���<=10000, �ж�ÿ���������Ƿ����ģʽ��.
N<=100,M<=100 ,�ַ�����Сд��ĸ
��������
��һ����N, M. ���N��ģʽ�����Լ�M�о���

�������
ÿ�����ӵ��жϽ����������Ӱ���ĳ���������1���������0

��������
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

�������
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

//�鿴��Щ���ϱ���˽����� 
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
