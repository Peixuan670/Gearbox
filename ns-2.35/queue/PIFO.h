#include "Level.h"
#include "Flow.h"
#include <vector>

#include<iostream>
#include<string>
#include<queue>
#include<time.h>
#include<algorithm>
#include <functional>


using namespace std;

class PIFO : public Queue {
private:
    static const int SET_NUMBER = 7;
    static const int SET_GRANULARITY = 10;       // TimeStamp Range of each queue set (level.cc)
    static const int DEFAULT_VOLUME = 7;
    int volume;                     // num of levels in scheduler
    int currentRound;           // current Round
    int pktCount;           // packet count

    // 08052019

    typedef pair<Packet*, int>unitPair;

    struct cmp{
        bool operator() (unitPair a, unitPair b) {
            return (a.second < b.second);
        }
    }
    
    priority_queue<unitPair, vector<unitPair>, cmp> pq;

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
    PIFO();
    explicit PIFO(int);
    void enque(Packet*);
    Packet* deque();
    void setCurrentRound(int);
    int cal_theory_departure_round(hdr_ip*, int);
    int cal_insert_level(int, int);
    // Packet* serveCycle();
    // vector<Packet> serveUpperLevel(int &, int);
};