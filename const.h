/*
	本程序要求数据的item是整体频率是单调减的
*/

#pragma once
#include <string>
//#pragma comment(linker, "/STACK:10240000000,10240000000")
using namespace std;
const string  path = "H:\\BaiDuYun\\Recover\\H\\Feiyang\\Documents\\Visual_Studio_2013\\Projects\\Con_Dpm\\Con_Dpm\\Data\\vote\\";
const string  foreground_file = path + "input\\p_vote.txt";
const string  background_file = path + "input\\e_vote.txt";
const int pattern_length = 3;
//const int num_fore_items = 3916;
//const int num_back_items = 4208;

//const string  path = "E:\\C++\\Con_Dpm\\Con_Dpm\\Data\\Disc_gene\\";
//const string  foreground_file = path + "input\\disc_geneV20_0.txt";
//const string  background_file = path + "input\\disc_geneV20_1.txt"; 