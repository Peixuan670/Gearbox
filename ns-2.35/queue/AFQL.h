#include "Level.h"
#include "Flow.h"
#include <vector>

using namespace std;

class AFQL : public Queue {
private:
    static const int DEFAULT_VOLUME = 1;
    int volume;                     // num of levels in scheduler
    int currentRound;           // current Round
    int pktCount;           // packet count
    //Level levels[3];
    Level levels[1];
    //Level hundredLevel;
    //Level decadeLevel;
    vector<Flow> flows;
    //06262019 Peixuan
    vector<Packet*> pktCurRound;

    // 06262019 Peixuan
    vector<Packet*> runRound();
    //vector<Packet*> serveUpperLevel(int); // HCS -> AFQ
    void setPktCount(int);
public:
    //hierarchicalQueue();
    //explicit hierarchicalQueue(int);
    AFQL();
    explicit AFQL(int);
    void enque(Packet*);
    Packet* deque();
    void setCurrentRound(int);
    int cal_theory_departure_round(hdr_ip*, int);
    int cal_insert_level(int, int);
    // Packet* serveCycle();
    // vector<Packet> serveUpperLevel(int &, int);
};