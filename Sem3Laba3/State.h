#ifndef STATE_H
#define STATE_H

#include <vector>

struct State {
    int totalValue;
    int totalWeight;
    int totalVolume;
    std::vector<bool> selectedItems;

    State(int itemCount) : totalValue(0), totalWeight(0), totalVolume(0), selectedItems(itemCount, false) {}
};

#endif