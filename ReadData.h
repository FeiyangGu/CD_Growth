#pragma once

#include "fp_tree.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<Transcations> Readdata(string file);
void  Readdata(string file, vector<Transcations>& transactions, vector<Transcations>& t_transactions);