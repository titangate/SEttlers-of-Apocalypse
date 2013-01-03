//
//  resource.h
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-06.
//
//

#ifndef __SEofASE__resource__
#define __SEofASE__resource__

#include "structure.h"
#include "ai.h"


class CostItem {
    
    
public:
    virtual void applyUpgrade(Chip*) = 0;
    virtual bool upgradable(Chip*) = 0;
    virtual AttSubitems getAttSubitems(Chip*) = 0;
};

class TimeCostItem {
public:
    double time;
    double time_elapsed;
    void applyUpgrade(Chip* c){
        
    }
    bool upgradable(Chip* c){
        return true;
    }
    virtual AttSubitems getAttSubitems(Chip * c);
    bool update(double t){
        return (time_elapsed+=t)>=time;
    }
    TimeCostItem(double t):time(t),time_elapsed(0){}
    double getProgress(){
        return time_elapsed/time;
    }
};

class ChargeCostItem: public CostItem {
    unsigned int cost;
public:
    ChargeCostItem(unsigned int c):cost(c){}
    void applyUpgrade(Chip* c){
        c->chargeCount -= cost;
    }
    bool upgradable(Chip* c){
        return c->chargeCount >= cost;
    }
    virtual AttSubitems getAttSubitems(Chip * c);
};

class Upgrade {
protected:
    unsigned int lvl;
    vector<CostItem*> costs[10];
    //vector<CostItem*> effects[10];
    unsigned int maxlvl;
    Chip * c;
    TimeCostItem * tci[10];
public:
    virtual string getName(){return "Upgrade";}
    //virtual unsigned int cost();
    void setTimeCost(unsigned int level,double t){
        tci[level] = new TimeCostItem(t);
    }
    TimeCostItem* getTimeCost(unsigned int level){
        return tci[level];
    }
    virtual CIw2DImage* getIcon(){return 0;}
    virtual double getProgress(){
        if (tci[getLevel()+1]) {
            return tci[getLevel()+1]->getProgress();
        }
        return 0;
    };
    virtual void applyCost(unsigned int level){
        for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
            (*i)->applyUpgrade(c);
        }
    }
    virtual void applyUpgrade(unsigned int level){
        /*for (vector<CostItem*>::iterator i=effects[level].begin(); i!=effects[level].end(); i++) {
            (*i)->applyUpgrade(c);
        }*/
        lvl = level;
    }
    virtual void applyUpgrade(SimpleChip*, unsigned int level) = 0;
    virtual bool upgradable(unsigned int level){
        for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
            if (!(*i)->upgradable(c))return false;
        }
        return true;
    }
    virtual vector<AttSubitems> getAttSubitems(unsigned int level,vector<AttSubitems> att = vector<AttSubitems>());
    void addCost(unsigned int level,CostItem* c){
        costs[level].push_back(c);
    }
    
    unsigned int getLevel(){
        return lvl;
    }
    Upgrade(Chip * chip,unsigned int level = 0,unsigned int maxlevel = 10):c(chip),lvl(level),maxlvl(maxlevel){
        for (unsigned int i=0; i<10; i++) {
            tci[i] = 0;
        }
    }
    ~Upgrade(){
        for (unsigned int level =0; level<10; level++) {
            for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
                delete(*i);
            }
            delete tci[level];
        }
        
    }
    bool update(double t){
        return tci[getLevel()+1]->update(t);
    }
};


class GenerationUpgrade :public Upgrade {
    double genRateModifier;
public:
    virtual string getName(){return "Generation";}
    CIw2DImage* getIcon(){return ExampleRenderer::getInstance().getImage("generation.png");}
    void applyUpgrade(unsigned int level);
    void applyUpgrade(SimpleChip*, unsigned int level);
    virtual vector<AttSubitems> getAttSubitems(unsigned int level,vector<AttSubitems> at = vector<AttSubitems>());
    GenerationUpgrade(Chip * chip,unsigned int level = 0,unsigned int maxlevel = 10);
};

class FortificationUpgrade:public Upgrade {
    static double getFortification(unsigned int);
public:
    virtual string getName(){return "Fortification";}
    CIw2DImage* getIcon(){return ExampleRenderer::getInstance().getImage("fortification.png");}
    void applyUpgrade(unsigned int level);
    void applyUpgrade(SimpleChip*, unsigned int level);
    virtual vector<AttSubitems> getAttSubitems(unsigned int level,vector<AttSubitems> at = vector<AttSubitems>());
    FortificationUpgrade(Chip * chip,unsigned int level = 0,unsigned int maxlevel = 10);
};
#endif /* defined(__SEofASE__resource__) */
