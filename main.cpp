#include<string.h>
#include<map>
#include<stdio.h>
#include<string>
#include <sstream>
#include<iostream>
using namespace std;
char math_symbol[4]={'+','-','*','/'};      //算术运算符
int user_math_symbol[4]={0};                //使用者需要的运算符

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
//数值为0时代表用户不需要该运算符
double deci_num[9]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
                                            //用于小数
int max_num;                                //算术的最大值
int is_brac=0;                              //用户是否选择括号，1—代表选择，0—代表不选择，这里默认是0
int is_deci=0;                              //用户是否选择小数，1—代表选择，0—代表不选择，这里默认是0
int exam_num=0;                             //用户选择的题目数量
int brac_sum=0;                             //用户需要的算符个数

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
void init1(){                                                  //初始化阶段，用于选择题目数量，运算符数量，最大值，是否需要小数点和括号
    printf("小朋友，准备开始做算术题了，Are you ready？\n");
	printf("首先请您先设置一下题目要求:\n");
	printf("请您选择需要题目的数量：\n");
	scanf("%d",&exam_num);
	printf("请您选择您需要的运算符的数量，最多是4个：\n");
	scanf("%d",&brac_sum);
	printf("\n");
	printf("0—代表加法;1—代表减法;2—代表乘法;3—代表除法\n");
	for(int i=0;i<brac_sum;++i){
		int temp;
		printf("请输入您需要选择的第%d个运算符\n",i+1);
		while(1){
		  scanf("%d",&temp);
		  if(temp>3||temp<0){
			printf("您输入的运算符不符合要求：请选择0~3里面的数字,重新输入:\n");
		  }
		  if(temp>=0&&temp<=3){
		  	break;
		  }
		}
		user_math_symbol[temp]=1;
	}
	printf("请输入您要选择的数字的最大值:\n");
	scanf("%d",&max_num);
	printf("您是否需要括号，需要写1，不需要写0:\n");
	scanf("%d",&is_brac);
	printf("您是否需要小数，需要写1，不需要写0:\n");
	scanf("%d",&is_deci);
}
string gen_exam(){                         //自动生成算术表达式，返回string字符串
	string exam_ans;
	if (is_brac==1){
		exam_ans+="(";
	}                                      //当用户需要括号运算时，先添加左括号
	int a1=rand()%max_num;                  //生成第一个随机数
	string temp_str1;                      //临时变量
	//is1(a1,temp_str1);                     //将第一个数字转换成字符串
	exam_ans+=temp_str1;
	if(user_math_symbol[0]==1){            //判断用户是否需要“+”或“-”
		exam_ans+="+";
	}else{
		exam_ans+="-";
	}
	int a2=rand()%max_num;                  //生成第二个随机数
	double a3=0.0;
	if(is_deci==1){                        //判断用户需要小数
		a3+=(double)a2+deci_num[rand()%10];
	//	is2(a3,temp_str1);
		exam_ans+=temp_str1;
	}else{                                  //用户不需要小数
	//	is1(a2,temp_str1);
		exam_ans+=temp_str1;
	}
	if(is_brac==1){                         //当用户需要括号时，加上右括号
		exam_ans+=")";
	}
	if(user_math_symbol[2]==1&&user_math_symbol[3]==0){      //用户只选择了乘法
		/// is3(math_symbol[2],temp_str1);
		 exam_ans+=temp_str1;
	}else if(user_math_symbol[2]==0&&user_math_symbol[3]==1){//用户只选择了除法
	//	is3(math_symbol[3],temp_str1);
		exam_ans+=temp_str1;
	}else if(user_math_symbol[2]==1&&user_math_symbol[3]==1){//用户既选择了乘法又选择了除法，此时乘法与除法随机选择
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
void do_exam(){                                     //函数功能：开始做题
	printf("现在开始做题了!\n");
	for(int i=0;i<exam_num;++i){
		printf("这是本次测试的第%d题：\n",i+1);
		cout<<gen_exam()<<endl;
		int t;
		printf("您是否还想继续作答，继续作答输入1，退出输入0\n");
		scanf("%d",&t);
        if(t==0){
			break;
		}
	}
	int judge=0;
	printf("您还想再来一次吗？想的话输入1，结束的话输入0:\n");
}

int judge_end(){                                //用户判断用户是否想结束本次作答
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
	printf("请选择您的输出方式：1-代表输出到文件；2-代表打印机\n");
	int chioce;
	scanf("%d",&chioce);
	solve(chioce);
	return 0;
}
