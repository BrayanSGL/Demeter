#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"
#include "font_big.h"
#include "UTouch.h"
#include "stdio.h"

float x=0,y=0;
int tecla = 0;
int xInt, yInt;

// the TFT is connected to SPI pin 5-7
SPI_TFT_ILI9341 TFT(D11, D12, D13, D8, D10, D9,"TFT");
// mosi, miso, sclk, cs, reset, dc ......................ojo reset a 3.3 v
UTouch  myTouch(A0, A1, D7, D5, D4);
//PinName tclk, PinName tcs, PinName tdin, PinName dout, PinName irq ojo esta para kl25Z funcional

//Prototipo de funciones

void tecladoAlfa();
int teclear(float x, float y);

int main()
{

    TFT.claim(stdout);      // arranca el stdout de la TFT
    TFT.set_orientation(0);
    TFT.background(Red);    // set background to black
    TFT.foreground(White);    // set chars to white
    TFT.cls();                // clear the screen

    //first show the 4 directions
    TFT.set_orientation(2);
    TFT.cls();

    myTouch.InitTouch();
    myTouch.SetPrecision(PREC_LOW);

    tecladoAlfa();

    while(1==1) {

        if (myTouch.DataAvailable()) {
            if(myTouch.Read()) {
                x = myTouch.GetX(); // toma x del touch
                y = myTouch.GetY(); // toma y del touch
                TFT.locate(60,10);
                xInt = (int)x;
                yInt = (int)y;
                TFT.printf("%d , %d  ", xInt, yInt);
                TFT.locate(110,60);
                tecla = teclear(x,y);

                if(tecla==42) {
                    TFT.printf("*  ");
                } else if (tecla==35) {
                    TFT.printf("#  ");
                } else {
                    TFT.printf("%d   ",tecla);
                }
            }
        }
    }
}

//////Definición de funviones

int teclear(float x, float y)
{
    int a = 0;
    /////////////1
    if (y > 0 && x > 44 && y < 33 && x < 69) {
        return 1;
    }
    /////////////2
    if (y > 33 && x > 44 && y < 66 && x < 69) {
        return 2;
    }
    /////////////3
    if (y > 66 && x > 44 && y < 100 && x < 69) {
        return 3;
    }
    /////////////4
    if (y > 0 && x > 69 && y < 33 && x < 94) {
        return 4;
    }
    /////////////5
    if (y > 33 && x > 69 && y < 66 && x < 94) {
        return 5;
    }
    /////////////6
    if (y > 66 && x > 69 && y < 100 && x < 94) {
        return 6;
    }

    /////////////7
    if (y > 0 && x > 94 && y < 33 && x < 119) {
        return 7;
    }
    /////////////8
    if (y > 33 && x > 94 && y < 66 && x < 119) {
        return 8;
    }
    /////////////9
    if (y > 66 && x > 94 && y < 100 && x < 119) {
        return 9;
    }
    /////////////0
    if (y > 33 && x > 119 && y < 66 && x < 144) {
        return 0;
    }
    /////////////#
    if (y > 66 && x > 119 && y < 100 && x < 144) {
        return 35;
    }
    /////////////*
    if (y > 0 && x > 119 && y < 33 && x < 144) {
        return 42;
    }
    return 219;
}

void tecladoAlfa()
{
    //Dibibujo del cuadrado

    TFT.fillrect(0,0,240,320,Red);
    TFT.rect(2,2,238,102,White);
    TFT.rect(3,3,237,101,White);
    TFT.rect(2,106,238,319,White);

    TFT.line(80,106,80,319,White);
    TFT.line(160,106,160,319,White);
    TFT.line(160,106,160,319,White);
    TFT.line(240,106,240,319,White);

    TFT.line(2,160,238,160,White);
    TFT.line(2,214,238,214,White);
    TFT.line(2,268,238,268,White);

    //Los números

    TFT.set_font((unsigned char*) Arial28x28);
    TFT.locate(30,120);
    printf("1");
    TFT.locate(110,120);
    printf("2");
    TFT.locate(190,120);
    printf("3");

    TFT.locate(30,174);
    printf("4");
    TFT.locate(110,174);
    printf("5");
    TFT.locate(190,174);
    printf("6");

    TFT.locate(30,228);
    printf("7");
    TFT.locate(110,228);
    printf("8");
    TFT.locate(190,228);
    printf("9");

    TFT.locate(30,282);
    printf("*");
    TFT.locate(110,282);
    printf("0");
    TFT.locate(190,282);
    printf("#");
}