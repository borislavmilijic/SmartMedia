#include "social_media.h"
#include <algorithm>

int SocialMediaAccount::broj_naloga = 1;

NormalAccount::NormalAccount(string name, shared_ptr<Person> osoba):SocialMediaAccount(name,osoba) { }

VipAccount::VipAccount(string name, shared_ptr<Person> osoba): SocialMediaAccount(name,osoba) { }

SocialMediaAccount::SocialMediaAccount(string ime, shared_ptr<Person> osoba): name { ime } {
	if (ime.length() == 0) {
		throw runtime_error("Name too short.");
	}
	score = 0;
	authorized_person.push_back(osoba);
	accountnumber = broj_naloga++;
}

SocialMediaAccount::~SocialMediaAccount() {}

ostream& SocialMediaAccount::print(ostream& o)const{
	o << "[Name: " << name << ", id: " << get_accountnumber() <<  ",  Msgs: {";
	for(size_t i = 0; i < messages.size(); i++){
		if(i == 0){	
	 		o<<messages.at(i);
		}else{
			o << ", ";
			o << messages.at(i);
		}
	}
	o << "}, Owner: {";
	for(size_t i = 0; i < authorized_person.size(); i++){
		if(i == 0){	
	 		authorized_person.at(i).lock()->print_small(o);
		}else{
			o << ", ";
			authorized_person.at(i).lock()->print_small(o);
		}
	}
	o << "},  Score: {" << to_string(score) << "}]";
	return o;
}

ostream& SocialMediaAccount::print_small(ostream& o)const{
	o << "[Name: "<< name << ", Owner: {";	
	for(size_t i = 0; i < authorized_person.size(); i++){
		if(i == 0){	
	 		authorized_person.at(i).lock()->print_small(o);
		}else{
			o << ", ";
			authorized_person.at(i).lock()->print_small(o);
		}
	}
	o << "}, #Msgs: "<< messages.size() << "]";
	return o;
}

ostream& NormalAccount::print(ostream& out) const{
	SocialMediaAccount::print(out) << " (Normal)" << endl;
	return out;
}

ostream& VipAccount::print(ostream& out) const{
	SocialMediaAccount::print(out) << " (VIP)" << endl;
	return out;
}

bool SocialMediaAccount::add_person(shared_ptr<Person> osoba){		
	for (auto index : authorized_person)
		if(auto ap = index.lock())
			while (ap == osoba)
				return false;
	authorized_person.push_back(osoba);
	return true;
}

bool SocialMediaAccount::clear_weak_ptr(){
		size_t size = authorized_person.size();
		authorized_person.erase(
		remove_if(authorized_person.begin(),authorized_person.end(),
		[](weak_ptr<Person> pokaz) { return pokaz.expired(); }),authorized_person.end());
		if(size != authorized_person.size())
			return true;
		return false;
}

void SocialMediaAccount::write_msg(shared_ptr<SocialMediaAccount> osoba_ptr, string poruka){
	if(poruka.size() > message_limit){
		throw runtime_error("Message too long!");
	}
	score += calc_score(poruka);
	(*osoba_ptr).messages.push_back(poruka);
}

void SocialMediaAccount::clear_messages(){
	messages.clear();
}

size_t SocialMediaAccount::size() const{
	return messages.size();
}

int SocialMediaAccount::get_accountnumber() const{
	return accountnumber;
}
		
int VipAccount::calc_score(string rez){
	int score = (10 + rez.length()) % 20;
	return score;
}
		
int NormalAccount::calc_score(string rez){
	int score = (5+rez.length())%10;
	return score;
}