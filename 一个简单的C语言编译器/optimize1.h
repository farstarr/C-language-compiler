

struct TreeNode {
	string w;//四元式第一位：符号
	string primary;//主标记
	vector<string> secondary;//次标记
	//int parent = -1;//父母位置：对于Tree数组下标  好像不需要
	int lchild = -1;
	int rchild = -1;
};

vector<TreeNode> Tree;


bool IsNumber(char ch) {
	if ((ch >= '0'&&ch <= '9'))
		return true;
	else
		return false;
}

int val(char ch) {//字符型转数值型函数
	return (int(ch - '0'));
}

double StringToDouble(string Input) {//string 变 double
	double Result;
	stringstream Oss;
	Oss << Input;
	Oss >> Result;
	return Result;
}
string DoubleToString(double Input) {//double 变 string
	stringstream Oss;
	Oss << Input;
	return Oss.str();
}

void change(int subscript) {//交换函数
	if (Tree[subscript].primary.at(0) == 't') {//如果是中间变量
		for (int i = 0; i < Tree[subscript].secondary.size(); i++) {
			if (Tree[subscript].secondary[i].at(0) != 't') {//不是中间变量
				//cout << "do change when : secondary = " << Tree[subscript].secondary[i] <<"primary = " << Tree[subscript].primary<<endl;
				string tem;
				tem = Tree[subscript].secondary[i];
				Tree[subscript].secondary[i] = Tree[subscript].primary;
				Tree[subscript].primary = tem;//交换操作
			}
		}
	}
}

int TraverseTreePrimary(string str) {//从后向前遍历
	int i;
	for (i = Tree.size()-1; i > -1; i--) {
		if (Tree[i].primary == str) {
			return i;
		}
	}
	return -1;//没找到
}

int TraverseTreeSecondary(string str) {//从后向前遍历
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
	return -1;//没找到
}

void optimize(int start, int end) {//优化函数
	for (; start <= end; start++) {
		//（= B/C _ A)
		if (Qt[start].first == "=") {// A = B 如果是赋值表达式  B = Qt[start].second A = Qt[start].fourth
			int mark = 0;//B没有被定义标记
			int pri = TraverseTreePrimary(Qt[start].second);
			int sec = TraverseTreeSecondary(Qt[start].second);
			if (pri != -1 || sec != -1) {//B已经被定义 把A附加到B所在节点上
				mark = 1;
				if (pri != -1) {
					//若 A 在 n2 已定义过，删除次标记
					int flag2 = 0;//secondary是否为空标记
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
					change(pri);//交换
				}
				else {
					//若 A 在 n2 已定义过，删除次标记
					int flag2 = 0;//secondary是否为空标记
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
					change(sec);//交换
				}
			}
			if (mark == 0) {//B没有被定义过，新建节点B
				TreeNode treenode;
				treenode.w = "_";//树节点第一位符号为空
				treenode.primary = Qt[start].second;
				treenode.secondary.push_back(Qt[start].fourth);//把A附加到B上
				Tree.push_back(treenode);
				//若 A 在 n2 已定义过，删除次标记
				int flag2 = 0;//secondary是否为空标记
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
			|| Qt[start].first == "<" || Qt[start].first == "+" || Qt[start].first == "-") {//双目运算符
			if (IsNumber(Qt[start].second.at(0)) && IsNumber(Qt[start].third.at(0))) {//四元式第二位和第三位为常数  A=C1 w C2
																					  //把第二位第三位变成数字进行计算，结果为result
				double sec = StringToDouble(Qt[start].second);
				double thi = StringToDouble(Qt[start].third);
				double result = sec * thi;
				string res = DoubleToString(result);
				int define = TraverseTreePrimary(res);
				if (define != -1) {//常数已经被定义过
					//若 A 在 n2 已定义过，删除次标记
					int flag2 = 0;//secondary是否为空标记
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
					Tree[define].secondary.push_back(Qt[start].fourth);//A放入次标记
				}
				else {//常数没有被定义过
					TreeNode treenode;
					treenode.w = "_";//树节点第一位符号为空
					treenode.primary = res;
					treenode.secondary.push_back(Qt[start].fourth);//A附加到res上
					Tree.push_back(treenode);
					//若 A 在 n2 已定义过，删除次标记
					int flag2 = 0;//secondary是否为空标记
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
				//找B存B_subscript,无：建存B_subscript
				int mark = 0;//B没有被定义标记
				int B_subsrcipt;//B位置
				int pri = TraverseTreePrimary(Qt[start].second);
				int sec = TraverseTreeSecondary(Qt[start].second);
				if (pri != -1 || sec != -1) {//B已经被定义
					mark = 1;
					if (pri != -1) {
						B_subsrcipt = pri;
					}
					else {
						B_subsrcipt = sec;
					}
				}
				if (mark == 0) {//B没有被定义过，新建节点B
					TreeNode treenode;
					treenode.w = "_";//树节点第一位符号为空
					treenode.primary = Qt[start].second;
					Tree.push_back(treenode);
					B_subsrcipt = Tree.size() - 1;
				}
				//找C存C_subscript,无：建存C_subscript
				mark = 0;//B没有被定义标记
				int C_subsrcipt;//B位置
				pri = TraverseTreePrimary(Qt[start].third);
				sec = TraverseTreeSecondary(Qt[start].third);
				if (pri != -1 || sec != -1) {//B已经被定义
					mark = 1;
					if (pri != -1) {
						C_subsrcipt = pri;
					}
					else {
						C_subsrcipt = sec;
					}
				}
				if (mark == 0) {//B没有被定义过，新建节点B
					TreeNode treenode;
					treenode.w = "_";//树节点第一位符号为空
					treenode.primary = Qt[start].third;
					Tree.push_back(treenode);
					C_subsrcipt = Tree.size() - 1;
				}
				//找有相同子节点的节点，把A加入，否则，新建节点A
				int flag = 0;
				for (int i = Tree.size() - 1; i > -1; i--) {
					flag = 0;
					if (Tree[i].lchild == B_subsrcipt && Tree[i].rchild == C_subsrcipt && Tree[i].w == Qt[start].first) {//找到，把A加入
						//cout << "do this " << Qt[start].fourth<<endl;
						flag = 1;
						//若 A 在 n2 已定义过，删除次标记
						int flag2 = 0;//secondary是否为空标记
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
				if (flag == 0) {//没找到，新建A
					TreeNode treenode;
					treenode.w = Qt[start].first;//树节点第一位符号w
					treenode.primary = Qt[start].fourth;//A
					treenode.lchild = B_subsrcipt;
					treenode.rchild = C_subsrcipt;
					Tree.push_back(treenode);
					//若 A 在 n2 已定义过，删除次标记
					int flag2 = 0;//secondary是否为空标记
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
}
}


vector<QtNode>NewQt;

void NewSend(string a, string b, string c, string d) {//重组四元式
	QtNode node;
	node.first = a;
	node.second = b;
	node.third = c;
	node.fourth = d;
	NewQt.push_back(node);
}
void Generation(int start, int end) {//生成四元式
	for (int i = 0; i < Tree.size(); i++){
		if (Tree[i].lchild == -1 && Tree[i].rchild == -1) {//叶节点
			//secondary非临时变量生成表达式 secondary = primary (=,primary,_,secondary)
			for (int j = 0; j < Tree[i].secondary.size(); j++) {
				if (Tree[i].secondary[j].at(0) != 't') {//非临时变量生成赋值四元式
					NewSend("=", Tree[i].primary, "_", Tree[i].secondary[j]);
				}
			}

		}
		else {//非叶节点
			NewSend(Tree[i].w, Tree[Tree[i].lchild].primary, Tree[Tree[i].rchild].primary, Tree[i].primary);
			for (int j = 0; j < Tree[i].secondary.size(); j++) {
				if (Tree[i].secondary[j].at(0) != 't') {//非临时变量生成赋值四元式
					NewSend("=", Tree[i].primary, "_", Tree[i].secondary[j]);
				}
			}
		}
}
	NewQt.push_back(Qt[end]);
}
