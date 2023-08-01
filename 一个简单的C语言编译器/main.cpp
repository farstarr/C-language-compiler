//程序名称：一个简单的编译器编译器
//作者：东北大学ArrowQin小组
//版权归作者及其组员所有。商业转载请联系作者获得授权，非商业转载请注明出处。
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <stack>
#include<string>
#include<sstream>
#include"输出.h"

using namespace std;
stack<string> SEM;
string funcname;
static int k;
string type;
string funcstring;
int OFF=0;
int UP;
int FN=0;
FILE * infile;
Node *poi;
SYNBLNode* SYNBLp;
int  AINFaddr=0;
int  PFINFaddr=0;
AINFLNode* AINFLp=AINFLHead;
PARAMLNode* PARAMp;
PFINFLNode* PFINFLp=PFINFLHead;
PFINFLNode* PFINFLp2=PFINFLHead;
AINFLNode*  AINFLp2=AINFLHead;



Node *TheSubsequentProgram(Node *  poi);
Node *Program(Node *  poi);
Node *CompoundStatement(Node *  poi); //复合语句
Node *TheStatementList(Node *  poi); //语句列表
Node* GeneralVariableDeclaration(Node* poi);//普通变量声明
Node* SubsequentVariableDeclaration(Node* poi);//后继变量声明
Node* ParameterList(Node* poi);//参数列表
Node* ParameterDeclaration(Node* poi);//参数申明
Node* SubsequentParameterDeclaration(Node* poi);//后继参数申明
Node* LogicStatement(Node* poi);//逻辑语句
Node* LogicItemt(Node* poi);//逻辑项
Node* LogicFactor1(Node* poi);//逻辑因子1
Node* LogicFactor2(Node* poi);//逻辑因子2
Node* ArrayAssignmentStatement(Node* poi);//数组赋值
Node* SubsequentArrayAssignmentStatement(Node* poi);//后继数组赋值
Node* ValueList(Node* poi);//值列表
Node* ArimeticExpression(Node* poi);//算术表达式
Node* Item(Node* poi);//算数项
Node* Factor(Node* poi);//算数因子
Node* Unit(Node* poi);
void error()
{
  printf("error");
  exit(0);
}
void SEND(string first,string second,string third,string fourth)
{
    QtNode temQt;
    temQt.first=first;
    temQt.second=second;
    temQt.third=third;
    temQt.fourth=fourth;
    Qt.push_back(temQt);
}
void IF()
{
    string tM;
    tM=SEM.top();
    SEM.pop();
    SEND("if",tM," "," ");
}
void ELSE()
{
    SEND("el"," "," "," ");
}
void IFEND()
{
    SEND("ie"," "," "," ");
}
void WHILE()
{
    SEND("wh"," "," "," ");
}
void DO()
{
    string tM;
    tM=SEM.top();
    SEM.pop();
    SEND("do",tM," "," ");
}
void WHILEEND()
{
    SEND("we"," "," "," ");
}
void GEQ(string oper)
{
    stringstream ss;
    string numt,Numt="t";
    ss<<t_value;
    ss>>numt;
    Numt=Numt+numt;
    string tM,tM1;
    tM=SEM.top();
    SEM.pop();
    tM1=SEM.top();
    SEM.pop();
    SEM.push(Numt);
    SEND(oper,tM1,tM,Numt);
    t_value++;
}
void GEQSingle(string oper)
{
    stringstream ss;
    string numt,Numt="t";
    ss<<t_value;
    ss>>numt;
    Numt=Numt+numt;
    string tM;
    tM=SEM.top();
    SEM.pop();
    SEM.push(Numt);
    SEND(oper,tM," ",Numt);
    t_value++;
}
void ASSI(string newString)
{
    string tM;
    tM=SEM.top();
    SEM.pop();
    SEND("=",tM," ",newString);
}
void OUTPUT2()
{
    int m;
    for(m=0; m<Qt.size(); m++)           //b.size()获取行向量的大小
    {
        cout<<"("<<Qt[m].first<<","<<Qt[m].second<<","<<Qt[m].third<<","<<Qt[m].fourth<<")"<<endl;
    }
}
void OUTPUT()
{
    int m;
    for(m=0; m<NewQt.size(); m++)           //b.size()获取行向量的大小
    {
        cout<<"("<<NewQt[m].first<<","<<NewQt[m].second<<","<<NewQt[m].third<<","<<NewQt[m].fourth<<")"<<endl;
    }
}
Node *Start(Node *  poi)
{
        Next(infile);
        poi = poi->next;
       poi=Program(poi);//进入 程序 子程序
        poi=TheSubsequentProgram(poi);//进入 后继程序 子程序
    return  poi;
}

Node *TheSubsequentProgram(Node *  poi)
{
    if(poi->type==45);//判断#
    else {
         poi=Program(poi); //进入 程序 子程序
          poi=TheSubsequentProgram(poi); //进入 后继程序 子程序

    }
    return poi;
}

Node *Program(Node *  poi)
{
    if(poi->type==4||poi->type==7)//判断int 和void
    {    type=poi->content;//读type准备写入符号总表
         Next(infile);
        poi = poi->next;
        if(poi->type==17)//判断main
        {   rangenum=oldrange;
            rangenum++;
             initSYNBL(rangenum);
             SYNBLp=SYNBLHead[rangenum];
              PFINFLp=new PFINFLNode();
              PFINFLp->content="main";
              PFINFLp->FN=0;
              PFINFLp->PARAM=NULL;
              PFINFLp->ENTRY=0;
              PFINFLp->next=NULL;
              PFINFLp2->next=PFINFLp;
              PFINFLp2=PFINFLp2->next;
              OFF=0;
            cout<<"("<<PFINFLp->FN<<","<<PFINFLp->PARAM<<","<<PFINFLp->ENTRY<<","<<PFINFLp->next<<")"<<endl;
            funcname="main";
            SEND("func","_","_","main");
                                            //填写函数表
              Next(infile);
              poi = poi->next;
              if(poi->type==38)//判断（
            {       Next(infile);
                poi = poi->next;
                if(poi->type==39)//判断）
                {

                    Next(infile);
                    poi = poi->next;
                    if(poi->type==42)//判断{
                    {
                     Next(infile);
                    poi = poi->next;
                    poi=CompoundStatement(poi);//进入 复合语句 子程序
                    oldrange=rangenum;
                    rangenum=0;
                    PFINFLp->OFF=OFF;
                           PFINFLp->OFF=OFF;
                    SEND("END","_","_","_");
                    return  poi;
                    }
                    else error();
                }
                else error();
            }
            else error();

        }else { if(poi->type==0)//判断标识符
                {
                  SYNBLp=SYNBLHead[rangenum];
                               while(strcmp(SYNBLp->content,poi->content)!=0)
                                {
                                    SYNBLp=SYNBLp->next;

                               }
                  if(SYNBLp->next!=NULL) {printf("重复定义"); exit(0);}
                     SYNBLp->type=type;
                     if(type=="int") OFF=OFF+4;//计算off
                    Next(infile);
                    poi = poi->next;
                     if(poi->type==38)//判断（
                     {    funcname=SYNBLp->content;
                          SEND("func","_","_",SYNBLp->content);
                          strcpy(SYNBLp->cat,"f");
                          SYNBLp->addr=++PFINFaddr;
                          SYNBLp->next=NULL;
                          rangenum=oldrange;
                  rangenum++;
             initSYNBL(rangenum);
             SYNBLp=SYNBLHead[rangenum];
             initPARAML(PARAMp);
              PFINFLp=new PFINFLNode();
              PFINFLp->content=funcname;
              FN=0;
              PFINFLp->PARAM=PARAMp;
              PFINFLp->ENTRY=0;
              PFINFLp->next=NULL;
              PFINFLp2->next=PFINFLp;
              PFINFLp2=PFINFLp2->next;
              OFF=0;
            cout<<"("<<PFINFLp->FN<<","<<PFINFLp->PARAM<<","<<PFINFLp->ENTRY<<","<<PFINFLp->next<<")"<<endl;

                                            //填写函数表
                         Next(infile);
                        poi = poi->next;
                        poi=ParameterList(poi);//进入 参数列表 子程序
                        if(poi->type==39)//判断）
                        {
                            Next(infile);
                            poi = poi->next;
                            if(poi->type==42)//判断{
                            {
                                    Next(infile);
                                    poi = poi->next;
                                    poi=CompoundStatement(poi);//进入 复合语句 子程序
                                    oldrange=rangenum;
                                    rangenum=0;
                                    PFINFLp->OFF=OFF;
                                    PFINFLp->FN=FN;

                    SEND("END","_","_","_");
                                    return  poi;
                            }else error();
                        }else error();
                     }else { if(poi->type==40)//判断[
                         {
                             strcpy(SYNBLp->cat,"a");
                             SYNBLp->addr=++AINFaddr;
                                 AINFLp=new AINFLNode();
                             AINFLp->CTP=type;
                             AINFLp->LOW=0;
                             AINFLp->next=NULL;
                             AINFLp2->next=AINFLp;
                             AINFLp2=AINFLp2->next;

                                                         //填写数组表
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==3)//判断数字
                             {   AINFLp->UP=atoi(poi->content);//数字写入up
                                 if(AINFLp->CTP=="int") AINFLp->CLEN=4*AINFLp->UP;
                                 if(AINFLp->CTP=="float") AINFLp->CLEN=8*AINFLp->UP;
                                 if(AINFLp->CTP=="bool"||AINFLp->CTP=="char") AINFLp->CLEN=AINFLp->UP;
                                 OFF=OFF+AINFLp->CLEN;

                                 Next(infile);
                                 poi = poi->next;
                                 if(poi->type==41)//判断]
                                 {
                                     Next(infile);
                                     poi = poi->next;
                                     poi=ArrayAssignmentStatement(poi);//进入 数组赋值语句 子程序
                                     poi=SubsequentArrayAssignmentStatement(poi);//进入 后继数组赋值语句 子程序

                                     return poi;
                                 }else error();

                             }else error();
                         }else {
                             if (poi->type==25)//判断=
                                   {
                                     strcpy(SYNBLp->cat,"v");
                                      cout<<SYNBLp->content <<","<<SYNBLp->type<<","<<SYNBLp->cat<<","<<SYNBLp->addr<<endl;                        //地址指向vall
                                     Next(infile);
                                     poi = poi->next;
                                     if (poi->type==1||poi->type==2)//判断字符，字符串（即常量）
                                         {
                                             Next(infile);
                                             poi = poi->next;
                                             poi=SubsequentVariableDeclaration(poi);//进入 后继变量声明 子程序

                                             return poi;
                                         }else {
                                                poi=ArimeticExpression(poi);//进入 算术表达式 子程序
                                                poi=SubsequentVariableDeclaration(poi);//进入 后继变量声明 子程序

                                                    return poi;
                                                }
                                   }   else {   strcpy(SYNBLp->cat,"v");
                                                 cout<<SYNBLp->content <<","<<SYNBLp->type<<","<<SYNBLp->cat<<","<<SYNBLp->addr<<endl;             //地址指向vall
                                                poi=SubsequentVariableDeclaration(poi);//进入 后继变量声明 子程序

                                                    return poi;
                                                }

                                }//判断=
                     }//判断[

                }else error();

                }//判断标识符
    } else { if (poi->type==5||poi->type==9||poi->type==11)//判断bool float char
              {     type=poi->content;//读type准备写入符号总表

                   Next(infile);
                   poi = poi->next;
                    if (poi->type==0)//判断标识符
                    {
                         SYNBLp=SYNBLHead[rangenum];
                 while(strcmp(SYNBLp->content,poi->content)!=0)
                    {
                        SYNBLp=SYNBLp->next;

                 }
                  if(SYNBLp->next!=NULL)
                  {
                      printf("重复定义");
                      exit(0);
                  }
                     SYNBLp->type=type;
                        Next(infile);
                        poi = poi->next;
                        if(poi->type==38)//判断（
                        {        if(type=="int") OFF=OFF+4;
                                 if(type=="float")  OFF=OFF+8;
                                 if(type=="bool"||AINFLp->CTP=="char")  OFF=OFF+1;
                                  funcname=SYNBLp->content;
                                  SEND("func","_","_",SYNBLp->content);
                            strcpy(SYNBLp->cat,"f");
                          SYNBLp->addr=++PFINFaddr;
                          SYNBLp->next=NULL;
                       rangenum=oldrange;
                       rangenum++;
             initSYNBL(rangenum);
             SYNBLp=SYNBLHead[rangenum];
             initPARAML(PARAMp);
              PFINFLp=new PFINFLNode();
               PFINFLp->content=SYNBLp->content;
              FN=0;
              PFINFLp->PARAM=PARAMp;
              PFINFLp->ENTRY=0;
              PFINFLp->next=NULL;
              PFINFLp2->next=PFINFLp;
              PFINFLp2=PFINFLp2->next;
              OFF=0;
            cout<<"("<<PFINFLp->FN<<","<<PFINFLp->PARAM<<","<<PFINFLp->ENTRY<<","<<PFINFLp->next<<")"<<endl;
                                            //填写函数表
                            Next(infile);
                            poi = poi->next;
                            poi=ParameterList(poi);//进入 参数列表 子程序
                            if(poi->type==39)//判断）
                            {
                                Next(infile);
                                poi = poi->next;
                                    if(poi->type==42)//判断{
                                    {
                                         Next(infile);
                                         poi = poi->next;
                                         poi=CompoundStatement(poi);//进入 复合语句 子程序
                                         oldrange=rangenum;
                                         rangenum=0;
                                         PFINFLp->OFF=OFF;
                                           SEND("END","_","_","_");
                                         return  poi;
                                    } else error();
                                }else error();
                        }else { if(poi->type==40)//判断[
                         {
                             cout<<SYNBLp->content <<","<<SYNBLp->type<<","<<SYNBLp->cat<<","<<SYNBLp->addr<<endl;
                             AINFLNode* AINFLp=new AINFLNode();
                             AINFLp->CTP=type;
                             AINFLp->LOW=0;
                             AINFLp->next=NULL;
                             AINFLp2->next=AINFLp;
                             AINFLp2=AINFLp2->next;
                                                         //填写数组表
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==3)//判断数字
                             {   AINFLp->UP=atoi(poi->content);//数字写入up
                                 if(AINFLp->CTP=="int") AINFLp->CLEN=4*AINFLp->UP;
                                 if(AINFLp->CTP=="float") AINFLp->CLEN=8*AINFLp->UP;
                                 if(AINFLp->CTP=="bool"||AINFLp->CTP=="char") AINFLp->CLEN=AINFLp->UP;
                                  cout<<AINFLp->CTP <<","<< AINFLp->LOW<<","<<AINFLp->CLEN<<","<<AINFLp->next<<endl;
                                  OFF=OFF+AINFLp->CLEN;
                                 Next(infile);
                                 poi = poi->next;
                                 if(poi->type==41)//判断]
                                 {
                                     Next(infile);
                                     poi = poi->next;
                                     poi=ArrayAssignmentStatement(poi);//进入 数组赋值语句 子程序
                                     poi=SubsequentArrayAssignmentStatement(poi);//进入 后继数组赋值语句 子程序

                                     return poi;
                                 }else error();

                             }else error();
                         }//判断[
                  else { if (poi->type==25)//判断=
                                   { strcpy(SYNBLp->cat,"v");
                                       if(type=="int") OFF=OFF+4;
                                      if(type=="float")  OFF=OFF+8;
                                      if(type=="bool"||AINFLp->CTP=="char")  OFF=OFF+1;                        //地址指向vall
                                     Next(infile);
                                     poi = poi->next;
                                     if (poi->type==1||poi->type==2)//判断字符，字符串（即常量）
                                         {
                                             Next(infile);
                                             poi = poi->next;
                                             poi=SubsequentVariableDeclaration(poi);//进入 后继变量声明 子程序

                                             return poi;
                                         }else {
                                                poi=ArimeticExpression(poi);//进入 算术表达式 子程序
                                                poi=SubsequentVariableDeclaration(poi);//进入 后继变量声明 子程序

                                                    return poi;
                                                }
                                   }   else {   strcpy(SYNBLp->cat,"v");
                                                  if(type=="int") OFF=OFF+4;
                                                  if(type=="float")  OFF=OFF+8;
                                                  if(type=="bool"||type=="char")  OFF=OFF+1;             //地址指向vall

                                                poi=SubsequentVariableDeclaration(poi);//进入 后继变量声明 子程序

                                                    return poi;
                                                }

              }


}
    } else error();
                    } else error();
                    }
                    }

Node *CompoundStatement(Node *  poi) //复合语句
{
    poi=TheStatementList(poi); //进入 语句列表 子程序
    if(poi->type==43)//判断}
    {
        Next(infile);
        poi = poi->next;
        return poi;
    }
    else error();
}


Node *TheStatementList(Node *  poi) //语句列表
{
    if(poi->type==12)//判断if
    {
         Next(infile);
         poi = poi->next;
         if(poi->type==38)//判断（
         {
             Next(infile);
             poi = poi->next;
             poi=LogicStatement(poi); //进入 逻辑语句 子程序
                if(poi->type==39)//判断）
                {
                     IF();
                     Next(infile);
                     poi = poi->next;
                     if(poi->type==42)//判断{
                     {
                         Next(infile);
                         poi = poi->next;
                         poi=CompoundStatement(poi); //进入 复合语句 子程序
                         if(poi->type==13)//判断else
                         {
                             ELSE();
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==42)//判断{
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 poi=CompoundStatement(poi); //进入 复合语句 子程序
                                 IFEND();
                                 poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                             }else{
                                error();
                             }
                         }else {
                             IFEND();
                             poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                         }

                     }else {
                         error();
                     }
                }else error();
         }else error();
    }else {
         if(poi->type==14)//判断while
    {
        WHILE();
         Next(infile);
         poi = poi->next;
         if(poi->type==38)//判断（
         {
             Next(infile);
             poi = poi->next;
             poi=LogicStatement(poi); //进入 逻辑语句 子程序
                if(poi->type==39)//判断）
                {
                    DO();
                     Next(infile);
                     poi = poi->next;
                     if(poi->type==42)//判断{
                     {
                         Next(infile);
                         poi = poi->next;
                         poi=CompoundStatement(poi); //进入 复合语句 子程序
                         WHILEEND();
                         poi=TheStatementList(poi); //进入 语句列表 子程序
                         return poi;
                     }else {
                          error();
                     }
    }else error();
}else error();
    }else{
        if(poi->type==18)//判断return
        {

            Next(infile);
            poi = poi->next;
            if(poi->type==0)//判断标识符
            {
                SYNBLp=SYNBLHead[rangenum];
                               while(strcmp(SYNBLp->content,poi->content)!=0&&SYNBLp->next!=NULL)
                                {SYNBLp=SYNBLp->next; }
                                if(SYNBLp->type==" ")
                                {   SYNBLp=SYNBLHead[0];
                                    while(strcmp(SYNBLp->content,poi->content)!=0&&SYNBLp->next!=NULL)
                                    {
                                        SYNBLp=SYNBLp->next;
                                    }
                                                  if(SYNBLp->type==" "||strcmp(SYNBLp->content,poi->content)!=0)
                                    {printf("调用未定义变量"); exit(0);}}
                                    if(strcmp(SYNBLp->cat,"v")==0||strcmp(SYNBLp->cat,"p")==0)
                                    {SEND("re","_",SYNBLp->content,funcname);}
                Next(infile);
                poi = poi->next;
                if(poi->type==37)//判断;
                {
                     Next(infile);
                     poi = poi->next;
                     poi=TheStatementList(poi); //进入 语句列表 子程序
                     return poi;
                }else error();
            }else {
                if(poi->type==1||poi->type==2||poi->type==3)//判断常量
                {   SEND("re","_",poi->content,funcname);
                    Next(infile);
                  poi = poi->next;
                if(poi->type==37)//判断;
                {
                     Next(infile);
                     poi = poi->next;
                     poi=TheStatementList(poi); //进入 语句列表 子程序
                     return poi;
                }else error();
                }else error();
            }
        }
        else {  if(poi->type==0)//判断标识符
                {
                    string newString="";
                    newString=poi->content;
                    while(poi->type==0)//判断标识符
              {      SYNBLp=SYNBLHead[rangenum];
                               while(strcmp(SYNBLp->content,poi->content)!=0&&SYNBLp->next!=NULL)
                                {SYNBLp=SYNBLp->next; }
                                if(SYNBLp->type==" ")
                                {   SYNBLp=SYNBLHead[0];
                                    while(strcmp(SYNBLp->content,poi->content)!=0&&SYNBLp->next!=NULL)
                                    {
                                        SYNBLp=SYNBLp->next;
                                    }
                                         if(SYNBLp->type==" "||strcmp(SYNBLp->content,poi->content)!=0)
                                    {printf("调用未定义变量"); exit(0);}}

                   Next(infile);
                   poi = poi->next;
                    if(poi->type==40)//判断[
                    {
                        newString=newString+'[';
                        Next(infile);
                       poi = poi->next;
                       if(poi->type==3)//判断数字
                       {
                           newString=newString+(poi->content);
                           Next(infile);
                           poi = poi->next; }else error();
                           if(poi->type==41)//判断]
                           {
                               newString=newString+']';
                                Next(infile);
                               poi = poi->next; }else error();
                    }
                               if(poi->type==25)//判断=
                   {
                       SEM.push(newString);
                       Next(infile);
                       poi = poi->next;
                       if(poi->type==1||poi->type==2)//判断常量
                       {
                           Next(infile);
                           poi = poi->next;
                       } else {poi=ArimeticExpression(poi);}//进入 算术表达式 子程序
                       ASSI(newString);
                           if(poi->type!=36)//判断,
                           break;
                           }else error();
                           }
                            if(poi->type==37)//判断;
                            {
                             Next(infile);
                             poi = poi->next;
                             poi=TheStatementList(poi); //进入 语句列表 子程序
                             return poi;
                            }
                           else  error();
        }

                  if(poi->type==7||poi->type==5||poi->type==9||poi->type==11)//判断char int bool float
                  {   type=poi->content;//读type准备写入符号总表
                      Next(infile);
                      poi = poi->next;
                      if(poi->type==0)//判断标识符
                      {
                            SYNBLp=SYNBLHead[rangenum];
                               while(strcmp(SYNBLp->content,poi->content)!=0) {SYNBLp=SYNBLp->next;}
                  if(SYNBLp->next!=NULL) {printf("重复定义"); exit(0);}
                     SYNBLp->type=type;
                           Next(infile);
                           poi = poi->next;
                           if(poi->type==40)//判断[
                      {
                          strcpy(SYNBLp->cat,"a");
                             SYNBLp->addr=++AINFaddr;
                            AINFLp=new AINFLNode();
                             AINFLp->CTP=type;
                             AINFLp->LOW=0;
                             AINFLp->next=NULL;
                             AINFLp2->next=AINFLp;
                             AINFLp2=AINFLp2->next;
                                                         //填写数组表
                          Next(infile);
                          poi = poi->next;
                          if(poi->type==3)//判断数字
                          {   AINFLp->UP=atoi(poi->content);//数字写入up
                                 if(AINFLp->CTP=="int") AINFLp->CLEN=4*AINFLp->UP;
                                 if(AINFLp->CTP=="float") AINFLp->CLEN=8*AINFLp->UP;
                                 if(AINFLp->CTP=="bool"||AINFLp->CTP=="char") AINFLp->CLEN=AINFLp->UP;
                                 cout<<AINFLp->CTP <<","<< AINFLp->LOW<<","<<AINFLp->CLEN<<","<<AINFLp->next<<endl;
                                 OFF=OFF+AINFLp->CLEN;
                              Next(infile);
                              poi = poi->next;
                              if(poi->type==41)//判断]
                              {
                                  Next(infile);
                                  poi = poi->next;
                                  poi=ArrayAssignmentStatement(poi);//进入 数组赋值语句 子程序
                                  poi=SubsequentArrayAssignmentStatement(poi);//进入 后继数组赋值语句 子程序
                                  poi=TheStatementList(poi); //进入 语句列表 子程序
                                  return poi;
                              }else error();
                          }else error();
                      }else {
                          if(poi->type==25)//判断=
                          {    strcpy(SYNBLp->cat,"v");
                                 if(type=="int") OFF=OFF+4;
                                 if(type=="float")  OFF=OFF+8;
                                 if(type=="bool"||AINFLp->CTP=="char")  OFF=OFF+1;                              //地址指向vall
                               Next(infile);
                               poi = poi->next;
                               if(poi->type==1||poi->type==2)//判断常量
                               {
                                    Next(infile);
                                    poi = poi->next;
                                    poi=SubsequentVariableDeclaration(poi); //进入 后继变量声明 子程序
                                    poi=TheStatementList(poi); //进入 语句列表 子程序
                                    return poi;
                               }else{
                                    poi=ArimeticExpression(poi);//进入 算术表达式 子程序
                                    poi=SubsequentVariableDeclaration(poi); //进入 后继变量声明 子程序
                                    poi=TheStatementList(poi); //进入 语句列表 子程序
                                    return poi;
                               }
                          }else{    strcpy(SYNBLp->cat,"v");
                                      if(type=="int") OFF=OFF+4;
                                 if(type=="float")  OFF=OFF+8;
                                 if(type=="bool"||type=="char")  OFF=OFF+1;                         //地址指向vall
                                    poi=SubsequentVariableDeclaration(poi); //进入 后继变量声明 子程序
                                    poi=TheStatementList(poi); //进入 语句列表 子程序
                                    return poi;
                          }

                      }
                      } else error();

                  }else return poi;
              }
        }
    }

         }
Node* GeneralVariableDeclaration(Node* poi)//普通变量声明
    {    if(poi->type==0)//判断标识符
                      {
     SYNBLp=SYNBLHead[rangenum];
                               while(strcmp(SYNBLp->content,poi->content)!=0) {SYNBLp=SYNBLp->next; }
                  if(SYNBLp->next!=NULL) {printf("重复定义"); exit(0);}
        SYNBLp->type=type;
        cout<<SYNBLp->type<<endl;
        Next(infile);
        poi=poi->next;
        if(strcmp(poi->content,"=")==0)
        {
            Next(infile);
            poi=poi->next;
            if((poi->type==1)||(poi->type==2))//判断是否是常量(字符串，常量)
            {
                Next(infile);
                poi=poi->next;
            }
            else
            {
                poi=ArimeticExpression(poi);//算术表达式
            }
        }
    }
    else
    {
        error();
    }
      strcpy(SYNBLp->cat,"v");
               if(type=="int") OFF=OFF+4;
                                 if(type=="float")  OFF=OFF+8;
                                 if(type=="bool"||type=="char")  OFF=OFF+1;                                                //地址指向vall
     cout<<SYNBLp->content<<SYNBLp->cat<<SYNBLp->type<<endl;
    return poi;
}

Node* SubsequentVariableDeclaration(Node* poi)//后继变量声明
{
    if(strcmp(poi->content,";")==0)
    {
        Next(infile);
        poi=poi->next;
    }
    else if(strcmp(poi->content,",")==0)
    {
        Next(infile);
        poi=poi->next;
        poi=GeneralVariableDeclaration(poi);//普通变量声明
        poi=SubsequentVariableDeclaration(poi);//后继变量声明
    }
    else
    {
        error();
    }
    return poi;
}

Node* ParameterList(Node* poi)//参数列表
{
    if((strcmp(poi->content,"int")==0)||(strcmp(poi->content,"char")==0)||(strcmp(poi->content,"float")==0)||(strcmp(poi->content,"bool")==0))
    {   FN++;
        poi=ParameterDeclaration(poi);//参数申明
        poi=SubsequentParameterDeclaration(poi);//后继参数申明
    }
    return poi;
}

Node* ParameterDeclaration(Node* poi)//参数申明
{
    if((strcmp(poi->content,"int")==0)||(strcmp(poi->content,"char")==0)||(strcmp(poi->content,"float")==0)||(strcmp(poi->content,"bool")==0))
    {   type=poi->content;//读type准备写入符号总表
    if(type=="int")OFF=OFF+4;
     if(type=="float")OFF=OFF+8;
      if(type=="bool"||type=="char")OFF=OFF+1;
        Next(infile);
        poi=poi->next;
        PARAMLNode* PARAMp2=new PARAMLNode();
        strcpy(PARAMp2->content,poi->content);
        if(poi->type==0)//判断是否是标识符
        {   SEND("param","_","_",poi->content);
              SYNBLp=SYNBLHead[rangenum];

                while(strcmp(SYNBLp->content,poi->content)!=0) {SYNBLp=SYNBLp->next;}
                  if(SYNBLp->next!=NULL) {printf("重复定义"); exit(0);}
            SYNBLp->type=type;
            PARAMp2->type=type;

            Next(infile);
            poi=poi->next;
            if(strcmp(poi->content,"=")==0)
            {   strcpy(SYNBLp->cat,"p");

                 strcpy(PARAMp2->cat,"p");
                                            //地址指向vall
                 PARAMp2->next-NULL;
                 PARAMp->next=PARAMp2;
                 PARAMp=PARAMp->next;
                Next(infile);
                poi=poi->next;
                if((poi->type==1)||(poi->type==2))//判断是否是常量(字符串，常量)
                {
                    Next(infile);
                    poi=poi->next;
                }
                else
                {   strcpy(SYNBLp->cat,"p");

                                                             //地址指向vall
                    poi=ArimeticExpression(poi);//算术表达式
                }
            }else{strcpy(SYNBLp->cat,"p");}
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
    return poi;
}

Node* SubsequentParameterDeclaration(Node* poi)//后继参数申明
{
    if(strcmp(poi->content,",")==0)
    {
        Next(infile);
        poi=poi->next;
        FN++;
        poi=ParameterDeclaration(poi);//参数申明
        poi=SubsequentParameterDeclaration(poi);//后继参数申明
    }
    return poi;
}


Node* LogicStatement(Node* poi)//逻辑语句
{
    poi=LogicItemt(poi);
    while(1)
    {
        if(strcmp(poi->content,"||")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=LogicItemt(poi);
            GEQ("||");
        }
        else
        {
            break;
        }
    }
    return poi;
}

Node* LogicItemt(Node* poi)//逻辑项
{
    poi=LogicFactor1(poi);
    while(1)
    {
        if(strcmp(poi->content,"&&")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=LogicItemt(poi);
            GEQ("&&");
        }
        else
        {
            break;
        }
    }
    return poi;
}

Node* LogicFactor1(Node* poi)//逻辑因子1
{
    poi=LogicFactor2(poi);
    while(1)
    {
        if(strcmp(poi->content,"==")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=LogicFactor2(poi);
            GEQ("==");
        }
        else if(strcmp(poi->content,"!=")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=LogicFactor2(poi);
            GEQ("!=");
        }
        else
        {
            break;
        }
    }
    return poi;
}

Node* LogicFactor2(Node* poi)//逻辑因子2
{
    poi=ArimeticExpression(poi);
    while(1)
    {
        if(strcmp(poi->content,">=")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=ArimeticExpression(poi);//算术表达式
            GEQ(">=");
        }
        else if(strcmp(poi->content,">")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=ArimeticExpression(poi);
            GEQ(">");
        }
        else if(strcmp(poi->content,"<=")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=ArimeticExpression(poi);
            GEQ("<=");
        }
        else if(strcmp(poi->content,"<")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=ArimeticExpression(poi);
            GEQ("<");
        }
        else
        {
            break;
        }
    }
    return poi;
}

Node* ArrayAssignmentStatement(Node* poi)//数组赋值
{
    if(strcmp(poi->content,"=")==0)
    {
        Next(infile);
        poi=poi->next;
        if(strcmp(poi->content,"{")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=ValueList(poi);//值列表
            if(strcmp(poi->content,"}")==0)
            {
                Next(infile);
                poi=poi->next;
            }
        }
        else
        {
            error();
        }
    }
    return poi;
}

Node* SubsequentArrayAssignmentStatement(Node* poi)//后继数组赋值
{
    if(strcmp(poi->content,",")==0)
    {
        Next(infile);
        poi=poi->next;
        if(poi->type==0)//判断是否是标识符
        {
         while(strcmp(SYNBLp->content,poi->content)!=0) SYNBLp=SYNBLp->next;
           if(SYNBLp->next!=NULL) {printf("重复定义"); exit(0);}
         SYNBLp->type=type;
            Next(infile);
            poi=poi->next;
            if(strcmp(poi->content,"[")==0)
            {      strcpy(SYNBLp->cat,"a");
                             SYNBLp->addr=++AINFaddr;
                             cout<<SYNBLp->content <<","<<SYNBLp->type<<","<<SYNBLp->cat<<","<<SYNBLp->addr<<endl;
                           AINFLNode* AINFLp=new AINFLNode();
                             AINFLp->CTP=type;
                             AINFLp->LOW=0;
                             AINFLp->next=NULL;
                             AINFLp2->next=AINFLp;
                             AINFLp2=AINFLp2->next;
                                                         //填写数组表
                Next(infile);
                poi=poi->next;
                if(poi->type==3)
                {   AINFLp->UP=atoi(poi->content);//数字写入up
                                 if(AINFLp->CTP=="int") AINFLp->CLEN=4*AINFLp->UP;
                                 if(AINFLp->CTP=="float") AINFLp->CLEN=8*AINFLp->UP;
                                 if(AINFLp->CTP=="bool"||AINFLp->CTP=="char") AINFLp->CLEN=AINFLp->UP;
                                  cout<<AINFLp->CTP <<","<< AINFLp->LOW<<","<<AINFLp->CLEN<<","<<AINFLp->next<<endl;
                                 OFF=OFF+AINFLp->CLEN;
                    Next(infile);
                    poi=poi->next;
                    if(strcmp(poi->content,"]")==0)
                    {
                        Next(infile);
                        poi=poi->next;
                        poi=ArrayAssignmentStatement(poi);//数组赋值
                        poi=SubsequentArrayAssignmentStatement(poi);//后继数组赋值
                    }
                    else
                    {
                        error();
                    }
                }
                else
                {
                    error();
                }
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
    else if(strcmp(poi->content,";")==0)
    {
        Next(infile);
        poi=poi->next;
    }
    else
    {
        error();
    }
    return poi;
}

Node* ValueList(Node* poi)//值列表
{
    while(1)
    {
        if(poi->type==3)//判断是否是数字
        {
            Next(infile);
            poi=poi->next;
            if(strcmp(poi->content,",")==0)
            {
                Next(infile);
                poi=poi->next;
            }
            else
            {
                break;
            }
        }
        else
        {
            error();
        }
    }
    return poi;
}

Node* ArimeticExpression(Node* poi)//算术表达式
{
    poi=Item(poi);
    while(1)
    {
        if(strcmp(poi->content,"+")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=Item(poi);
            GEQ("+");
        }
        else if(strcmp(poi->content,"-")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=Item(poi);
            GEQ("-");
        }
        else
        {
            break;
        }
    }
    return poi;
}

Node* Item(Node* poi)//算数项
{
    poi=Factor(poi);//算数因子
    while(1)
    {
        if(strcmp(poi->content,"*")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=Factor(poi);
            GEQ("*");
        }
        else if(strcmp(poi->content,"/")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=Factor(poi);
            GEQ("/");
        }
        else if(strcmp(poi->content,"%")==0)
        {
            Next(infile);
            poi=poi->next;
            poi=Factor(poi);
            GEQ("%");
        }
        else
        {
            break;
        }
    }
    return poi;
}

Node* Factor(Node* poi)//算数因子
{
    if(strcmp(poi->content,"+")==0)
    {
        Next(infile);
        poi=poi->next;
        poi=Unit(poi);
        GEQSingle("+");
    }
    else if(strcmp(poi->content,"-")==0)
    {
        Next(infile);
        poi=poi->next;
        poi=Unit(poi);
        GEQSingle("-");
    }
    else if(strcmp(poi->content,"!")==0)
    {
        Next(infile);
        poi=poi->next;
        poi=Unit(poi);
        GEQSingle("!");
    }
    else
    {
        poi=Unit(poi);
    }
    return poi;
}

Node* Unit(Node* poi)//算数单元
{
    string newString="";
    funcstring="";
    if(poi->type==0)//判断是否是标识符
    {      SYNBLp=SYNBLHead[rangenum];
                               while(strcmp(SYNBLp->content,poi->content)!=0&&SYNBLp->next!=NULL)
                                {SYNBLp=SYNBLp->next; }
                                if(SYNBLp->type==" ")
                                {   SYNBLp=SYNBLHead[0];
                                    while(strcmp(SYNBLp->content,poi->content)!=0&&SYNBLp->next!=NULL)
                                    {
                                        SYNBLp=SYNBLp->next;
                                    }
                                        if(SYNBLp->type==" "||strcmp(SYNBLp->content,poi->content)!=0)
                                    {printf("调用未定义变量"); exit(0);}}

         newString=poi->content;
         funcstring=poi->content;
        Next(infile);
        poi=poi->next;
        if(strcmp(poi->content,"[")==0)//判断是否是[
        {
            newString=newString+'[';
            Next(infile);
            poi=poi->next;
            if(poi->type==3)//判断是否是数字
            {
                newString=newString+(poi->content);
                Next(infile);
                poi=poi->next;
                if(strcmp(poi->content,"]")==0)//判断是否是]
                {
                    newString=newString+']';
                    Next(infile);
                    poi=poi->next;
                }
                 else
            {
                error();
            }
        }  else
            {
                error();
            }
              }

                else

                {
                   if(strcmp(poi->content,"(")==0)//判断是否是(
                    {  string funcflag=SYNBLp->content;

                            Next(infile);
                            poi=poi->next;
                            if(strcmp(poi->content,")")!=0)
                            { SEND("TEM","_","_",funcflag);
                                poi=ArimeticExpression(poi);
                            SEND("value","_","_",funcstring);
                            if(strcmp(poi->content,",")==0)
                             {
                            do
                            { Next(infile);
                              poi=poi->next;
                                poi=ArimeticExpression(poi);
                            SEND("value","_","_",funcstring);
                            } while (strcmp(poi->content,",")==0);}}
                            //判断是否是,
                             if(strcmp(poi->content,")")==0)//判断是否是)
                              {SEND("call","_","_",funcflag);
                                   Next(infile);
                                  poi=poi->next;
                              }else  error();


                    }
                }


    }
    else if ((poi->type==1)||(poi->type==2)||(poi->type==3))//常量
    {
        newString=poi->content;
        funcstring=poi->content;
        Next(infile);
        poi=poi->next;
    }

    else if(strcmp(poi->content,"(")==0)
    {
        Next(infile);
        poi=poi->next;
        poi=LogicStatement(poi);
        if(strcmp(poi->content,")")==0)
        {
            Next(infile);
            poi=poi->next;
            return poi;
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
    SEM.push(newString);
    return poi;
}


struct Active//变量活跃信息
{
   string q;
   bool qac;
};
string RDL;
struct ObjectCode
{
    int id;//标号
    string operation;//操作指令
    string dest;//目的操作数
    string source;//源操作数
};
vector<ObjectCode>_code;//目标代码存储区
stack<int>Sem;//语义栈
void CODE(string operation,string dest,string source)//送目标代码到存储区
{
    ObjectCode temOb;
    temOb.id=_code.size();
    temOb.operation=operation;
    temOb.dest=dest;
    temOb.source=source;
    _code.push_back(temOb);
}
void BACK(int Pi,int Pk)//把Pk返填到Pi
{
    stringstream ss;
    string temdest;
    ss<<Pk;
    ss>>temdest;
    _code[Pi].source=temdest;
}
void DoubleOb(string operation,int rdl,int i,string RDL)//双目运算符
{
    if(RDL==" ")
    {
        CODE("LD","R",NewQt[i].second);
        CODE(operation,"R",NewQt[i].third);
    }
    else if(RDL==NewQt[i].second)
    {
        if(NewQt[i].secondac)
        {
            CODE("ST","R",NewQt[i].second);
        }
        CODE(operation,"R",NewQt[i].third);
    }
    else if(((operation=="ADD")||(operation=="MUL")||(operation=="AND")||(operation=="OR")||(operation=="NE")||(operation=="EQ"))&&(RDL==NewQt[i].third))
    {
        if(NewQt[i].thirdac)
        {
            CODE("ST","R",NewQt[i].third);
        }
        CODE(operation,"R",NewQt[i].second);
    }
    else
    {
        if((rdl!=-1)&&(NewQt[rdl].fourthac))
        {
            CODE("ST","R",RDL);
        }
        CODE("LD","R",NewQt[i].second);
        CODE(operation,"R",NewQt[i].third);
    }
}
void SingleOb(int rdl,int i,string RDL)//单目运算符
{
    if(RDL==" ")
    {
        CODE("LD","R",NewQt[i].second);
    }
    else if(RDL==NewQt[i].second)
    {
        if(Qt[i].secondac)
        {
            CODE("ST","R",NewQt[i].second);
        }
    }
    else
    {
        if((rdl!=-1)&&(NewQt[rdl].fourthac))
        {
            CODE("ST","R",RDL);
        }
        CODE("LD","R",NewQt[i].second);
    }
}
void ObjectCodeGeneration(int dstart,int dend)//生成目标代码
{
    string RDL=" ";//寄存器状态
    int rdl=-1;
    int i;//当前处理的四元式
    int pi;
    for(i=dstart;i<dend;i++)
    {
        if((NewQt[i].first=="+")&&(NewQt[i].third!=" "))//处理加法
        {
            DoubleOb("ADD",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if((NewQt[i].first=="-")&&(NewQt[i].third!=" "))//处理减法
        {
            DoubleOb("SUB",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="*")
        {
            DoubleOb("MUL",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="/")
        {
            DoubleOb("DIV",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="%")
        {
            DoubleOb("MOD",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="&&")
        {
            DoubleOb("AND",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="||")
        {
            DoubleOb("OR",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first==">=")
        {
            DoubleOb("GE",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first==">")
        {
            DoubleOb("GT",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="<=")
        {
            DoubleOb("LE",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="<")
        {
            DoubleOb("LT",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="!=")
        {
            DoubleOb("NE",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="==")
        {
            DoubleOb("EQ",rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="+")
        {
            SingleOb(rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="=")
        {
            SingleOb(rdl,i,RDL);
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="-")
        {
            if(RDL==" ")
            {
                CODE("LD","R",NewQt[i].second);
                CODE("NEG"," ","R");
            }
            else if(RDL==NewQt[i].second)
            {

                CODE("ST","R",NewQt[i].second);
                CODE("NEG"," ","R");
            }
            else
            {
                if((rdl!=-1)&&(NewQt[rdl].fourthac))
                {
                    CODE("ST","R",RDL);
                }
                CODE("LD","R",NewQt[i].second);
                CODE("NEG"," ","R");
            }
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="!")
        {
            if(RDL==" ")
            {
                CODE("LD","R",NewQt[i].second);
                CODE("NO"," ","R");
            }
            else if(RDL==NewQt[i].second)
            {
                if(NewQt[i].secondac)
                {
                    CODE("ST","R",NewQt[i].second);
                }
                CODE("NO"," ","R");
            }
            else
            {
                if((rdl!=-1)&&(NewQt[rdl].fourthac))
                {
                    CODE("ST","R",RDL);
                }
                CODE("NO"," ","R");
                CODE("LD","R",NewQt[i].second);
            }
            RDL=NewQt[i].fourth;
            rdl=i;
        }
        else if(NewQt[i].first=="if")
        {
            if(RDL==" ")
            {
                CODE("LD","R",NewQt[i].second);
                Sem.push(_code.size());
                CODE("FJ"," ","R");
            }
            else if(RDL==NewQt[i].second)
            {
                if(NewQt[i].secondac)
                {
                    CODE("ST","R",NewQt[i].second);
                }
                Sem.push(_code.size());
                //cout<<_code.size()<<endl;
                CODE("FJ"," ","R");
                RDL=" ";
            }
            else
            {
                if((rdl!=-1)&&(NewQt[rdl].fourthac))
                {
                    CODE("ST","R",RDL);
                }
                CODE("LD","R",NewQt[i].second);
                Sem.push(_code.size());
                CODE("FJ"," ","R");
                RDL=" ";
            }
        }
        else if(NewQt[i].first=="el")
        {
            if((RDL!=" ")&&(rdl!=-1)&&(NewQt[rdl].fourthac))
            {
                CODE("ST","R",RDL);
            }
            pi=Sem.top();
            Sem.pop();
            BACK(pi,_code.size()+1);
            Sem.push(_code.size());
            //cout<<_code.size()<<endl;
            CODE("JMP"," "," ");
        }
        else if(NewQt[i].first=="ie")
        {
            if((RDL!=" ")&&(rdl!=-1)&&(NewQt[rdl].fourthac))
            {
                CODE("ST","R",RDL);
            }
            pi=Sem.top();
            Sem.pop();
            BACK(pi,_code.size());
        }
        else if(NewQt[i].first=="wh")
        {
            Sem.push(_code.size());
        }
        else if(NewQt[i].first=="do")
        {
            if(RDL==" ")
            {
                CODE("LD","R",NewQt[i].second);
                Sem.push(_code.size());
                CODE("FJ"," ","R");
            }
            else if(RDL==NewQt[i].second)
            {
                if(NewQt[i].secondac)
                {
                    CODE("ST","R",NewQt[i].second);
                }
                Sem.push(_code.size());
                CODE("FJ"," ","R");
                RDL=" ";
            }
            else
            {
                if((rdl!=-1)&&(NewQt[rdl].fourthac))
                {
                    CODE("ST","R",RDL);
                }
                CODE("LD","R",NewQt[i].second);
                Sem.push(_code.size());
                CODE("FJ"," ","R");
                RDL=" ";
            }
        }
        else if(NewQt[i].first=="we")
        {
            if((RDL!=" ")&&(rdl!=-1)&&(NewQt[rdl].fourthac))
            {
                CODE("ST","R",RDL);
            }
            RDL=" ";
            pi=Sem.top();
            Sem.pop();
            BACK(pi,_code.size()+1);
            pi=Sem.top();
            Sem.pop();
            stringstream ss;
            string temdest;
            ss<<pi;
            ss>>temdest;
            CODE("JMP"," ",temdest);
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
        }else if(NewQt[i].first=="func"){
            CODE(NewQt[i].fourth,"PROC"," ");//f PROC
        }else if(NewQt[i].first=="param"){
            CODE("POP","R"," ");//POP R
            CODE("ST","R",NewQt[i].fourth);//ST R,a 取值到地址
        }else if(NewQt[i].first=="re"){
            CODE("ST","R",RDL);
            RDL=" ";
            CODE("LD","R",NewQt[i].third);//LD R,a
            CODE("PUSH","R"," ");//PUSH R
            CODE("RET"," "," ");//RET
        } else if(NewQt[i].first=="END"){
            CODE("END"," "," ");//END
        }else if(NewQt[i].first=="value"){
            CODE("LD","R",NewQt[i].fourth);//LD R,a
            CODE("PUSH","R"," ");//PUSH R
        }else if(NewQt[i].first=="call"){
            CODE("CALL",NewQt[i].fourth," ");//call f
            CODE("POP","R"," ");//POP R
            CODE("LD","R",NewQt[i].fourth);//LD R,f
       PFINFLNode* PFINFLP=PFINFLHead->next;
        cout<<NewQt[i].first<<"     "<<NewQt[i].fourth<<endl;
        cout<<PFINFLP->OFF<<"     "<<PFINFLP->content<<endl;
       int i=1;
         while(SYNBLHead[i]==NULL||
         SYNBLHead[i]->next==NULL
      )
       {if(NewQt[i].fourth==PFINFLP->content){break;}
            i++;}
            SYNBLp2=SYNBLHead[i]->next;
    while(SYNBLp2!=NULL&&SYNBLp2->next!=NULL)

    {    //cout<<"("<<SYNBLHead[1]->content<<","<<SYNBLHead[1]->cat<<","<<SYNBLHead[1]->type<<")"<<endl;

        CODE("POP","R"," ");
        CODE("ST","R",SYNBLp2->content);//ST R,a 取值到地址
         SYNBLp2=SYNBLp2->next;
    }
    i++;
cout<<endl;
}else if(NewQt[i].first=="TEM"){
       PFINFLNode* PFINFLP=PFINFLHead->next;
        cout<<NewQt[i].first<<"     "<<NewQt[i].fourth<<endl;
        cout<<PFINFLP->OFF<<"     "<<PFINFLP->content<<endl;
   int i=1;
   while(SYNBLHead[i]==NULL||
         SYNBLHead[i]->next==NULL
      )
       {if(NewQt[i].fourth==PFINFLP->content){break;}
            i++;}
            SYNBLp2=SYNBLHead[i]->next;
    while(SYNBLp2!=NULL&&SYNBLp2->next!=NULL)

    {    //cout<<"("<<SYNBLHead[1]->content<<","<<SYNBLHead[1]->cat<<","<<SYNBLHead[1]->type<<")"<<endl;

        CODE("LD","R",SYNBLp2->content);//LD R,a 取值到寄存器
        CODE("PUSH","R"," ");
         SYNBLp2=SYNBLp2->next;
    }
    i++;
cout<<endl;
}
    }
}
void SendDivision(int dstart,int dend)//处理基本块
{
    vector<Active>Ac;
    Active act;
    int i,k;
    bool flagq2;
    bool flagq3;
    bool flagq4;
    for(i=dstart;i<dend;i++)
    {
        flagq2=true;
        flagq3=true;
        flagq4=true;
        if((NewQt[i].first=="el")||(NewQt[i].first=="ie")||(NewQt[i].first=="wh")||(NewQt[i].first=="we"))
        {
            continue;
        }
        if(Ac.size()==0)//如果当前数组为空，则先添加一个数据
        {
            act.q=NewQt[i].second;
            if(act.q.at(0)=='t')
            {
                act.qac=false;
            }
            else
            {
                act.qac=true;
            }
            Ac.push_back(act);
        }
        for(k=0;k<Ac.size();k++)
        {
            if((NewQt[i].second==" ")||(NewQt[i].second==Ac[k].q))
            {
                flagq2=false;
                break;
            }
        }
        if(flagq2)
        {
            act.q=NewQt[i].second;
            if(act.q.at(0)=='t')
            {
                act.qac=false;
            }
            else
            {
                act.qac=true;
            }
            Ac.push_back(act);
        }
        for(k=0;k<Ac.size();k++)
        {
            if((NewQt[i].third==" ")||(NewQt[i].third==Ac[k].q))
            {
                flagq3=false;
                break;
            }
        }
        if(flagq3)
        {
            act.q=NewQt[i].third;
            if(act.q.at(0)=='t')
            {
                act.qac=false;
            }
            else
            {
                act.qac=true;
            }
            Ac.push_back(act);
        }
        for(k=0;k<Ac.size();k++)
        {
            if((NewQt[i].fourth==" ")||(NewQt[i].fourth==Ac[k].q))
            {
                flagq4=false;
                break;
            }
        }
        if(flagq4)
        {
            act.q=NewQt[i].fourth;
            if(act.q.at(0)=='t')
            {
                act.qac=false;
            }
            else
            {
                act.qac=true;
            }
            Ac.push_back(act);
        }
    }
    int m;
    /*for(m=0; m<Ac.size(); m++)           //获取活跃信息
    {
        cout<<"("<<Ac[m].q<<","<<Ac[m].qac<<")"<<endl;
    }*/
    for(i=dend-1;i>=dstart;i--)
    {
        for(m=0; m<Ac.size(); m++)
        {
            if(NewQt[i].fourth==Ac[m].q)
            {
                NewQt[i].fourthac=Ac[m].qac;
                Ac[m].qac=false;
            }
            if((NewQt[i].second!=" ")&&(NewQt[i].second==Ac[m].q))
            {
                NewQt[i].secondac=Ac[m].qac;
                Ac[m].qac=true;
            }
            if((NewQt[i].third!=" ")&&(NewQt[i].third==Ac[m].q))
            {
                NewQt[i].thirdac=Ac[m].qac;
                Ac[m].qac=true;
            }
        }
    }
    /*cout<<endl;
    for(i=dstart;i<dend;i++)          //b.size()获取行向量的大小
    {
        cout<<"("<<Qt[i].first<<","<<Qt[i].second<<","<<Qt[i].secondac<<","<<Qt[i].third<<","<<Qt[i].thirdac<<","<<Qt[i].fourth<<","<<Qt[i].fourthac<<")"<<endl;
    }
    cout<<endl;*/
    ObjectCodeGeneration(dstart,dend);
}
void BlockDivision2()//基本块划分2
{
    int m,n;
    for(m=0,n=0;m<Qt.size();m++)
    {
        if((Qt[m].first=="if")||(Qt[m].first=="el")||(Qt[m].first=="ie")||(Qt[m].first=="do")||(Qt[m].first=="we")||(Qt[m].first=="we")||(Qt[m].first=="wh"))
        {
            SendDivision(n,m+1);
            n=m+1;
        }
    }
    SendDivision(n,m);
}
void BlockDivision()//基本块划分
{
    int m,n;
    for(m=0,n=0;m<Qt.size();m++)
    {
        if((Qt[m].first=="if")||(Qt[m].first=="el")||(Qt[m].first=="ie")||(Qt[m].first=="do")||(Qt[m].first=="we")||(Qt[m].first=="we")||(Qt[m].first=="wh"))
        {
            optimize(n,m+1);
            Generation(n,m+1);
            n=m+1;
        }
    }
    if(n < m){
        optimize(n,m);
        Generation(n,m);
    }
}
void BlockDivision3()//基本块划分3
{
    int m,n;
    for(m=0,n=0;m<NewQt.size();m++)
    {
        if((NewQt[m].first=="if")||(NewQt[m].first=="el")||(NewQt[m].first=="ie")||(NewQt[m].first=="do")||(NewQt[m].first=="we")||(NewQt[m].first=="we")||(NewQt[m].first=="wh"))
        {
            SendDivision(n,m+1);
            n=m+1;
        }
    }
    if(n < m){
        SendDivision(n,m);
    }
}
void OUTPUT_code()
{
    int m;
    for(m=0; m<_code.size(); m++)           //b.size()获取行向量的大小
    {
        cout<<"("<<_code[m].id<<","<<_code[m].operation<<","<<_code[m].dest<<","<<_code[m].source<<")"<<endl;
    }
}

void OutputObjectCode(){
    ofstream file("ObjectCode.txt");
       SYNBLNode* SYNBLp2=SYNBLHead[0];
 file<<"全局数据段"<<endl;
           while(SYNBLp2->next!=NULL)
    {    //cout<<"("<<SYNBLHead[1]->content<<","<<SYNBLHead[1]->cat<<","<<SYNBLHead[1]->type<<")"<<endl;
          SYNBLp2=SYNBLp2->next;
        if(strcmp(SYNBLp2->cat,"v")==0||strcmp(SYNBLp2->cat,"f")==0)
        {string longD="DB" ;
        if (SYNBLp2->type=="int") longD="DD" ;
            if (SYNBLp2->type=="float") longD="DT" ;
        file<<"("<<SYNBLp2->content<<","<<longD<<","<<"0"<<")"<<endl;}
        if(strcmp(SYNBLp2->cat,"a")==0)

        {string longD="DB" ;
         //cout<<"("<<AINFLHead->CTP<<","<<AINFLHead->CLEN<<","<<AINFLHead->UP<<")"<<endl;
         AINFLp2 =AINFLHead;
        for(int i=0;i<SYNBLp2->addr;i++)
             AINFLp2= AINFLp2->next;
        int  longa;
        longa= AINFLp2->UP;
        if (SYNBLp2->type=="int") longD="DD" ;
            if (SYNBLp2->type=="float") longD="DT" ;
        file<<"("<<SYNBLp2->content<<","<<longD<<","<<longa<<"DUP(0))"<<endl;}
    }
                 file <<"局部变量"<<endl;
                for(int i=0;i<t_value;i++)
    {
         file <<"("<<"t"<<i<<","<<"DT"<<","<<"0"<<")"<<endl;
    }
SYNBLp2=SYNBLHead[0];
   int i=1;
while(SYNBLHead[i]!=NULL&&SYNBLHead[i]->next!=NULL) {
        file<<"函数数据段"<<endl;
    while(SYNBLHead[i]!=NULL&&SYNBLHead[i]->next!=NULL)

    {    //cout<<"("<<SYNBLHead[1]->content<<","<<SYNBLHead[1]->cat<<","<<SYNBLHead[1]->type<<")"<<endl;
          SYNBLHead[i]=SYNBLHead[i]->next;
        if(strcmp(SYNBLHead[i]->cat,"v")==0||strcmp(SYNBLHead[i]->cat,"p")==0)
        {string longD="DB" ;
        if (SYNBLHead[i]->type=="int") longD="DD" ;
            if (SYNBLHead[i]->type=="float") longD="DT" ;
        file<<"("<<SYNBLHead[i]->content<<","<<longD<<","<<"0"<<")"<<endl;}
        if(strcmp(SYNBLHead[i]->cat,"a")==0)
        {string longD="DB" ;
         //cout<<"("<<AINFLHead->CTP<<","<<AINFLHead->CLEN<<","<<AINFLHead->UP<<")"<<endl;
        AINFLp2 =AINFLHead;
        for(int i=0;i<SYNBLHead[i]->addr;i++)
            AINFLp2=AINFLp2->next;
        int  longa;
    longa=AINFLp2->UP;
        if (SYNBLHead[i]->type=="int") longD="DD" ;
            if (SYNBLHead[i]->type=="float") longD="DT" ;
       file<<"("<<SYNBLHead[i]->content<<","<<longD<<","<<longa<<"DUP(0))"<<endl;
    }

    }
    i++;
cout<<endl;
             }
	for (int p = 0; p < _code.size(); p++) {
		file << _code[p].id << '\t' << _code[p].operation << '\t' << _code[p].dest << '\t' << _code[p].source << '\t' << endl;
	}
	file.close();
}


int main()
{
    t_value=0;
    initNode();
PFINFLp2=PFINFLHead;
AINFLp2 =AINFLHead;
SYNBLp=SYNBLHead[0];
SYNBLNode* P=SYNBLHead[1];
    char filename[30];
    Node * poi = Head;
    printf("请输入要进行语法分析的C语言程序：\n");
    //scanf("%s",filename);
    infile = fopen("b.txt","r");
     while(!infile)
    {
        printf("打开文件失败！\n");
        return 0;
    }
        poi=Start(poi);
            if(k==0)
    {   printtable();
        cout<<"语法正确"<<endl;
        OUTPUT2();
        cout<<'\n';
        BlockDivision();
       OUTPUT();
       BlockDivision3();
        OUTPUT_code();
    }

    else cout<<"语法错误"<<endl;
        printtoken();
        OutputQt();
        OutputNewQt();
        OutputObjectCode();
        delete SYNBLHead;
        delete AINFLHead;
        delete PARAMLHead;
        delete PFINFLHead;
        delete Head;






}
