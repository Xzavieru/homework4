#include<string.h>
#include<map>
#include<stdio.h>
#include<string>
#include <sstream>
#include<iostream>
using namespace std;
char math_symbol[4]={'+','-','*','/'};      //���������
int user_math_symbol[4]={0};                //ʹ������Ҫ�������

template <typename T>
class Smartptr{
public:
   explicit Smartptr(T* =(T*)0) ;
   Smartptr<T>& operator=(Smartptr<T>&);
   Smartptr(Smartptr<T>&);
   ~Smartptr();
   T* operator->();
   T&  operator*();
private:
   T* ptr;
   static map<T*,int> cou;
};

template<typename T>
map<T*,int> Smartptr<T> :: cou;


template<typename T>
Smartptr<T>::Smartptr(T* x){
    ptr = x;
    cou[x]++;
}
const int MAXN=200005;
template<typename T>
Smartptr<T>& Smartptr<T>::operator=(Smartptr<T>& x){
     if(x.ptr == ptr)return *this;
     cou[ptr]--;
     if(cou[x.ptr]<=0){
         delete ptr;
         ptr = 0;
     }
     ptr = x.ptr;
     cou[ptr]++;
     return *this;
}

template<typename T>
Smartptr<T>::~Smartptr(){
     if(*this.ptr){
        cou[ptr]--;
        delete ptr;
     }
}
template<typename T>
Smartptr<T>::Smartptr(Smartptr<T>& x){
     ptr = x.ptr;
     cou[ptr]++;
}
//��ֵΪ0ʱ�����û�����Ҫ�������
double deci_num[9]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
                                            //����С��
int max_num;                                //���������ֵ
int is_brac=0;                              //�û��Ƿ�ѡ�����ţ�1������ѡ��0������ѡ������Ĭ����0
int is_deci=0;                              //�û��Ƿ�ѡ��С����1������ѡ��0������ѡ������Ĭ����0
int exam_num=0;                             //�û�ѡ�����Ŀ����
int brac_sum=0;                             //�û���Ҫ���������

#include<set>
//const int MAXN=200005;
int p[MAXN],loc[MAXN];
set <int> :: iterator *it;
struct DSU
{
    int fa[MAXN];
    set<int> val[MAXN];
    void init(int n)
    {
        for(int i=1;i<=n;i++)
        {
            fa[i]=i;
            val[i].insert(p[i]);
        }
    }
    int find(int x)
    {
        return fa[x]==x ? x : fa[x]=find(fa[x]);
    }
    void merge(int x,int y)
    {
        x=find(x),y=find(y);
        if(x==y)return;
        fa[x]=y;
        if(val[x].size()>val[y].size())
            val[x].swap(val[y]);
        for(auto &t:val[x])
            val[y].insert(t);
        val[x].clear();
    }
    int query(int x,int y,int v)
    {
        x=find(x),y=find(y);
        if(val[x].size()>val[y].size())
            swap(x,y);
        int res=0;
    //    for(it=val[x.begin();)
        for(auto &t:val[x])
            res+=val[y].count(v-t);
        return res;
    }
}dsu;
void init1(){                                                  //��ʼ���׶Σ�����ѡ����Ŀ��������������������ֵ���Ƿ���ҪС���������
    printf("С���ѣ�׼����ʼ���������ˣ�Are you ready��\n");
	printf("��������������һ����ĿҪ��:\n");
	printf("����ѡ����Ҫ��Ŀ��������\n");
	scanf("%d",&exam_num);
	printf("����ѡ������Ҫ��������������������4����\n");
	scanf("%d",&brac_sum);
	printf("\n");
	printf("0������ӷ�;1���������;2������˷�;3���������\n");
	for(int i=0;i<brac_sum;++i){
		int temp;
		printf("����������Ҫѡ��ĵ�%d�������\n",i+1);
		while(1){
		  scanf("%d",&temp);
		  if(temp>3||temp<0){
			printf("������������������Ҫ����ѡ��0~3���������,��������:\n");
		  }
		  if(temp>=0&&temp<=3){
		  	break;
		  }
		}
		user_math_symbol[temp]=1;
	}
	printf("��������Ҫѡ������ֵ����ֵ:\n");
	scanf("%d",&max_num);
	printf("���Ƿ���Ҫ���ţ���Ҫд1������Ҫд0:\n");
	scanf("%d",&is_brac);
	printf("���Ƿ���ҪС������Ҫд1������Ҫд0:\n");
	scanf("%d",&is_deci);
}
string gen_exam(){                         //�Զ������������ʽ������string�ַ���
	string exam_ans;
	if (is_brac==1){
		exam_ans+="(";
	}                                      //���û���Ҫ��������ʱ�������������
	int a1=rand()%max_num;                  //���ɵ�һ�������
	string temp_str1;                      //��ʱ����
	//is1(a1,temp_str1);                     //����һ������ת�����ַ���
	exam_ans+=temp_str1;
	if(user_math_symbol[0]==1){            //�ж��û��Ƿ���Ҫ��+����-��
		exam_ans+="+";
	}else{
		exam_ans+="-";
	}
	int a2=rand()%max_num;                  //���ɵڶ��������
	double a3=0.0;
	if(is_deci==1){                        //�ж��û���ҪС��
		a3+=(double)a2+deci_num[rand()%10];
	//	is2(a3,temp_str1);
		exam_ans+=temp_str1;
	}else{                                  //�û�����ҪС��
	//	is1(a2,temp_str1);
		exam_ans+=temp_str1;
	}
	if(is_brac==1){                         //���û���Ҫ����ʱ������������
		exam_ans+=")";
	}
	if(user_math_symbol[2]==1&&user_math_symbol[3]==0){      //�û�ֻѡ���˳˷�
		/// is3(math_symbol[2],temp_str1);
		 exam_ans+=temp_str1;
	}else if(user_math_symbol[2]==0&&user_math_symbol[3]==1){//�û�ֻѡ���˳���
	//	is3(math_symbol[3],temp_str1);
		exam_ans+=temp_str1;
	}else if(user_math_symbol[2]==1&&user_math_symbol[3]==1){//�û���ѡ���˳˷���ѡ���˳�������ʱ�˷���������ѡ��
		//is3(math_symbol[rand()%2+2],temp_str1);
		 exam_ans+=temp_str1;
	}else{
		if(user_math_symbol[0]==1){
			exam_ans+="+";
		}else{
		    exam_ans+="-";
		}
	}
	int a4=rand()%(max_num+1);
//	is1(a4,temp_str1);
	exam_ans+= temp_str1;
	return exam_ans;
}
void do_exam(){                                     //�������ܣ���ʼ����
	printf("���ڿ�ʼ������!\n");
	for(int i=0;i<exam_num;++i){
		printf("���Ǳ��β��Եĵ�%d�⣺\n",i+1);
		cout<<gen_exam()<<endl;
		int t;
		printf("���Ƿ���������𣬼�����������1���˳�����0\n");
		scanf("%d",&t);
        if(t==0){
			break;
		}
	}
	int judge=0;
	printf("����������һ������Ļ�����1�������Ļ�����0:\n");
}

int judge_end(){                                //�û��ж��û��Ƿ��������������
	int judge;
	scanf("%d",&judge);
	if(judge==0){
		return 0;
	}else{
		return 1;
	}
}
void solve(int chioce){

}

int main(){
	while(1){
    init1();
	do_exam();
	if(judge_end()==0){
		break;
	  }
	}
	printf("��ѡ�����������ʽ��1-����������ļ���2-�����ӡ��\n");
	int chioce;
	scanf("%d",&chioce);
	solve(chioce);
	return 0;
}
