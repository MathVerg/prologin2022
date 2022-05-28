#include "ducktroop-baker.hh"
#include <iostream>

using namespace std;

string reprBakerState(baker_state state) {
    switch (state)
    {
    case LOADING:
        return "LOADING";
    case FULL :
        return "FULL";
    default:
        return "unknown state";
    }
}

DucktroopBaker::DucktroopBaker(int id, Env* env) : Ducktroop(id, env)
{
}

DucktroopBaker::DucktroopBaker(int id, Env* env, int goalSize) : Ducktroop(id, env)
{
    mGoalSize = goalSize;
}

DucktroopBaker::~DucktroopBaker()
{
}

int DucktroopBaker::getGoalSize() {
    return mGoalSize;
}

void DucktroopBaker::setGoalSize(int s){
    mGoalSize = s;
}

void DucktroopBaker::specificPlay() {
    if (DEBUG) cout << "Baker state is " << reprBakerState(mState) << endl;
    if (getSize() < mGoalSize) {
        if (DEBUG) cout << "To small, go bigger" << endl;
        grandirTroupe();
    }
    if (getGenState() == IDLE) {
        if (DEBUG) cout << "Inventory " << getInventory() << " and size " << getSize() << endl;
        if (mState == LOADING && getInventory() == getSize()/3) {
            mState = FULL;
        }
        else if (mState == FULL && getInventory() == 0) {
            mState = LOADING;
        }
        position pos = thisTroupe().maman;
        dir_path goal;
        switch (mState)
        {
            case LOADING:
                if (DEBUG) cout << "Searching for bread" << endl;
                goal = mEnv->findClosestBread(pos);
                if (!goal.size()) {
                    if (DEBUG) cout << "No bread found, searching for papy" << endl;
                    goal = mEnv->findClosest(pos, PAPY);
                }
                break;
            case FULL:
                if (DEBUG) cout << "Searching for a nest of mine" << endl;
                goal = closestPos(pos, posFilter(isNestMine, mEnv->getNests()));
                if (!goal.size()) {
                    if (DEBUG) cout << "No nest found, searching for free nest" << endl;
                    goal = closestPos(pos, posFilter(isNestFree, mEnv->getNests()));
                }
            break;
        }
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
    }
    genericPlay();
}