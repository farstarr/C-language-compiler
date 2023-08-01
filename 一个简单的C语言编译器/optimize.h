#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "ɨ����Next.h"
using namespace std;

struct TreeNode {
	string w;//��Ԫʽ��һλ������
	string primary;//�����
	vector<string> secondary;//�α��
	//int parent = -1;//��ĸλ�ã�����Tree�����±�  ������Ҫ
	int lchild = -1;
	int rchild = -1;
	string q2;
	string q3;
	string q4;
};

vector<TreeNode> Tree;


bool IsNumber(char ch) {
	if ((ch >= '0'&&ch <= '9'))
		return true;
	else
		return false;
}

int val(char ch) {//�ַ���ת��ֵ�ͺ���
	return (int(ch - '0'));
}

double StringToDouble(string Input) {//string �� double
	double Result;
	stringstream Oss;
	Oss << Input;
	Oss >> Result;
	return Result;
}
string DoubleToString(double Input) {//double �� string
	stringstream Oss;
	Oss << Input;
	return Oss.str();
}

void change(int subscript) {//��������
	if (Tree[subscript].primary.at(0) == 't') {//������м����
		for (int i = 0; i < Tree[subscript].secondary.size(); i++) {
			if (Tree[subscript].secondary[i].at(0) != 't') {//�����м����
				//cout << "do change when : secondary = " << Tree[subscript].secondary[i] <<"primary = " << Tree[subscript].primary<<endl;
				string tem;
				tem = Tree[subscript].secondary[i];
				Tree[subscript].secondary[i] = Tree[subscript].primary;
				Tree[subscript].primary = tem;//��������
			}
		}
	}
}

int TraverseTreePrimary(string str) {//�Ӻ���ǰ����
	int i;
	for (i = Tree.size()-1; i > -1; i--) {
		if (Tree[i].primary == str) {
			return i;
		}
	}
	return -1;//û�ҵ�
}

int TraverseTreeSecondary(string str) {//�Ӻ���ǰ����
	int i;
	int flag = 0;
	for (i = Tree.size() - 1; i > -1; i--) {
		flag = 0;
		if (Tree[i].secondary.empty()) {
			flag = 1;
		}
		if (flag == 0) {
			for (int j = Tree[i].secondary.size() - 1; j > -1; j--) {
				if (Tree[i].secondary[j] == str) {
					return i;
				}
			}
		}

	}
	return -1;//û�ҵ�
}

vector<QtNode>NewQt;

void optimize(int start, int end) {//�Ż�����
	if(Qt[start].first == "if" || Qt[start].first == "ie" || Qt[start].first == "el" || Qt[start].first == "we"
     || Qt[start].first == "do"){
        NewQt.push_back(Qt[start]);
     }
	for (; start < end; start++) {
		//��= B/C _ A)

		if (Qt[start].first == "=") {// A = B ����Ǹ�ֵ���ʽ  B = Qt[start].second A = Qt[start].fourth
			int mark = 0;//Bû�б�������
			int pri = TraverseTreePrimary(Qt[start].second);
			int sec = TraverseTreeSecondary(Qt[start].second);
			if (pri != -1 || sec != -1) {//B�Ѿ������� ��A���ӵ�B���ڽڵ���
				mark = 1;
				if (pri != -1) {
					//�� A �� n2 �Ѷ������ɾ���α��
					int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
					for (int n = Tree.size() - 1; n > -1; n--) {
						flag2 = 0;
						if (Tree[n].secondary.empty()) {
							flag2 = 1;
						}
						if (flag2 == 0) {
							for (int m = Tree[n].secondary.size() - 1; m > -1; m--) {
								if (Tree[n].secondary[m] == Qt[start].fourth) {
									Tree[n].secondary.erase(Tree[n].secondary.begin() + m);
									break;
								}
							}
						}
					}
					Tree[pri].secondary.push_back(Qt[start].fourth);
					change(pri);//����
				}
				else {
					//�� A �� n2 �Ѷ������ɾ���α��
					int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
					for (int n = Tree.size() - 1; n > -1; n--) {
						flag2 = 0;
						if (Tree[n].secondary.empty()) {
							flag2 = 1;
						}
						if (flag2 == 0) {
							for (int m = Tree[n].secondary.size() - 1; m > -1; m--) {
								if (Tree[n].secondary[m] == Qt[start].fourth) {
									Tree[n].secondary.erase(Tree[n].secondary.begin() + m);
									break;
								}
							}
						}
					}
					Tree[sec].secondary.push_back(Qt[start].fourth);
					change(sec);//����
				}
			}
			if (mark == 0) {//Bû�б���������½��ڵ�B
				TreeNode treenode;
				treenode.w = "_";//���ڵ��һλ����Ϊ��
				treenode.primary = Qt[start].second;
				treenode.secondary.push_back(Qt[start].fourth);//��A���ӵ�B��
				Tree.push_back(treenode);
				//�� A �� n2 �Ѷ������ɾ���α��
				int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
				for (int i = Tree.size() - 2; i > -1; i--) {
					flag2 = 0;
					if (Tree[i].secondary.empty()) {
						flag2 = 1;
					}
					if (flag2 == 0) {
						for (int j = Tree[i].secondary.size() - 1; j > -1; j--) {
							if (Tree[i].secondary[j] == Qt[start].fourth) {
								Tree[i].secondary.erase(Tree[i].secondary.begin() + j);
								break;
							}
						}
					}
				}
			}
		}
		if (Qt[start].first == "*" || Qt[start].first == "/" || Qt[start].first == "%" || Qt[start].first == "||" || Qt[start].first == "&&"
			|| Qt[start].first == "==" || Qt[start].first == "!=" || Qt[start].first == ">=" || Qt[start].first == ">" || Qt[start].first == "<="
			|| Qt[start].first == "<" || Qt[start].first == "+" || Qt[start].first == "-") {//˫Ŀ�����
			if (IsNumber(Qt[start].second.at(0)) && IsNumber(Qt[start].third.at(0))) {//��Ԫʽ�ڶ�λ�͵���λΪ����  A=C1 w C2
																					  //�ѵڶ�λ����λ������ֽ��м��㣬���Ϊresult
				double sec = StringToDouble(Qt[start].second);
				double thi = StringToDouble(Qt[start].third);
				double result = sec * thi;
				string res = DoubleToString(result);
				int define = TraverseTreePrimary(res);
				if (define != -1) {//�����Ѿ��������
					//�� A �� n2 �Ѷ������ɾ���α��
					int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
					for (int n = Tree.size() - 1; n > -1; n--) {
						flag2 = 0;
						if (Tree[n].secondary.empty()) {
							flag2 = 1;
						}
						if (flag2 == 0) {
							for (int m = Tree[n].secondary.size() - 1; m > -1; m--) {
								if (Tree[n].secondary[m] == Qt[start].fourth) {
									Tree[n].secondary.erase(Tree[n].secondary.begin() + m);
									break;
								}
							}
						}
					}
					Tree[define].secondary.push_back(Qt[start].fourth);//A����α��
				}
				else {//����û�б������
					TreeNode treenode;
					treenode.w = "_";//���ڵ��һλ����Ϊ��
					treenode.primary = res;
					treenode.secondary.push_back(Qt[start].fourth);//A���ӵ�res��
					Tree.push_back(treenode);
					//�� A �� n2 �Ѷ������ɾ���α��
					int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
					for (int i = Tree.size() - 2; i > -1; i--) {
						flag2 = 0;
						if (Tree[i].secondary.empty()) {
							flag2 = 1;
						}
						if (flag2 == 0) {
							for (int j = Tree[i].secondary.size() - 1; j > -1; j--) {
								if (Tree[i].secondary[j] == Qt[start].fourth) {
									Tree[i].secondary.erase(Tree[i].secondary.begin() + j);
									break;
								}
							}
						}
					}
				}
			}
			else {//A=BwC  (w B C A)
				//��B��B_subscript,�ޣ�����B_subscript
				int mark = 0;//Bû�б�������
				int B_subsrcipt;//Bλ��
				int pri = TraverseTreePrimary(Qt[start].second);
				int sec = TraverseTreeSecondary(Qt[start].second);
				if (pri != -1 || sec != -1) {//B�Ѿ�������
					mark = 1;
					if (pri != -1) {
						B_subsrcipt = pri;
					}
					else {
						B_subsrcipt = sec;
					}
				}
				if (mark == 0) {//Bû�б���������½��ڵ�B
					TreeNode treenode;
					treenode.w = "_";//���ڵ��һλ����Ϊ��
					treenode.primary = Qt[start].second;
					Tree.push_back(treenode);
					B_subsrcipt = Tree.size() - 1;
				}
				//��C��C_subscript,�ޣ�����C_subscript
				mark = 0;//Bû�б�������
				int C_subsrcipt;//Bλ��
				pri = TraverseTreePrimary(Qt[start].third);
				sec = TraverseTreeSecondary(Qt[start].third);
				if (pri != -1 || sec != -1) {//B�Ѿ�������
					mark = 1;
					if (pri != -1) {
						C_subsrcipt = pri;
					}
					else {
						C_subsrcipt = sec;
					}
				}
				if (mark == 0) {//Bû�б���������½��ڵ�B
					TreeNode treenode;
					treenode.w = "_";//���ڵ��һλ����Ϊ��
					treenode.primary = Qt[start].third;
					Tree.push_back(treenode);
					C_subsrcipt = Tree.size() - 1;
				}
				//������ͬ�ӽڵ�Ľڵ㣬��A���룬�����½��ڵ�A
				int flag = 0;
				for (int i = Tree.size() - 1; i > -1; i--) {
					flag = 0;
					if (Tree[i].lchild == B_subsrcipt && Tree[i].rchild == C_subsrcipt && Tree[i].w == Qt[start].first) {//�ҵ�����A����
						//cout << "do this " << Qt[start].fourth<<endl;
						flag = 1;
						//�� A �� n2 �Ѷ������ɾ���α��
						int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
						for (int n = Tree.size() - 1; n > -1; n--) {
							flag2 = 0;
							if (Tree[n].secondary.empty()) {
								flag2 = 1;
							}
							if (flag2 == 0) {
								for (int m = Tree[n].secondary.size() - 1; m > -1; m--) {
									if (Tree[n].secondary[m] == Qt[start].fourth) {
										Tree[n].secondary.erase(Tree[n].secondary.begin() + m);
										break;
									}
								}
							}
						}
						Tree[i].secondary.push_back(Qt[start].fourth);
						change(i);
						break;
					}
				}
				if (flag == 0) {//û�ҵ����½�A
					TreeNode treenode;
					treenode.w = Qt[start].first;//���ڵ��һλ����w
					treenode.primary = Qt[start].fourth;//A
					treenode.lchild = B_subsrcipt;
					treenode.rchild = C_subsrcipt;
					Tree.push_back(treenode);
					//�� A �� n2 �Ѷ������ɾ���α��
					int flag2 = 0;//secondary�Ƿ�Ϊ�ձ��
					for (int i = Tree.size() - 2; i > -1; i--) {
						flag2 = 0;
						if (Tree[i].secondary.empty()) {
							flag2 = 1;
						}
						if (flag2 == 0) {
							for (int j = Tree[i].secondary.size() - 1; j > -1; j--) {
								if (Tree[i].secondary[j] == Qt[start].fourth) {
									Tree[i].secondary.erase(Tree[i].secondary.begin()+j);
									break;
								}
							}
						}
					}
				}
			}
		}
        if(Qt[start].first == "func" || Qt[start].first == "re" || Qt[start].first == "call" || Qt[start].first == "value" || Qt[start].first == "param"
           || Qt[start].first == "END" || Qt[start].first == "TEM"){
            TreeNode treenode;
			treenode.w = Qt[start].first;
			treenode.q2 = Qt[start].second;
			treenode.q3 = Qt[start].third;
			treenode.q4 = Qt[start].fourth;
			Tree.push_back(treenode);
        }
        if((Qt[start].first == "!" &&Qt[start].third == " ")){
            TreeNode treenode;
			treenode.w = Qt[start].first;
			treenode.q2 = Qt[start].second;
			treenode.q3 = Qt[start].third;
			treenode.q4 = Qt[start].fourth;
			Tree.push_back(treenode);
           }
}

}




void NewSend(string a, string b, string c, string d) {//������Ԫʽ
	QtNode node;
	node.first = a;
	node.second = b;
	node.third = c;
	node.fourth = d;
	NewQt.push_back(node);
}
void Generation(int start, int end) {//������Ԫʽ
	for (int i = 0; i < Tree.size(); i++){
		if (Tree[i].lchild == -1 && Tree[i].rchild == -1 && Tree[i].w != "func" && Tree[i].w != "re" && Tree[i].w != "call"
      && Tree[i].w != "value" && Tree[i].w != "param" && Tree[i].w != "END"&& Tree[i].w != "TEM"&& !(Tree[i].w == "!" && Tree[i].q3 == " ")) {//Ҷ�ڵ�
			//secondary����ʱ�������ɱ��ʽ secondary = primary (=,primary,_,secondary)
			for (int j = 0; j < Tree[i].secondary.size(); j++) {
				if (Tree[i].secondary[j].at(0) != 't') {//����ʱ�������ɸ�ֵ��Ԫʽ
					NewSend("=", Tree[i].primary, "_", Tree[i].secondary[j]);
				}
			}
		}
		else if(Tree[i].w != "func" && Tree[i].w != "re" && Tree[i].w != "call"
      && Tree[i].w != "value" && Tree[i].w != "param" && Tree[i].w != "END" && Tree[i].w != "TEM" &&!(Tree[i].w == "!" && Tree[i].q3 == " ")){//��Ҷ�ڵ�
			NewSend(Tree[i].w, Tree[Tree[i].lchild].primary, Tree[Tree[i].rchild].primary, Tree[i].primary);
			for (int j = 0; j < Tree[i].secondary.size(); j++) {
				if (Tree[i].secondary[j].at(0) != 't') {//����ʱ�������ɸ�ֵ��Ԫʽ
					NewSend("=", Tree[i].primary, "_", Tree[i].secondary[j]);
				}
			}
		}
		else if(Tree[i].w == "func" || Tree[i].w == "re" || Tree[i].w == "call" || Tree[i].w == "value" || Tree[i].w == "param" || Tree[i].w == "END"
         || Tree[i].w == "TEM" ||(Tree[i].w == "!" && Tree[i].q3 == " ")){
            NewSend(Tree[i].w,Tree[i].q2,Tree[i].q3,Tree[i].q4);
		}
}
    Tree.clear();
    if(Qt[end-1].first == "wh" || Qt[end-1].first == "if" || Qt[end-1].first == "ie" || Qt[end-1].first == "el" || Qt[end-1].first == "we"
     || Qt[end-1].first == "do"){
        NewQt.push_back(Qt[end-1]);
     }
}
