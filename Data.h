#pragma once
#include <string>
#include "fp_tree.h"
using namespace std;
void split(string file_p, string file_e);
void readdata(vector<Transcations>& fore_transactions, vector<Transcations>& back_transactions, int k);
void write_data_svm();
void trans_data_svm(string file, string file_svm, vector<Transcations> & pattern);