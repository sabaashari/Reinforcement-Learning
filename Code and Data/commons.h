#ifndef _COMMONS_H_
#define _COMMONS_H_
/*********************************/
//......Includes....................
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <math.h>
#include <stdio.h>
//...................................

//........Data Type Defenitions...........
struct question
{
	char *number;
	int iterations;
	int episodes;
};
struct Poison
{
	int value;
	float prob;

};
struct Gosal
{
	int num_probs;
	Poison poisons[5];

};
struct state
{
	int num_actions;
	int selected_action;
	int next_state;
	int num_returns;
	int num_action_returns[4];
	double state_value;
	double value_of_action[4];
	double preference[4];
	double prob_of_action[4];
};
//....................................

//..............Declare Functions......
int give_reward(Gosal g);
void read_input(FILE *);
void esoft_mc(int num_episodes,int num_iterations);
void print_output_a(FILE *);
void TD0(int iteration,int num_episodes);
void first_visit_mc(int num_episodes,int num_iterations);

/**************common functions of part b*****************/
void initialize_action_values();
int generate_one_episode();
int return_next_state(int state, int action);
void print_output_b(FILE *);
void TD_one_iteration(int num_episodes);
/********************************************************/

/************Question2-b*********************/
void dijkstra();
void actor_critic(int num_iterations);
void policy_update();
//********************************************

#endif
