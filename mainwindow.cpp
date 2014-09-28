#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>

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

    ss = "";
    addToSS();
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
    temp.operator()(0,1) = ui->m12->text().toDouble();
    temp.operator()(0,2) = ui->m13->text().toDouble();
    temp.operator()(1,0) = ui->m21->text().toDouble();
    temp.operator()(1,1) = ui->m22->text().toDouble();
    temp.operator()(1,2) = ui->m23->text().toDouble();
    temp.operator()(2,0) = ui->m31->text().toDouble();
    temp.operator()(2,1) = ui->m32->text().toDouble();
    temp.operator()(2,2) = ui->m33->text().toDouble();

    ui->oglwidget->pushMatrix(temp);
    addToSS();

    ui->m11->setText("1");
    ui->m12->setText("0");
    ui->m13->setText("0");
    ui->m21->setText("0");
    ui->m22->setText("1");
    ui->m23->setText("0");
    ui->m31->setText("0");
    ui->m32->setText("0");
    ui->m33->setText("1");
}

void MainWindow::addToSS() {

    int i, j;
    QMatrix3x3 stackTop = ui->oglwidget->stack.top();
    QString tempString = ss;  //save the old string to append later

    // Find the max length of the elements to format properly
    int maxLength = 0;
    int spaces[3][3];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            spaces[i][j] = (QString::number(stackTop.operator()(i,j))).length();
            if ((QString::number(stackTop.operator()(i,j))).contains("."))  // Format for the '.'
                spaces[i][j] -= 1;
            if ((QString::number(stackTop.operator()(i,j))).length() > maxLength)
                maxLength = (QString::number(stackTop.operator()(i,j))).length();
        }
    }

    ss = "";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            qDebug() << spaces[i][j];
            // Do not try to understand the next line.  Crazy formatting because \t in C++ sucks
            ss += "| " + (QString::number(stackTop.operator()(i,j))).leftJustified(spaces[i][j] + ((maxLength - spaces[i][j]) * 2), ' ') + " ";
        }
        ss += "| \n";
    }
    ss += "\n";

    ss += tempString;
    ui->textBrowser->setText(ss);
}

void MainWindow::popMatrix() {
    ui->oglwidget->popMatrix();
    ss.remove(0, (ss.indexOf("\n\n") + 2));
    if (ss.isEmpty()) {  // Put the Identity back on
        ui->oglwidget->newStack();
        addToSS();
    }
    else {
        ui->textBrowser->setText(ss);
    }
}

void MainWindow::clearMatrix() {

}

void MainWindow::printMatrices() {


    //ui->textBrowser->setText(ss);


    //"| 1 | 0 | 0 |\n| 0 | 1 | 0 |\n| 0 | 0 | 1 |\n\n| 1 | 0 | 0 |\n| 0 | 1 | 0 |\n| 0 | 0 | 1 |\n"
    //"------\n| 1 | 0 | 0 |\n------\n| 0 | 1 | 0 |\n------\n| 0 | 0 | 1 |\n"
}



