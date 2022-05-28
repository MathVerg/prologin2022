#pragma once
/**
 * A ducktroop that tries to conquer the free nests
 */

#include "ducktroop.hh"

class DucktroopRusher : public Ducktroop
{
private:
    /* data */
public:
    DucktroopRusher(int id, Env* env);
    virtual ~DucktroopRusher();

    /**
     * override the parent class specific
     */
    void specificPlay() override;

    /**
     * action to do once the goal is reached
     */
    void goalReachedAction() override;
};

