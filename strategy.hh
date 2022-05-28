#pragma once
#include "env.hh"

class Strategy
{
protected:
    Env* mEnv;
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