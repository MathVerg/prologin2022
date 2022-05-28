#include "ducktroop-baker.hh"

DucktroopBaker::DucktroopBaker(int id, Env* env) : Ducktroop(id, env)
{
    mGoalSize = TAILLE_DEPART;
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
    if (getSize() < mGoalSize) {
        grandirTroupe();
    }
    if (getGenState() == IDLE) {
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
            goal = mEnv->findClosestBread(pos);
            if (!goal.size()) {
                goal = mEnv->findClosest(pos, PAPY);
            }
            break;
        case FULL:
            goal = closestPos(pos, posFilter(isNestMine, mEnv->getNests()));
            if (!goal.size()) {
                goal = closestPos(pos, posFilter(isNestFree, mEnv->getNests()));
            }
            break;
        }
        if (goal.size()) {
            setGenState(MOVING);
        }
        else {
            exhaustActions();
        }
    }
    genericPlay();
}