//#include <cmath>
#include "fp_tree.h"
//#pragma comment(linker, "/STACK:102400000,102400000")

// 全局变量
FPNode * trie_root ;
// result保存最终得到的模式 
vector<Transcation> result;
int num_fore_items;
int num_back_items;
string dmp_file;



template <class T > 
T min(T A, T B)
{
	if (A > B)
		return B;
	return A;
}

template <class T >
T max(T A, T B)
{
	if (A < B)
		return B;
	return A;
}

void get_data_num(const vector<Transcations> & fore_transactions, const vector<Transcations> & back_transactions)
{
	num_fore_items = fore_transactions.size();
	num_back_items = back_transactions.size();
	trie_root = new FPNode(Item{}, nullptr);
}

void get_dmp(string dmp_name)
{
	dmp_file = dmp_name;
}

void fptree_growth( FPTree & fptree,  Pattern & x, double limit_f, double limit_fb, double limit_b, double limit_bf)
{
	// 为了追求速度， 将pattern size 设为2
	
	if (x.transcation.size() >= pattern_length)
	{
		if (result.size() % 1000 == 0)
		{
			print_result();
		}
		return;
	}
	
	double sup = 0;
	double sig_l = 0;
	double sig_g = 0;

	int old_fore_frequency = 0;
	int old_back_frequency = 0;
	int fore_frequency = 0;
	int back_frequency = 0;

	for (pair<Item, FPNode* > y : fptree.header_table)
	//for ( map<Item, shared_ptr<FPNode> >::iterator it = fptree.header_table.end(); it != fptree.header_table.begin(); )
	{   
		//it--;
		//保护现场
		old_fore_frequency = x.fore_frequency;
		old_back_frequency = x.back_frequency;
		
		fore_frequency = 0;
		back_frequency = 0;
		FPNode * path_starting_fpnode = y.second;
		while (path_starting_fpnode)
		{
			fore_frequency += path_starting_fpnode->fore_frequency;
			back_frequency += path_starting_fpnode->back_frequency;
			path_starting_fpnode = path_starting_fpnode->node_link;
		}
		
		//将item加入x
		x.transcation.push_back(y.first);
		x.fore_frequency = fore_frequency;
		x.back_frequency = back_frequency;

		// 计算前景支持度 与 全局差异度
		sup = fore_frequency*1.0 / num_fore_items;


		/// ***** 如果 （前景频率+背景频率）/ 总数 >0.95就认为用当前pattern构造出来的是没有意义的
		/*if ((1.0*fore_frequency + back_frequency) / (num_fore_items + num_back_items) > 0.95)
		{
			x.transcation.pop_back();
			x.fore_frequency = old_fore_frequency;
			x.back_frequency = old_back_frequency;
			continue;
		}*/
		/// *****  这个处理可能会有稍微误差， 但是效率能大大增加


		//sig_g = fabs(sup - back_frequency*1.0 / num_back_items);
		bool flag = false;
		sig_g = sup - back_frequency*1.0 / num_back_items;
		if (sup >= Sup  &&  sig_g >= Sig_G)
		{
			flag = true;
			/*
			result.push_back(x.transcation);
			if (result.size() % 10000 == 0)
			{
				print_result();
			}
			*/
			//计算局部差异度
			if (back_frequency*1.0 / num_back_items <= limit_b*(sup / limit_bf - Sig_L)
				&& sup >= limit_f*(Sig_L + back_frequency*1.0 / num_back_items/limit_fb  ) )
				sig_l = get_sig_l(x, trie_root);
			else sig_l = 0;

			if (sig_l >= Sig_L)
			{
				result.push_back(x.transcation);
				if (result.size() % 1000 == 0)
				{
					print_result();
				}
			}
			insert_trie(x, 0, trie_root);
		}
		
		if (sup >= Sup)
		{
			vector<Transcations> con_fore_transactions;
			vector<Transcations> con_back_transactions;
			FPNode * path_starting_fpnode = y.second;
			while (path_starting_fpnode)
			{
				FPNode * curr_path_fpnode = path_starting_fpnode->parent;
				if (curr_path_fpnode->parent)
				{                                                                                                                                                                                                                                                                      
					Transcations fore_transaction;
					//Transcations back_transaction;
					
					while (curr_path_fpnode->parent)
					{
						fore_transaction.transcation.push_back(curr_path_fpnode->item);
						//back_transaction.transcation.push_back(curr_path_fpnode->item);
						curr_path_fpnode = curr_path_fpnode->parent;
					}

					int size = fore_transaction.transcation.size();
					for (int i = 0; i < size / 2; i++)
					{
						swap(fore_transaction.transcation[i], fore_transaction.transcation[size-1-i]);
					}

					fore_transaction.frequency = path_starting_fpnode->fore_frequency;
					con_fore_transactions.push_back(fore_transaction);
					// 加入背景集， 元素与前景集一样， 只是频率不一样
					fore_transaction.frequency = path_starting_fpnode->back_frequency;
					con_back_transactions.push_back(fore_transaction);
				}
				path_starting_fpnode = path_starting_fpnode->node_link;
			}
			FPTree conditional_fptree(con_fore_transactions, con_back_transactions);
			double temp_b, temp_bc, temp_f, temp_fb;
			if (flag && limit_b > back_frequency*1.0 / num_back_items)
			{
				temp_b = back_frequency*1.0 / num_back_items; 
				temp_bc = sup;
			}
			else { temp_b = limit_b; temp_bc = limit_bf; }
			if (flag && limit_f < sup)
			{
				temp_f = sup;
				temp_fb = back_frequency*1.0 / num_back_items;
			}
			else { temp_f = limit_f; temp_fb = limit_fb; }
			fptree_growth(conditional_fptree, x, temp_f, temp_fb, temp_b, temp_bc);
		}

		// 恢复现场
		x.transcation.pop_back();
		x.fore_frequency = old_fore_frequency;
		x.back_frequency = old_back_frequency;
	}
}

double get_sig_l(Pattern & x, FPNode *  root)
{
	double ret = 1e100;
	int xp = x.transcation.size()-1;
	//int xp = 0;
	
	int root_size = root->children.size();
	int rp = 0;

	while (xp >=0 && rp < root_size)
	{
		if (x.transcation[xp] == root->children[rp]->item)
		{
			//double temp = fabs(x.fore_frequency*1.0 / root->children[rp]->fore_frequency - x.back_frequency*1.0 / root->children[rp]->back_frequency);
			double f_frequency = 0;
			double b_frequency = 0;
			f_frequency = root->children[rp]->fore_frequency == 0 ? 1 : x.fore_frequency*1.0 / root->children[rp]->fore_frequency;
			b_frequency = root->children[rp]->back_frequency == 0 ? 1 : x.back_frequency*1.0 / root->children[rp]->back_frequency;

			double temp = f_frequency - b_frequency;
			
			ret = min (ret, temp);
			if (ret < Sig_L)
			{
				return ret;
			}
			ret = min(ret, get_sig_l(x, root->children[rp]));
			rp++;
		}
		else if (x.transcation[xp] > root->children[rp]->item)
		{
			rp++;
		}
		else
		{
			xp--;
		}
	}
	return ret;
}

void insert_trie(Pattern & x, int k, FPNode *  root)
{
	if (k < x.transcation.size())
	{
		int left = 0;
		int right = root->children.size() - 1;
		int mid = 0;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (x.transcation[k] == root->children[mid]->item)
			{
				insert_trie(x, k + 1, root->children[mid]);
				return;
			}
			else if (x.transcation[k] < root->children[mid]->item)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		FPNode * curr_fpnode_new_child = new FPNode (x.transcation[k], root);
		curr_fpnode_new_child->fore_frequency = x.fore_frequency;
		curr_fpnode_new_child->back_frequency = x.back_frequency;
		root->children.push_back(curr_fpnode_new_child);
		insert_trie(x, k + 1, curr_fpnode_new_child);
	}
}


void print_result()
{
	ofstream fout(dmp_file,ios::app);
	for (int i = 0; i < result.size(); i++)
	{
		if (!flag)
		{
			fout << "0";
		}
		else
		{
			fout << "1";
		}
		for (int j = result[i].size() - 1; j>=0; j--)
		{
			fout <<" "<< result[i][j];
		}
		fout << endl;
	}
	fout.close();
	result.clear();
	return;
}

void tail_make()
{
	dfs(trie_root);
}