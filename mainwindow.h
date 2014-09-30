#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGenericMatrix>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <QString>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    /**
      * we use this slot to trigger our widget's redraw function
      * with the timer
      */
    void drawOpenGL();
    void pushMatrix();
    void popMatrix();
    void clearStack();
    void toggleMatrices(bool toggled);
    
private:
    Ui::MainWindow *ui;

    /* Additional Variables */
    QString ss;  // stack string

    /* Additional Functions */
    void addToSS();



};

#endif // MAINWINDOW_H
