
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<vector>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include "���ű�.h"
#define IDENTIFER 99
using namespace std;
int static_iden_number = 0;

  const char * KT[] = {"void","char","short","int","long","float","double","bool","if","else","while","do","for","main","return"};
  const char * PT[] = {">=","<=","==","!=",">","<","=","&&","||","!","+","-","*","/","%","<<",">>",",",";","(",")","[","]","{","}",".","#" };


   struct Node//token�ڵ�
{
    char content[30];//����
    int type;//�ֱ���
    int addr;//��ڵ�ַ
    Node * next;//��һ���ڵ�
};Node * Head;
//��־���ڵ�

   struct QtNode//��Ԫʽ�ڵ�
{
   string first;
   bool firstac;
   string second;
   bool secondac;
    string third;
   bool thirdac;
    string fourth;
   bool fourthac;
};
//��־���ڵ�
vector<QtNode>Qt;
int t_value;//�м����ֵ

void initNode()
{
    Head = new Node();//��ʼ��token
    strcpy(Head->content,"");
    Head->type = -1;
    Head->addr = -1;
    Head->next = NULL;


    SYNBLHead[0]= new SYNBLNode();//��ʼ�������ܱ�
    strcpy(SYNBLHead[0]->content,"");
    SYNBLHead[0]->type = " ";
    strcpy(SYNBLHead[0]->cat,"");
    SYNBLHead[0]->addr=0;
    SYNBLHead[0]->active=' ';
    SYNBLHead[0]->next=NULL;

    /*TYPELHead= new TYPELNode();//��ʼ�����ͱ�
    TYPELHead->TVAL=' ';
    TYPELHead->TPOINT=' ';
     TYPELHead->TPOINT_num=0;
     TYPELHead->next=NULL;*/

     AINFLHead= new AINFLNode();//��ʼ�������
     AINFLHead->LOW=0;
     AINFLHead->UP=0;
     AINFLHead->CTP== " ";
     AINFLHead->next=NULL;
     AINFLHead->CLEN=0;

       PFINFLHead=new PFINFLNode();//��ʼ��������
     PFINFLHead->OFF=0;
     PFINFLHead->FN=0;
     PFINFLHead->PARAM=NULL;
     PFINFLHead->ENTRY=0;
     PFINFLHead->next=NULL;

     /*RINFLHead= new RINFLNode();//��ʼ���ṹ��
      strcpy( RINFLHead->ID,"");
     RINFLHead->OFF=0;
     RINFLHead->TP=NULL;
     RINFLHead->next=NULL;*/

}
void initSYNBL(int i)
{
    SYNBLHead[i]= new SYNBLNode();//��ʼ�������ܱ�
    strcpy(SYNBLHead[i]->content,"");
    SYNBLHead[i]->type = " ";
    strcpy(SYNBLHead[1]->cat,"");
    SYNBLHead[i]->addr=0;
    SYNBLHead[i]->active=' ';
    SYNBLHead[i]->next=NULL;


}

void initPARAML(PARAMLNode* PARAMLHead)
{
       PARAMLHead=new PARAMLNode();//��ʼ��������
       strcpy(SYNBLHead[rangenum]->content,"");
       SYNBLHead[rangenum]->type = " ";
       strcpy(SYNBLHead[rangenum]->cat," ");
       SYNBLHead[rangenum]->addr=0;
       SYNBLHead[rangenum]->active=' ';
       SYNBLHead[rangenum]->next=NULL;

}

int seekKT(char * word)
{
    for(int i=0; i<15; i++)
    {
        if(strcmp(word,KT[i]) == 0)
        {
            return i+4;
        }
    }
    return 99;
}


int seekPT(char * word)
{
    for(int i=0; i<27; i++)
    {
        if(strcmp(word,PT[i]) == 0)
        {
            return i+19;
        }
    }
    return 99;
}


void createNewNode(char * content,int type,int addr)
{
    Node * p = Head;
    Node * temp = new Node();

    while(p->next!=NULL)
    {
        p = p->next;
    }

    strcpy(temp->content,content);
    temp->type = type;
    temp->addr = addr;
    temp->next = NULL;
    p->next = temp;
}


int createSYNBLNode(char * content,int type,int addr)
{
    SYNBLNode * p = SYNBLHead[rangenum];
    int flag = 0;
    int i=0;
    int addr_temp = -2;
    while(p->next!=NULL)
    {   i++;
        if(strcmp(content,p->next->content)==0)
        {
            flag = 1;
            addr_temp = i;
        }
        p = p->next;
    }
    if(flag == 0)
    {  SYNBLNode * temp = new SYNBLNode();
        addr_temp = ++static_iden_number;//��������ģ����ڵ�ַ
    strcpy(temp->content,content);
    temp->type = " ";
    strcpy(temp->cat,"");
    temp->addr=0;
    temp->next = NULL;
    p->next = temp;}

    return addr_temp;
}
void Next(FILE * infile)
{     char array[30];
    char ch;
    char * word;
    int i=0;
          do
     {
         ch = fgetc(infile);
     }while(ch==' '||ch=='\n'||ch=='\r'||ch=='\t');

        //����ĸ�����»��߿�ͷ,����ؼ��ֻ��߱�ʶ��
        if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || ch == '_')
        {
            while((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||(ch>='0' && ch<='9') || ch == '_')
            {
                array[i++] = ch;
                ch = fgetc(infile);
            }
            word = new char[i+1];
            memcpy(word,array,i);
            word[i] = '\0';
            int seekTemp = seekKT(word);
             if(seekTemp!=99)
            {
                createNewNode(word,seekTemp,-1);
            }
            else
            {
                int addr_tmp = createSYNBLNode(word,seekTemp,-1);
                createNewNode(word,0,addr_tmp);
            }
            fseek(infile,-1L,SEEK_CUR);//������һλ
        }
        //�����ֿ�ͷ����������
        else if(ch >='0' && ch<='9')
        {
            int flag = 0;
            int flag2 = 0;
            //��������
            while(ch >='0' && ch<='9')
            {
                array[i++] = ch;
                ch = fgetc(infile);
            }
            //����float
            if(ch == '.')
            {
                flag2 = 1;
                array[i++] = ch;
                ch = fgetc(infile);
                if(ch>='0' && ch<='9')
                {
                    while(ch>='0' && ch<='9')
                    {
                        array[i++] = ch;
                        ch = fgetc(infile);
                    }
                }}
                //�����ѧ������
                 if (ch == 'e')
                {
                    flag = 1;
                      array[i++] = ch;
                       ch = fgetc(infile);
                      if(ch=='+'||ch=='-')
                      {
                array[i++] = ch;
                ch = fgetc(infile);
                      }
                if(ch>='0' && ch<='9')
                {
                    while(ch>='0' && ch<='9')
                    {
                        array[i++] = ch;
                        ch = fgetc(infile);
                    }

                }
                }

            word = new char[i+1];
            memcpy(word,array,i);
            word[i] = '\0';
                if(flag2 == 0)
                {
                    createNewNode(word,3,-1);
                }
                else
                {
                    createNewNode(word,3,-1);
                }

            fseek(infile,-1L,SEEK_CUR);//������һλ
    }
     //�����ַ�����
       else if(ch=='\'' )

          {
            array[i++] = ch;
            ch = fgetc(infile);
            if(ch=='\\' )
           {
             do
            {
                array[i++] = ch;
                ch = fgetc(infile);
            }while(ch>='0' && ch<='9');}
           else {
               array[i++] = ch;
                ch = fgetc(infile);
           }
           if(ch=='\'')
             {array[i++] = ch;
                ch = fgetc(infile);}
                else { cout<<"tokenc����"<<endl;
                        exit(0);
                }//�쳣����
            word = new char[i+1];
            memcpy(word,array,i);
            word[i] = '\0';

                createNewNode(word,1,-1);
                 fseek(infile,-1L,SEEK_CUR);//������һλ
            }

 //�����ַ�������
       else if(ch=='"' )
        {
            array[i++] = ch;
            ch = fgetc(infile);
            while(ch!='"')
            {
                array[i++] = ch;
                ch = fgetc(infile);
            }
             array[i++] = ch;
                ch = fgetc(infile);
            word = new char[i+1];
            memcpy(word,array,i);
            word[i] = '\0';

                createNewNode(word,2,-1);
                 fseek(infile,-1L,SEEK_CUR);//������һλ
            }

        //���
   else  if((ch>=';' && ch<='>') || (ch>='(' && ch<='/') ||(ch >= '{'&& ch <= '}')|| ch == '%'|| ch == '['|| ch == ']' || ch == '&'  || ch == '#' || ch == '!')
    {
        array[i++] = ch;
        if(ch == '='||ch == '<'||ch == '>'||ch == '!')
        {ch = fgetc(infile);
          if(ch == '=')
            {
                array[i++] = ch;
                ch = fgetc(infile);
    }}
    else if(ch == '<')
        {ch = fgetc(infile);
          if(ch == '<')
            {
                array[i++] = ch;
                ch = fgetc(infile);
    }}
        else if(ch == '>')
        {ch = fgetc(infile);
          if(ch == '>')
            {
                array[i++] = ch;
                ch = fgetc(infile);
    }}
        else if(ch == '<')
        {ch = fgetc(infile);
          if(ch == '<')
            {
                array[i++] = ch;
                ch = fgetc(infile);
    }}
       else if(ch == '&')
        {ch = fgetc(infile);
          if(ch == '&')
            {
                array[i++] = ch;
                ch = fgetc(infile);
    }}
      else if(ch == '|')
        {ch = fgetc(infile);
          if(ch == '|')
            {
                array[i++] = ch;
                ch = fgetc(infile);
    }}
    else    ch = fgetc(infile);
            word = new char[i+1];
            memcpy(word,array,i);
            word[i] = '\0';
            int seekTemp = seekPT(word);
      createNewNode(word,seekTemp,-1);
       fseek(infile,-1L,SEEK_CUR);
    }
      else { cout<<"token����"<<endl;
      exit(0);}


    }



void printtoken()
{

Node * p = Head;
    p = p->next;
 ofstream file("token.txt");
     file<<"************************************������******************************"<<endl<<endl;
    file<<setw(30)<<"����"<<"\t"<<"�ֱ���"<<"\t"<<"��ʶ����ַ"<<"\t"<<endl;
     while(p!=NULL)
    {
        if(p->type == IDENTIFER)
        {
            file<<setw(30)<<p->content<<"\t"<<p->type<<"\t"<<p->addr<<"\t"<<endl;
        }
        else
        {
             file<<setw(30)<<p->content<<"\t"<<p->type<<"\t"<<p->addr<<"\t"<<endl;
        }
        p = p->next;
    }
    file<<endl<<endl;
    file.close();
}
