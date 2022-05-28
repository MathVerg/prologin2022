#include <array>
#include <vector>
#include <functional>

#include "api.hh"

typedef std::vector<direction> dir_path;
typedef std::vector<position> pos_path;
typedef std::vector<direction> dir_vec;
typedef std::vector<position> pos_vec;

/**
 * Gives a list of the getNeighbors (account for map borders)
 */
pos_vec getNeighbors(const position& pos);

/**
 * Updates a position according to a direction
 */
void updatePos(position* pos, direction dir);

/**
 * Translates a path given as directions to a path given as positions
 */
pos_path pathAsPos(const dir_path &path, const position& start);

/**
 * Whether a position is crossable or not, ignore the ducks
 */
bool isCrossable(position pos);

/**
 * Create a new position vector by filtering out position that do not match a condition
 */
pos_vec posFilter(std::function<bool(position)> f, const pos_vec& sample);

/**
 * Finds the position in the vector that is the closest from the reference
 */
dir_path closestPos(const position& ref, const pos_vec& list);

/**
 * Finds a position in the vector that is at a distance less than dmax from the reference
 */
dir_path closePos(const position& ref, const pos_vec& list, uint dmax);

/**
 * Tells wether there is a duck on this case or not
 */
bool isDucked(const position& pos);

/**
 * manhattan distance between two same-level positions
 */
int manhattanDistance(const position& a, const position& b);

/**
 * Direction to take to get to a given case (assumed neighbor)
 */
direction findDir(const position& pos, const position& goal);

/**
 * pick a position from an array
 */
position pickPos(const pos_vec& sample);

/**
 * query nest state
 */
bool isNestMine(const position& pos);
bool isNestFree(const position& pos);
bool isNestAdversary(const position& pos);