#ifndef _EXTERNS_H_
#define _EXTERNS_H_
/*********************************/
#include "commons.h"

//Global Variables
extern Gosal gosals[100][100];
extern int policy[100];
extern int state_values[100];
extern int m,n,num_states,num_gosals;
extern int start,End;
extern int End_reward ;
extern double gama;
extern double epsilon;
extern double alpha;
extern state states[100];
extern double reward_of_one_iteration[100];
extern int previous[100];
extern double beta;
extern double delta;
extern int num_questions;
extern question questions[4];
extern double optimal_prob;
#endif //
/****************************/
