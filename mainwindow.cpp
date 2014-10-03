#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ss = "";    // Initialize Stack String
    addToSS();  // Add the identity to the Stack String
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ********************** PUBLIC SLOTS ********************** */

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

    ui->m11->setText(".866");
    ui->m12->setText("-.5");
    ui->m13->setText("0");
    ui->m21->setText(".5");
    ui->m22->setText(".866");
    ui->m23->setText("0");
    ui->m31->setText("0");
    ui->m32->setText("0");
    ui->m33->setText("1");
}

void MainWindow::popMatrix()
{
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

void MainWindow::clearStack()
{
    ss = "";
    ui->oglwidget->clearStack();
    addToSS();
}

/* ******************** PRIVATE FUNCTIONS ******************** */

void MainWindow::addToSS()
{
    int i, j;
    QMatrix3x3 stackTop = ui->oglwidget->stack.top();
    QString tempString = ss;  //save the old string to append later

    // Find the max length of the elements to format properly
    int maxLength[3] = {0, 0, 0};
    int spaces[3][3];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            spaces[i][j] = (QString::number(stackTop.operator()(i,j))).length();
            if ((QString::number(stackTop.operator()(i,j))).contains("."))  // Format for the '.'
                spaces[i][j] -= 1;
            if ((QString::number(stackTop.operator()(i,j))).length() > maxLength[j])
                maxLength[j] = (QString::number(stackTop.operator()(i,j))).length();
        }
    }

    ss = "";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            // Do not try to understand the next line.  Crazy formatting because \t in C++ sucks
            ss += "| " + (QString::number(stackTop.operator()(i,j))).leftJustified(spaces[i][j] + ((maxLength[j] - spaces[i][j]) * 2), ' ', true) + " ";
        }
        ss += "| \n";
    }
    ss += "\n";

    ss += tempString;
    ui->textBrowser->setText(ss);
}


