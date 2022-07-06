#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QSplashScreen>
#include <QTimer>

class Game : public QWidget
{
public:
    Game();

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent *event) override;

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;
    static const int DELAY = 85;

    void draw();
    void localApple();
    void move();
    void checkField();
    void gameOver();
    void checkApple();

    int timerId;

    QPoint apple;

    enum Directions{
        left, right, up, down
    };

    Directions direction;

    bool isInGame;
    QVector<QPoint> dots;

    void initGame();
};

#endif // GAME_H
