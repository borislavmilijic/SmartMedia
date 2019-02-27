#include "management.h"
#include "person.h"

Management::Management (double d) {
	if(efficiency < 0 && efficiency > 100) {
		throw runtime_error("Invalid efficiency");
	} else {
	efficiency = d;
	}
}

bool Management::work(int hours, string mode) {
	double sum = work_effect(hours,mode);

	if(0< sum && sum >100)
		return false;
	efficiency += sum;
	return true;
}

std::ostream& Management::print(std::ostream& o) const {
	Administration::print(o);
	cout << " Efficiency: " << efficiency << endl;
	return o;
}

M_NBA::M_NBA(double d): Management (d) {}

double M_NBA::work_effect(int hours, string mode) const {
	double we=0;
	if(mode=="diligent") {
		we=1;
	} else we=-1;

	return hours*2.5*we;
}

M_AM::M_AM(double d): Management(d) {}

double M_AM::work_effect(int h, string str) const {
	double we=0;
	if(str=="diligent") {
		we=1;
	} else we=-1;

	return h*5*we;
}