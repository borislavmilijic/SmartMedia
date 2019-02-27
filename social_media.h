#ifndef SOCIALMEDIAACCOUNT_H
#define SOCIALMEDIAACCOUNT_H

#include<vector>
#include<iostream>
#include<memory>
#include<string>
#include "person.h"
using namespace std;

class Person;

class SocialMediaAccount{
	constexpr static size_t message_limit{100};

	int score;
	string name;
	int accountnumber;

	vector<weak_ptr<Person>> authorized_person;
	vector<string> messages;

	void add_msg(const string);

	static int broj_naloga;
	public:
	SocialMediaAccount(string, shared_ptr<Person>);
	~SocialMediaAccount();
	bool add_person(shared_ptr<Person>);
	bool clear_weak_ptr();
	void clear_messages();
	virtual int calc_score(string) = 0 ;
	void write_msg(shared_ptr<SocialMediaAccount>, string);
	size_t size() const;
	int get_accountnumber() const;
	virtual ostream& print(ostream&)const;
	ostream& print_small(ostream&)const;
};

class VipAccount: public SocialMediaAccount{

	public:
		VipAccount(string, shared_ptr<Person>);
		ostream& print(ostream&) const;
		int calc_score(string);
};

class NormalAccount: public SocialMediaAccount{

	public:
		NormalAccount(string, shared_ptr<Person>);
		ostream& print(ostream&) const;
		int calc_score(string);
};
#endif
