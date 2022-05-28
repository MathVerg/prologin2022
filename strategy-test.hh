#pragma once
#include "strategy.hh"
#include "ducktroop-baker.hh"

class StrategyTest : public Strategy
{
private:
    DucktroopBaker *mBaker1;
    DucktroopBaker *mBaker2;
public:
    StrategyTest(Env* env);
    virtual ~StrategyTest();

    void init() override;
    void play() override;
};
