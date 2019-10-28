#include <cmath>

#include "PIFO2.h"
//#include "PIFO.h"

static class PIFO2Class : public TclClass {
public:
        PIFO2Class() : TclClass("Queue/HRCC") {}
        TclObject* create(int, const char*const*) {
            fprintf(stderr, "Created new TCL PIFO instance\n"); // Debug: Peixuan 07062019
	        return (new PIFO2);
	}
} class_hierarchical_queue;

PIFO2::PIFO2():PIFO2(DEFAULT_VOLUME) {
    fprintf(stderr, "Created new PIFO instance\n"); // Debug: Peixuan 07062019
}

PIFO2::PIFO2(int volume) {
    fprintf(stderr, "Created new PIFO instance with volumn = %d\n", volume); // Debug: Peixuan 07062019
    this->volume = volume;
    flows.push_back(Flow(0, 2, 100));
    flows.push_back(Flow(1, 2, 100));
    flows.push_back(Flow(2, 2, 100));
    flows.push_back(Flow(3, 2, 100));
    flows.push_back(Flow(4, 2));        //07062019: Peixuan adding more flows for strange flow 3 problem
    flows.push_back(Flow(5, 2));        //07062019: Peixuan adding more flows for strange flow 3 problem
    flows.push_back(Flow(6, 2));        //07062019: Peixuan adding more flows for strange flow 3 problem
    //flows.push_back(Flow(1, 0.2));
    // Flow(1, 0.2), Flow(2, 0.3)};
    currentRound = 0;
    pktCount = 0; // 07072019 Peixuan
    //pktCurRound = new vector<Packet*>;
}

void PIFO2::setCurrentRound(int currentRound) {
    fprintf(stderr, "Set Current Round: %d\n", currentRound); // Debug: Peixuan 07062019
    this->currentRound = currentRound;

    level0ServingB = ((int)(currentRound/10)%2);
    level1ServingB = ((int)(currentRound/100)%2);

    fprintf(stderr, "Set Round: %d, level 0 serving B = %d, level 1 serving B = %d.\n", currentRound, level0ServingB, level1ServingB); // Debug: Peixuan 07062019

}

void PIFO2::setPktCount(int pktCount) {
    fprintf(stderr, "Set Packet Count: %d\n", pktCount); // Debug: Peixuan 07072019
    this->pktCount = pktCount;
}

void PIFO2::enque(Packet* packet) {   
    hdr_ip* iph = hdr_ip::access(packet);
    int pkt_size = packet->hdrlen_ + packet->datalen();

    fprintf(stderr, "AAAAA Start Enqueue Flow %d Packet\n", iph->saddr()); // Debug: Peixuan 07062019

    ///////////////////////////////////////////////////
    // TODO: get theory departure Round
    // You can get flowId from iph, then get
    // "lastDepartureRound" -- departure round of last packet of this flow
    int departureRound = cal_theory_departure_round(iph, pkt_size);
    ///////////////////////////////////////////////////

    // 20190626 Yitao
    /* With departureRound and currentRound, we can get the insertLevel, insertLevel is a parameter of flow and we can set and read this variable.
    */

    int flowId = iph->flowid();
    int insertLevel = 0;

    departureRound = max(departureRound, currentRound);

    if ((departureRound - currentRound) >= 7 * 10) {
        fprintf(stderr, "?????Exceeds maximum round, drop the packet from Flow %d\n", iph->saddr()); // Debug: Peixuan 07072019
        drop(packet);
        return;   // 07072019 Peixuan: exceeds the maximum round
    }

    
    int curFlowID = iph->saddr();   // use source IP as flow id
    int curBrustness = flows[curFlowID].getBrustness();
    if ((departureRound - currentRound) >= curBrustness) {
        fprintf(stderr, "?????Exceeds maximum brustness, drop the packet from Flow %d\n", iph->saddr()); // Debug: Peixuan 07072019
        drop(packet);
        return;   // 07102019 Peixuan: exceeds the maximum brustness
    }

    flows[curFlowID].setLastDepartureRound(departureRound);

    struct Unit unit;

    unit.packet = packet;
    unit.finishTime = departureRound;
    pq.push(unit);


    setPktCount(pktCount + 1);
    fprintf(stderr, "Packet Count ++\n");

    fprintf(stderr, "Finish Enqueue\n");
}

// Peixuan: This can be replaced by any other algorithms
int PIFO2::cal_theory_departure_round(hdr_ip* iph, int pkt_size) {
    //int		fid_;	/* flow id */
    //int		prio_;
    // parameters in iph
    // TODO

    // Peixuan 06242019
    // For simplicity, we assume flow id = the index of array 'flows'

    fprintf(stderr, "$$$$$Calculate Departure Round at VC = %d\n", currentRound); // Debug: Peixuan 07062019

    //int curFlowID = iph->saddr();   // use source IP as flow id
    int curFlowID = iph->flowid();   // use flow id as flow id
    float curWeight = flows[curFlowID].getWeight();
    int curLastDepartureRound = flows[curFlowID].getLastDepartureRound();
    int curStartRound = max(currentRound, curLastDepartureRound);

    fprintf(stderr, "$$$$$Last Departure Round of Flow%d = %d\n",iph->saddr() , curLastDepartureRound); // Debug: Peixuan 07062019
    fprintf(stderr, "$$$$$Start Departure Round of Flow%d = %d\n",iph->saddr() , curStartRound); // Debug: Peixuan 07062019

    //int curDeaprtureRound = (int)(curStartRound + pkt_size/curWeight); // TODO: This line needs to take another thought

    int curDeaprtureRound = (int)(curStartRound + curWeight); // 07072019 Peixuan: basic test

    fprintf(stderr, "$$$$$At Round: %d, Calculated Packet From Flow:%d with Departure Round = %d\n", currentRound, iph->saddr(), curDeaprtureRound); // Debug: Peixuan 07062019
    // TODO: need packet length and bandwidh relation
    //flows[curFlowID].setLastDepartureRound(curDeaprtureRound);
    return curDeaprtureRound;
}

//06262019 Peixuan deque function of Gearbox:

//06262019 Static getting all the departure packet in this virtual clock unit (JUST FOR SIMULATION PURPUSE!)

Packet* PIFO2::deque() {

    fprintf(stderr, "Start Dequeue\n"); // Debug: Peixuan 07062019




    /*if (pktCurRound.size()) {
        // Pop out the first packet in pktCurRound until it is empty
        //Packet* pkt = pktCurRound.
        Packet *p = pktCurRound.front();
        pktCurRound.erase(pktCurRound.begin());

        hdr_ip* iph = hdr_ip::access(p);
        fprintf(stderr, "Dequeue Packet p with soure IP: %x\n", iph->saddr()); // Debug: Peixuan 07062019
        return p;
    } else {
        fprintf(stderr, "Empty Round\n"); // Debug: Peixuan 07062019
        pktCurRound = this->runRound();
        this->setCurrentRound(currentRound + 1); // Update system virtual clock
        this->deque();
    }*/

    if (pktCount == 0) {
        fprintf(stderr, "Scheduler Empty\n"); // Debug: Peixuan 07062019
        return 0;
    }

    Unit unit = pq.top();
    pq.pop();
    Packet* p = unit.packet;

    fprintf(stderr, "PIFO dequeue packet with Finish Time of %d\n", unit.finishTime);
    setPktCount(pktCount - 1);
    fprintf(stderr, "Packet Count --\n");

    hdr_ip* iph = hdr_ip::access(p);
    fprintf(stderr, "*****Dequeue Packet p with soure IP: %x\n", iph->saddr()); // Debug: Peixuan 07062019

    return p;

}

vector<Packet*> PIFO2::runRound() {
    fprintf(stderr, "Run Round\n"); // Debug: Peixuan 07062019

    vector<Packet*> result;

    int curServeSet = (currentRound / 10) % 7;    // Find the current serving set

    fprintf(stderr, "Serving Set %d\n", curServeSet); // Debug: Peixuan 08022019

    Packet* p = levels[curServeSet].deque();

    //fprintf(stderr, "Get packet pointer\n"); // Debug: Peixuan 07062019

    if (!p) {
        fprintf(stderr, "No packet\n"); // Debug: Peixuan 07062019
    }

    while (p) {

        hdr_ip* iph = hdr_ip::access(p);                   // 07092019 Peixuan Debug

        fprintf(stderr, "^^^^^At Round:%d, Round Deque Flow %d Packet From Level %d: fifo %d\n", currentRound, iph->saddr(), curServeSet, levels[curServeSet].getCurrentIndex()); // Debug: Peixuan 07092019

        result.push_back(p);
        p = levels[curServeSet].deque();
    }

    levels[curServeSet].getAndIncrementIndex();               // Level 0 move to next FIFO
    fprintf(stderr, "<<<<<At Round:%d, Level %d update current FIFO as: fifo %d\n", currentRound, curServeSet, levels[curServeSet].getCurrentIndex()); // Debug: Peixuan 07212019

    return result;

}



// This is the trail to implement the real logic
/*Packet* PIFO2::deque(){
    // If level 0 not empty, dequeue from level 0 and update the virtual clock by packet's finish time

    Packet* pkt = levels[0]->deque();
    if (pkt) {
        //this->setCurrentRound(max(pkt->departureRound, currentRound)); // update virtual clock (We don't have packet's deaprture time)
        return pkt;
    }
    pkt = levels[1]->deque();
    if (pkt) {
        return pkt;
    }
    pkt = levels[2]->deque();
    if (pkt) {
        return pkt;
    }
    // ToDo, update round and get packet from the next FIFO in level 0
    return 0;
}*/

// vector<Packet> Scheduler::serveUpperLevel(int &currentCycle, int currentRound) {
//     vector<Packet> result;

//     //first level 2
//     if (currentRound / 100 % 10 == 5) {
//         int size = static_cast<int>(ceil(hundredLevel.getCurrentFifoSize() * 1.0 / (10 - currentRound % 10)));
//         for (int i = 0; i < size; i++) {
//             Packet p = hundredLevel.pull();
//             if (p.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             p.setDepartureCycle(currentCycle);
//             p.setActlDepartureRound(currentRound);
//             result.push_back(p);
//         }
//         if (currentRound % 10 == 9)
//             hundredLevel.getAndIncrementIndex();
//     }
//     else if (!levels[2].isCurrentFifoEmpty()) {
//         int size = static_cast<int>(ceil(levels[2].getCurrentFifoSize() * 1.0 / (100 - currentRound % 100)));
//         for (int i = 0; i < size; i++) {
//             Packet p = levels[2].pull();
//             if (p.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             p.setDepartureCycle(currentCycle);
//             p.setActlDepartureRound(currentRound);
//             result.push_back(p);
//         }
//     }

//     // then level 1
//     if (currentRound / 10 % 10 == 5) {
//         int size = decadeLevel.getCurrentFifoSize();
//         for (int i = 0; i < size; i++) {
//             Packet p = decadeLevel.pull();
//             if (p.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             p.setDepartureCycle(currentCycle);
//             p.setActlDepartureRound(currentRound);
//             result.push_back(p);
//         }
//         decadeLevel.getAndIncrementIndex();
//     }
//     else if (!levels[1].isCurrentFifoEmpty()) {
//         int size = static_cast<int>(ceil(levels[1].getCurrentFifoSize() * 1.0 / (10 - currentRound % 10)));
//         for (int i = 0; i < size; i++) {
//             Packet p = levels[1].pull();
//             if (p.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             p.setDepartureCycle(currentCycle);
//             p.setActlDepartureRound(currentRound);
//             result.push_back(p);
//         }
//     }

//     return result;
// }