#include <algorithm>
#include <cassert>
#include <utility>
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include "fp_tree.h"

int hh = 0;

FPNode::FPNode(Item  item, FPNode * paren):
item(item), fore_frequency(0), back_frequency(0), node_link(nullptr), parent(paren), children()
{
   
}
FPNode::~FPNode()
{
	
}

void  dfs(FPNode * rt)
{
	for (int i = 0; i < rt->children.size(); i++)
	{
		dfs(rt->children[i]);
		rt->children[i] = NULL;
	}
	delete rt;
}

FPTree::~FPTree()
{
	//cout << root->item << endl;
	dfs(root );
}

FPTree::FPTree(const vector<Transcations> & fore_transactions, const vector<Transcations> & back_transactions) 
{
	root = new FPNode(Item{}, nullptr);

	for (const Transcations & transactions : fore_transactions)
	{
		FPNode * curr_fpnode = root;
		int frequency = transactions.frequency;

		for (int i = 0; i < transactions.transcation.size(); i++)
		{
			Item	item = transactions.transcation[i];	
			bool flag = false;
			if (curr_fpnode->children.size() != 0)
			{
				for (int j = 0; j < curr_fpnode->children.size(); j++)
				{
					if (curr_fpnode->children[j]->item == item)
					{
						flag = true;
						curr_fpnode->children[j]->fore_frequency += frequency;
						curr_fpnode = curr_fpnode->children[j];
						break;
					}
				}
			}
			if (!flag)
			{
				FPNode * curr_fpnode_new_child = new FPNode (item, curr_fpnode);
				curr_fpnode_new_child->fore_frequency = frequency;
				curr_fpnode->children.push_back(curr_fpnode_new_child);
				if (header_table.count(curr_fpnode_new_child->item)) 
				{
					FPNode* prev_fpnode = laster_table[curr_fpnode_new_child->item];
					prev_fpnode->node_link = curr_fpnode_new_child;
					laster_table[curr_fpnode_new_child->item] = curr_fpnode_new_child;
				}
				else
				{
					header_table[curr_fpnode_new_child->item] = curr_fpnode_new_child;
					laster_table[curr_fpnode_new_child->item] = curr_fpnode_new_child;
				}
				curr_fpnode = curr_fpnode_new_child;
			}
		}
	}


	for (const Transcations & transactions : back_transactions)
	{
		FPNode * curr_fpnode = root;
		for (int i = 0; i < transactions.transcation.size(); i++)
		{
			Item	item = transactions.transcation[i];
			int frequency = transactions.frequency;
			bool flag = false;
			if (curr_fpnode->children.size() != 0)
			{
				for (int j = 0; j < curr_fpnode->children.size(); j++)
				{
					if (curr_fpnode->children[j]->item == item)
					{
						flag = true;
						curr_fpnode->children[j]->back_frequency += frequency;
						curr_fpnode = curr_fpnode->children[j];
						break;
					}
				}
			}
			if (!flag)
			{
				FPNode * curr_fpnode_new_child = new FPNode(item, curr_fpnode);
				curr_fpnode_new_child->back_frequency = frequency;
				curr_fpnode->children.push_back(curr_fpnode_new_child);
				if (header_table.count(curr_fpnode_new_child->item))
				{
					FPNode * prev_fpnode = laster_table[curr_fpnode_new_child->item];
					prev_fpnode->node_link = curr_fpnode_new_child;
					laster_table[curr_fpnode_new_child->item] = curr_fpnode_new_child;
				}
				else
				{
					header_table[curr_fpnode_new_child->item] = curr_fpnode_new_child;
					laster_table[curr_fpnode_new_child->item] = curr_fpnode_new_child;
				}
				curr_fpnode = curr_fpnode_new_child;
			}
		}
	}
}