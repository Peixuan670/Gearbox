#include "Level.h"
#include "Flow.h"
#include <vector>

using namespace std;

class AFQ_10 : public Queue {
private:
    static const int SET_NUMBER = 7;
    static const int SET_GRANULARITY = 10;       // TimeStamp Range of each queue set (level.cc)
    static const int DEFAULT_VOLUME = 7;
    int volume;                     // num of levels in scheduler
    int currentRound;           // current Round
    int pktCount;           // packet count
    //Level levels[3];
    Level levels[SET_NUMBER];        // same queue number with HCS
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
    AFQ_10();
    explicit AFQ_10(int);
    void enque(Packet*);
    Packet* deque();
    void setCurrentRound(int);
    int cal_theory_departure_round(hdr_ip*, int);
    int cal_insert_level(int, int);
    // Packet* serveCycle();
    // vector<Packet> serveUpperLevel(int &, int);
};