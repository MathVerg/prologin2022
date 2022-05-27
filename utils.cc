#include <iostream>

#include "utils.hh"

using namespace std;

pos_vec getNeighbors(const position& pos) {
    pos_vec res = {};
    position vois = pos;
    if (pos.colonne > 0) {
        vois.colonne -=1;
        res.push_back(vois);
        vois.colonne +=1;
    }
    if (pos.colonne < LARGEUR - 1) {
        vois.colonne +=1;
        res.push_back(vois);
        vois.colonne -=1;
    }
    if (pos.ligne > 0) {
        vois.ligne -=1;
        res.push_back(vois);
        vois.ligne +=1;
    }
    if (pos.ligne < HAUTEUR - 1) {
        vois.ligne +=1;
        res.push_back(vois);
        vois.ligne -=1;
    }
    return res;
}

void updatePos(position &pos, direction dir) {
    switch (dir)
    {
    case NORD:
        pos.ligne += 1;
        break;
    case SUD:
        pos.ligne -= 1;
        break;
    case EST:
        pos.colonne += 1;
        break;
    case OUEST:
        pos.colonne -= 1;
        break;
    case HAUT:
        pos.niveau += 1;
        break;
    case BAS:
        pos.niveau -= 1;
        break;
    default:
        break;
    }
}

pos_path pathAsPos(const dir_path &path, const position& start) {
    pos_path positions = {};
    position current = start;
    for (direction dir : path) {
        updatePos(current, dir);
        positions.push_back(current);
    }
    return positions;
}

bool isCrossable(position pos) {
    etat_case state = info_case(pos);
    switch (state.contenu)
    {
    case GAZON:
    case NID:
    case PAPY:
    case TROU:
    case TUNNEL:
        return true;
    case TERRE:
    case BUISSON:
        return false;
    case BARRIERE:
        switch (info_barriere(pos))
        {
        case FERMEE:
            return false;
        case OUVERTE:
            return true;
        case PAS_DE_BARRIERE:
            exit(EXIT_FAILURE);
        }
    }
}

pos_vec posFilter(std::function<bool(position)> f, const pos_vec& sample) {
    pos_vec new_pos = {};
    for (position pos : sample) {
        if (f(pos)) {
            new_pos.push_back(pos);
        }
    }
    return new_pos;
}

dir_path closestPos(const position& ref, const pos_vec& list) {
    if (list.size() == 0) {
        cerr << "Position list is empty !" << endl;
        exit(EXIT_FAILURE);
    }
    dir_path best_path = {};
    for (position goal : list) {
        dir_path path = trouver_chemin(ref, goal);
        if (path.size() > 0 ) {
            if (best_path.size() && best_path.size() > path.size()) {
                best_path = path;
            }
        }
    }
    return best_path;
}

dir_path closePos(const position& ref, const pos_vec& list, uint dmax) {
    for (position goal : list) {
        dir_path path = trouver_chemin(ref, goal);
        if (path.size() && path.size() <= dmax ) {
            return path;
        }
    }
    return {};
}

bool isDucked(position& pos) {
    vector<troupe> troops = troupes_joueur(moi());
    vector<troupe> othertroops = troupes_joueur(adversaire());
    troops.insert(troops.begin(), othertroops.begin(), othertroops.end());
    for (troupe t : troops) {
        for (position can : t.canards) {
            if (pos == can) {
                return true;
            }
        }
    }
    return false;
}