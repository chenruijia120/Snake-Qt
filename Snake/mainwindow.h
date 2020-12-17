#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QTimer>
#include <QObject>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QKeyEvent>
#include <Qt>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QRect>

#include "snakenode.h"
#include "snake.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~MainWindow();
    void init();
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *event);

private slots:

    void on_pushButton_clicked();


    void on_actionExit_triggered();

    void on_actionStart_triggered();

    void on_actionStop_triggered();

    void showTime();

    void on_actionContinue_triggered();

    void on_actionRestart_triggered();


    void on_actionSave_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_actionLoad_triggered();

    void on_tbStart_clicked();

    void on_tbStop_clicked();

    void on_tbContinue_clicked();

    void on_tbRestart_clicked();

    void on_tbExit_clicked();

    void on_tbLoad_clicked();

    void on_tbSave_clicked();

    void gameOver();

private:
    int s=0;
    int status=0;

    QTimer* timer;
    QTimer* movetimer;
    QString str;

    Snake * snake;


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
