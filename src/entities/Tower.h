#ifndef TOWER_H
#define TOWER_H

class Tower
{
private:
    int level;

public:
    Tower();
    ~Tower();

    const int getLevel() const;
};

#endif // TOWER_H
