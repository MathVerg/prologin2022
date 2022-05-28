#include <vector>
#include <array>

#include "api.hh"
#include "utils.hh"
#include "env.hh"
#include "strategy-test.hh"

using namespace std;

Env env;
StrategyTest strat(&env);

/// Fonction appelée au début de la partie.
void partie_init()
{
    env.init();
    strat.init();
}

/// Fonction appelée à chaque tour.
void jouer_tour()
{
    if (tour_actuel() == ROUND_FERMETURE + 1) {
        env.init();
    } else {
        env.updateFromOpponent();
    }
    strat.play();
}

/// Fonction appelée à la fin de la partie.
void partie_fin()
{
    // TODO
}
