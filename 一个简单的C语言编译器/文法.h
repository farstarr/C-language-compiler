Node *Start(Node *  poi)
{
        Next(infile);
        poi = poi->next;
       poi=Program(poi);//���� ���� �ӳ���
        poi=TheSubsequentProgram(poi);//���� ��̳��� �ӳ���
    return  poi;
}

Node *TheSubsequentProgram(Node *  poi)
{
    if(poi->type==45);//�ж�#
    else {
         poi=Program(poi); //���� ���� �ӳ���
          poi=TheSubsequentProgram(poi); //���� ��̳��� �ӳ���

    }
    return poi;
}


Node *Program(Node *  poi)
{
    if(poi->type==4||poi->type==7)//�ж�int ��void
    {
         Next(infile);
        poi = poi->next;
        if(poi->type==17)//�ж�main
        {
              Next(infile);
              poi = poi->next;
              if(poi->type==38)//�жϣ�
            {       Next(infile);
                poi = poi->next;
                if(poi->type==39)//�жϣ�
                {
                    Next(infile);
                    poi = poi->next;
                    if(poi->type==42)//�ж�{
                    {
                     Next(infile);
                    poi = poi->next;
                    poi=CompoundStatement(poi);//���� ������� �ӳ���
                    return  poi;
                    }
                    else error();
                }
                else error();
            }
            else error();

        }else { if(poi->type==0)//�жϱ�ʶ��
                {
                    Next(infile);
                    poi = poi->next;
                     if(poi->type==38)//�жϣ�
                     {
                         Next(infile);
                        poi = poi->next;
                        poi=ParametersList(poi);//���� �����б� �ӳ���
                        if(poi->type==39)//�жϣ�
                        {
                            Next(infile);
                            poi = poi->next;
                            if(poi->type==42)//�ж�{
                            {
                                    Next(infile);
                                    poi = poi->next;
                                    poi=CompoundStatement(poi);//���� ������� �ӳ���
                                    return  poi;
                            }else error();
                        }else error();
                     }else { if(poi->type==40)//�ж�[
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==3)//�ж�����
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 if(poi->type==41)//�ж�]
                                 {
                                     Next(infile);
                                     poi = poi->next;
                                     poi=ArrayAssignmentStatement(poi);//���� ���鸳ֵ��� �ӳ���
                                     poi=SubsequentArrayAssignmentStatement(poi);//���� ���鸳ֵ��� �ӳ���
                                     return poi;
                                 }else error();

                             }else error();
                         }else { if (poi->type==21)//�ж�=
                                   {
                                     Next(infile);
                                     poi = poi->next;
                                     if (poi->type==1||poi->type==2||poi->type==3)//�ж��ַ����ַ��������֣���������
                                         {
                                             Next(infile);
                                             poi = poi->next;
                                             poi=SubsequentVariableDeclarations(poi);//���� ��̱������� �ӳ���
                                             return poi;
                                         }else {
                                                poi=ArithmeticExpression(poi);//���� �������ʽ �ӳ���
                                                poi=SubsequentVariableDeclarations(poi);//���� ��̱������� �ӳ���
                                                    return poi;
                                                }
                                   }   else {
                                                Next(infile);
                                                poi = poi->next;
                                                poi=SubsequentVariableDeclarations(poi);//���� ��̱������� �ӳ���
                                                    return poi;
                                                }

                                }//�ж�=
                     }//�ж�[

                }else error();

                }//�жϱ�ʶ��
    } else { if (poi->type==5||poi->type==9||poi->type==11)//�ж�bool float char
              {
                   Next(infile);
                   poi = poi->next;
                    if (poi->type==0)//�жϱ�ʶ��
                    {
                        Next(infile);
                        poi = poi->next;
                        if(poi->type==38)//�жϣ�
                        {
                            Next(infile);
                            poi = poi->next;
                            poi=ParametersList(poi);//���� �����б� �ӳ���
                            if(poi->type==39)//�жϣ�
                            {
                                Next(infile);
                                poi = poi->next;
                                    if(poi->type==42)//�ж�{
                                    {
                                         Next(infile);
                                         poi = poi->next;
                                         poi=CompoundStatement(poi);//���� ������� �ӳ���
                                         return  poi;
                                    } else error();
                                }else error();
                        }else { if(poi->type==40)//�ж�[
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==3)//�ж�����
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 if(poi->type==41)//�ж�]
                                 {
                                     Next(infile);
                                     poi = poi->next;
                                     poi=ArrayAssignmentStatement(poi);//���� ���鸳ֵ��� �ӳ���
                                     poi=SubsequentArrayAssignmentStatement(poi);//���� ������鸳ֵ��� �ӳ���
                                     return poi;
                                 }else error();

                             }else error();
                         }//�ж�[
                  else { if (poi->type==21)//�ж�=
                                   {
                                     Next(infile);
                                     poi = poi->next;
                                     if (poi->type==1||poi->type==2||poi->type==3)//�ж��ַ����ַ��������֣���������
                                         {
                                             Next(infile);
                                             poi = poi->next;
                                             poi=SubsequentVariableDeclarations(poi);//���� ��̱������� �ӳ���
                                             return poi;
                                         }else {
                                                poi=ArithmeticExpression(poi);//���� �������ʽ �ӳ���
                                                poi=SubsequentVariableDeclarations(poi);//���� ��̱������� �ӳ���
                                                    return poi;
                                                }
                                   }   else {
                                                Next(infile);
                                                poi = poi->next;
                                                poi=SubsequentVariableDeclarations(poi);//���� ��̱������� �ӳ���
                                                    return poi;
                                                }

              }


}
    } else error();
                    } else error();
                    }
                    }



Node *CompoundStatement(Node *  poi) //�������
{
    poi=TheStatementlist(poi); //���� ����б� �ӳ���
    if(poi->type==43)//�ж�}
    {
        Next(infile);
        poi = poi->next;
        return poi;
    }
    else error();
}



Node *TheStatementList(Node *  poi) //����б�
{
    if(poi->type==12)//�ж�if
    {
         Next(infile);
         poi = poi->next;
         if(poi->type==38)//�жϣ�
         {
             Next(infile);
             poi = poi->next;
             poi=LogicStatement(poi); //���� �߼���� �ӳ���
                if(poi->type==39)//�жϣ�
                {
                     Next(infile);
                     poi = poi->next;
                     if(poi->type==42)//�ж�{
                     {
                         Next(infile);
                         poi = poi->next;
                         poi=CompoundStatement(poi); //���� ������� �ӳ���
                         if(poi->type==13)//�ж�else
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==42)//�ж�{
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 poi=CompoundStatement(poi); //���� ������� �ӳ���
                                 poi=TheStatementList(poi); //���� ����б� �ӳ���
                                 return poi;
                             }else{
                                 poi=Statement(poi); //���� ��� �ӳ���
                                 poi=TheStatementList(poi); //���� ����б� �ӳ���
                                 return poi;
                             }
                         }else {
                             poi=TheStatementList(poi); //���� ����б� �ӳ���
                                 return poi;
                         }

                     }else {
                         poi=Statement(poi); //���� ��� �ӳ���
                             if(poi->type==13)//�ж�else
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==42)//�ж�{
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 poi=CompoundStatement(poi); //���� ������� �ӳ���
                                 poi=TheStatementList(poi); //���� ����б� �ӳ���
                                 return poi;
                             }else{
                                 poi=Statement(poi); //���� ��� �ӳ���
                                 poi=TheStatementList(poi); //���� ����б� �ӳ���
                                 return poi;
                             }
                         }else {
                             poi=TheStatementList(poi); //���� ����б� �ӳ���
                                 return poi;
                         }
                     }
                }else error();
         }else error();
    }else {
         if(poi->type==14)//�ж�while
    {
         Next(infile);
         poi = poi->next;
         if(poi->type==38)//�жϣ�
         {
             Next(infile);
             poi = poi->next;
             poi=LogicStatement(poi); //���� �߼���� �ӳ���
                if(poi->type==39)//�жϣ�
                {
                     Next(infile);
                     poi = poi->next;
                     if(poi->type==38)//�жϣ�
                     {
                         Next(infile);
                         poi = poi->next;
                         poi=CompoundStatement(poi); //���� ������� �ӳ���
                         poi=TheStatementList(poi); //���� ����б� �ӳ���
                         return poi;
                     }else {
                          poi=Statement(poi); //���� ��� �ӳ���
                          poi=TheStatementList(poi); //���� ����б� �ӳ���
                          return poi;
                     }
    }else error();
}else error();
    }else{
        if(poi->type==18)//�ж�return
        {
            Next(infile);
            poi = poi->next;
            if(poi->type==0)//�жϱ�ʶ��
            {
                Next(infile);
                poi = poi->next;
                if(poi->type==37)//�ж�;
                {
                     Next(infile);
                     poi = poi->next;
                     poi=TheStatementList(poi); //���� ����б� �ӳ���
                     return poi;
                }else error();
            }else {
                if(poi->type==5||poi->type==9||poi->type==11)//�жϳ���
                {
                    Next(infile);
                poi = poi->next;
                if(poi->type==37)//�ж�;
                {
                     Next(infile);
                     poi = poi->next;
                     poi=TheStatementList(poi); //���� ����б� �ӳ���
                     return poi;
                }else error();
                }else error();
            }
        }
        else {
              if(poi->type==0)//�жϱ�ʶ��
              {
                   Next(infile);
                   poi = poi->next;
                   if(poi->type==25)//�ж�=
                   {
                       Next(infile);
                       poi = poi->next;
                       if(poi->type==5||poi->type==9||poi->type==11)//�жϳ���
                       {
                            Next(infile);
                            poi = poi->next;
                             poi=SubsequentVariableDeclarations(poi); //���� ��̱������� �ӳ���
                             poi=TheStatementList(poi); //���� ����б� �ӳ���
                             return poi;
                       }else {
                           poi=ArithmeticExpression(poi);//���� �������ʽ �ӳ���
                            poi=SubsequentVariableDeclarations(poi); //���� ��̱������� �ӳ���
                             poi=TheStatementList(poi); //���� ����б� �ӳ���
                             return poi;
                       }

                   }else error();
              }else {
                  if(poi->type==7||poi->type==5||poi->type==9||poi->type==11)//�ж�char int bool float
                  {
                      Next(infile);
                      poi = poi->next;
                      if(poi->type==40)//�ж�[
                      {
                          Next(infile);
                          poi = poi->next;
                          if(poi->type==3)//�ж�����
                          {
                              Next(infile);
                              poi = poi->next;
                              if(poi->type==41)//�ж�]
                              {
                                  poi=ArrayAssignmentStatement(poi);//���� ���鸳ֵ��� �ӳ���
                                  poi=SubsequentArrayAssignmentStatement(poi);//���� ������鸳ֵ��� �ӳ���
                                  poi=TheStatementList(poi); //���� ����б� �ӳ���
                                  return poi;
                              }else error();
                          }else error();
                      }else {
                          if(poi->type==25)//�ж�=
                          {
                               Next(infile);
                               poi = poi->next;
                               if(poi->type==1||poi->type==2||poi->type==3)//�жϳ���
                               {
                                    Next(infile);
                                    poi = poi->next;
                                    poi=SubsequentVariableDeclarations(poi); //���� ��̱������� �ӳ���
                                    poi=TheStatementList(poi); //���� ����б� �ӳ���
                                    return poi;
                               }else{
                                    poi=ArithmeticExpression(poi);//���� �������ʽ �ӳ���
                                    poi=SubsequentVariableDeclarations(poi); //���� ��̱������� �ӳ���
                                    poi=TheStatementList(poi); //���� ����б� �ӳ���
                                    return poi;
                               }
                          }else{
                                    poi=SubsequentVariableDeclarations(poi); //���� ��̱������� �ӳ���
                                    poi=TheStatementList(poi); //���� ����б� �ӳ���
                                    return poi;
                          }

                      }

                  }
              }
        }
    }
