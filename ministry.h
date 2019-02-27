#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<memory>
#include<algorithm>
#include"management.h"

using namespace std;

struct Ministry {
	vector<shared_ptr<Management>> ptrvector;
	bool order(int, string);
};