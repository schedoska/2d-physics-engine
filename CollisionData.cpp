#include "CollisionData.h"

dm2::CollisionData::CollisionData(bool _collides, dm2::Object* _a, dm2::Object* _b, dm2::Vector _cpA, dm2::Vector _cpB)
    : collides(_collides), objectA(_a), objectB(_b), cpA(_cpA), cpB(_cpB) {}