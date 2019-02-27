#ifndef PERSON_H
#define PERSON_H

#include<vector>
#include<iostream>
#include<memory>
#include<string>
#include<stdexcept>
#include<algorithm>
#include"social_media.h"

using namespace std;

class SocialMediaAccount;

class Person: public enable_shared_from_this<Person>{
private:
	string name;
	vector<shared_ptr<SocialMediaAccount>> media_accounts;
public:
	Person(string);
	string get_name() const;
	int add_account(string, int=1);
	bool remove_account(int);
	bool share(shared_ptr<Person>, shared_ptr<SocialMediaAccount>);
	ostream& print(ostream&) const;
	ostream& print_small(ostream&) const;
	const vector<shared_ptr<SocialMediaAccount>>& get_accounts() const;
};
ostream& operator<<(ostream& o, Person p);

//----------------------ADMINISTRATION---------------------------//

#include<unordered_map>
#include<string>
#include<iostream>
//#include "person.h"
using namespace std;

struct Administration{
	unordered_map<string, shared_ptr<Person>> map;
	string create_person(string name);
	void del_person(string name);
	virtual ostream& print(ostream& o) const;
};

ostream& operator<<(ostream&, Administration);

#endif
