#include "new_const.h"
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;

string dir = "H:\\BaiDuYun\\work\\CDPM\\Data\\";
string kind = "cancer_gene\\";
string source = dir + kind + "source\\";
string source_p = source + "p_cancer_gene.txt";
string source_e = source + "e_cancer_gene.txt";
string profold;
string parafolder;
string times;
string input;
string output;
string cv_nu;
string dmp;
string train;
string test;
string train_svm;
string test_svm;

void mk_profold()
{
	profold = dir + kind + "profold";
	char cmd[200] = "md ";
	int len = strlen(cmd);
	for (int i = 0; i < profold.length(); i++)
	{
		cmd[len++] = profold[i];
	}
	cmd[len++] = '\n';
	cout << cmd << endl;
	system(cmd);
}

void mk_parafold(double sup, double sig_l, double sig_g, int pattern_length)
{
	stringstream ss;
	ss.precision(2);
	ss << showpoint << sup << "__" << sig_l << "__" << sig_g;
	parameter = ss.str();
	ss.clear();
	parafolder = profold + "\\" + parameter;
	char cmd[200] = "md ";
	int len = strlen(cmd);
	for (int i = 0; i < profold.length(); i++)
	{
		cmd[len++] = profold[i];
	}
	cmd[len++] = '\n';
	system(cmd);
}

void mk_timesfold(int time)
{
	char temp[100];
	_itoa_s(time, temp, 10);
	times = parafolder+"\\";
	times += temp;
	char cmd[200] = "md ";
	int len = strlen(cmd);
	for (int i = 0; i < times.length(); i++)
	{
		cmd[len++] = times[i];
	}
	cmd[len++] = '\n';
	system(cmd);
}

void mk_input()
{
	input = times + "\\" + "input";
	char cmd[200] = "md ";
	int len = strlen(cmd);
	for (int i = 0; i < input.length(); i++)
	{
		cmd[len++] = input[i];
	}
	cmd[len++] = '\n';
	system(cmd);
}

void mk_output()
{
	output = times + "\\" + "output";
	char cmd[200] = "md ";
	int len = strlen(cmd);
	for (int i = 0; i < output.length(); i++)
	{
		cmd[len++] = output[i];
	}
	cmd[len++] = '\n';
	system(cmd);
}

void mk_cv_nu(int nu)
{
	char temp[100];
	_itoa_s(nu, temp, 10);
	cv_nu = output + "\\";
	cv_nu += temp;
	char cmd[200] = "md ";
	int len = strlen(cmd);
	for (int i = 0; i < cv_nu.length(); i++)
	{
		cmd[len++] = cv_nu[i];
	}

	cmd[len++] = '\n';
	cout << endl << endl << "  "<<cmd << endl;
	system(cmd);
	dmp = cv_nu + "\\" + "dmp.txt";
	train = cv_nu + "\\" + "train.txt";
	test = cv_nu + "\\" + "test.txt";
	train_svm = cv_nu + "\\" + "train_svm.txt";
	test_svm =  cv_nu + "\\" + "test_svm.txt";
}
