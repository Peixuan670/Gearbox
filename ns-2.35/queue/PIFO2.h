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

class PIFO2 : public Queue {
private:
    static const int DEFAULT_VOLUME = 3;
    int volume;                     // num of levels in scheduler
    int currentRound;           // current Round
    int pktCount;           // packet count

    struct Unit {
        Packet* packet;
        int finishTime;
    };

    struct cmp{
        bool operator() (Unit a, Unit b) {
            return (a.finishTime < b.finishTime);
        }
    };
    //priority_queue<unitPair, vector<unitPair>, cmp> pq;
    //priotiry_queue<Unit> pq;

    priority_queue<Unit, vector<Unit>, cmp> pq;

    Level levels[3];
    Level levelsB[2];       // Back up Levels

    Level hundredLevel;
    Level decadeLevel;

    //Level hundredLevelB;    // Back up Levels
    Level decadeLevelB;     // Back up Levels

    bool level0ServingB;          // is serve Back up Levels
    bool level1ServingB;          // is serve Back up Levels

    vector<Flow> flows;
    //06262019 Peixuan
    vector<Packet*> pktCurRound;

    // 06262019 Peixuan
    vector<Packet*> runRound();
    vector<Packet*> serveUpperLevel(int);
    void setPktCount(int);
public:
    PIFO2();
    explicit PIFO2(int);
    void enque(Packet*);
    Packet* deque();
    void setCurrentRound(int);
    int cal_theory_departure_round(hdr_ip*, int);
    int cal_insert_level(int, int);
    // Packet* serveCycle();
    // vector<Packet> serveUpperLevel(int &, int);
};