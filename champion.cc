/**
 * @author Matheo Vergnolle (mvergnolle)
 * I tried to make generic and proper code.
 * It took me quite a time, but it is now easy to define new behaviors and test new strategies
 * We have two important things :
 * - an environment, which contains up do date information about the field (bagends, position of nests, etc.)
 * - a strategy, which tells how to actually play
 * The strategy can rely on troops. Troops have general routines for getting to an objective, and can be inherited to specify their behavior.
 * I have written two specified troops so far : Baker (fetch bread) and Rusher (rush to own the free nests), but more can be writtn, with different behaviors.
 * A strategy can also make use of a bush placing loop and a tunnel digging loop (not sure I will have the time to implement them though)
 * And then, I tried different combinations of troops and loops until I found something satisfactory...
 * With more time I would have made a python script that generate strategies and run them againt different maps and opponents to find a good one.
 */

#include <vector>
#include <array>
#include <iostream>

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
    if (DEBUG) cout << "Environment initialized" << endl;
    strat.init();
    if (DEBUG) cout << "Strategy initialized" << endl;
}

/// Fonction appelée à chaque tour.
void jouer_tour()
{   
    if (DEBUG) cout << "----" << endl << "Turn " << 2*tour_actuel() << endl << "****" << endl;
    if (tour_actuel() == ROUND_FERMETURE + 1) {
        env.init(); //recompute environment at the barrier switch
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
