// Circuits.h
#ifndef CIRCUITS_H
#define CIRCUITS_H
#pragma once
#include <raylib.h>
#include "../Components/GPIO/IGPIO.h"
//#include <string>


// Prototyper för alla kretsar
void DrawCircuit(int circuit, int level,bool active,bool ledState,float potValue,IGPIO* gpio);


#endif