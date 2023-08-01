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
    {
         Next(infile);
        poi = poi->next;
        if(poi->type==17)//判断main
        {
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
                    return  poi;
                    }
                    else error();
                }
                else error();
            }
            else error();

        }else { if(poi->type==0)//判断标识符
                {
                    Next(infile);
                    poi = poi->next;
                     if(poi->type==38)//判断（
                     {
                         Next(infile);
                        poi = poi->next;
                        poi=ParametersList(poi);//进入 参数列表 子程序
                        if(poi->type==39)//判断）
                        {
                            Next(infile);
                            poi = poi->next;
                            if(poi->type==42)//判断{
                            {
                                    Next(infile);
                                    poi = poi->next;
                                    poi=CompoundStatement(poi);//进入 复合语句 子程序
                                    return  poi;
                            }else error();
                        }else error();
                     }else { if(poi->type==40)//判断[
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==3)//判断数字
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 if(poi->type==41)//判断]
                                 {
                                     Next(infile);
                                     poi = poi->next;
                                     poi=ArrayAssignmentStatement(poi);//进入 数组赋值语句 子程序
                                     poi=SubsequentArrayAssignmentStatement(poi);//进入 数组赋值语句 子程序
                                     return poi;
                                 }else error();

                             }else error();
                         }else { if (poi->type==21)//判断=
                                   {
                                     Next(infile);
                                     poi = poi->next;
                                     if (poi->type==1||poi->type==2||poi->type==3)//判断字符，字符串，数字（即常量）
                                         {
                                             Next(infile);
                                             poi = poi->next;
                                             poi=SubsequentVariableDeclarations(poi);//进入 后继变量声明 子程序
                                             return poi;
                                         }else {
                                                poi=ArithmeticExpression(poi);//进入 算术表达式 子程序
                                                poi=SubsequentVariableDeclarations(poi);//进入 后继变量声明 子程序
                                                    return poi;
                                                }
                                   }   else {
                                                Next(infile);
                                                poi = poi->next;
                                                poi=SubsequentVariableDeclarations(poi);//进入 后继变量声明 子程序
                                                    return poi;
                                                }

                                }//判断=
                     }//判断[

                }else error();

                }//判断标识符
    } else { if (poi->type==5||poi->type==9||poi->type==11)//判断bool float char
              {
                   Next(infile);
                   poi = poi->next;
                    if (poi->type==0)//判断标识符
                    {
                        Next(infile);
                        poi = poi->next;
                        if(poi->type==38)//判断（
                        {
                            Next(infile);
                            poi = poi->next;
                            poi=ParametersList(poi);//进入 参数列表 子程序
                            if(poi->type==39)//判断）
                            {
                                Next(infile);
                                poi = poi->next;
                                    if(poi->type==42)//判断{
                                    {
                                         Next(infile);
                                         poi = poi->next;
                                         poi=CompoundStatement(poi);//进入 复合语句 子程序
                                         return  poi;
                                    } else error();
                                }else error();
                        }else { if(poi->type==40)//判断[
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==3)//判断数字
                             {
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
                  else { if (poi->type==21)//判断=
                                   {
                                     Next(infile);
                                     poi = poi->next;
                                     if (poi->type==1||poi->type==2||poi->type==3)//判断字符，字符串，数字（即常量）
                                         {
                                             Next(infile);
                                             poi = poi->next;
                                             poi=SubsequentVariableDeclarations(poi);//进入 后继变量声明 子程序
                                             return poi;
                                         }else {
                                                poi=ArithmeticExpression(poi);//进入 算术表达式 子程序
                                                poi=SubsequentVariableDeclarations(poi);//进入 后继变量声明 子程序
                                                    return poi;
                                                }
                                   }   else {
                                                Next(infile);
                                                poi = poi->next;
                                                poi=SubsequentVariableDeclarations(poi);//进入 后继变量声明 子程序
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
    poi=TheStatementlist(poi); //进入 语句列表 子程序
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
                     Next(infile);
                     poi = poi->next;
                     if(poi->type==42)//判断{
                     {
                         Next(infile);
                         poi = poi->next;
                         poi=CompoundStatement(poi); //进入 复合语句 子程序
                         if(poi->type==13)//判断else
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==42)//判断{
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 poi=CompoundStatement(poi); //进入 复合语句 子程序
                                 poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                             }else{
                                 poi=Statement(poi); //进入 语句 子程序
                                 poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                             }
                         }else {
                             poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                         }

                     }else {
                         poi=Statement(poi); //进入 语句 子程序
                             if(poi->type==13)//判断else
                         {
                             Next(infile);
                             poi = poi->next;
                             if(poi->type==42)//判断{
                             {
                                 Next(infile);
                                 poi = poi->next;
                                 poi=CompoundStatement(poi); //进入 复合语句 子程序
                                 poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                             }else{
                                 poi=Statement(poi); //进入 语句 子程序
                                 poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                             }
                         }else {
                             poi=TheStatementList(poi); //进入 语句列表 子程序
                                 return poi;
                         }
                     }
                }else error();
         }else error();
    }else {
         if(poi->type==14)//判断while
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
                     Next(infile);
                     poi = poi->next;
                     if(poi->type==38)//判断（
                     {
                         Next(infile);
                         poi = poi->next;
                         poi=CompoundStatement(poi); //进入 复合语句 子程序
                         poi=TheStatementList(poi); //进入 语句列表 子程序
                         return poi;
                     }else {
                          poi=Statement(poi); //进入 语句 子程序
                          poi=TheStatementList(poi); //进入 语句列表 子程序
                          return poi;
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
                if(poi->type==5||poi->type==9||poi->type==11)//判断常量
                {
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
        else {
              if(poi->type==0)//判断标识符
              {
                   Next(infile);
                   poi = poi->next;
                   if(poi->type==25)//判断=
                   {
                       Next(infile);
                       poi = poi->next;
                       if(poi->type==5||poi->type==9||poi->type==11)//判断常量
                       {
                            Next(infile);
                            poi = poi->next;
                             poi=SubsequentVariableDeclarations(poi); //进入 后继变量声明 子程序
                             poi=TheStatementList(poi); //进入 语句列表 子程序
                             return poi;
                       }else {
                           poi=ArithmeticExpression(poi);//进入 算术表达式 子程序
                            poi=SubsequentVariableDeclarations(poi); //进入 后继变量声明 子程序
                             poi=TheStatementList(poi); //进入 语句列表 子程序
                             return poi;
                       }

                   }else error();
              }else {
                  if(poi->type==7||poi->type==5||poi->type==9||poi->type==11)//判断char int bool float
                  {
                      Next(infile);
                      poi = poi->next;
                      if(poi->type==40)//判断[
                      {
                          Next(infile);
                          poi = poi->next;
                          if(poi->type==3)//判断数字
                          {
                              Next(infile);
                              poi = poi->next;
                              if(poi->type==41)//判断]
                              {
                                  poi=ArrayAssignmentStatement(poi);//进入 数组赋值语句 子程序
                                  poi=SubsequentArrayAssignmentStatement(poi);//进入 后继数组赋值语句 子程序
                                  poi=TheStatementList(poi); //进入 语句列表 子程序
                                  return poi;
                              }else error();
                          }else error();
                      }else {
                          if(poi->type==25)//判断=
                          {
                               Next(infile);
                               poi = poi->next;
                               if(poi->type==1||poi->type==2||poi->type==3)//判断常量
                               {
                                    Next(infile);
                                    poi = poi->next;
                                    poi=SubsequentVariableDeclarations(poi); //进入 后继变量声明 子程序
                                    poi=TheStatementList(poi); //进入 语句列表 子程序
                                    return poi;
                               }else{
                                    poi=ArithmeticExpression(poi);//进入 算术表达式 子程序
                                    poi=SubsequentVariableDeclarations(poi); //进入 后继变量声明 子程序
                                    poi=TheStatementList(poi); //进入 语句列表 子程序
                                    return poi;
                               }
                          }else{
                                    poi=SubsequentVariableDeclarations(poi); //进入 后继变量声明 子程序
                                    poi=TheStatementList(poi); //进入 语句列表 子程序
                                    return poi;
                          }

                      }

                  }
              }
        }
    }
