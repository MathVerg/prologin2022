#include "utils.hh"

using namespace std;

vector<position> neighbors(const position& pos) {
    vector<position> res = {};
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