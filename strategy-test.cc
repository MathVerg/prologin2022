#include "strategy-test.hh"
#include "utils.hh"
#include "ducktroop-baker.hh"
#include "ducktroop-rusher.hh"
#include "troopless-loops.hh"

using namespace std;

StrategyTest::StrategyTest(Env *env) : Strategy(env)
{
}

StrategyTest::~StrategyTest()
{
}

void StrategyTest::init() {
    vector<int> ids = getTroupesId(moi());
    mTroop1 = new DucktroopRusher(ids[0], mEnv);
    mTroop2 = new DucktroopBaker(ids[1], mEnv, 21);
}

void StrategyTest::play() {
    if (mPhase == 0 && posFilter(isNestFree, mEnv->getNests()).size() == 0) {
        mPhase = 1;
        delete mTroop1;
        vector<int> ids = getTroupesId(moi());
        mTroop1 = new DucktroopBaker(ids[0], mEnv, 21);
    }
    mTroop1->specificPlay();
    mTroop2->specificPlay();
    oneBushKillPerTurn(mEnv, 20);
}
