#include "game.h"

int counter = 0;

Game::Game()
{
    this->resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
    this->setWindowTitle("Snake Game");
    initGame();
}

void Game::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if(isInGame){
        checkApple();
        move();
        checkField();
    }

    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left && direction != Directions::right){
        direction = Directions::left;
    }
    if(event->key() == Qt::Key_Right && direction != Directions::left){
        direction = Directions::right;
    }
    if(event->key() == Qt::Key_Up && direction != Directions::down){
        direction = Directions::up;
    }
    if(event->key() == Qt::Key_Down && direction != Directions::up){
        direction = Directions::down;
    }
}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    draw();
}

void Game::move()
{
    for(int i = dots.size() - 1; i > 0; i--){
        dots[i] = dots[i - 1];
    }
    switch(direction){
    case left: {
        dots[0].rx() -= 1;
        break;
    }
    case right: {
        dots[0].rx() += 1;
        break;
    }
    case up: {
        dots[0].ry() -= 1;
        break;
    }
    case down: {
        dots[0].ry() += 1;
        break;
    }
    }
}

void Game::checkField()
{
    if(dots.size() > 4){
        for(int i = 1; i < dots.size(); i++){
            if(dots[0] == dots[i]){
                isInGame = false;
            }
        }
    }

    if(dots[0].x() >= FIELD_WIDTH || dots[0].x() < 0 || dots[0].y() >= FIELD_HEIGHT || dots[0].y() < 0){
        isInGame = false;
    }

    if(!isInGame){
        killTimer(timerId);
    }
}

void Game::gameOver()
{
    if(counter){
        QMessageBox message;
        message.setText("Game over");
        message.exec();
    }
    counter++;
    initGame();
}

void Game::checkApple()
{
    if(apple == dots[0]){
        dots.push_back(QPoint(0, 0));
        localApple();
    }
}

void Game::draw()
{
    QPainter canvas(this);

    if(isInGame){
        canvas.setBrush(Qt::red);
        canvas.drawEllipse(apple.x() * DOT_WIDTH, apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

        for(int i = 0; i < dots.size(); i++){
            if(i == 0){
                canvas.setBrush(Qt::white);
                canvas.drawEllipse(dots[i].x() * DOT_WIDTH, dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
            else{
                canvas.setBrush(Qt::green);
                canvas.drawEllipse(dots[i].x() * DOT_WIDTH, dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
        }
    }
    else{
        gameOver();
    }
}

void Game::localApple()
{
    apple.rx() = rand() % DOT_WIDTH;
    apple.ry() = rand() % DOT_HEIGHT;
}

void Game::initGame(){
    isInGame = true;
    direction = right;
    dots.resize(3);

    for(int i = 0; i < dots.size(); i++){
        dots[i].rx() = dots.size() - i - 1;
        dots[i].ry() = 0;
    }

    localApple();

    timerId = startTimer(DELAY);
}
