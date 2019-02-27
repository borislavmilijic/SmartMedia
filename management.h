#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<memory>
#include<algorithm>
#include"person.h"
#include"social_media.h"

using namespace std;

class Management: public Administration {
	double efficiency;
public:
	Management(double);
	virtual double work_effect(int, string) const = 0;
	bool work(int, string);
	std::ostream& print(std::ostream&) const;
};

class M_NBA: public Management {
public:
	M_NBA(double);
	double work_effect(int,string) const;
};

class M_AM: public Management {
public:
	M_AM(double);
	double work_effect(int, string) const;
};
