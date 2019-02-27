#include "person.h"
#include "social_media.h"
#include "ministry.h"
#include "management.h"
using namespace std;

int main(){

//------------Aufgabe1-----------------//

Administration NBA;

NBA.create_person("LeBron");
NBA.create_person("Kobe");

NBA.map["LeBron"]->add_account("Cavaliers", 1);
NBA.map["Kobe"]->add_account("Lakers", 0);

auto shared_acc = make_shared<VipAccount>(VipAccount("Shared", NBA.map["LeBron"]));
NBA.map["LeBron"]->share(NBA.map["Kobe"], shared_acc);

vector<shared_ptr<SocialMediaAccount>> acc_osoba2 = NBA.map["LeBron"]->get_accounts();
vector<shared_ptr<SocialMediaAccount>> acc_osoba1 = NBA.map["Kobe"]->get_accounts();
NBA.map["LeBron"]->share(NBA.map["Kobe"], acc_osoba2.at(0));

acc_osoba2[0]->write_msg(acc_osoba1[0], "LeBron's back home");
acc_osoba1[0]->write_msg(acc_osoba2[0], "Look again");

cout << *(NBA.map["LeBron"]) <<endl;
cout << *(NBA.map["Kobe"]) <<endl;

acc_osoba2[0]->print(cout);
acc_osoba1[0]->print(cout);

NBA.del_person("LeBron");
acc_osoba2[0]->clear_weak_ptr();

acc_osoba2[0]->print(cout);
acc_osoba1[0]->print(cout);

//------------Aufgabe2-----------------//

auto b = new M_NBA(50);
auto c = new M_AM(50);

b->work(10,"diligent");
b->work(5, "lazy");

c->work(10, "diligent");
c->work(5, "lazy");

b->print(cout);
c->print(cout);


//------------Aufgabe3-----------------//

auto pointa = make_shared<M_NBA>(M_NBA(50));
auto pointb = make_shared<M_AM>(M_AM(50));

Ministry nba;

nba.ptrvector.push_back(pointa);
nba.ptrvector.push_back(pointb);

nba.order(2, "lazy");
nba.order(100, "diligent");

for_each(nba.ptrvector.begin(),nba.ptrvector.end(), [&] (auto el) {
		el->print(cout);
		});

	return 0;
}