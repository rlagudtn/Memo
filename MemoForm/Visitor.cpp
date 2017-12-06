//Visitor.cpp
#include"Visitor.h"
#include"Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Page.h"
#include "Character.h"
#include <iostream>
using namespace std;
//Visitor::Visitor() {}
//Visitor::~Visitor(){}
void Visitor::Visit(SingleByteCharacter *singleByteCharacter) {}
void Visitor::Visit(DoubleByteCharacter *doubleByteCharacter) {}

void Visitor::Visit(Row *row) {} 

void Visitor::Visit(Text *text) {}
void Visitor::Visit(Page *page){}