#include "person.h"

const vector<shared_ptr<SocialMediaAccount>>& Person::get_accounts() const{
	return media_accounts;
}

string Person::get_name() const{
	return name;
}

ostream& Person::print_small(ostream& out) const{
		return out << name;
}

bool Person::share(shared_ptr<Person> pers1, shared_ptr<SocialMediaAccount> account){
	size_t index {0};
	while (index < media_accounts.size()) {
		if(media_accounts.at(index) == account){
			account->add_person(pers1);
			(*pers1).media_accounts.push_back(account);
			return true;
		}
		index++;
	}
	return false;
}

bool Person::remove_account(int br_acc){
	size_t index {0};
	while (index < media_accounts.size()) {
		if(media_accounts.at(index)->get_accountnumber() == br_acc){
			media_accounts.erase(media_accounts.begin() + index);
			return true;
		}
		index++;
	}
	return false;
}

Person::Person(string name):name { name } {
	if(name.size() == 0) 
		throw runtime_error("Name too short.");
}

int Person::add_account(string name, int acc_nr){
	//VIP
	if(acc_nr == 1) {
		auto priv1 = shared_from_this();
		auto nalog = VipAccount(name,priv1);
		auto priv = make_shared<VipAccount>(nalog);
		media_accounts.push_back(priv);
		return priv->get_accountnumber();
	} else if(acc_nr == 0) { //Normal
		auto priv1 = shared_from_this();
		auto nalog = NormalAccount{name,priv1};
		auto priv = make_shared<NormalAccount>(nalog);
		media_accounts.push_back(priv);
		return priv->get_accountnumber();
	} else 
		throw runtime_error("Not a valid account.");
	return 0;
}
	
ostream& Person::print(ostream& o) const{
	o <<"[Name: " << name <<",  Accounts:{" ;
	for(size_t i = 0; i < media_accounts.size(); i++){
		if(i == 0){	
			media_accounts.at(i)->print_small(o);
		}else{
			o << ", ";
			media_accounts.at(i)->print_small(o);
		}
	}
	o<<"}]";
	return o;
}

ostream& operator<<(ostream& o, Person osoba){
	return osoba.print(cout);
}

//---------------------ADMINISTRATION------------------------//

string Administration::create_person(string name){
	auto pers_ptr = make_shared<Person>(Person(name));
	if(map.find(name) != map.end()){
		map.erase(name);
		map[name] = pers_ptr;
	} else {
		map.insert({name,pers_ptr});
	}
	return name;
}

void Administration::del_person(string name){
	if(map.find(name) != map.end()){
		map.erase(name);
	} else
		throw runtime_error("Name not found.");
}

ostream& Administration::print(ostream& o) const{
	o << "Map: [";
	for_each(map.begin(),map.end(),[&o](pair<string, shared_ptr<Person>> x){
		x.second->print(o);
		o << "\n";
	});
	o << "]";
	return o;
}

ostream& operator<<(ostream& out, Administration admin){
	return admin.print(out);
}