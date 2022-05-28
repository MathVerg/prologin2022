#pragma once
#include "env.hh"

/**
 * attempts to kill an enemy that has only one place to go (exept backends, of course)
 * @param threshold the score threshold above which this action is activated
 */
void oneBushKillPerTurn(Env *env, int threshold);