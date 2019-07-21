//
// Created by Zhou Yitao on 2018-12-04.
//

#include "Level.h"

Level::Level(): volume(10), currentIndex(0) {
    // Debug: Peixuan 07062019 Level Constructor
    // Bug: where is FIFO itself?

    // Debug: Peixuan 07062019 Level Constructor
    for (int i=0; i<10; i++) {
        fifos[i] = new PacketQueue;
    }
    //fprintf(stderr, "Constructed Level\n"); // Debug: Peixuan 07062019

}

void Level::enque(Packet* packet, int index) {
    // packet.setInsertFifo(index);
    // packet.setFifoPosition(static_cast<int>(fifos[index].size()));
    // hdr_ip* iph = hdr_ip::access(packet);

    fifos[index]->enque(packet);
}

Packet* Level::deque() {
    Packet *packet;

    fprintf(stderr, "Dequeue from this level\n"); // Debug: Peixuan 07062019

    if (isCurrentFifoEmpty()) {
        fprintf(stderr, "No packet in the current serving FIFO\n"); // Debug: Peixuan 07062019
        return 0;
    }
    packet = fifos[currentIndex]->deque();
    return packet;
}

int Level::getCurrentIndex() {
    return currentIndex;
}

void Level::setCurrentIndex(int index) {
    currentIndex = index;
}

void Level::getAndIncrementIndex() {
    if (currentIndex + 1 < volume) {
        currentIndex++;
    } else {
        currentIndex = 0;
    }
}

bool Level::isCurrentFifoEmpty() {
    fprintf(stderr, "Checking if the FIFO is empty\n"); // Debug: Peixuan 07062019
    //fifos[currentIndex]->length() == 0;
    //fprintf(stderr, "Bug here solved\n"); // Debug: Peixuan 07062019
    return fifos[currentIndex]->length() == 0;
}

int Level::getCurrentFifoSize() {
    return fifos[currentIndex]->length();
}
