/*#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>*/

#include "engine.h"

#define FIELD_SIZE 60
#ifndef LEVEL_H
#define LEVEL_H



QM *init_qm(int value, int x, int y)
{
 QM *q;
 q = (QM*)malloc(sizeof(QM));
 
 q->value = value;
 q->flip = 0;
 q->x = x;
 q->y = y;
 
 //q->next = NULL;
 
 return q;                 
}

int stick_qm_to_level(QM *q, LEVEL *l)
{
 //q->next = l->qm->next;
 //l->qm->next = q;
 
 return 1;   
}







#endif
