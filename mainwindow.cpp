#include "mainwindow.h"
#include "constants.h"
#include "searchcombs.h"
#include <algorithm>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("Рассчёт вечного календаря");

    // ввод даты
    dayLabel = new QLabel("Номер дня");
    monthLabel = new QLabel("Номер месяца");
    dayBox = new QSpinBox();
    monthBox = new QSpinBox();
    dayLayout = new QHBoxLayout();
    monthLayout = new QHBoxLayout();

    dayBox->setMinimum(1);
    dayBox->setMaximum(31);
    monthBox->setMinimum(1);
    monthBox->setMaximum(12);

    dayLayout->addWidget(dayLabel);
    dayLayout->addWidget(dayBox);
    monthLayout->addWidget(monthLabel);
    monthLayout->addWidget(monthBox);

    // таймер
    minuteLabel = new QLabel("0");
    secondLabel = new QLabel("0");
    timer = new QTimer();
    timerLayout = new QHBoxLayout();

    timerLayout->addWidget(minuteLabel);
    timerLayout->addWidget(secondLabel);

    // поле
    startButton = new QPushButton("Рассчитать");
    boardGrid = new QGridLayout();

    QList<QList<QString>> boardLabelsText = Board::getLabelsPattern(BOARD_PATTERN);
    boardLabels = QList<QList<QLabel*>>(7);
    for (int i = 0; i < 7; i++) {
        boardLabels[i] = QList<QLabel*>(7);
        for (int j = 0; j < 7; j++) {
            // qDebug() << i << " " << j;
            boardLabels[i][j] = new QLabel(boardLabelsText[i][j]);
            boardLabels[i][j]->setFixedWidth(50);
            boardLabels[i][j]->setFixedHeight(50);
            boardGrid->addWidget(boardLabels[i][j], i, j);
        }
    }

    // выстраивание окна
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(dayLayout);
    mainLayout->addLayout(monthLayout);
    mainLayout->addWidget(startButton);
    mainLayout->addLayout(timerLayout);
    mainLayout->addLayout(boardGrid);

    // подключение слотов
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startCalculating);
    connect(this->startButton, &QPushButton::clicked, this, &MainWindow::testStartButton);
}

void MainWindow::testStartButton()
{
    qDebug() << "test start button";
}

void MainWindow::clearBoard()
{
    // qDebug() << "clearBoard start";
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            boardLabels[i][j]->setStyleSheet("");
        }
    }
    // qDebug() << "clearBoard end";
}

void MainWindow::fillBoard(Board &board)
{
    // qDebug() << "fillBoard start";
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            Cell &cell = board.field[i][j];
            if (cell.detailInd == -1) continue;
            QLabel *label = boardLabels[i][j];

            QString color = DETAILS_COLORS[cell.detailInd];
            label->setStyleSheet("background-color: " + color + "; color: " + color + ";");
        }
    }
    // qDebug() << "fillBoard end";
}

void MainWindow::startCalculating()
{
    // очистка доски
    // clearBoard();

    QList<Detail> details;
    for (int i = 0; i < DETAILS_SHAPES.size(); i++) {
        details.push_back(Detail(DETAILS_SHAPES[i], i));
    }

    srand(time(0));
    std::random_shuffle(details.begin(), details.end());

    Board start_board = Board(BOARD_PATTERN);

    int day, month;
    day = dayBox->value();
    month = monthBox->value();
    start_board.block(day, month);

    // запуск перебора
    SearchCombs *search = new SearchCombs(start_board, 0, details);
    QThread *searchThread = new QThread();

    search->moveToThread(searchThread);
    connect(searchThread, &QThread::started, search, &SearchCombs::run);
    connect(search, &SearchCombs::finished, searchThread, &QThread::terminate);

    // прерываем предыдущий поток, если рассчёты начались заново
    connect(this->startButton, &QPushButton::clicked, searchThread, &QThread::quit);

    qRegisterMetaType<Board>();
    connect(search, &SearchCombs::finished, this, &MainWindow::showResult);

    searchThread->start();
}

void MainWindow::showResult(Board res_board)
{
    clearBoard();
    fillBoard(res_board);
}
