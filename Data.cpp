#include "Data.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "new_const.h"
using namespace std;

void split(string file_p, string file_e)
{
	ifstream fin[2];
	fin[0].open(file_p); 
	fin[1].open(file_e);
	ofstream fout[2][5];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0) fout[i][j].open(input + "\\p_" + char(j + '0') + ".txt");
			else fout[i][j].open(input + "\\e_" + char(j + '0') + ".txt");
		}
	}

	for (int i = 0; i < 2; i++)
	{
		string str;
		while (getline(fin[i], str))
		{
			int index = rand() % 5;
			fout[i][index] << str << endl;
		}
		fin[i].close();
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
			fout[i][j].close();
	}
}
void readdata(vector<Transcations>& fore_transactions, vector<Transcations>& back_transactions, int k)
{
	ifstream fin[2][5];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0) fin[i][j].open(input + "\\p_" + char(j + '0') + ".txt");
			else fin[i][j].open(input + "\\e_" + char(j + '0') + ".txt");
		}
	}
	ofstream fout[2];
	fout[0].open(train);
	fout[1].open(test);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			string str;
			while (getline(fin[i][j], str) )
			{
				Transcations trans_temp;
				trans_temp.frequency = 1;
				stringstream ss(str);
				int int_temp;
				while (ss >> int_temp)
				{
					trans_temp.transcation.push_back(int_temp);
				}
				if (j != k) // 这是训练数据
				{
					if (i == 0)
					{
						fore_transactions.push_back(trans_temp);
					}
					else back_transactions.push_back(trans_temp);
					fout[0] << i << " " << str << endl;
				}
				else if(j == k) //这是测试数据
				{
					fout[1] << i << " " << str << endl;
				}
			}
			fin[i][j].close();
		}
	}
	fout[0].close();
	fout[1].close();
}
void write_data_svm()
{
	ifstream fin(dmp);
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
	trans_data_svm(train, train_svm, pattern);
	trans_data_svm(test, test_svm, pattern);
}

void trans_data_svm(string file, string file_svm, vector<Transcations> & pattern)
{
	ifstream fin(file);
	ofstream fout(file_svm);
	string str;
	while (getline(fin, str))
	{
		Transcations trans_temp;
		trans_temp.frequency = 1;
		stringstream ss(str);
		int label;
		int int_temp;
		ss >> label;
		while (ss >> int_temp)
		{
			trans_temp.transcation.push_back(int_temp);
		}
		vector<int> temp;
		for (int j = 0; j < pattern.size(); j++)
		{
			int L_t = 0;
			int P_t = 0;
			bool flag = true;
			while (L_t < trans_temp.transcation.size() && P_t < pattern[j].transcation.size())
			{
				if (trans_temp.transcation[L_t] == pattern[j].transcation[P_t])
				{
					L_t++;
					P_t++;
				}
				else if (trans_temp.transcation[L_t] < pattern[j].transcation[P_t])
				{
					L_t++;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag && P_t == pattern[j].transcation.size() ) temp.push_back(j);
		}
		fout << label;
		for (int j = 0; j < temp.size(); j++)
		{
			fout << " " << temp[j];
		}
		fout << endl;
	}
	fin.close();
	fout.close();
}