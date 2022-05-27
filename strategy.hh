

class Strategy
{
private:
    /* data */
public:
    Strategy(/* args */);
    ~Strategy();

    /**
     * override with the actual strategy
     */
    virtual void play();
};