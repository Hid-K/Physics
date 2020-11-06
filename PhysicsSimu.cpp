#include "PhysicsSimu.hpp"

PhysicsSimu::PhysicsSimu()
{
    this->objectsList = new std::vector<PhysicsSimuObject>;
};
PhysicsSimu::~PhysicsSimu()
{
    delete this->objectsList;
};
/**
 * Calculating collisions and speeds of objects for 1 period
*/
void
PhysicsSimu::step()
{
    PhysicsSimuObject * currientObject;
    double destToObject;
    for(size_t i = 0; i < this->objectsList->size(); ++i)
    {
        currientObject = &(*(this->objectsList))[i];
        for(size_t j = 0; j < this->objectsList->size() - 1; ++j)
        {
            if(&(*(this->objectsList))[i] == currientObject) continue;
            if( ( destToObject = currientObject->getDest((*(this->objectsList))[i]) ) <= 0)
            {
                std::cout<<"Dest to obj:"<<destToObject<<std::endl;
            };
        };
    };
};

/**
 * Calculating collisions and speeds of objects for t periods
 * 
 * @param t periods to calcilate count
*/
void
PhysicsSimu::step(size_t t)
{
    for(;t > 0; t--)this->step();
};

void
PhysicsSimu::addObject(PhysicsSimuObject & o)
{
    this->objectsList->push_back(o);
};