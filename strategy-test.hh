#pragma once
#include "strategy.hh"
#include "ducktroop.hh"

class StrategyTest : public Strategy
{
private:
    Ducktroop *mTroop0;
    Ducktroop *mTroop1;
public:
    StrategyTest(Env* env);
    virtual ~StrategyTest();

    void init() override;
    void play() override;
};
