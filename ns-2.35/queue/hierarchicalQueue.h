#include "Level.h"
#include "Flow.h"
#include <vector>

using namespace std;

class hierarchicalQueue : public Queue {
private:
    static const int DEFAULT_VOLUME = 3;
    int volume;                     // num of levels in scheduler
    int currentRound;           // current Round
    Level levels[3];
    Level hundredLevel;
    Level decadeLevel;
    Flow flows[2];
public:
    hierarchicalQueue();
    explicit hierarchicalQueue(int);
    void enque(Packet*);
    Packet* deque();
    void setCurrentRound(int);
    int cal_theory_departure_round(hdr_ip*);
    // Packet* serveCycle();
    // vector<Packet> serveUpperLevel(int &, int);
};