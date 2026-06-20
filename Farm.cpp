#include "Farm.h"

Farm::Farm()
{
    croplandCapacity = 3;
    farmlandCapacity = 3;
}

void Farm::updateCycles() {
    for (auto& plant : cropland) {
        plant.currentCycles++;
    }

    for (auto& animal : farmland) {
        animal.currentCycles++;
    }
}
