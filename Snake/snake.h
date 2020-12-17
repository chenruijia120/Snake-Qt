#ifndef SNAKE_H
#define SNAKE_H

#include <QLabel>

#include "snakenode.h"

class MainWindow;

class Snake : public QLabel
{
    Q_OBJECT
public:
    explicit Snake(QWidget *parent = nullptr);
    friend class MainWindow;
    Snake();
    void init();
    void verseinit();
    void initBorder();
    void createFood();
    void restartinit();
    ~Snake();
signals:
    void gameOver();
private:
    int speed=100;
    int step=0;
    SnakeNode *snake_label[SIZE+2][SIZE+2];// 储存游戏画面
    QList<SnakeNode*> snake_list;     // 蛇身
    int dX,dY;      // 移动方向
    int score=0;
    SnakeNode *head;               // 蛇头和蛇尾指针
    SnakeNode *tail;

public slots:
    void moveSnake();
};

#endif // SNAKE_H
