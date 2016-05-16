
#include <queue>
#include "AstarNode.h"

template <class T>
class PriorityUpdateQueue : public std::priority_queue < T >
{

public:
	PriorityUpdateQueue()<T>;
	~PriorityUpdateQueue()<T>;

	// Check if entry already exists and update if it does
	bool updateEntry(<T> inUpdate) {
		
	};

private:

};