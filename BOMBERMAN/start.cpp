#include "start.h"
#include "ui_start.h"
#include "player.h"
#include "bomba.h"
#include "empate.h"
#include <QTimer>
#include <QLabel>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QVector>
#include <QPixmap>
#include <QString>
#include <string>
#include "win.h"
#include "win2.h"
using namespace std;

QGridLayout* entorno;
QVector <QVector <QLabel*>> matriz;
string s[11][15];

QString bomba = "C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/bomba.jpg";
QString piso = "C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/Textura.jpg";
QString muro = "C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/Muro.png";
QString imagen = "C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/descarga.png";
QString imagen2 = "C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/descarga2.png";
QString destruible = "C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/images.jpg";
QString fuego="C:/Users/jaime/Documents/BOMBERMAN/Camera Roll/8893340-illustration-Symbol-fire-shiny-flame-over-white-background-Stock-Vector.jpg";

Player* jugador1;
Player* jugador2;

int pos_xj1 = 0;
int pos_yj1 = 0;

int pos_xj2 = 10;
int pos_yj2 = 14;

QTimer *finish;

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    crear_entorno();
    crear_bloques();
    QMediaPlayer* song=new QMediaPlayer;
    song->setMedia(QUrl::fromLocalFile("C:/Users/jaime/Music/Bomberman.mp3"));
    song->play();
    ui->gridLayout->addLayout(entorno,0,0);
    finish = new QTimer(this);
    connect(finish,SIGNAL(timeout()),this,SLOT(empate__()));
    finish->start(72000);
}

Start::~Start()
{
    delete ui;
}

void Start::crear_entorno()
{
    entorno = new QGridLayout(this);
    jugador1 = new Player;
    jugador2 = new Player;
    int i,j;
    for(i = 0; i != 11; i++){
        QVector<QLabel*>lista;
        for(j = 0; j != 15; j++){
            QLabel* cuadro;
            cuadro=new QLabel;
           if(((i+1)%2==0)&&((j+1)%2==0)){
               cuadro->setPixmap(QPixmap(muro));
               s[i][j] = "X";
           }
           else{
               s[i][j] = "x";
               cuadro->setPixmap(QPixmap(piso));
           }
           cuadro->setMaximumHeight(80);
           cuadro->setMaximumWidth(100);
           cuadro->setScaledContents(true);
           entorno->addWidget(cuadro,i,j);
           lista.push_back(cuadro);
        }
        matriz.push_back(lista);
    }
    entorno->setSpacing(0);
    jugador1->set_rostro(imagen);
    jugador2->set_rostro(imagen2);
    matriz[0][0]->setPixmap(QPixmap(jugador1->rostro));
    matriz[10][14]->setPixmap(QPixmap(jugador2->rostro));
}

void Start::fuego__(){
    if((jugador1->Mybomb->pos_x==0)&&(jugador1->Mybomb->pos_y==0)){
        matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(piso));

        matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(piso));

        matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(piso));
    }
    else if(((jugador1->Mybomb->pos_x)==0)&&((jugador1->Mybomb->pos_y==14))){

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
            }
    else if(((jugador1->Mybomb->pos_x)==10)&&((jugador1->Mybomb->pos_y==0))){

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
            }

    delete jugador1->Mybomb->fuego_tiempo;
}

void Start::explosion_j1()
{
    matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(piso));
    if((jugador1->Mybomb->pos_x==0)&&(jugador1->Mybomb->pos_y==0)){
                 matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                 s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                 matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                 s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                 matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                 s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                 ++jugador1->limite;
                 jugador1->Mybomb->fuego_tiempo = new QTimer;
                 connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                 jugador1->Mybomb->fuego_tiempo->start(1000);
            }
    else if(((jugador1->Mybomb->pos_x)==0)&&((jugador1->Mybomb->pos_y==14))){

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";
                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);
            }
    else if(((jugador1->Mybomb->pos_x)==10)&&((jugador1->Mybomb->pos_y==0))){

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);
            }
    else if(((jugador1->Mybomb->pos_x)==10)&&((jugador1->Mybomb->pos_y==14))){

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);
            }
    else if((jugador1->Mybomb->pos_x%2==0)&&((jugador1->Mybomb->pos_y+1)%2==0)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);
            }
    else if((jugador1->Mybomb->pos_x==0)&&(jugador1->Mybomb->pos_y%2==0)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";

                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";

                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);

            }
    else if((jugador1->Mybomb->pos_x==10)&&(jugador1->Mybomb->pos_y%2==0)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);

            }
    else if((jugador1->Mybomb->pos_x%2==0)&&(jugador1->Mybomb->pos_y==0)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);

            }
    else if((jugador1->Mybomb->pos_x%2==0)&&(jugador1->Mybomb->pos_y==14)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);

            }
    else if(((jugador1->Mybomb->pos_x+1)%2==0)&&(jugador1->Mybomb->pos_y%2==0)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);


            }
    else if((jugador1->Mybomb->pos_x%2==0)&&(jugador1->Mybomb->pos_y!=0)){
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x-1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y-1] = "x";
                matriz[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                ++jugador1->limite;
                jugador1->Mybomb->fuego_tiempo = new QTimer;
                connect(jugador1->Mybomb->fuego_tiempo,SIGNAL(timeout()),this,SLOT(fuego__()));
                jugador1->Mybomb->fuego_tiempo->start(1000);
            }
    delete jugador1->Mybomb->my_tiempo;
}

void Start::explosion_j2()
{
    matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(piso));
    if((jugador2->Mybomb->pos_x==0)&&(jugador2->Mybomb->pos_y==0)){
                 matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                 s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                 matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                 s[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y] = "x";
                 matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                 s[jugador2->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                 ++jugador2->limite;
            }
    else if(((jugador2->Mybomb->pos_x)==0)&&((jugador2->Mybomb->pos_y==14))){

                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x+1][jugador1->Mybomb->pos_y] = "x";
                ++jugador2->limite;
            }
    else if(((jugador2->Mybomb->pos_x)==10)&&((jugador2->Mybomb->pos_y==0))){

                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador1->Mybomb->pos_y+1] = "x";
                ++jugador2->limite;
            }
    else if(((jugador2->Mybomb->pos_x)==10)&&((jugador2->Mybomb->pos_y==14))){

                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                ++jugador2->limite;
            }
    else if((jugador2->Mybomb->pos_x%2==0)&&((jugador2->Mybomb->pos_y+1)%2==0)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1] = "x";
                ++jugador2->limite;
            }
    else if((jugador2->Mybomb->pos_x==0)&&(jugador2->Mybomb->pos_y%2==0)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1] = "x";
                matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y] = "x";
                ++jugador2->limite;

            }
    else if((jugador2->Mybomb->pos_x==10)&&(jugador2->Mybomb->pos_y%2==0)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                ++jugador2->limite;

            }
    else if((jugador2->Mybomb->pos_x%2==0)&&(jugador2->Mybomb->pos_y==0)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1] = "x";
                ++jugador2->limite;

            }
    else if((jugador2->Mybomb->pos_x%2==0)&&(jugador2->Mybomb->pos_y==14)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                ++jugador2->limite;

            }
    else if(((jugador2->Mybomb->pos_x+1)%2==0)&&(jugador2->Mybomb->pos_y%2==0)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y] = "x";
                ++jugador2->limite;


            }
    else if((jugador2->Mybomb->pos_x%2==0)&&(jugador2->Mybomb->pos_y!=0)){
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x-1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x+1][jugador2->Mybomb->pos_y] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y-1] = "x";
                matriz[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1]->setPixmap(QPixmap(fuego));
                s[jugador2->Mybomb->pos_x][jugador2->Mybomb->pos_y+1] = "x";
                ++jugador2->limite;
            }
    delete jugador2->Mybomb->my_tiempo;
}

void Start::empate__()
{
    empate *p=new empate;
    p->show();
    finish->stop();
    this->close();
}

void Start::ganador1()
{
    win *p=new win;
    p->show();

    this->close();
}
void Start::ganador2()
{
    win2 *p=new win2;
    p->show();

    this->close();
}


void Start::crear_bloques()
{
    int totalidad = 130;
    int x;
    int y;
    while(totalidad!=0){
        x = qrand() % 11;
        y = qrand() % 15;
        if(!(((x+1)%2==0)&&((y+1)%2==0))){
            if(!((x == 0 && y == 0) ||(x == 10 && y == 14))){
                if(!((x == 1 && y == 0) || (x == 10 && y == 13))){
                    if(!((x == 0 && y == 1) || (x == 9 && y == 14))){
                        if(s[x][y] != "m")
                            s[x][y] = "m";
                            --totalidad;
                            matriz[x][y]->setPixmap(QPixmap(destruible));

                    }
                }
            }
        }
    }
}

void Start::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_A){
        if (pos_yj1 != 0){
            if(!(((pos_xj1+1)%2==0)&&((pos_yj1)%2==0))){
                if(s[pos_xj1][pos_yj1-1] != "m"){
                    if(s[pos_xj1][pos_yj1-1] != "b"){
                        if(s[pos_xj1][pos_yj1]=="b"){
                            --pos_yj1;
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                        else{
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(piso));
                            --pos_yj1;
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                    }
                }
             }
         }
    }

    if(event->key() == Qt::Key_D){
        if (pos_yj1 != 14){
            if(!(((pos_xj1+1)%2==0)&&((pos_yj1)%2==0))){
                if(s[pos_xj1][pos_yj1+1] != "m"){
                    if(s[pos_xj1][pos_yj1+1] != "b"){
                        if(s[pos_xj1][pos_yj1] == "b"){
                            ++pos_yj1;
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                        else{
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(piso));
                            ++pos_yj1;
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_W){
        if (pos_xj1 != 0){
            if(!(((pos_xj1)%2==0)&&((pos_yj1+1)%2==0))){
                if(s[pos_xj1-1][pos_yj1] != "m"){
                    if(s[pos_xj1-1][pos_yj1] != "b"){
                        if(s[pos_xj1][pos_yj1] == "b"){
                                --pos_xj1;
                                matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                            }
                        else{
                                matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(piso));
                                --pos_xj1;
                                matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_S){
        if (pos_xj1 != 10){
            if(!(((pos_xj1)%2==0)&&((pos_yj1+1)%2==0))){
                if(s[pos_xj1+1][pos_yj1] != "m"){
                    if(s[pos_xj1+1][pos_yj1] != "b"){
                        if(s[pos_xj1][pos_yj1] == "b"){
                            ++pos_xj1;
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                        else{
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(piso));
                            ++pos_xj1;
                            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_G){
        if (jugador1->limite == 1){
            jugador1->Mybomb = new Bomba;
            matriz[pos_xj1][pos_yj1]->setPixmap(QPixmap(jugador1->Mybomb->bomb));
            jugador1->Mybomb->set_x(pos_xj1);
            jugador1->Mybomb->set_y(pos_yj1);
            s[jugador1->Mybomb->pos_x][jugador1->Mybomb->pos_y] = "b";
            --jugador1->limite;
            jugador1->Mybomb->my_tiempo = new QTimer;
            connect(jugador1->Mybomb->my_tiempo,SIGNAL(timeout()),this,SLOT(explosion_j1()));
            jugador1->Mybomb->my_tiempo->start(3000);
        }
    }

    /************************************************************************************************/
    if(event->key() == Qt::Key_Left){
        if (pos_yj2 != 0){
            if(!(((pos_xj2+1)%2==0)&&((pos_yj2)%2==0))){
                if(s[pos_xj2][pos_yj2-1] != "m"){
                    if(s[pos_xj2][pos_yj2-1] != "b"){
                        if(s[pos_xj2][pos_yj2] == "b"){
                            --pos_yj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                        else{
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(piso));
                            --pos_yj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_Right){
        if (pos_yj2 != 14){
            if(!(((pos_xj2+1)%2==0)&&((pos_yj2)%2==0))){
                if(s[pos_xj2][pos_yj2+1] != "m"){
                    if(s[pos_xj2][pos_yj2+1] != "b"){
                        if(s[pos_xj2][pos_yj2] == "b"){
                            ++pos_yj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                        else{
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(piso));
                            ++pos_yj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_Up){
        if (pos_xj2 != 0){
            if(!(((pos_xj2)%2==0)&&((pos_yj2+1)%2==0))){
                if(s[pos_xj2-1][pos_yj2] != "m"){
                    if(s[pos_xj2-1][pos_yj2] != "b"){
                        if(s[pos_xj2][pos_yj2] == "b"){
                            --pos_xj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                        else{
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(piso));
                            --pos_xj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_Down){
        if (pos_xj2 != 10){
            if(!(((pos_xj2)%2==0)&&((pos_yj2+1)%2==0))){
                if(s[pos_xj2+1][pos_yj2] != "m"){
                    if(s[pos_xj2+1][pos_yj2] != "b"){
                        if(s[pos_xj2][pos_yj2] == "b"){
                            ++pos_xj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                        else{
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(piso));
                            ++pos_xj2;
                            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->rostro));
                        }
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_5){
        if (jugador2->limite == 1){
            jugador2->Mybomb = new Bomba;
            matriz[pos_xj2][pos_yj2]->setPixmap(QPixmap(jugador2->Mybomb->bomb));
            s[pos_xj2][pos_yj2] = "b";
            jugador2->Mybomb->set_x(pos_xj2);
            jugador2->Mybomb->set_y(pos_yj2);
            --jugador2->limite;
            jugador2->Mybomb->my_tiempo = new QTimer;
            connect(jugador2->Mybomb->my_tiempo,SIGNAL(timeout()),this,SLOT(explosion_j2()));
            jugador2->Mybomb->my_tiempo->start(3000);
        }
    }
}
