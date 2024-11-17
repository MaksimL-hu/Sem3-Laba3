#ifndef ITEM_H
#define ITEM_H

struct Item {
    int weight;
    int volume;
    int value;

    Item(int weight, int volume, int value) : weight(weight), volume(volume), value(value) {}
    Item() : weight(0), volume(0), value(0) {}

    bool operator==(const Item& other) const
    {
        return other.weight == weight && other.volume == volume && other.value == value;
    }

    bool operator!=(const Item& other) const
    {
        return other.weight != weight || other.volume != volume || other.value != value;
    }
};

#endif