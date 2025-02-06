#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>
#include <QList>
#include <QThread>
#include "board.h"
#include "searchcombs.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QLabel *dayLabel;
    QLabel *monthLabel;
    QSpinBox *dayBox;
    QSpinBox *monthBox;
    QHBoxLayout *dayLayout;
    QHBoxLayout *monthLayout;

    QLabel *timeLabel;
    QLabel *minuteLabel;
    QLabel *secondLabel;
    QTimer *timer;
    int runningTime;
    QHBoxLayout *timerLayout;

    QVBoxLayout *mainLayout;
    QGridLayout *boardGrid;
    QList<QList<QLabel*>> boardLabels;
    QPushButton *startButton;

    QThread *searchThread;
    SearchCombs *search;

    void clearBoard();
    void fillBoard(Board&);

private slots:
    void startCalculating();
    void showResult(Board);
    void readyTest();
    void timeOut();
    void startTimer();
    void stopTimer();
};

#endif // MAINWINDOW_H
