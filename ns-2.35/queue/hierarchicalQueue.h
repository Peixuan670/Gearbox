#include <string.h>
#include <vector>
#include "queue.h"
#include "address.h"

using namespace std;

class hierarchicalQueue : public Queue {
 public:
    hierarchicalQueue(int volumn = DEFAULT_VOLUME) { 
		levels = vector<vector<PacketQueue>>(volumn, vector<PacketQueue>(10));
        this->volumn = volumn;
		currentRound = 0;
	}

 protected:
    void enque(Packet*);
	Packet* deque();
    vector<vector<PacketQueue>> levels;

    int volumn;
    int currentRound;
    static const int DEFAULT_VOLUME = 3;

};