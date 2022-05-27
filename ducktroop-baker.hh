/**
 * A ducktroop that merely seeks for bread then bring it back
 */

#include "ducktroop.hh"

class DucktroopBaker : Ducktroop
{
private:
    /* data */
public:
    DucktroopBaker(/* args */);
    ~DucktroopBaker();

    /**
     * have the ducktroop play as a single player
     */
    void play();
};

