#include "object.h"
#include <vector>
using namespace std;

vector<Object*> Objects = vector<Object*>();

void register_object(Object* object)
{
	Objects.push_back(object);
}

void unregister_object(Object* object)
{
	vector<Object*>::iterator it;
	for (it = Objects.begin(); it != Objects.end(); ++it)
	{
		if ((*it) != object)
			continue;

		Objects.erase(it);
		return;
	}
}

vector<Object*>& get_all_objects()
{
	return Objects;
}
