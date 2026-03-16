// Circuits.h
#ifndef CIRCUITS_H
#define CIRCUITS_H
#pragma once
#include <raylib.h>
#include <string>
#include "Components.h"
//#include "Util.h"

// Prototyper för alla kretsar
void DrawCircuit(int circuit, int level,bool active,bool ledState);

void DrawGPIOPanel(int startX, int startY);

// krets 1 nivåer
void DrawCircuit1_Basic(bool active);
void DrawCircuit1_Mid(bool ledState);
void DrawCircuit1_Full();

void DrawCircuit2_Basic();
void DrawCircuit2_Mid(bool ledOn);
void DrawCircuit2_Full(bool ledOn);

void DrawCircuit3_Basic(float potValue);


#endif