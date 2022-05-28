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
    std::array<std::array<bool, LARGEUR>, HAUTEUR> mBagends;
    pos_vec mPapys;
    pos_vec mHoles;
    pos_vec mNests;
public:
    Env(/* args */);
    virtual ~Env();

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
     * accessors
     */
    pos_vec getPapys();
    pos_vec getHoles();
    pos_vec getNests();

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
    dir_path findClosest(const position& pos, type_case casetype);

    /**
     * Find a case of a given type at distance lower than dmax
     * @return the path to this case, empty if none is found
     */
    dir_path findClose(const position& pos, type_case casetype, uint dmax);

    /**
     * Finds the bread that is the closest from the reference
     */
    dir_path findClosestBread(const position& ref);

    /**
     * Finds a bread that is at a distance less than dmax from the reference
     */
    dir_path findCloseBread(const position& ref, uint dmax);

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

    /**
     * Tells wether their is a bag end on the path
     */
    bool bagendOnPath(const pos_path& path);

    /**
     * Tells wether the first steps of the path are accessible
     */
    bool canStartPath(const pos_path& path, int start, int steps);
};
