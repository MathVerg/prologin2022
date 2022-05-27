/**
 * Represents the game environment
 */

#include <vector>
#include <array>

#include "api.hh"
#include "utils.hh"

class Env
{
private:
    /**
     * A map of all the places where you don't want to go
     */
    std::array<std::array<bool, LARGEUR>, HAUTEUR> bagends;
    pos_vec papys;
    pos_vec holes;
    pos_vec nests;
public:
    Env(/* args */);
    ~Env();

    /**
     * Object-oriented versions of the API action
     */
    void construireBuisson(position pos);

    /**
     * Object-oriented versions of the API action
     */
    void creuserTunnel(position pos);

    /**
     * Initializes the environment
     */
    void init();

    /**
     * Updates the bagends map around this position
     */
    void updateBagends(const position& pos);

    /**
     * Tells wether the given position is in a bagend
     */
    bool isBagend(const position& pos);

    /**
     * Negation of the previous function
     */
    bool isNotBagend(const position& pos);

    /**
     * Removes the positions that are in bagends
     */
    pos_vec filterBagend(const pos_vec& sample);

    /**
     * update the env after the opponent's moves
     */
    void updateFromOpponent();

    /**
     * Find the closest case of a given type
     * @return the path to this case, empty if none is found
     */
    dir_path findClosest(const position& pos, type_case& casetype);

    /**
     * Find a case of a given type at distance lower than dmax
     * @return the path to this case, empty if none is found
     */
    dir_path findClose(const position& pos, type_case& casetype, uint dmax);

    /**
     * Tells wether you could move to this case or not
     */
    bool isMovableTo(const position& pos);

    /**
     * Removes the positions that are not moveable to
     */
    pos_vec filterMovable(const pos_vec& sample);

    /**
     * gives all the position where you can move
     */
    pos_vec moveOptions(const position& pos);
};
