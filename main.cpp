//juego prueba version 5.1
#include"iostream"
#include"stdio.h"
#include"windows.h"
#include"conio.h"
#include "stdlib.h"
#include"mmsystem.h"
using namespace std;
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ENTER 13
#define ESC 27
void juego();
int vidas=3;
float TIMEP=25;
int backcolor=0;
string audio[3]{
"audio1(1).wav","audio(2).wav"
};



int color[7]{
    0x009,
    0x00E,
    0x00C,
    0x002,
    0x00B,
    0x005,
    0x00F,
};

int puntos=0;
void gotoxy(int x,int y){
    HANDLE Sitio;
    Sitio=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(Sitio,dwPos);
}
void setCColor(int color){
    static HANDLE hConsole;
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color|(backcolor*0x10+0x100));
}
void pantalla_inicial(){
    PlaySound(TEXT("intro.wav"),NULL,SND_ASYNC);
    gotoxy(30,16);printf(" * *   * *    **   ****  ****");
    gotoxy(30,17);printf("*   *  *  *  *  *  *     *   ");
    gotoxy(30,18);printf(" *     *  *  *  *  *     *   ");
    gotoxy(30,19);printf("  *    *  *  *  *  *     *   ");
    gotoxy(30,20);printf("       ***   *  *  *     *** ");
    gotoxy(30,21);printf("   *   *     ****  *     *   ");
    gotoxy(30,22);printf("    *  *     *  *  *     *   ");
    gotoxy(30,23);printf("*   *  *     *  *  *     *   ");
    gotoxy(30,24);printf(" * *   *     *  *  ****  ****");

    gotoxy(42,27); printf("  %c  ",30);
    gotoxy(42,28); printf(" %c %c",30,30);
    gotoxy(42,29); printf(" %c %c",30,30);
    gotoxy(42,30); printf("%c   %c",30,30);
    gotoxy(42,31);printf("%c%c %c%c",30,30,30,30);
    gotoxy(42,32); printf("  %c  \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",30);

    puntos=0;
}

void limpia(){
for(int l=0;l<90;l++){
        for(int c;c<50;c++){
            cout<<" ";
        }
        cout<<endl;
    }
}
void limpiar_pantalla(){
    char tecla;
    limpia();
    vidas=3;
    pantalla_inicial(); system("pause");
    limpia();
    juego();
}
void quitandocursor(){
    HANDLE Sitio;
    Sitio=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursora;
    cursora.dwSize=2;
    cursora.bVisible=FALSE;
    SetConsoleCursorInfo(Sitio,&cursora);
}

class personaje{
    int x,y;
    int dibujar;
public:
   personaje(int _x,int _y,int _dibujar):x(_x),y(_y),dibujar(_dibujar){}
    int X(){return x;}
    int Y(){return y;}
    void pintar();
    void borrar();
    void mover();
    void muerte();
    void dibujarvida();
};
class asteroide{
int x,y;
public:
    asteroide(int h,int k):x(h),y(k){}
    void dibuja();
    void mover();
    void colision(class personaje &n);

};
void asteroide::dibuja(){
    gotoxy(x,y);setCColor(color[1]);printf("%c",184);
}
void asteroide::mover(){
    gotoxy(x,y);printf(" ");

    y++;
    if(y>49){
        x=rand()%60;
        y=0;
    }
    dibuja();
}
void asteroide::colision(class personaje &n){
  if(x>=n.X()&&x<n.X()+5&&y>=n.Y()&&y<=n.Y()+2){
        vidas--;
        x=rand()%60;
        y=0;
        n.borrar();
        //PlaySound(TEXT("muerte.wav"),NULL,SND_ASYNC);
        n.pintar();
}}
void dibujarvida(){
    int a=0;
    gotoxy(75,23);printf("VIDAS");
    switch(vidas){
        case 3:
        for( a ; a<21; a=a+7){
        gotoxy(68+a,25);setCColor(color[4]);printf("  %c",30);
        gotoxy(68+a,26);printf(" %c%c%c",40,207,41);
        gotoxy(68+a,27);printf("%c%c %c%c",30,190,190,30);}
        break;
        case 2:
            for( a ; a<14; a=a+7){
            gotoxy(68+a,25);setCColor(color[4]);printf("  %c",30);
            gotoxy(68+a,26);printf(" %c%c%c",40,207,41);
            gotoxy(68+a,27);printf("%c%c %c%c",30,190,190,30);}
            gotoxy(82,25);setCColor(color[4]);printf("   ");
        gotoxy(82,26);printf("    ");
        gotoxy(82,27);printf("     ");

            break;
        case 1:
             for( a ; a<7; a=a+7){
            gotoxy(68+a,25);setCColor(color[4]);printf("  %c",30);
            gotoxy(68+a,26);printf(" %c%c%c",40,207,41);
            gotoxy(68+a,27);printf("%c%c %c%c",30,190,190,30);}
            gotoxy(75,25);setCColor(color[4]);printf("   ");
        gotoxy(75,26);printf("    ");
        gotoxy(75,27);printf("     ");
            break;
        case 0:
            gotoxy(68,25);setCColor(color[4]);printf("   ");
        gotoxy(68,26);printf("    ");
        gotoxy(68,27);printf("     ");
             gotoxy(68,27);printf("GAME OVER");
             break;

    }}
void personaje::pintar(){
gotoxy(x,y);setCColor(color[2]);printf("  %c",30);
gotoxy(x,y+1);printf(" %c%c%c",40,207,41);
gotoxy(x,y+2);printf("%c%c %c%c",30,190,190,30);}

void personaje::muerte(){
    if(vidas==0){
            PlaySound(TEXT("muerte.wav"),NULL,SND_ASYNC);
    for(int f=0;f<8;f++){
        borrar();
        gotoxy(x,y);setCColor(color[1]);printf("   **   ");
        gotoxy(x,y+1);printf("  ****  ");
        gotoxy(x,y+2);printf("   **   ");
        Sleep(200);
        borrar();
        gotoxy(x,y);setCColor(color[2]);printf(" * ** *");
        gotoxy(x,y+1);printf("  ****  ");
        gotoxy(x,y+2);printf(" * ** * ");
        Sleep(200);
        Sleep(TIMEP);
    }
    //PlaySound(TEXT("Gameover.wav"),NULL,SND_ASYNC);
      limpiar_pantalla();
    }}

void personaje::borrar(){
gotoxy(x,y);printf("     ");
gotoxy(x,y+1);printf("     ");
gotoxy(x,y+2);printf("     ");}
bool juegoterminado = false;
void personaje::mover(){
    if(kbhit()){
            char tecla=getch();
            borrar();
            if(tecla== IZQUIERDA&&x>0){
                x--;}
            if(tecla==DERECHA&&x<60){
                    x++;}
            if(tecla==ARRIBA&&y>0){
                y--;}
            if(tecla==ABAJO&&y<47){
                y++;}
            pintar();
            if(tecla==ESC){
                juegoterminado =true;}
            if(tecla==112){
                //system("pause");
                gotoxy(75,29);cout<<"PAUSA";
                getch();

                limpia();
                pintar();}
               }
                }
void TIMEs(){
    gotoxy(65,10);
    cout<<"puntos";
    gotoxy(75,10);
    cout<<puntos;}
void juego(){
    personaje n(30,25,3);
    n.pintar();
    PlaySound(TEXT("Star Wars Epic Music Medley.wav"),NULL,SND_ASYNC);
    asteroide loc1(10,0),loc2(5,5),loc3(1,16),loc4(25,10);
    while(!juegoterminado){
        loc1.mover();loc1.colision(n);
        loc4.mover();loc4.colision(n);
        TIMEs();loc2.colision(n);loc3.colision(n);
        loc2.mover();
        loc3.mover();dibujarvida();
        n.mover();
        n.muerte();
         Sleep(TIMEP);
         puntos++;
        TIMEP=TIMEP-0.0001;}
    exit(0);
    }
int main(){
    system("mode con: cols=90 lines=50");
    quitandocursor();
    pantalla_inicial();
    getch();
    limpia();
    juego();
}
