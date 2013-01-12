#include "ai.h"
#include "resource.h"
#include <utility>
#include <algorithm>

using namespace std;

SimpleChip::SimpleChip(Chip* c):generateRate(c->generateRate), fortification(c->fortification), 
upgrades(c->upgrades), owner(c->owner), currentUpgrade(c->currentUpgrade), chargeCount(c->chargeCount), game(c->game) {};

SimpleCurrent::SimpleCurrent(Current* cur):current(cur),owner(cur->getOwner()),charges(cur->getCharges()), currentSpeed(cur->getCurrentSpeed()), src(cur->getSource()), dest(cur->getTarget()) {
    distanceToTarget = src->wires[dest]->getLength();
}


AI::AI(Game* g,Player* p):game(g),me(p),neutral(0) {
	// neutral not defined
	// game->players is private
	for (set<Player*>::iterator pit=game->players.begin();pit!=game->players.end();pit++) {
		currents[*pit] = set<SimpleCurrent*>();
		if ((*pit)!=me && (*pit)!=neutral) {
			enemies.insert(*pit);
		}
	}

}

AI::~AI() {
    for (map<Player*, set<SimpleCurrent*> >::iterator i = currents.begin(); i != currents.end(); i++) {
        for (set<SimpleCurrent*>::iterator sci = i->second.begin(); sci != i->second.end(); sci++) {
            delete *sci;
        }
		i->second.clear();
    }
}


void AI::currentSent(Current* cur) {
	SimpleCurrent* scur = new SimpleCurrent(cur);
	currents[scur->owner].insert(scur);
	return;
}
void AI::currentReceived(Current* cur) {
	Player* curOwner = cur->getOwner();
	for (set<SimpleCurrent*>::iterator scit=currents[curOwner].begin();
		 scit != currents[curOwner].end();
		 scit++) {
		if ((*scit)->current == cur) {
			delete *scit;
			scit = 0;
			currents[curOwner].erase(scit);
			return;
		}
	}
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

	// do stuff
	return s;
}