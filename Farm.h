#pragma once
#include <vector>

struct GrowingItem {
    int id;
    int currentCycles;
    int requiredCycles;
    int givesProductId;
    GrowingItem(int pid, int req, int gives)
        : id(pid), currentCycles(0), requiredCycles(req), givesProductId(gives) {
    }
};

class Farm {
public:
std::vector<GrowingItem> cropland;
std::vector<GrowingItem> farmland;
int croplandCapacity;
int farmlandCapacity;
Farm();
void updateCycles();

};
