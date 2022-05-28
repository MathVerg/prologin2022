#pragma once
/**
 * Represents a ducktroop, can be used as it or herited from
 */
#include "api.hh"
#include "env.hh"

#define MAX_IDLE_TURNS 3

typedef enum gen_state {
        IDLE, //nothing to do
        MOVING, //on the way to a given point
        SUICIDE //SUICIDE
    } gen_state;

class Ducktroop
{
private:

    /**
     * The generic state
     */
    gen_state mGenState;
protected:
    /**
     * The troupe id
     */
    int mId;

    /**
     * The global environment
     */
    Env* mEnv;

    /**
     * The path to be followed
     */
    dir_path mPath;

    /**
     * The same, as a position path
     */
    pos_path mPosPath;

    /**
     * the position in the path
     */
    int mPathIndex;

    /**
     * when did it start to be idle
     */
    int mIdleTurn;
public:
    Ducktroop(int id, Env* env);

    virtual ~Ducktroop();
    /**
     * Object-oriented versions of the troop action
     */
    void avancerTroupe(direction dir);

    /**
     * Object-oriented versions of the troop action
     */
    void grandirTroupe();

    /**
     * Returns the troupe struct corresponding to this troupe
     */
    troupe thisTroupe();

    /**
     * Accessors for the generic state
     */
    gen_state getGenState();
    void setGenState(gen_state state);

    /**
     * set a goal to achieve
     */
    void setPath(const dir_path& path);

    /**
     * plays according to the generic state
     */
    void genericPlay();

    /**
     * plays according to the specific state
     */
    virtual void specificPlay();

    /**
     * Follow the path for a given number of steps
     */
    void followPath(int steps);

    /**
     * follow its path
     */
    void moveAlong();

    /**
     * die, as fast as possible
     */
    void suicide();

    /**
     * try to move without dying in order to have no action left
     */
    void exhaustActions();

    /**
     * actions to do at the beginning of a turn
     */
    void beginTurn();

    /**
     * how many actions are left for this turn
     */
    int getActionPts();

    /**
     * Size of the troupe
     */
    int getSize();

    /**
     * inventaire
     */
    int getInventory();
};
