/**
 * Represents the game environment
 */

#include <vector>
#include <array>

#include "api.hh"

class Env
{
private:
    /**
     * A map of all the places where you don't want to go
     */
    std::array<std::array<bool, LARGEUR>, HAUTEUR> bagends;
public:
    Env(/* args */);
    ~Env();

    void init();

    /**
     * Object-oriented versions of the API action
     */
    erreur construire_buisson(position pos);

    /**
     * Object-oriented versions of the API action
     */
    erreur creuser_tunnel(position pos);

    /**
     * Updates the bagends map around this position
     */
    void update_bagends(const position& pos);

    /**
     * update the env after the opponent's moves
     */
    void update_from_opponent();

    /**
     * Find the closest case of a given type
     */
    position find_closest(type_case& casetype);

    /**
     * gives all the position where you can move
     */
    std::vector<position> move_options(const position& pos);

    /**
     * Tells wether you could move to this case or not
     */
    bool is_movable_to(const position& pos);
};
