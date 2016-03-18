#pragma once
#include "const.h"
bool flag;

string  parameter = "0.6__0.9__0.6";
string  output_file = path + "output\\" + parameter + "\\DMP.txt";
string  svm_p_output_file = path + "output\\" + parameter + "\\P_for_SVM.txt";
string  svm_e_output_file = path + "output\\" + parameter + "\\E_for_SVM.txt";

//const int num_fore_items = 217;
//const int num_back_items = 78;
//  每条trainscation 有22个item， 一共100+种item

double Sup = 0.6;     // 前景集支持度
double Sig_L = 0.9;
double Sig_G = 0.6;