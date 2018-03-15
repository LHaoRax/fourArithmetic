#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <time.h> 

using namespace std;
//////数字随机
//////数字个数随机
//////数字间符号随机
typedef long long LL;

class CfourArith
{
public:
	vector<vector<double>> v_data;//定义存储四则运算数字的二维vector
	vector<vector<double>> v_data_simp;//vector副本，用来在进行乘除时简化计算，存储乘除计算结果
	vector<vector<string>> v_op;//定义存储四则运算符号的二维vector
	vector<vector<string>> v_op_simp;//用来在进行乘除时简化计算,最终里面只有+和-
	vector<double> v_answer;//答案
	int arithNum;//题目数量
	double grades;//分数

	CfourArith(int n);//构造函数生成四则运算
	~CfourArith();
	void calArith();//计算答案的函数
	void showArith();//显示函数
	double round(double number, unsigned int bits);//四舍五入两位小数
	double getGrades();//获取成绩
};
CfourArith::CfourArith(int n) {
	///初始化
	grades = 100;
	arithNum = n;
	///
	string op[4] = {"+", "-", "*", "/"};
	double num;//运算里面的具体数字
	int numNum;//每个运算有几个数字
	int opNum;//符号位置
	vector<double>num_temp;//存储每个四则运算数字的临时vector
	vector<string>op_temp;//存储每个四则运算符号的临时vector
	srand((unsigned)time(NULL)); 
	for (int i = 0; i < n; i++) {
		numNum = rand() % (4 - 2 + 1) + 2;//每个表达式随机有1-4个数字
		num_temp.clear();//清空临时vector
		op_temp.clear();
		for (int j = 0; j < numNum; j++) {
			num = rand() % (50 - 1 + 1) + 1;//随机生成表达式里面的具体数字1-50
			if (j > 0) {
				opNum = rand() % (3 - 0 + 1) + 0;//随机选择符号
				op_temp.push_back(op[opNum]);
			}
			num_temp.push_back(num);
		}
		v_data.push_back(num_temp);//将临时vector压入总vector
		v_op.push_back(op_temp);
		v_data_simp.push_back(num_temp);
		v_op_simp.push_back(op_temp);
	}
}
CfourArith::~CfourArith()
{
	v_data.clear();
	v_op.clear();
	v_answer.clear();
}
void CfourArith::showArith() {
	for (int i = 0; i < arithNum; i++)
	{
		for (int j = 0; j < v_data[i].size() - 1; j++)
			cout<<v_data[i][j]<<" "<<v_op[i][j]<<" ";
		cout<<v_data[i][v_data[i].size() - 1];
//		cout<<endl;
		cout<<" "<<"="<<" "<<v_answer[i]<<endl;
	}
}
void CfourArith::calArith()
{
	double temp;
	for (int i = 0; i < arithNum; i++)
	{//先处理乘除
		while (1) {
			int u = 0;
			for (int j = 0; j < v_op_simp[i].size(); j++)
			{
				if (v_op_simp[i][j] == "*" || v_op_simp[i][j] == "/")
					break;
				u++;
			}
			if (u == v_op_simp[i].size())
				break;
			if (v_op_simp[i][u] == "*") {
				temp = v_data_simp[i][u] * v_data_simp[i][u + 1];
				v_op_simp[i].erase(v_op_simp[i].begin() + u);
				v_data_simp[i].erase(v_data_simp[i].begin() + u);
				v_data_simp[i].erase(v_data_simp[i].begin() + u);
				v_data_simp[i].insert(v_data_simp[i].begin() + u, temp);
			}
			else {
				temp = (double)v_data_simp[i][u] / v_data_simp[i][u + 1];
				v_op_simp[i].erase(v_op_simp[i].begin() + u);
				v_data_simp[i].erase(v_data_simp[i].begin() + u);
				v_data_simp[i].erase(v_data_simp[i].begin() + u);
				v_data_simp[i].insert(v_data_simp[i].begin() + u, temp);
			}
			
		}
		double result = v_data_simp[i][0];
		for (int j = 0; j < v_data_simp[i].size() - 1;j++)
		{//处理加减
			temp = v_data_simp[i][j + 1];
			string op = v_op_simp[i][j];
			if (op == "+") {
				result += temp;
			}
			else if (op == "-"){
				result -= temp;
			}
			else if (op == "*"){
				result *= temp;
			}
			else{
				result /= temp;
			}
		}
		v_answer.push_back(round(result, 2));
	}
}
double CfourArith::round(double number, unsigned int bits) {
	LL integerPart = number;
	number -= integerPart;
	for (unsigned int i = 0; i < bits; ++i)
		number *= 10;
	number = (LL) (number + 0.5);
	for (unsigned int i = 0; i < bits; ++i)
		number /= 10;
	return integerPart + number;
}
double CfourArith::getGrades()
{
	return grades;
}
int main() 
{
	int n;
	cout<<"请生成题目数量:"<<endl;
	cin>>n;
	cout<<"题目数量为:"<<n<<endl;
	cout<<"每题分数为:"<<" "<<fixed<<setprecision(2)<<(double)100/n<<endl;
	cout<<"答案请保留两位小数"<<endl;
	CfourArith c(n);
		
		c.calArith();
		c.showArith();
		system("pause");

	return 1;
}
