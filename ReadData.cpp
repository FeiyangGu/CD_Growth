#include "ReadData.h"



vector<Transcations> Readdata(string file)
{
	vector<Transcations> data;
	ifstream fin(file);
	string str;
	while (getline(fin, str))
	{
		Transcations trans_temp;
		trans_temp.frequency = 1;
		stringstream ss(str);
		int int_temp;
		while (ss >> int_temp)
		{
			trans_temp.transcation.push_back(int_temp);
		}
		data.push_back(trans_temp);
		ss.clear();
	};
	fin.close();
	return data;
}

void  Readdata(string file, vector<Transcations>& transactions, vector<Transcations>& t_transactions)
{ 
	ifstream fin(file);
	string  t_p_output_file = path + "output\\" + parameter + "\\t_P.txt";
	string  t_e_output_file = path + "output\\" + parameter + "\\t_E.txt";
	ofstream fout_p(t_p_output_file);
	ofstream fout_e(t_e_output_file);
	string str;
	int a;
	while (getline(fin, str))
	{
		Transcations trans_temp;
		trans_temp.frequency = 1;
		stringstream ss(str);
		int int_temp;
		while (ss >> int_temp)
		{
			trans_temp.transcation.push_back(int_temp);
		}

		a = rand() % 3;
		if (a < 2)
		{
			transactions.push_back(trans_temp);
		}
		else
		{
			t_transactions.push_back(trans_temp);
		}
		ss.clear();
	};
	fin.close();
	fout_p.close();
	fout_e.close();
}
