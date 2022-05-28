#include <vector>
#include <iostream>

#include "utils.hh"
#include "ducktroop.hh"

using namespace std;

Ducktroop::Ducktroop(Env* env)
{
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

gen_state Ducktroop::getState() {
    return mGenState;
}

void Ducktroop::setPath(const dir_path& path) {
    mPath = path;
    mPosPath = pathAsPos(path, thisTroupe().maman);
    mPathIndex = 0;
}

void Ducktroop::genericPlay() {
    if (!actionPts()) {
        return;
    } 
    switch (mGenState)
    {
    case SPECIFIC:
        specificPlay();
        break;
    case SUICIDE:
        suicide();
        break;
    case IDLE:
        exhaustActions();
        break;
    case MOVING:
        moveAlong();
        break;
    }
}

void Ducktroop::specificPlay() {
    cerr << "No specific behavior" << endl;
}

void Ducktroop::getNewGoal() {
    mGenState = IDLE;
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
        mGenState = SUICIDE;
        genericPlay();
        return;
    }
    int stepsLeft = mPath.size() - mPathIndex;
    int pts = actionPts();
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
            mGenState = IDLE;
            genericPlay();
            return;
        }
    }
    followPath(intendedSteps);
    getNewGoal();
    genericPlay();
}

void Ducktroop::suicide() {
    position pos = thisTroupe().maman;
    while (actionPts() > 0 && info_case(pos).contenu == TROU) {
        avancerTroupe(NORD);
        updatePos(&pos, NORD);
        if (!(mEnv->isMovableTo(pos))) {
            mGenState = IDLE;
            return;
        }
    }
    if (actionPts() > 0) {
        avancerTroupe(BAS);
        mGenState = IDLE;
        return;
    }
}

void Ducktroop::exhaustActions() {
    position pos = thisTroupe().maman;
    for (int i = 0; i < actionPts(); i++) {
        pos_vec options = mEnv->moveOptions(pos);
        if (options.size() > 0) {
            mGenState = SUICIDE;
            genericPlay();
            return;
        }
        position goal = options[0]; //TODO : pick randomly
        direction dir = findDir(pos, goal);
        avancerTroupe(dir);
    }
}

void Ducktroop::beginTurn() {
    
}

int Ducktroop::actionPts() {
    return thisTroupe().pts_action;
}