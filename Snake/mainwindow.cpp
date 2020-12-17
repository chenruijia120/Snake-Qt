#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1200,900);
    this->setWindowIcon(QIcon(":/png/snake.png"));
    this->setWindowTitle("Snake by CRJ");
    ui->pushButton->setGeometry(820,110,200,80);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);

    ui->lcdNumber->setGeometry(820,570,200,100);
    ui->textBrowser->setGeometry(770,230,300,300);
    ui->textBrowser->setVisible(false);
    ui->labelup->setGeometry(880,100,80,80);
    ui->labeldown->setGeometry(880,230,80,80);
    ui->labelleft->setGeometry(795,165,80,80);
    ui->labelright->setGeometry(965,165,80,80);
    ui->labelup->setScaledContents(true);
    ui->labeldown->setScaledContents(true);
    ui->labelleft->setScaledContents(true);
    ui->labelright->setScaledContents(true);
    ui->labelup->setVisible(false);
    ui->labeldown->setVisible(false);
    ui->labelleft->setVisible(false);
    ui->labelright->setVisible(false);
    ui->labelscore->setVisible(false);
    ui->pushButton->setEnabled(true);

    QFont ft;
    ft.setPointSize(24);
    ui->labelscore->setFont(ft);
    ui->labelscore->setGeometry(850,400,200,100);

    ui->horizontalSlider->setGeometry(830,50,180,30);

    ui->actionStart->setEnabled(true);
    ui->actionContinue->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(false);
    ui->actionRestart->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->tbStart ->setEnabled(true);
    ui->tbContinue->setEnabled(false);
    ui->tbLoad->setEnabled(true);
    ui->tbSave->setEnabled(false);
    ui->tbRestart->setEnabled(false);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(false);

    timer=new QTimer;
    movetimer=new QTimer;
    connect(timer, &QTimer::timeout,this,&MainWindow::showTime);


    init();
    setFocusPolicy(Qt::StrongFocus);

    connect(movetimer, &QTimer::timeout,snake,&Snake::moveSnake);
    connect(snake,SIGNAL(gameOver()),this,SLOT(gameOver()));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush(QBrush(Qt::white));
    p.drawRect(50,70,GRID*40,GRID*40);
    p.setPen(QPen(Qt::gray));
    for(int i=1;i<=39;i++){
        p.drawLine(50,70+GRID*i,50+GRID*40,70+GRID*i);
        p.drawLine(50+GRID*i,70,50+GRID*i,70+GRID*40);
    }


}

MainWindow::~MainWindow()
{
    delete snake;
    delete ui;
}

void MainWindow::init()
{
    s=0;
    ui->lcdNumber->display(QString("00:00"));
    snake=new Snake(this);

    snake->show();
}


void MainWindow::gameOver()
{
    status=3;
    ui->actionStart->setEnabled(false);
    ui->actionContinue->setEnabled(false);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionRestart->setEnabled(true);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->tbStart->setEnabled(false);
    ui->tbContinue->setEnabled(false);
    ui->tbLoad->setEnabled(false);
    ui->tbSave->setEnabled(false);
    ui->tbRestart->setEnabled(true);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(false);

    movetimer->stop();
    timer->stop();

    QMessageBox::information(this,"Message:","Game over!\nPlease try again!",QMessageBox::Ok);

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Escape:
        on_actionExit_triggered();
        break;
    default:
        break;

    }
    if(status==1){
        switch (e->key()) {
        case Qt::Key_Up:
            if(s==0){
                snake->verseinit();
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            if(snake->dY!=1)
            {
                snake->dX=0;
                snake->dY=-1;
            }
            break;
        case Qt::Key_Down:
            if(s==0){
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            if(snake->dY!=-1)
            {
                snake->dX=0;
                snake->dY=1;
            }
            break;
        case Qt::Key_Right:
            if(s==0){
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            if(snake->dX!=-1)
            {
                snake->dX=1;
                snake->dY=0;
            }
            break;
        case Qt::Key_Left:
            if(s==0){
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            if(snake->dX!=1)
            {
                snake->dX=-1;
                snake->dY=0;
            }
            break;
        default:
            break;
        }
    }

    switch (e->key()) {
        case Qt::Key_Space:
            if(status==1){
                on_actionStop_triggered();
            }
            else if(status==2){
                on_actionContinue_triggered();
            }
            else if (status==0) {
                on_actionStart_triggered();
            }
            break;
        default:
            break;
        }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(status==0){
        int x=event->x()-50;
        x=x/GRID+1;
        int y=event->y()-70;
        y=y/GRID+1;
        if(x<=40&&y<=40&&x>=1&&y>=1){
            if(snake->snake_label[x][y]->type==NORMAL_LABEL){
                snake->snake_label[x][y]->label->setStyleSheet("background:rgba(70,130,180,0.6)");
                snake->snake_label[x][y]->label->show();
                snake->snake_label[x][y]->type = BORDER_LABEL;
            }
            else if(snake->snake_label[x][y]->type==BORDER_LABEL){
                snake->snake_label[x][y]->label->hide();
                snake->snake_label[x][y]->type = NORMAL_LABEL;
            }
        }
    }
    else if (status==1) {
        int x=event->x();
        int y=event->y();
        if(x>=880&&x<=960&&y>=100&&y<=180&&snake->dY!=1){
            if(s==0){
                snake->verseinit();
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            snake->dX=0;
            snake->dY=-1;
        }
        else if (x>=880&&x<=960&&y>=230&&y<=310&&snake->dY!=-1) {
            if(s==0){
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            snake->dX=0;
            snake->dY=1;
        }
        else if (x>=795&&x<=875&&y>=165&&y<=245&&snake->dX!=1) {
            if(s==0){
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            snake->dX=-1;
            snake->dY=0;
        }
        else if (x>=965&&x<=1055&&y>=165&&y<=245&&snake->dX!=-1) {
            if(s==0){
                movetimer->start(snake->speed);
                timer->start(snake->speed);
            }
            snake->dX=1;
            snake->dY=0;
        }
    }

}





void MainWindow::on_pushButton_clicked()
{
    if(ui->textBrowser->isVisible()){
        ui->textBrowser->setVisible(false);
    }
    else{
        ui->textBrowser->setVisible(true);
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionStart_triggered()
{
    status=1;
    s=0;
    snake->score=0;
    ui->lcdNumber->display("00:00");
    str="Score:\n"+QString::number(snake->score);
    ui->labelscore->setText(str);

    ui->pushButton->setEnabled(false);
    ui->pushButton->setVisible(false);
    ui->textBrowser->setVisible(false);

    ui->horizontalSlider->setVisible(false);
    ui->horizontalSlider->setEnabled(false);

    ui->actionStart->setEnabled(false);
    ui->actionContinue->setEnabled(false);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionRestart->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(true);

    ui->tbStart->setEnabled(false);
    ui->tbContinue->setEnabled(false);
    ui->tbLoad->setEnabled(false);
    ui->tbSave->setEnabled(false);
    ui->tbRestart->setEnabled(false);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(true);

    ui->labelup->setVisible(true);
    ui->labeldown->setVisible(true);
    ui->labelleft->setVisible(true);
    ui->labelright->setVisible(true);
    ui->labelscore->setVisible(true);


    snake->createFood();

}

void MainWindow::on_actionStop_triggered()
{
    movetimer->stop();
    timer->stop();
    status=2;
    ui->actionStart->setEnabled(false);
    ui->actionContinue->setEnabled(true);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(true);
    ui->actionRestart->setEnabled(true);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->tbStart->setEnabled(false);
    ui->tbContinue->setEnabled(true);
    ui->tbLoad->setEnabled(false);
    ui->tbSave->setEnabled(true);
    ui->tbRestart->setEnabled(true);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(false);

}

void MainWindow::showTime()
{
    s++;
    QString text;

    if(s==0){
        text="00:00";
    }
    else{
        if(s/60<10){
            text = "0"+QString::number(s/60)+":";
        }
        else{
            text = QString::number(s/60)+":";
        }
        if(s%60<10){
            text=text+"0"+QString::number(s%60);
        }
        else{
            text=text+QString::number(s%60);
        }
    }

    ui->lcdNumber->display(text);
    str="Score:\n"+QString::number(snake->score);
    ui->labelscore->setText(str);
}

void MainWindow::on_actionContinue_triggered()
{
    movetimer->start(snake->speed);
    timer->start(snake->speed);
    status=1;

    ui->actionStart->setEnabled(false);
    ui->actionContinue->setEnabled(false);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionRestart->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(true);

    ui->tbStart->setEnabled(false);
    ui->tbContinue->setEnabled(false);
    ui->tbLoad->setEnabled(false);
    ui->tbSave->setEnabled(false);
    ui->tbRestart->setEnabled(false);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(true);

}

void MainWindow::on_actionRestart_triggered()
{

    status=0;
    s=0;
    snake->score=0;
    snake->step=0;
    ui->lcdNumber->display("00:00");
    str="Score:\n"+QString::number(snake->score);
    ui->labelscore->setText(str);

    ui->actionStart->setEnabled(true);
    ui->actionContinue->setEnabled(false);
    ui->actionLoad->setEnabled(true);
    ui->actionSave->setEnabled(false);
    ui->actionRestart->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->tbStart->setEnabled(true);
    ui->tbContinue->setEnabled(false);
    ui->tbLoad->setEnabled(true);
    ui->tbSave->setEnabled(false);
    ui->tbRestart->setEnabled(false);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(false);

    ui->horizontalSlider->setVisible(true);
    ui->horizontalSlider->setEnabled(true);

    ui->labelup->setVisible(false);
    ui->labeldown->setVisible(false);
    ui->labelleft->setVisible(false);
    ui->labelright->setVisible(false);
    ui->labelscore->setVisible(false);
    ui->pushButton->setVisible(true);
    ui->textBrowser->setVisible(false);
    ui->pushButton->setEnabled(true);

    snake->restartinit();
    snake->init();
    snake->initBorder();
}


void MainWindow::on_actionSave_triggered()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Save File"),"",tr("Text File(*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Warning","The file name is not right, please Input again!");
        return;
    }

    QTextStream txtOutput(&file);
    txtOutput<<"direction X:"<<endl;
    txtOutput<<snake->dX<<endl;
    txtOutput<<"direction Y:"<<endl;
    txtOutput<<snake->dY<<endl;
    txtOutput<<"Time:"<<endl;
    txtOutput<<s<<endl;
    txtOutput<<"Score:"<<endl;
    txtOutput<<snake->score<<endl;
    txtOutput<<"Step:"<<endl;
    txtOutput<<snake->step<<endl;
    txtOutput<<"Speed:"<<endl;
    txtOutput<<snake->speed<<endl;


    txtOutput<<"Label:"<<endl;
    for(int x=0;x<SIZE+2;x++){
        for(int y=0;y<SIZE+2;y++){
            txtOutput<<snake->snake_label[x][y]->type<<" ";
        }
        txtOutput<<endl;
    }
    txtOutput<<"Snake:"<<endl;
    for(int i=0;i<snake->snake_list.length()-1;i++){
        txtOutput<<snake->snake_list.at(i)->x<<" "<<snake->snake_list.at(i)->y<<endl;
    }
    txtOutput<<snake->snake_list.at(snake->snake_list.length()-1)->x<<" "<<snake->snake_list.at(snake->snake_list.length()-1)->y;
    file.close();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    snake->speed=value*10;
}

void MainWindow::on_actionLoad_triggered()
{

    status=2;
    ui->actionStart->setEnabled(false);
    ui->actionContinue->setEnabled(true);
    ui->actionLoad->setEnabled(false);
    ui->actionSave->setEnabled(true);
    ui->actionRestart->setEnabled(true);
    ui->actionExit->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->tbStart->setEnabled(false);
    ui->tbContinue->setEnabled(true);
    ui->tbLoad->setEnabled(false);
    ui->tbSave->setEnabled(true);
    ui->tbRestart->setEnabled(true);
    ui->tbExit->setEnabled(true);
    ui->tbStop->setEnabled(false);

    QString fileName = QFileDialog::getOpenFileName(this,tr("Please choose the file"),"",tr("TXT(*.txt)"));
    if (fileName.isEmpty())     //如果未选择文件便确认，即返回
        return;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream ts(&file);
        QString line = ts.readLine();
        line = ts.readLine();
        snake->dX=line.toInt();
        line = ts.readLine();
        line = ts.readLine();
        snake->dY=line.toInt();
        line = ts.readLine();
        line = ts.readLine();
        s=line.toInt();
        line = ts.readLine();
        line = ts.readLine();
        snake->score=line.toInt();
        line = ts.readLine();
        line = ts.readLine();
        snake->step=line.toInt();
        line = ts.readLine();
        line = ts.readLine();
        snake->speed=line.toInt();
        line = ts.readLine();
        for(int x=0;x<=SIZE+1;x++){
            for(int y=0;y<=SIZE+1;y++){
                int temp;
                ts>>temp;
                snake->snake_label[x][y]->type=temp;
                switch (snake->snake_label[x][y]->type) {
                case NORMAL_LABEL:
                    snake->snake_label[x][y]->label->hide();
                    break;
                case BORDER_LABEL:
                    snake->snake_label[x][y]->label->setStyleSheet("background:rgba(70,130,180,0.6)");
                    snake->snake_label[x][y]->label->show();
                    break;
                case HEAD_LABEL:
                    snake->snake_label[x][y]->label->setStyleSheet("background:rgb(0,0,0)");
                    snake->snake_label[x][y]->label->show();
                    break;
                case SNAKE_LABEL:
                    snake->snake_label[x][y]->label->setStyleSheet("background:rgb(170,170,170)");
                    snake->snake_label[x][y]->label->show();
                    break;
                case FOOD_LABEL:
                    snake->snake_label[x][y]->label->setStyleSheet("background:rgba(205,92,92,0.9)");
                    snake->snake_label[x][y]->label->show();
                    break;
                }
            }
        }
        line = ts.readLine();
        line = ts.readLine();
        snake->snake_list.clear();
        while(!ts.atEnd()){
            int x,y;
            ts>>x>>y;
            snake->snake_list.append(snake->snake_label[x][y]);
        }
    }
    showTime();
    str="Score:\n"+QString::number(snake->score);
    ui->labelscore->setText(str);
    ui->pushButton->setEnabled(false);
    ui->pushButton->setVisible(false);
    ui->textBrowser->setVisible(false);

    ui->horizontalSlider->setVisible(false);
    ui->horizontalSlider->setEnabled(false);

    ui->labelup->setVisible(true);
    ui->labeldown->setVisible(true);
    ui->labelleft->setVisible(true);
    ui->labelright->setVisible(true);
    ui->labelscore->setVisible(true);

    file.close();
}

void MainWindow::on_tbStart_clicked()
{
    on_actionStart_triggered();
}

void MainWindow::on_tbStop_clicked()
{
    on_actionStop_triggered();
}

void MainWindow::on_tbContinue_clicked()
{
    on_actionContinue_triggered();
}

void MainWindow::on_tbRestart_clicked()
{
    on_actionRestart_triggered();
}

void MainWindow::on_tbExit_clicked()
{
    on_actionExit_triggered();
}

void MainWindow::on_tbLoad_clicked()
{
    on_actionLoad_triggered();
}

void MainWindow::on_tbSave_clicked()
{
    on_actionSave_triggered();
}
