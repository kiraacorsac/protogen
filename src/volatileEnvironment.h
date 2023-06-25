#include "ProtogenHead.h"
#include "AnimationBook.h"
#include <mutex>

#ifndef VOLATILEENVIRONMENT_H_
#define VOLATILEENVIRONMENT_H_

volatile ProtogenHead *head;
volatile AnimationBook *book;

std::mutex animation_mutex;
volatile char current_animation[10] = STARTUP_ANIMATION;

#endif