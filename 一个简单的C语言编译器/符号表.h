#include "string"
#include <fstream>
using namespace std;

int rangenum=0;
int oldrange=0;
/*struct TYPELNode//���ͱ�
{
    char TVAL;//����
    char TPOINT;//ָ��
    int TPOINT_num;
    TYPELNode* next;//��һ���ڵ�
};
TYPELNode* TYPELHead;//�׽ڵ�*/

struct SYNBLNode//�����ܱ�
{
    char content[30];//���ݣ����֣�
    string type;//����
    char cat[3];//����
    int addr;//��ַ
    char active;
    SYNBLNode* next;//��һ���ڵ�
};
SYNBLNode* SYNBLHead[50];//�׽ڵ�

SYNBLNode* SYNBLp2;
struct AINFLNode//�����
{
    int LOW;//�����½�
    int UP;//�����Ͻ�
    string  CTP;//�ɷ�
    int CLEN; //�ɷ����͵ĳ���
    AINFLNode* next;//��һ���ڵ�
};
AINFLNode * AINFLHead;//�׽ڵ�
AINFLNode * AINFLPn;

/*struct RINFLNode//�ṹ��
{   char ID[30];//�ṹ������
    int OFF;//���ࡪ��idk��ֵ��Ԫ��ַ��������ڼ�¼ֵ����ͷλ�ã�
    TYPELNode*  TP;//��ɷ�����ָ��
    RINFLNode* next;//��һ���ڵ�
};
RINFLNode * RINFLHead;//�׽ڵ�*/


 struct PARAMLNode//������
{   char content[30];//���ݣ����֣�
    string type;//����
    char cat[3];//����
    int addr_num;//��ַ
    PARAMLNode* next;//��һ���ڵ�
};
 PARAMLNode *  PARAMLHead;//�׽ڵ�


struct PFINFLNode//������
{   string content;
    int OFF;//����C�ù���������������ʼ��Ԫ��Ըù���ֵ����ͷλ��
    int FN;//��������
    PARAMLNode*  PARAM;//��ɷ�����ָ��
    int ENTRY;//�ú���Ŀ������׵�ַ
    PFINFLNode* next;//��һ���ڵ�
};
 PFINFLNode *  PFINFLHead;//�׽ڵ�

PFINFLNode* PFINFLP;


// int    LENL[100];
void printtable()
{
    SYNBLp2=SYNBLHead[0];
    ofstream file("���ű�.txt");
     file<<"************************************���ñ�ʶ����******************************"<<endl<<endl;
    file<<setw(30)<<"����"<<"\t"<<"����"<<"\t"<<"����"<<"\t"<<"��ַ"<<"\t"<<endl;
    while( SYNBLp2->next!=NULL)
    {
         SYNBLp2=SYNBLp2->next;
    file<<setw(30)<<SYNBLp2->content<<"\t"<<SYNBLp2->type<<"\t"<<SYNBLp2->cat<<"\t"<<SYNBLp2->addr<<"\t"<<endl;
    }
    file<<endl<<endl;
    int i=1;
    while (SYNBLHead[i]!=NULL&&SYNBLHead[i]->next!=NULL) {
    SYNBLp2=SYNBLHead[i];
     file<<"************************************������ʶ����"<<i<<"******************************"<<endl<<endl;
    file<<setw(30)<<"����"<<"\t"<<"����"<<"\t"<<"����"<<"\t"<<"��ַ"<<"\t"<<endl;
    while( SYNBLp2->next!=NULL)
    {
         SYNBLp2=SYNBLp2->next;
    file<<setw(30)<<SYNBLp2->content<<"\t"<<SYNBLp2->type<<"\t"<<SYNBLp2->cat<<"\t"<<SYNBLp2->addr<<"\t"<<endl;
    }
    file<<endl<<endl;
    PFINFLP=PFINFLHead;
    i++;
    }
     file<<"************************************������******************************"<<endl<<endl;
    file<<setw(30)<<"����"<<"\t"<<"��������"<<"\t"<<"\t"<<endl;
    while(PFINFLP->next!=NULL)
    {
         PFINFLP=PFINFLP->next;
    file<<setw(30)<<PFINFLP->OFF<<"\t"<<PFINFLP->FN<<"\t"<<"\t"<<endl;
    }
file<<endl<<endl;

    AINFLPn=AINFLHead;
    file<<"************************************�����******************************"<<endl<<endl;
    file<<setw(30)<<"����"<<"\t"<<"�ɷ�����"<<"\t"<<"�ɷָ���"<<"\t"<<endl;
    while(AINFLPn->next!=NULL)
    {
    AINFLPn=AINFLPn->next;
    file<<setw(30)<<AINFLPn->CLEN<<"\t"<<AINFLPn->CTP<<"\t"<<AINFLPn->UP<<"\t"<<endl;
    }
file<<endl<<endl;

    file.close();
}



