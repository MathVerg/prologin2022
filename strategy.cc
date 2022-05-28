#include "strategy.hh"

Strategy::Strategy(Env* env)
{
    mEnv = env;
}

Strategy::~Strategy()
{
}

void Strategy::init() {
    mIds = getTroupesId(moi());
}

void Strategy::play() {

}