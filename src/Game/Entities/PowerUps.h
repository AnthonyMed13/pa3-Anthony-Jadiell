#pragma once

#include <algorithm>

class PowerUps {
    private:
        int ranking;

    public:
        virtual int getRanking() = 0;
        virtual void activate() = 0;
        virtual void render() = 0;
        virtual bool operator<(PowerUps&p) = 0;
};