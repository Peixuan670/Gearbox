//
// Created by Zhou Yitao on 2018-12-04.
//

#include "Flow.h"

Flow::Flow(int id, float weight) {
    this->flowId = id;
    this->weight = weight;
    this->insertLevel = 0;
    this->lastDepartureRound = 0;
}

int Flow::getLastDepartureRound() const {
    return lastDepartureRound;
}

void Flow::setLastDepartureRound(int lastDepartureRound) {
    Flow::lastDepartureRound = lastDepartureRound;
}

float Flow::getWeight() const {
    return weight;
}

void Flow::setWeight(float weight) {
    Flow::weight = weight;
}

int Flow::getInsertLevel() const {
    return insertLevel;
}

void Flow::setInsertLevel(int insertLevel) {
    Flow::insertLevel = insertLevel;
}
