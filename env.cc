#include <iostream>

#include "env.hh"
#include "utils.hh"

using namespace std;

Env::Env(){
}

Env::~Env()
{
}

void Env::construireBuisson(position pos) {
    erreur err = construire_buisson(pos);
    if (err) {
        afficher_erreur(err);
    }
    updateBagends(pos);
}

void Env::creuserTunnel(position pos) {
    erreur err = creuser_tunnel(pos);
    if (err) {
        afficher_erreur(err);
    }
}

void Env::init() {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            mBagends[i][j] = false;
        }
    }
    position pos;
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            pos.ligne = i;
            pos.colonne = j;
            if (!isCrossable(pos)) {
                updateBagends(pos);
            }
            etat_case state = info_case(pos); 
            switch (state.contenu)
            {
            case PAPY:
                mPapys.push_back(pos);
                break;
            case NID:
                mNests.push_back(pos);
                break;
            case TROU:
                mHoles.push_back(pos);
                break;
            default:
                break;
            }
        }
    }
    mPapys = filterBagend(mPapys);
    mNests = filterBagend(mNests);
}

void Env::updateBagends(const position& pos) {
    if (isBagend(pos)) {
        return;
    }
    vector<position> ok_neighbors = filterBagend(getNeighbors(pos)); 
    if (!isCrossable(pos) || ok_neighbors.size() < 2 ) {
        mBagends[pos.ligne][pos.colonne] = true;
        for (position vois : ok_neighbors) {
            updateBagends(vois);
        }
    }
}

bool Env::isBagend(const position& pos) {
    return mBagends[pos.ligne][pos.colonne];
}

bool Env::isNotBagend(const position& pos) {
    return !mBagends[pos.ligne][pos.colonne];
}

pos_vec Env::filterBagend(const pos_vec& sample) {
    pos_vec new_pos = {};
    for (position pos : sample) {
        if (isNotBagend(pos)) {
            new_pos.push_back(pos);
        }
    }
    return new_pos;
}

void Env::updateFromOpponent() {
    vector<action_hist> history = historique();
    for (action_hist act : history) {
        switch (act.action_type)
        {
        case ACTION_CONSTRUIRE:
            updateBagends(act.action_pos);
            break;
        default:
            break;
        }
    }
}

dir_path Env::findClosest(const position& pos, type_case& casetype) {
    switch (casetype)
    {
    case PAPY:
        return closestPos(pos, mPapys);
    case NID:
        return closestPos(pos, mNests);
    case TROU :
        return closestPos(pos, mHoles);
    default:
        cerr << "Not implemented case type ";
        afficher_type_case(casetype);
        exit(EXIT_FAILURE);
    }
 }

 dir_path Env::findClose(const position& pos, type_case& casetype, uint dmax) {
    switch (casetype)
    {
    case PAPY:
        return closePos(pos, mPapys, dmax);
    case NID:
        return closePos(pos, mNests, dmax);
    case TROU :
        return closePos(pos, mHoles, dmax);
    default:
        cerr << "Not implemented case type : ";
        afficher_type_case(casetype);
        exit(EXIT_FAILURE);
    }
 }

 bool Env::isMovableTo(const position& pos) {
    return !(isBagend(pos) || isDucked(pos));
 }

 pos_vec Env::filterMovable(const pos_vec& sample) {
    pos_vec new_pos = {};
    for (position pos : sample) {
        if (isMovableTo(pos)) {
            new_pos.push_back(pos);
        }
    }
    return new_pos;
 }

 pos_vec Env::moveOptions(const position& pos) {
    return filterMovable(getNeighbors(pos));
 }

 bool Env::bagendOnPath(const pos_path& path) {
    for (position pos : path) {
        if (isBagend(pos)) {
            return true;
        }
    }
    return false;
 }

 bool Env::canStartPath(const pos_path& path, int start, int steps) {
    for (int i = start; i < start + steps; i++) {
        if (!isMovableTo(path[i])) {
            return false;
        }
    }
    return true;
 }
