#include "externs.h"
//.........Variables........
bool is_visited[100];
double reward_of_one_episode[100];
//..........................
void MC_one_episode(int start_of_episode)
{
	//Initialize for one episode..............
	for(int i=0;i<num_states;i++)
	{
		reward_of_one_episode[i] = 0;
		is_visited[i] = false;
	}
	//........................................
	int current = start_of_episode;
	double temp_gama = 1;
	while (current!=End)
	{
		int next = policy[current];
		Gosal g = gosals[current][next];
		double reward =(double) give_reward(g);
		if(next==End)
			reward = reward + End_reward;
		reward_of_one_episode[next] = reward_of_one_episode[current]+temp_gama*reward;
		current = next;
		temp_gama = temp_gama*gama;
	}
	current = start_of_episode;
	temp_gama = 1;
	while (current!=-1)
	{
		if(!is_visited[current])
		{
			if(current==End)
				reward_of_one_episode[End] = End_reward;
			else
				reward_of_one_episode[current] = ((reward_of_one_episode[End]-
				reward_of_one_episode[current]))/temp_gama ;
			//update Mean- because this state is encountered another time......................................
			int num = states[current].num_returns;
			states[current].state_value=( (states[current].state_value)*(double)num+ reward_of_one_episode[current])/(double)(num+1);
			states[current].num_returns++;
			//..................................................
			is_visited[current] =true;
		}
		current = policy[current];
		temp_gama = temp_gama*gama;
	}
}
void first_visit_mc(int num_episodes,int num_iterations)
{
	initialize_action_values();
	for(int i=0;i<num_iterations;i++)
	{
		for(int j=0;j<num_episodes;j++)
		{
			int start_of_episode = rand() % (num_states);
			MC_one_episode(start_of_episode);
		}
	}
}
