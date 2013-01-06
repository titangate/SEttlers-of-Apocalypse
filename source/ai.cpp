#include "ai.h"
#include "resource.h"
#include <utility>
#include <algorithm>

using namespace std;

SimpleChip::SimpleChip(Chip* c):generateRate(c->generateRate), fortification(c->fortification), 
upgrades(c->upgrades), owner(c->owner), currentUpgrade(c->currentUpgrade), chargeCount(c->chargeCount), game(c->game) {};

SimpleCurrent::SimpleCurrent(Current* cur):owner(cur->getOwner()),charges(cur->getCharges()), currentSpeed(cur->getCurrentSpeed()), src(cur->getSource()), dest(cur->getTarget()) {
    distanceToTarget = src->wires[dest]->getLength();
}

SimpleChip AI::predict(Chip* c, double t) {
    SimpleChip s(c);
    vector<pair<double, SimpleCurrent*> > currentImpacts;
    double upgradeCompletionTime;
    //TimeCostItem
    for (map<Player*, set<SimpleCurrent*> >::iterator i = currents.begin(); i != currents.end(); i++) {
        for (set<SimpleCurrent*>::iterator cur = i->second.begin(); cur != i->second.end(); cur++) {
            if ((*cur)->src == c) {
                currentImpacts.push_back(pair<double, SimpleCurrent*>((*cur)->estTimeArrival(), *cur));
            }
        }
    }
    sort(currentImpacts.begin(), currentImpacts.end());
    //c->currentUpgrade->getTimeCost()
}