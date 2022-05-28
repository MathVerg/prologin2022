#include "troopless-loops.hh"

#include <vector>

using namespace std;


void oneBushKillPerTurn(Env *env, int threshold) {
    if (score(moi()) >= threshold) {
        vector<troupe> adv = troupes_joueur(adversaire());
        for (troupe t : adv) {
            position pos = t.maman;
            pos_vec possib = env->moveOptions(pos);
            if ((!env->isBagend(pos))
                && possib.size() == 1
                && info_case(possib[0]).est_constructible
                && t.inventaire > 0
                ){
                    env->construireBuisson(possib[0]);
            }
        }
    }
}