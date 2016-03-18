#pragma once

#include <string>
using namespace std;
extern string dir;
extern string kind;
extern string source;
extern string source_p;
extern string source_e;
extern string profold;
extern string parameter;
extern string times;
extern string input;
extern string output;
extern string cv_nu;
extern string dmp;
extern string train;
extern string test;
extern string train_svm;
extern string test_svm;

void mk_profold();
void mk_parafold(double sup, double sig_l, double sig_g, int pattern_length);
void mk_timesfold(int time);
void mk_input();
void mk_output();
void mk_cv_nu(int nu);
