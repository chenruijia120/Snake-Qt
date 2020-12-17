#include "snake.h"

Snake::Snake(QWidget *parent) : QLabel(parent)
{
    this->setGeometry(0,30,50+41*GRID,40+41*GRID);
    for(int x = 0; x < SIZE+2; x++) {
        for(int y = 0; y < SIZE+2; y++) {
            QLabel *label = new QLabel(this);
            label->setGeometry(50+(x-1) * GRID, 40+(y-1) * GRID, GRID, GRID);
            label->hide();

            snake_label[x][y] = new SnakeNode;
            snake_label[x][y]->label = label;
            snake_label[x][y]->type = NORMAL_LABEL;
            snake_label[x][y]->x = x;
            snake_label[x][y]->y = y;
        }
    }

    init();
    initBorder();
}

void Snake::init()
{
    int snakeX=20;
    int snakeY=20;

    dX=0;
    dY=0;

    snake_list.clear();

    snake_list.append(snake_label[snakeX][snakeY]);
    snake_list.at(snake_list.length() - 1)->x = snakeX;
    snake_list.at(snake_list.length() - 1)->y = snakeY;
    snake_label[snakeX][snakeY]->type = SNAKE_LABEL;
    snake_label[snakeX][snakeY]->label->setStyleSheet("background:rgb(170,170,170)");
    snake_label[snakeX][snakeY]->label->show();

    snake_list.append(snake_label[snakeX][snakeY+1]);
    snake_list.at(snake_list.length() - 1)->x = snakeX;
    snake_list.at(snake_list.length() - 1)->y = snakeY+1;
    snake_label[snakeX][snakeY+1]->type = HEAD_LABEL;
    snake_label[snakeX][snakeY+1]->label->setStyleSheet("background:rgb(0,0,0)");
    snake_label[snakeX][snakeY+1]->label->show();

}

void Snake::verseinit()
{
    int snakeX=20;
    int snakeY=20;

    snake_list.clear();

    snake_list.append(snake_label[snakeX][snakeY+1]);
    snake_list.at(snake_list.length() - 1)->x = snakeX;
    snake_list.at(snake_list.length() - 1)->y = snakeY+1;
    snake_label[snakeX][snakeY+1]->type = SNAKE_LABEL ;
    snake_label[snakeX][snakeY+1]->label->setStyleSheet("background:rgb(170,170,170)");
    snake_label[snakeX][snakeY+1]->label->show();

    snake_list.append(snake_label[snakeX][snakeY]);
    snake_list.at(snake_list.length() - 1)->x = snakeX;
    snake_list.at(snake_list.length() - 1)->y = snakeY;
    snake_label[snakeX][snakeY]->type = HEAD_LABEL;
    snake_label[snakeX][snakeY]->label->setStyleSheet("background:rgb(0,0,0)");
    snake_label[snakeX][snakeY]->label->show();


}

void Snake::initBorder()
{
    for(int x = 0; x < SIZE+2; x++) {
        for(int y = 0; y < SIZE+2; y++) {
            if(x == 0 || y == 0 || x == SIZE +1 || y == SIZE +1) {
                snake_label[x][y]->label->setStyleSheet("background:rgba(70,130,180,0.6)");
                snake_label[x][y]->label->show();
                snake_label[x][y]->type = BORDER_LABEL;
            }
        }
    }
}

void Snake::createFood()
{
    int foodX;
    int foodY;
    // 随机生成食物坐标
    srand((unsigned)time(0));
    do{
        foodX = rand()%(SIZE+1);
        foodY = rand()%(SIZE+1);
    }while(snake_label[foodX][foodY]->type != NORMAL_LABEL);
    snake_label[foodX][foodY]->type = FOOD_LABEL;
    snake_label[foodX][foodY]->label->setStyleSheet("background:rgba(205,92,92,0.9)");
    snake_label[foodX][foodY]->label->show();
}

void Snake::restartinit()
{
    for(int x = 0; x < SIZE+2; x++) {
        for(int y = 0; y < SIZE+2; y++) {
            snake_label[x][y]->type = NORMAL_LABEL;
            snake_label[x][y]->label->hide();
        }

    }
}

void Snake::moveSnake()
{
    if(!(dX==0&&dY==0)){
        head = snake_list.at(snake_list.length() - 1);
        tail = snake_list.at(0);
        SnakeNode *tempNode=snake_label[head->x+dX][head->y+dY];
        SnakeNode *tempNode2=snake_label[head->x][head->y];
        tempNode->label->setStyleSheet("background:rgb(0,0,0)");
        tempNode2->label->setStyleSheet("background:rgb(170,170,170)");
        tempNode2->type=SNAKE_LABEL;
        tempNode->label->show();
        //检测是否撞到自己或边界
        if(tempNode->type==BORDER_LABEL||tempNode->type==SNAKE_LABEL)
        {
            tempNode->label->setStyleSheet("background:gray");
            emit gameOver();
        }
        else
        {
            if(tempNode->type==FOOD_LABEL)
            {
                score=score+5;
                tempNode->type=HEAD_LABEL;
                snake_list.append(tempNode);
                step=step+2;
                createFood();
            }
            else if(step==0)
            {
                tempNode->type=HEAD_LABEL;
                snake_list.append(tempNode);
                tail->label->hide();
                tail->type=NORMAL_LABEL;
                snake_list.removeFirst();
            }
            else{
                step--;
                tempNode->type=HEAD_LABEL;
                snake_list.append(tempNode);
            }
        }
    }
}



Snake::~Snake()
{
    for(int x=0;x<SIZE+2;x++){
        for(int y=0;y<SIZE+2;y++){
            delete snake_label[x][y];
        }
    }
}
