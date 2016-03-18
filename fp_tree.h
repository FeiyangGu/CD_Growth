#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include "const.h"

//#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;
using Item = int;
using Transcation = vector<Item>;

struct  Transcations
{
	Transcation transcation;
	int frequency;
};

struct  Pattern
{
	Transcation transcation;
	int fore_frequency;
	int back_frequency;
};

struct  FPNode 
{

    Item item;
	int fore_frequency;
	int back_frequency;
	FPNode * node_link;
	FPNode * parent;
	vector< FPNode *> children;
	FPNode(Item item,  FPNode *);
	~FPNode();
};

struct FPTree
{
	FPNode * root;
	map<Item, FPNode * > header_table;
	map<Item, FPNode * > laster_table;
	FPTree(const vector<Transcations> &, const vector<Transcations> &);
	
	~FPTree();
};

void fptree_growth(FPTree & fptree, Pattern & x, double limit_f, double fb, double limit_b, double limit_bf);
void print_result();
double get_sig_l(Pattern & x, FPNode *  root);
void insert_trie(Pattern & x, int k,  FPNode*  root);
void  dfs(FPNode *);
void tail_make();
void get_data_num(const vector<Transcations> & fore_transactions, const vector<Transcations> & back_transactions);
void get_dmp(string dmp_file);
// 全局变量
//shared_ptr<FPNode> trie_root({}, nullptr);
// result保存最终得到的模式 
// vector<Transcation> result;

extern bool flag;
extern string  parameter;
extern string  output_file;
extern string  svm_p_output_file;
extern string  svm_e_output_file;
//const int num_fore_items = 217;
//const int num_back_items = 78;
//  每条trainscation 有22个item， 一共100+种item

extern double Sup;     // 前景集支持度
extern double Sig_L;
extern double Sig_G;