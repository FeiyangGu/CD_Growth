#include "Evaluate.h"
#include <cstdlib>
#include <ctime>
#include<windows.h>
using namespace std;

void EVALUATE(vector<Transcations> & t_fore_transactions, vector<Transcations> & t_back_transactions)
{
	print_test(t_fore_transactions, t_back_transactions);
	return ;
	// 读取pattern
	vector< vector<int> > pattern; // 存储挖掘出的差异模式
	vector<int> pa_temp;
	ifstream fin(output_file);
	string str;
	while (getline(fin, str))
	{
		stringstream ss(str);
		pa_temp.clear();
		int int_temp;
		while (ss >> int_temp)
		{
			pa_temp.push_back(int_temp);
		}
		pattern.push_back(pa_temp);
	}
	cout << pattern.size() << endl;
	double ret = Count2(t_fore_transactions, pattern) + t_back_transactions.size() - Count2(t_back_transactions, pattern);
	ret = 1.0*ret / (t_fore_transactions.size() + t_back_transactions.size());
	cout << ret << endl;
	/*
	vector<int> count_fore(pattern.size() + 2, 0);
	vector<int> count_back(pattern.size() + 2, 0);
	Count(t_fore_transactions, pattern, count_fore);
	Count(t_back_transactions, pattern, count_back);
	
	double ret = 0;
	for (int i = 0; i < pattern.size(); i++)
	{
		ret = ret + (1.0*count_back[i] / (count_back[i] + count_fore[i]));
	}
	ret /= pattern.size();
	cout << ret << endl;
	*/
}

void Count(vector<Transcations> & t_transactions, vector< vector<int> > & pattern, vector<int>& count_t)
{
	for (int i = 0; i<t_transactions.size(); i++)
	{
		for (int j = 0; j < pattern.size(); j++)
		{
			int k = 0;
			int l = 0;
			bool flag = true;
			while (k < t_transactions[i].transcation.size() && l < pattern[j].size())
			{
				if (t_transactions[i].transcation[k] == pattern[j][l])
				{
					k++; l++;
				}
				else if (t_transactions[i].transcation[k] < pattern[j][l])
				{
					k++;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				count_t[j]++;
			}
		}
	}
}

int Count2(vector<Transcations> & t_transactions, vector< vector<int> > & pattern)
{
	int ret = 0;
	for (int i = 0; i<t_transactions.size(); i++)
	{
		for (int j = 0; j < pattern.size(); j++)
		{
			int k = 0;
			int l = 0;
			bool flag = true;
			while (k < t_transactions[i].transcation.size() && l < pattern[j].size())
			{
				if (t_transactions[i].transcation[k] == pattern[j][l])
				{
					k++; l++;
				}
				else if (t_transactions[i].transcation[k] < pattern[j][l])
				{
					k++;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				ret++;
				break;
			}
		}
	}
	return ret;
}


void print_test(vector<Transcations> & t_fore_transactions, vector<Transcations> & t_back_transactions)
{
	// 读pattern
	ifstream fin(output_file);
	vector<Transcations> pattern;
	string str;
	while (getline(fin, str))
	{
		Transcations trans_temp;
		trans_temp.frequency = 1;
		stringstream ss(str);
		int int_temp;
		ss >> int_temp;
		while (ss >> int_temp)
		{
			trans_temp.transcation.push_back(int_temp);
		}
		pattern.push_back(trans_temp);
		ss.clear();
	};
	fin.close();
	
	//ofstream fout(svm_p_output_file); fout.close();
	//fout.open(svm_e_output_file); fout.close();
	
	get_svm_data(t_fore_transactions, svm_p_output_file, pattern, 0);
	get_svm_data(t_back_transactions, svm_e_output_file, pattern, 1);
}

void get_svm_data(vector<Transcations> & t_fore_transactions, string path, vector<Transcations>& pattern, int label)
{
	ofstream fout(path);
	for (int i = 0; i < t_fore_transactions.size(); i++)
	{
		vector<int> temp;
		for (int j = 0; j < pattern.size(); j++)
		{
			int L_t = 0;
			int P_t = 0;
			bool flag = true;
			while (L_t < t_fore_transactions[i].transcation.size() && P_t < pattern[j].transcation.size())
			{
				if (t_fore_transactions[i].transcation[L_t] == pattern[j].transcation[P_t])
				{
					L_t++;
					P_t++;
				}
				else if (t_fore_transactions[i].transcation[L_t] < pattern[j].transcation[P_t])
				{
					L_t++;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag) temp.push_back(j);
		}
		fout << label;
		for (int j = 0; j < temp.size(); j++)
		{
			fout << " " << temp[j];
		}
		fout << endl;
	}
	fout.close();
}