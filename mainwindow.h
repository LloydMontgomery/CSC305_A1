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

    /* void pushMatrix()
     *
     * Pushes a new matrix onto the stack based on the values currently stored
     * in the table entries in the UI.  Finishes by setting the table values
     * back to the identity
     */
    void pushMatrix();

    /* void popMatrix()
     *
     * Pop off one matrix from the stack.  Take it off the actual stack as well as
     * take if off the visual stack.
     */
    void popMatrix();

    /* void clearStack()
     *
     * Clears the matrix transformation stack and clears the stack printing to the screen
     */
    void clearStack();
    
private:
    Ui::MainWindow *ui;
    QString ss;  // stack string

    /* void addToSS()
     *
     * Adds the top of the matrix stack to the stack string so it can be displayed.
     * Most of the code below is for formatting.
     */
    void addToSS();

};

#endif // MAINWINDOW_H
