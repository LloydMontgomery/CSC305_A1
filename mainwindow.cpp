#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animationTimer(NULL)
{
    ui->setupUi(this);

    // we create a simple timer, with the widget being its parent
    animationTimer = new QTimer(this);
    // the timer will send a signal timeout at regular intervals.
    // whenever this timeout signal occurs, we want it to call our drawOpenGL
    // function
    animateon=false;
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(drawOpenGL()));
    // we start the timer with a timeout interval of 20ms
//    animationTimer->start(20);
}

void MainWindow::drawOpenGL()
{
    // whenever drawOpenGL gets called, we only want to repaint our opengl widget
    ui->oglwidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::animate()
{
    animateon = !animateon;
    //ui->oglwidget->setanimate(animateon);
}

void MainWindow::pushMatrix()
{
    QMatrix3x3 temp = QMatrix3x3();
    temp.operator()(0,0) = ui->m11->text().toDouble();
    temp.operator()(0,1) = ui->m11->text().toDouble();
    temp.operator()(0,2) = ui->m11->text().toDouble();
    temp.operator()(1,0) = ui->m11->text().toDouble();
    temp.operator()(1,1) = ui->m11->text().toDouble();
    temp.operator()(1,2) = ui->m11->text().toDouble();
    temp.operator()(2,0) = ui->m11->text().toDouble();
    temp.operator()(2,1) = ui->m11->text().toDouble();
    temp.operator()(2,2) = ui->m11->text().toDouble();

    ui->oglwidget->pushMatrix(temp);
}
