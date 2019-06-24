#include <cmath>

#include "hierarchicalQueue.h"

static class hierarchicalQueueClass : public TclClass {
public:
        hierarchicalQueueClass() : TclClass("Queue/HRCC") {}
        TclObject* create(int, const char*const*) {
	         return (new hierarchicalQueue);
	}
} class_hierarchical_queue;

hierarchicalQueue::hierarchicalQueue():hierarchicalQueue(DEFAULT_VOLUME) {
}

hierarchicalQueue::hierarchicalQueue(int volume) {
    this->volume = volume;
    flows = {Flow(0, 0.1), Flow(1, 0.2), Flow(1, 0.3)};
    currentRound = 0;
}

void hierarchicalQueue::setCurrentRound(int currentRound) {
    this->currentRound = currentRound;
}

void hierarchicalQueue::enque(Packet* packet) {

    hdr_ip* iph = hdr_ip::access(packet);

    ///////////////////////////////////////////////////
    // TODO: get theory departure Round
    // You can get flowId from iph, then get
    // "lastDepartureRound" -- departure round of last packet of this flow
    int departureRound = cal_theory_departure_round(iph);
    ///////////////////////////////////////////////////

    int insertLevel = cal_insert_level(departureRound, currentRound);

    departureRound = max(departureRound, currentRound);
    if (departureRound / 100 != currentRound / 100 || insertLevel == 2) {
        if (departureRound / 100 % 10 == 5) {
            hundredLevel.enque(packet, departureRound / 10 % 10);
            // return 1;
        } else {
            // packet.setInsertLevel(2);
            levels[2].enque(packet, departureRound / 100 % 10);
            // return 2;
        }
    } else if (departureRound / 10 != currentRound / 10 || insertLevel == 1) {
        if (departureRound / 10 % 10 == 5) {
            // packet.setInsertLevel(0);
            decadeLevel.enque(packet, departureRound  % 10);
            // return 0;
        } else {
            // packet.setInsertLevel(1);
            levels[1].enque(packet, departureRound / 10 % 10);
            // return 1;
        }
    } else {
        // packet.setInsertLevel(0);
        levels[0].enque(packet, departureRound % 10);
        // return 0;
    }
}

int cal_theory_departure_round(hdr_ip* iph) {
  // int		fid_;	/* flow id */
  // int		prio_;
  // parameters in iph
  // TODO
}

int cal_insert_level(int departureRound, int currentRound) {
  return 0;
}

// Packet Scheduler::serveCycle() {
//     Packet packet = levels[0].pull();
//     if (packet.getThryDepartureRound() == -1) {
//         levels[0].getAndIncrementIndex();

//         if (levels[0].getCurrentIndex() == 0) {
//             levels[1].getAndIncrementIndex();

//             if (levels[1].getCurrentIndex() == 0)
//                 levels[2].getAndIncrementIndex();
//         }
//     }
//     return packet;
// }

// vector<Packet> Scheduler::serveUpperLevel(int &currentCycle, int currentRound) {
//     vector<Packet> result;

//     //first level 2
//     if (currentRound / 100 % 10 == 5) {
//         int size = static_cast<int>(ceil(hundredLevel.getCurrentFifoSize() * 1.0 / (10 - currentRound % 10)));
//         for (int i = 0; i < size; i++) {
//             Packet tmp = hundredLevel.pull();
//             if (tmp.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             tmp.setDepartureCycle(currentCycle);
//             tmp.setActlDepartureRound(currentRound);
//             result.push_back(tmp);
//         }
//         if (currentRound % 10 == 9)
//             hundredLevel.getAndIncrementIndex();
//     }
//     else if (!levels[2].isCurrentFifoEmpty()) {
//         int size = static_cast<int>(ceil(levels[2].getCurrentFifoSize() * 1.0 / (100 - currentRound % 100)));
//         for (int i = 0; i < size; i++) {
//             Packet tmp = levels[2].pull();
//             if (tmp.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             tmp.setDepartureCycle(currentCycle);
//             tmp.setActlDepartureRound(currentRound);
//             result.push_back(tmp);
//         }
//     }

//     // then level 1
//     if (currentRound / 10 % 10 == 5) {
//         int size = decadeLevel.getCurrentFifoSize();
//         for (int i = 0; i < size; i++) {
//             Packet tmp = decadeLevel.pull();
//             if (tmp.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             tmp.setDepartureCycle(currentCycle);
//             tmp.setActlDepartureRound(currentRound);
//             result.push_back(tmp);
//         }
//         decadeLevel.getAndIncrementIndex();
//     }
//     else if (!levels[1].isCurrentFifoEmpty()) {
//         int size = static_cast<int>(ceil(levels[1].getCurrentFifoSize() * 1.0 / (10 - currentRound % 10)));
//         for (int i = 0; i < size; i++) {
//             Packet tmp = levels[1].pull();
//             if (tmp.getPacketOrder() == -1)
//                 break;
//             currentCycle++;
//             tmp.setDepartureCycle(currentCycle);
//             tmp.setActlDepartureRound(currentRound);
//             result.push_back(tmp);
//         }
//     }

//     return result;
// }