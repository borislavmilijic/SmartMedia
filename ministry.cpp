#include "ministry.h"

bool Ministry::order(int hours, string mode) {
	bool ind = false;

	for_each(ptrvector.begin(),ptrvector.end(), [&] (auto el) {
		if(el->work(hours, mode))
			ind = true;});
	return ind;
}