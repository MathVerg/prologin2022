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
    mIds = getTroupesId(moi());
    mTroop0 = new DucktroopRusher(mIds[0], mEnv);
    mTroop1 = new DucktroopRusher(mIds[1], mEnv);
}

void StrategyTest::play() {
    switch (mPhase)
    {
    case 0:
         if (posFilter(isNestFree, mEnv->getNests()).size() < 2) {
            mPhase = 1;
            delete mTroop0;
            mTroop0 = new DucktroopBaker(mIds[0], mEnv, 21);
        };
    case 1:
        if ( posFilter(isNestFree, mEnv->getNests()).size() == 0) {
            mPhase = 2;
            delete mTroop1;
            mTroop1 = new DucktroopBaker(mIds[1], mEnv, 21);
        }
        break;
    default:
        break;
    }
    mTroop0->specificPlay();
    mTroop1->specificPlay();
    oneBushKillPerTurn(mEnv, 20);
}
