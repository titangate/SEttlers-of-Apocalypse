//
//  resource.cpp
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-06.
//
//

#include "resource.h"

AttSubitems TimeCostItem::getAttSubitems(Chip * c){
    AttSubitems att = {
        ExampleRenderer::getInstance().getImage("time.png"),
        "Time",
        toString((int)time_elapsed),
        toString((int)(time-time_elapsed)),
        toString((int)time),
        ATT_NEGATIVE,
        ATT_NEGATIVE
    };
    return att;
}

AttSubitems ChargeCostItem::getAttSubitems(Chip * c){
    AttSubitems att = {
        ExampleRenderer::getInstance().getImage("button_glow.png"),
        "Charges",
        toString((int)c->chargeCount),
        toString((int)cost),
        toString((int)(c->chargeCount - cost)),
        ATT_NEGATIVE,
        upgradable(c)?ATT_NEGATIVE:ATT_DISABLE
    };
    return att;
}

vector<AttSubitems> Upgrade::getAttSubitems(unsigned int level,vector<AttSubitems> att){
    for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
        att.push_back((*i)->getAttSubitems(c));
    }
    if (tci[level]) {
        att.push_back(tci[level]->getAttSubitems(c));
    }
    return att;
}

void GenerationUpgrade::applyUpgrade(unsigned int level){
    Upgrade::applyUpgrade(level);
    c->generateRate -= genRateModifier;
    vec2 s = c->dimension.size;
    genRateModifier = level * s.x*s.y/20000;
    c->generateRate += genRateModifier;
}

void GenerationUpgrade::applyUpgrade(SimpleChip * sc, unsigned int level) {
    //sc->generateRate -= genRateModifier;
    vec2 s = c->dimension.size;
    //genRateModifier = level * s.x*s.y/20000;
    sc->generateRate = sc->generateRate - genRateModifier + level * s.x*s.y/20000;
}

vector<AttSubitems> GenerationUpgrade::getAttSubitems(unsigned int level,vector<AttSubitems> at){
    vec2 s = c->dimension.size;
    struct AttSubitems att = {
        getIcon(),
        "Generation",
        toString(c->generateRate*60),
        toString(s.x*s.y/20000*60),
        toString((c->generateRate+s.x*s.y/20000)*60),
        ATT_POSITIVE,
        ATT_POSITIVE
    };
    vector<AttSubitems> t;
    t.push_back(att);
    return Upgrade::getAttSubitems(level,t);
}

GenerationUpgrade::GenerationUpgrade(Chip * chip,unsigned int level,unsigned int maxlevel):Upgrade(chip,level,maxlevel),genRateModifier(0){
    for (unsigned int i=0; i<10; i++) {
        vec2 s = chip->getSize();
        addCost(i, new ChargeCostItem(i*s.x*s.y/2000));
        setTimeCost(i,i*15);
    }
}

double FortificationUpgrade::getFortification(unsigned int level){
    const double fortificationConstant = .1;
    return level*fortificationConstant/(1+level*fortificationConstant);
}

void FortificationUpgrade::applyUpgrade(unsigned int level){
    Upgrade::applyUpgrade(level);
    c->fortification = getFortification(level);
}

void FortificationUpgrade::applyUpgrade(SimpleChip* sc, unsigned int level) {
    sc->fortification = getFortification(level);
}


vector<AttSubitems> FortificationUpgrade::getAttSubitems(unsigned int level,vector<AttSubitems> at){
    vec2 s = c->dimension.size;
    stringstream ss;
    ss.setf(ios::fixed, ios::floatfield);
    ss.precision(1);
    ss << 100*c->fortification << "%";
    string current = ss.str();
    ss.str("");
    ss.precision(1);
    ss << 100*getFortification(level) << "%";
    string after = ss.str();
    ss.str("");
    ss.precision(1);
    ss << (getFortification(level)-c->fortification)*100 << "%";
    string diff = ss.str();
    
    struct AttSubitems att = {
        getIcon(),
        "Fortification",
        current,
        after,
        diff,
        ATT_POSITIVE,
        ATT_POSITIVE
    };
    vector<AttSubitems> t;
    t.push_back(att);
    return Upgrade::getAttSubitems(level,t);
}


FortificationUpgrade::FortificationUpgrade(Chip * chip,unsigned int level,unsigned int maxlevel):Upgrade(chip,level,maxlevel){
    for (unsigned int i=0; i<10; i++) {
        vec2 s = chip->getSize();
        addCost(i, new ChargeCostItem(i*s.x*s.y/2000));
        setTimeCost(i,i*15);
    }
}