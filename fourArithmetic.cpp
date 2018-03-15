#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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
	vector<vector<double>> v_data;
	vector<vector<double>> v_data_simp;
	vector<vector<string>> v_op;
	vector<vector<string>> v_op_simp;
	vector<double> v_answer;
	int arithNum;
	int grades;

	CfourArith(int n);
	~CfourArith();
	void calArith();
	void showArith();
	double round(double number, unsigned int bits);
	int getGrades();
};
CfourArith::CfourArith(int n) {
	int grades = 100;
	arithNum = n;
	string op[4] = {"+", "-", "*", "/"};
	double num;
	int numNum;
	int opNum;
	vector<double>num_temp;
	vector<string>op_temp;
//	srand((unsigned)time(NULL)); 
	for (int i = 0; i < n; i++) {
		numNum = rand() % (4 - 2 + 1) + 2;
		num_temp.clear();
		op_temp.clear();
		for (int j = 0; j < numNum; j++) {
			num = rand() % (50 - 1 + 1) + 1;
			if (j > 0) {
				opNum = rand() % (3 - 0 + 1) + 0;
				op_temp.push_back(op[opNum]);
			}
			num_temp.push_back(num);
		}
		v_data.push_back(num_temp);
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
	{
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
		{
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
int main() 
{
	int n;
	cout<<"请生成题目数量:"<<endl;
	cin>>n;
	cout<<"题目数量为:"<<n<<endl;
	cout<<"每题分数为:"<<" "<<100/n<<endl;
	cout<<"答案请保留两位小数"<<endl;
	CfourArith c(n);
		
		c.calArith();
		c.showArith();
		system("pause");

	return 1;
}
