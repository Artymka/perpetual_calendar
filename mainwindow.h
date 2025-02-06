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
#include "board.h"

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
    QPushButton *startButton;
    QLabel *minuteLabel;
    QLabel *secondLabel;
    QTimer *timer;
    QHBoxLayout *timerLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *dayLayout;
    QHBoxLayout *monthLayout;
    QGridLayout *boardGrid;
    QList<QList<QLabel*>> boardLabels;

    void clearBoard();
    void fillBoard(Board&);

private slots:
    void startCalculating();
    void showResult(Board);
    void testStartButton();
};

#endif // MAINWINDOW_H
