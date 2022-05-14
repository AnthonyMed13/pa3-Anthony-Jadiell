#pragma once

#include <algorithm>
#include <string>

class PowerUps {
    private:
        int ranking;
        std::string name;

    public:
        virtual std::string getName() = 0;
        virtual int getRanking() = 0;
        virtual void activate() = 0;
        virtual bool operator<(PowerUps&p) = 0;
};