#ifndef _VARIABLES_H_
#define _VARIABLES_H_
/*********************************/
#include "commons.h"

//Global Variables
Gosal gosals[100][100];
int policy[100];
int state_values[100];
int m,n,num_states,num_gosals;
int start,End;
int End_reward = 300;
double gama = 1;
double epsilon = 0.1;
double alpha = 1;
double beta = 1;
double delta;
state states[100];
double reward_of_one_iteration[100];
int previous[100];
int num_questions;
question questions[4];
double optimal_prob;
#endif //
/****************************/
