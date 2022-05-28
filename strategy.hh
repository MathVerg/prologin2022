#pragma once
#include "env.hh"

class Strategy
{
protected:
    /**
     * game environment, propagated to the troops
     */
    Env* mEnv;

    /**
     * strategy phase, for miscellaneous uses
     */
    int mPhase = 0;

    /**
     * ids of my troops
     */
    std::vector<int> mIds;
public:
    Strategy(Env* env);
    virtual ~Strategy();

    /**
     * initializes on a given env
     */
    virtual void init();

    /**
     * override with the actual strategy
     */
    virtual void play();
};