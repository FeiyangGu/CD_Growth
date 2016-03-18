#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "main.h"
#include "const.h"
#include "ReadData.h"
#include "fp_tree.h"
#include "Evaluate.h"
#include "new_const.h"
#include "Data.h"
#include <ctime>
//#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;

void init()
{
	char dir[200] = "md ";
	string temp_output = "output\\";
	int len = strlen(dir);
	for (int i = 0; i < path.length(); i++)
		dir[len++] = path[i];
	for (int i = 0; i < temp_output.length(); i++)
		dir[len++] = temp_output[i];
	for (int i = 0; i < parameter.length(); i++)
		dir[len++] = parameter[i];
	dir[len] = '\0';
	system(dir);
}

void GFP(vector<Transcations> & fore_transactions, vector<Transcations> & back_transactions, int times, int k)
{
	time_t tt = time(NULL);                       //这句返回的只是一个时间cuo
	tm tmp;
	tm *t = &tmp;
	localtime_s(t, &tt);
	ofstream fout(dir+kind + "log.txt", ios::app);
	fout.precision(2);
	cout << "Sup = " << Sup << "    Sig_l = " << Sig_L << "    Sig_G = " << Sig_G << "    times = "<<times<<"    fold="<<k<<"  ";
	fout << showpoint << Sup << ' ' << Sig_L << ' ' << Sig_G << " "<<times<<" "<<k<<" ";
	cout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
	fout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << " ";

	flag = false;
	get_data_num(fore_transactions, back_transactions);
	get_dmp(dmp);
	ofstream fout2(dmp);
	fout2.close();
	FPTree f_fptree(fore_transactions, back_transactions);
	Pattern  x;
	fptree_growth(f_fptree, x, 0, 1, 1, 0.00001);
	print_result();
	tail_make();

	flag = true;
	get_data_num(back_transactions, fore_transactions);
	FPTree b_fptree(back_transactions, fore_transactions);
	Pattern y;
	fptree_growth(b_fptree, y, 0, 1, 1, 0.00001);
	print_result();
	tail_make();
	write_data_svm();


	tt = time(NULL);
	t = &tmp;
	localtime_s(t, &tt);
	cout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl << endl << endl;
	fout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
	fout.close();

}

/*void GFP()
{
	time_t tt = time(NULL);                       //这句返回的只是一个时间cuo
	tm tmp;
	tm *t = &tmp;
	localtime_s(t, &tt);

	ofstream fout(path + "parameter.txt", ios::app);
	fout.precision(2);
	cout << "Sup = " << Sup << "     Sig_l = " << Sig_L << "     Sig_G = " << Sig_G << endl;
	fout <<showpoint<< Sup << ' ' << Sig_L << ' ' << Sig_G << " ";
	cout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
	fout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << " ";

	ofstream f_out(output_file);
	f_out.close(); 

	vector<Transcations> fore_transactions;
	vector<Transcations> t_fore_transactions;
	vector<Transcations> back_transactions;
	vector<Transcations> t_back_transactions;
	
	Readdata(foreground_file, fore_transactions, t_fore_transactions);
	Readdata(background_file, back_transactions, t_back_transactions);
	flag = false;
	get_data_num(fore_transactions, back_transactions);
	FPTree f_fptree(fore_transactions, back_transactions);
	Pattern  x;
	fptree_growth(f_fptree, x);
	print_result();
	tail_make();
	flag = true;
	get_data_num(back_transactions, fore_transactions);
	FPTree b_fptree(back_transactions, fore_transactions);
	Pattern y;
	fptree_growth(b_fptree, y);
	print_result();
	tail_make();
	

	tt = time(NULL);
	t = &tmp;
	localtime_s(t, &tt);
	cout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl << endl << endl;
	fout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
	fout.close();	
	EVALUATE(t_fore_transactions, t_back_transactions);
}
*/
void Brest2_size()
{
	Sup = 0.45;     // 前景集支持度
	Sig_L = 0;
	Sig_G = 0.05;
	stringstream ss;
	ss.precision(2);
	ss << showpoint << Sup << "__" << Sig_L << "__" << Sig_G;
	parameter = ss.str();
	ss.clear();
	output_file = path + "output\\" + parameter + "\\DMP.txt";
	svm_p_output_file = path + "output\\" + parameter + "\\P_for_SVM.txt";
	svm_e_output_file = path + "output\\" + parameter + "\\E_for_SVM.txt";
	init();
	//GFP();
}

int main()
{
	/*
	ofstream fout(path + "parameter.txt", ios::app);
	fout.close();
	Brest2_size();
	return 0;
	*/


	srand(time(0));
	double sup = 0.40;
	double sig_g = 0.20;
	mk_profold(); //创建处理目录
	for (double sig_l = 0.20; sig_l < 0.21; sig_l += 0.05)
	{
		//ofstream fout(path + "parameter.txt", ios::app);
		Sup = sup;     // 前景集支持度
		Sig_L = sig_l;
		Sig_G = sig_g;
		mk_parafold(Sup, Sig_L, Sig_G, pattern_length); //对于每个参数创建目录

		time_t tt = time(NULL);                       //这句返回的只是一个时间cuo
		tm tmp;
		tm *t = &tmp;
		localtime_s(t, &tt);
		ofstream fout(dir+kind + "parameter.txt", ios::app);
		fout.precision(2);
		cout << "Sup = " << Sup << "     Sig_l = " << Sig_L << "     Sig_G = " << Sig_G << endl;
		fout << showpoint << Sup << ' ' << Sig_L << ' ' << Sig_G << " ";
		cout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
		fout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << " ";

		for (int times = 0; times < 1; times++)            //对于每个参数重复10次，保证稳定
		{ 
			mk_timesfold(times);                          //创建每次对应的目录
			mk_input();                                  //每次对应的输入，包含五个文件
			mk_output();                                 //对应的输出结果
			split(source_p, source_e);
			for (int i = 0; i < 1; i++)                  //5-CV
			{
				mk_cv_nu(i);                             //创建每次CV，对应的目录
				vector<Transcations> fore_transactions;
				vector<Transcations> back_transactions;
				readdata(fore_transactions, back_transactions, i);
				GFP(fore_transactions, back_transactions, times, i);
			}
		}

		tt = time(NULL);
		t = &tmp;
		localtime_s(t, &tt);
		cout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl << endl << endl;
		fout << t->tm_mday << "__" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
		fout.close();
	}
	/*
	for (double sup = 0.15; sup > 0.001; sup -= 0.005)
	{
		for (double sig_g = 0; sig_g <= sup; sig_g += 0.005)
		{
			for (double sig_l = 95; sig_l >= -1; sig_l -= 5)
			{
				Sup = sup;     // 前景集支持度
				Sig_L = sig_l/100;
				Sig_G = sig_g;
				stringstream ss;
				ss.precision(2);
				ss << showpoint<< Sup << "__" << Sig_L << "__" << Sig_G<<"__"<<pattern_length;
				parameter = ss.str();
				ss.clear();
				output_file = path + "output\\" + parameter + "\\DMP.txt";
				svm_p_output_file = path + "output\\" + parameter + "\\P_for_SVM.txt";
				svm_e_output_file = path + "output\\" + parameter + "\\E_for_SVM.txt";
				init();
				GFP();
			}
		}
	}*/
	return 0;
}