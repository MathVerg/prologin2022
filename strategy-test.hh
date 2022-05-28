#pragma once
#include "strategy.hh"
#include "ducktroop.hh"

class StrategyTest : public Strategy
{
private:
    Ducktroop *mTroop1;
    Ducktroop *mTroop2;
public:
    StrategyTest(Env* env);
    virtual ~StrategyTest();

    void init() override;
    void play() override;
};
