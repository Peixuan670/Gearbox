//
// Created by Zhou Yitao on 2018-12-04.
//

#include "Level.h"

Level::Level(): volume(10), currentIndex(0) {
}

void Level::enque(Packet* packet, int index) {
    // packet.setInsertFifo(index);
    // packet.setFifoPosition(static_cast<int>(fifos[index].size()));
    // hdr_ip* iph = hdr_ip::access(packet);

    fifos[index]->enque(packet);
}

Packet* Level::deque() {
    Packet *packet;

    if (isCurrentFifoEmpty()) {
        return 0;
    }
    packet = fifos[currentIndex]->deque();
    return packet;
}

int Level::getCurrentIndex() {
    return currentIndex;
}

void Level::getAndIncrementIndex() {
    if (currentIndex + 1 < volume) {
        currentIndex++;
    } else {
        currentIndex = 0;
    }
}

bool Level::isCurrentFifoEmpty() {
    return fifos[currentIndex]->length() == 0;
}

int Level::getCurrentFifoSize() {
    return fifos[currentIndex]->length();
}
