#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Manage.hpp"

int Manage::curWonStage = 0;
int Manage::curStage = 0;

void Manage::setCurStage (int val){
    curStage = val;
}
int Manage::getCurStage () const{
    return curStage;
}

void Manage::setCurWonStage (int val){
    curWonStage = val;
}

int Manage::getCurWonStage () const{
    return curWonStage;
}