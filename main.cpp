#include <game.h>
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("D:/Qt/63cec0f38ed9cd1613c36969c1eea3db.jpg"));
    splash->show();
    Game game;

    QTimer::singleShot(2500, splash, SLOT(close()));
    QTimer::singleShot(2500, &game, SLOT(show()));

    return app.exec();
}
