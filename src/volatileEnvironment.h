#include "ProtogenHead.h"
#include "AnimationBook.h"

#ifndef VOLATILEENVIRONMENT_H_
#define VOLATILEENVIRONMENT_H_

volatile ProtogenHead *head;
volatile AnimationBook *book;
volatile char current_animation[10] = STARTUP_ANIMATION;

#endif