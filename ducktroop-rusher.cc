#include "ducktroop-rusher.hh"
#include <iostream>

using namespace std;

DucktroopRusher::DucktroopRusher(int id, Env* env) : Ducktroop(id, env)
{
}

DucktroopRusher::~DucktroopRusher()
{
}

void DucktroopRusher::specificPlay() {
    position pos = thisTroupe().maman;
    dir_path goal;
    goal = closestPos(pos, posFilter(isNestFree, mEnv->getNests()));
    if (goal.size()) {
        if (DEBUG) cout << "Found a goal, moving there" << endl;
        setPath(goal);
        setGenState(MOVING);
    }
    else {
        if (DEBUG) cout << "No goal found, going IDLE" << endl;
        exhaustActions();
        setGenState(IDLE);
    }
    genericPlay();
}

void DucktroopRusher::goalReachedAction() {
    if (DEBUG) cout << "Goal reached !" << endl;
}