#ifndef GOLDENIDOL_H
#define GOLDENIDOL_H
#include "Object.h"

class GoldenIdol: public Object
{
    public:
        GoldenIdol(Temple* t, Coord p);
        virtual std::string getObjectType() const;
        virtual char getSymbol() const;
        virtual void getPicked();
        virtual std::string useFromInvent();
};

#endif