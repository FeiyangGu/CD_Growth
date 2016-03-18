#pragma once
#include "fp_tree.h"
#include <iostream>
#include <sstream>
using namespace std;
void EVALUATE(vector<Transcations> & t_fore_transactions, vector<Transcations> & t_back_transactions);
// Count 统计每个pattern能够在测试集中匹配到多少record
void Count(vector<Transcations> & t_transactions, vector< vector<int> > & pattern, vector<int>& count_t);
// Count2 统计出数据集中的record被pattern覆盖的数目
int Count2(vector<Transcations> & t_transactions, vector< vector<int> > & pattern);
void print_test(vector<Transcations> & t_fore_transactions, vector<Transcations> & t_back_transactions);
void get_svm_data(vector<Transcations> & t_fore_transactions, string path, vector<Transcations>& pattern, int label);


