#include "game.h"
#include "ui_game.h"
#include "QString"
#include "start.h"
#include "instrucciones.h"
#include <QMediaPlayer>

QMediaPlayer* Fondo=new QMediaPlayer;
GAME::GAME(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GAME)
{
    ui->setupUi(this);

    Fondo->setMedia(QUrl::fromLocalFile("C:/Users/jaime/Music/Bomberman Generation OST - Classic Mode _ Standard - 128K MP3.mp3"));
    Fondo->play();
}

GAME::~GAME()
{
    delete ui;
}

void GAME::on_pushButton_3_clicked()
{
    Instrucciones*GAME=new Instrucciones();
    GAME->show();
}

void GAME::on_Start_clicked()
{
    Start*Bomber=new Start();
    Bomber->show();
    Fondo->stop();
    close();
}

void GAME::detener(){
    Fondo->stop();
}
