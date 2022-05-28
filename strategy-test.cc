#include "strategy-test.hh"
#include "utils.hh"

using namespace std;

StrategyTest::StrategyTest(Env *env) : Strategy(env)
{
}

StrategyTest::~StrategyTest()
{
}

void StrategyTest::init() {
    vector<int> ids = getTroupesId(moi());
    mBaker1 = new DucktroopBaker(ids[0], mEnv, 21);
    mBaker2 = new DucktroopBaker(ids[1], mEnv, 21);
}

void StrategyTest::play() {
    mBaker1->specificPlay();
    mBaker2->specificPlay();
}
