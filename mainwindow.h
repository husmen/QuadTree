#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include <QLabel>

class ScribbleArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void timerEvent(QTimerEvent *e);

private slots:
    //void MainWindow::nbrChanged();
    void randomize();
    void select();
    void clear();

private:

    ScribbleArea *scribbleArea;
    QSpinBox *nbrSpinBox;
    QSpinBox *radSpinBox;
    QLabel *label;
    QLabel *nbrLabel;
    QLabel *radLabel;
    //QAction *nbrAct;
};

#endif // MAINWINDOW_H
