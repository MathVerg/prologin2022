#include <vector>
#include <iostream>

#include "utils.hh"
#include "ducktroop.hh"

using namespace std;

Ducktroop::Ducktroop(int id, Env* env)
{
    mId = id;
    mEnv = env;
}

Ducktroop::~Ducktroop()
{
}

void Ducktroop::avancerTroupe(direction dir) {
    erreur err = avancer(mId, dir);
    if (err) {
        afficher_erreur(err);
    }
}

void Ducktroop::grandirTroupe() {
    erreur err = grandir(mId);
    if (err) {
        afficher_erreur(err);
    }
}

troupe Ducktroop::thisTroupe() {
    vector<troupe> myTroupes = troupes_joueur(moi());
    if (myTroupes[0].id == mId) {
        return myTroupes[0];
    } else {
        return myTroupes[1];
    }
}

gen_state Ducktroop::getGenState() {
    return mGenState;
}

void Ducktroop::setGenState(gen_state state) {
    switch (state)
    {
    case IDLE:
        mIdleTurn = tour_actuel();
        mGenState = IDLE;
        break;
    default:
        mGenState = state;
        break;
    }
}

void Ducktroop::setPath(const dir_path& path) {
    mPath = path;
    mPosPath = pathAsPos(path, thisTroupe().maman);
    mPathIndex = 0;
}

void Ducktroop::genericPlay() {
    if (!getActionPts()) {
        return;
    } 
    switch (mGenState)
    {
    case SUICIDE:
        suicide();
        break;
    case IDLE:
        if (tour_actuel() - mIdleTurn > MAX_IDLE_TURNS) {
            setGenState(SUICIDE);
            genericPlay();
        }
        else {
            specificPlay();
        }
        break;
    case MOVING:
        moveAlong();
        break;
    }
}

void Ducktroop::specificPlay() {
    exhaustActions();
}

void Ducktroop::followPath(int steps) {
    for (int i = mPathIndex; i < mPathIndex + steps; i++) {
        avancerTroupe(mPath[i]);
    }
    mPathIndex += steps;
}

void Ducktroop::moveAlong() {
    position currentPos = thisTroupe().maman;
    if (mEnv->isBagend(currentPos)) {
        setGenState(SUICIDE);
        genericPlay();
        return;
    }
    int stepsLeft = mPath.size() - mPathIndex;
    int pts = getActionPts();
    int intendedSteps = min(pts, stepsLeft);
    position goal = mPosPath[mPosPath.size()];
    if (!(mEnv->canStartPath(mPosPath, mPathIndex, intendedSteps)) || mEnv->bagendOnPath(mPosPath)) {
        
        dir_path newPath = trouver_chemin(currentPos, goal);
        if (newPath.size()) {
            setPath(newPath);
            stepsLeft = mPath.size() - mPathIndex;
            intendedSteps = min(pts, stepsLeft);
        }
        else {
            setGenState(IDLE);
            genericPlay();
            return;
        }
    }
    followPath(intendedSteps);
    if (thisTroupe().maman == goal) {
        setGenState(IDLE);
    }
    genericPlay();
}

void Ducktroop::suicide() {
    position pos = thisTroupe().maman;
    while (getActionPts() > 0 && info_case(pos).contenu == TROU) {
        avancerTroupe(NORD);
        updatePos(&pos, NORD);
        if (!(mEnv->isMovableTo(pos))) {
            setGenState(IDLE);
            return;
        }
    }
    if (getActionPts() > 0) {
        avancerTroupe(BAS);
        setGenState(IDLE);
        return;
    }
}

void Ducktroop::exhaustActions() {
    position pos = thisTroupe().maman;
    for (int i = 0; i < getActionPts(); i++) {
        pos_vec options = mEnv->moveOptions(pos);
        if (options.size() > 0) {
            setGenState(SUICIDE);
            genericPlay();
            return;
        }
        position goal = pickPos(options);
        direction dir = findDir(pos, goal);
        avancerTroupe(dir);
    }
}

void Ducktroop::beginTurn() {
    
}

int Ducktroop::getActionPts() {
    return thisTroupe().pts_action;
}

int Ducktroop::getSize() {
    return thisTroupe().taille;
}

int Ducktroop::getInventory() {
    return thisTroupe().inventaire;
}