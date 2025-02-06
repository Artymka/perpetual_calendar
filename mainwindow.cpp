#include "mainwindow.h"
#include "constants.h"
#include <algorithm>


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
    timeLabel = new QLabel("Время перебора");
    minuteLabel = new QLabel("0 мин");
    secondLabel = new QLabel("0 с");
    minuteLabel->setAlignment(Qt::AlignRight);
    secondLabel->setAlignment(Qt::AlignLeft);
    timerLayout = new QHBoxLayout();

    timerLayout->addWidget(timeLabel);
    timerLayout->addWidget(minuteLabel);
    timerLayout->addWidget(secondLabel);

    timer = new QTimer();
    runningTime = 0;

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

    // connect(this->startButton, &QPushButton::clicked, this, &MainWindow::testStartButton);

    searchThread = new QThread();
    search = new SearchCombs();
    search->moveToThread(searchThread);
    searchThread->start();

    qRegisterMetaType<Board>();

    // подключение слотов
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startCalculating);

    connect(search, &SearchCombs::finished, this, &MainWindow::showResult);
    connect(search, &SearchCombs::ready, this, &MainWindow::readyTest);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(search, &SearchCombs::finished, this, &MainWindow::stopTimer);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeOut);
}

void MainWindow::readyTest()
{
    qDebug() << "ready";
}

void MainWindow::timeOut()
{
    qDebug() << "timeout";
    runningTime++;
    secondLabel->setText(QString::number(runningTime % 60) + QString(" с"));
    minuteLabel->setText(QString::number(runningTime / 60) + QString(" мин"));
}

void MainWindow::startTimer()
{
    qDebug() << "startTimer";
    runningTime = 0;
    timer->start(1000);
    secondLabel->setText("0 с");
    minuteLabel->setText("0 мин");
}

void MainWindow::stopTimer()
{
    qDebug() << "stopTimer";
    timer->stop();
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
    // startButton->setEnabled(false);

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
    search->setData(start_board, 0, details);
    search->restart();
    // search->terminate();

    // search->moveToThread(searchThread);
    // connect(searchThread, &QThread::started, search, &SearchCombs::run);
    // connect(search, &SearchCombs::finished, searchThread, &QThread::quit);

    // прерываем предыдущий поток, если рассчёты начались заново
    // connect(startButton, &QPushButton::clicked, search, &SearchCombs::terminate);
    // connect(startButton, &QPushButton::clicked, searchThread, &QThread::terminate);



    // searchThread->start();
}

void MainWindow::showResult(Board res_board)
{
    clearBoard();
    fillBoard(res_board);
}
