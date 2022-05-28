#pragma once
/**
 * A ducktroop that merely seeks for bread then bring it back
 */

#include "ducktroop.hh"
#include <string>

typedef enum baker_state {
        LOADING, //not full of bread, looking for bread
        FULL, //full of bread
    } baker_state;

/**
 * String representation of the state
 */
std::string reprBakerState(baker_state state);

class DucktroopBaker : public Ducktroop
{
private:
    int mGoalSize = TAILLE_DEPART;
    baker_state mState = LOADING;
public:
    DucktroopBaker(int id, Env* env);
    DucktroopBaker(int id, Env* env, int goalSize);
    virtual ~DucktroopBaker();

    /**
     * accessors for goal size
     */
    int getGoalSize();
    void setGoalSize(int s);

    /**
     * override the parent class specific
     */
    void specificPlay() override;

};