#include <iostream>
#include <vector>
#include <random>

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

dir_vec availableDirs(const position& pos) {
    dir_vec res = {};
    if (pos.ligne > 0) {
        res.push_back(SUD);
    }
    if (pos.ligne < LARGEUR - 1) {
        res.push_back(NORD);
    }
    if (pos.colonne > 0) {
        res.push_back(OUEST);
    }
    if (pos.colonne < HAUTEUR - 1) {
        res.push_back(EST);
    }
    return res;
}

bool isDirOk(const position& pos, direction dir) {
    switch (dir) {
        case NORD:
            return pos.ligne < LARGEUR - 1;
        case SUD:
            return pos.ligne > 0;
        case EST :
            return pos.colonne < HAUTEUR - 1;
        case OUEST :
            return pos.colonne > 0;
        default :
            return false;
    }
}

void updatePos(position* pos, direction dir) {
    switch (dir)
    {
    case NORD:
        pos->ligne += 1;
        break;
    case SUD:
        pos->ligne -= 1;
        break;
    case EST:
        pos->colonne += 1;
        break;
    case OUEST:
        pos->colonne -= 1;
        break;
    case HAUT:
        pos->niveau += 1;
        break;
    case BAS:
        pos->niveau -= 1;
        break;
    default:
        break;
    }
}

pos_path pathAsPos(const dir_path &path, const position& start) {
    pos_path positions = {};
    position current = start;
    for (direction dir : path) {
        updatePos(&current, dir);
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
    return false; //suppress compiler warning
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
        if (DEBUG) cout<< "No path found because list is empty" << endl;
        return {};
    }
    dir_path best_path = {};
    for (position goal : list) {
        dir_path path = trouver_chemin(ref, goal);
        if (path.size() > 0 ) {
            if (DEBUG) cout<< "Found a path !" << endl;
            if ((!best_path.size()) || best_path.size() > path.size()) {
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

bool isDucked(const position& pos) {
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

bool posKills(const position& pos) {
    return (!isCrossable(pos)) || isDucked(pos);
}

int manhattanDistance(const position& a, const position& b) {
    int x = abs(a.ligne - b.ligne);
    int y = abs(a.colonne - b.colonne);
    return x + y;
}

direction findDir(const position& pos, const position& goal) {
    if (pos.ligne < goal.ligne ) {
        return NORD;
    }
    if (pos.ligne > goal.ligne ) {
        return SUD;
    }
    if (pos.colonne < goal.colonne ) {
        return EST;
    }
    if (pos.colonne > goal.colonne ) {
        return OUEST;
    }
    if (pos.niveau < goal.niveau ) {
        return HAUT;
    }
    if (pos.niveau > goal.niveau ) {
        return BAS;
    }
    cerr << "Same positions !";
    exit(EXIT_FAILURE);
}

int pickNumber(int low, int high) {
    std::random_device r;
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(low, high);
    int idx = uniform_dist(e1);
    return idx;
}

direction pickDir(const dir_vec& sample) {
    int idx = pickNumber(0, sample.size() - 1 );
    return sample[idx];
}

position pickPos(const pos_vec& sample) {
    int idx = pickNumber(0, sample.size() - 1 );
    return sample[idx];
}

bool isNestMine(const position& pos) {
    return info_nid(pos) == moi();
}

bool isNestFree(const position& pos) {
    return info_nid(pos) == LIBRE;
}
bool isNestAdversary(const position& pos) {
    return info_nid(pos) == adversaire();
}

vector<int> getTroupesId(int joueur) {
    vector<troupe> troupes = troupes_joueur(joueur);
    vector<int> ids = {};
    for (troupe t : troupes) {
        ids.push_back(t.id);
    }
    return ids;
}

pos_vec getMotherPos() {
    pos_vec res;
    vector<troupe> troupes = troupes_joueur(moi());
    for (troupe t : troupes) {
        res.push_back(t.maman);
    }
    troupes = troupes_joueur(adversaire());
    for (troupe t : troupes) {
        res.push_back(t.maman);
    }
    return res;
}