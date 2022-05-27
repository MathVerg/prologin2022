/**
 * Represents a ducktroop, can be used as it or herited from
 */
#include "api.hh"

class Ducktroop
{
private:
protected:
    int id;
protected:
    /**
     * Object-oriented versions of the troop action
     */
    erreur avancer(direction dir);

    /**
     * Object-oriented versions of the troop action
     */
    erreur grandir();

    /**
     * follow its path for a given number of steps
     */
    void move_along(int steps);

    /**
     * set a goal to achieve
     */
    void set_goal(position pos);

    /**
     * die, as fast as possible
     */
    void suicide();

    /**
     * try to move without dying in order to have no action left
     */
    void exhaut_actions();
public:
    Ducktroop(/* args */);

    ~Ducktroop();
};
