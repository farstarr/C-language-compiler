#include "string"
#include <fstream>
using namespace std;

int rangenum=0;
int oldrange=0;
/*struct TYPELNode//类型表
{
    char TVAL;//类码
    char TPOINT;//指针
    int TPOINT_num;
    TYPELNode* next;//下一个节点
};
TYPELNode* TYPELHead;//首节点*/

struct SYNBLNode//符号总表
{
    char content[30];//内容（名字）
    string type;//类型
    char cat[3];//种类
    int addr;//地址
    char active;
    SYNBLNode* next;//下一个节点
};
SYNBLNode* SYNBLHead[50];//首节点

SYNBLNode* SYNBLp2;
struct AINFLNode//数组表
{
    int LOW;//数组下界
    int UP;//数组上界
    string  CTP;//成分
    int CLEN; //成分类型的长度
    AINFLNode* next;//下一个节点
};
AINFLNode * AINFLHead;//首节点
AINFLNode * AINFLPn;

/*struct RINFLNode//结构表
{   char ID[30];//结构的域名
    int OFF;//区距—是idk的值单元首址相对于所在记录值区区头位置；
    TYPELNode*  TP;//域成分类型指针
    RINFLNode* next;//下一个节点
};
RINFLNode * RINFLHead;//首节点*/


 struct PARAMLNode//参数表
{   char content[30];//内容（名字）
    string type;//类型
    char cat[3];//种类
    int addr_num;//地址
    PARAMLNode* next;//下一个节点
};
 PARAMLNode *  PARAMLHead;//首节点


struct PFINFLNode//函数表
{   string content;
    int OFF;//区距–该过函自身数据区起始单元相对该过函值区区头位置
    int FN;//参数个数
    PARAMLNode*  PARAM;//域成分类型指针
    int ENTRY;//该函数目标程序首地址
    PFINFLNode* next;//下一个节点
};
 PFINFLNode *  PFINFLHead;//首节点

PFINFLNode* PFINFLP;


// int    LENL[100];
void printtable()
{
    SYNBLp2=SYNBLHead[0];
    ofstream file("符号表.txt");
     file<<"************************************公用标识符表******************************"<<endl<<endl;
    file<<setw(30)<<"内容"<<"\t"<<"种类"<<"\t"<<"类型"<<"\t"<<"地址"<<"\t"<<endl;
    while( SYNBLp2->next!=NULL)
    {
         SYNBLp2=SYNBLp2->next;
    file<<setw(30)<<SYNBLp2->content<<"\t"<<SYNBLp2->type<<"\t"<<SYNBLp2->cat<<"\t"<<SYNBLp2->addr<<"\t"<<endl;
    }
    file<<endl<<endl;
    int i=1;
    while (SYNBLHead[i]!=NULL&&SYNBLHead[i]->next!=NULL) {
    SYNBLp2=SYNBLHead[i];
     file<<"************************************函数标识符表"<<i<<"******************************"<<endl<<endl;
    file<<setw(30)<<"内容"<<"\t"<<"种类"<<"\t"<<"类型"<<"\t"<<"地址"<<"\t"<<endl;
    while( SYNBLp2->next!=NULL)
    {
         SYNBLp2=SYNBLp2->next;
    file<<setw(30)<<SYNBLp2->content<<"\t"<<SYNBLp2->type<<"\t"<<SYNBLp2->cat<<"\t"<<SYNBLp2->addr<<"\t"<<endl;
    }
    file<<endl<<endl;
    PFINFLP=PFINFLHead;
    i++;
    }
     file<<"************************************函数表******************************"<<endl<<endl;
    file<<setw(30)<<"区距"<<"\t"<<"参数个数"<<"\t"<<"\t"<<endl;
    while(PFINFLP->next!=NULL)
    {
         PFINFLP=PFINFLP->next;
    file<<setw(30)<<PFINFLP->OFF<<"\t"<<PFINFLP->FN<<"\t"<<"\t"<<endl;
    }
file<<endl<<endl;

    AINFLPn=AINFLHead;
    file<<"************************************数组表******************************"<<endl<<endl;
    file<<setw(30)<<"长度"<<"\t"<<"成分类型"<<"\t"<<"成分个数"<<"\t"<<endl;
    while(AINFLPn->next!=NULL)
    {
    AINFLPn=AINFLPn->next;
    file<<setw(30)<<AINFLPn->CLEN<<"\t"<<AINFLPn->CTP<<"\t"<<AINFLPn->UP<<"\t"<<endl;
    }
file<<endl<<endl;

    file.close();
}



