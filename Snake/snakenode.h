#ifndef SNAKENODE_H
#define SNAKENODE_H

#define GRID 17
#define SIZE 40

#include <QLabel>

enum Label
{
    NORMAL_LABEL,
    BORDER_LABEL,
    HEAD_LABEL,
    SNAKE_LABEL,//蛇节点
    FOOD_LABEL,//食物
};

class SnakeNode
{
public:
    QLabel *label;
    int type;
    int x;
    int y;
};


#endif // SNAKENODE_H
