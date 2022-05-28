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
    mBaker1 = new DucktroopBaker(ids[0], mEnv, 6);
    mBaker2 = new DucktroopBaker(ids[1], mEnv, 6);
}

void StrategyTest::play() {
    mBaker1->genericPlay();
    mBaker2->genericPlay();
}
