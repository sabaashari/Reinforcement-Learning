#include "externs.h"
void TD_one_iteration(int num_episodes)
{
	for(int i=0;i<num_states;i++)
	{
		reward_of_one_iteration[i] = 0;
	}
	reward_of_one_iteration[End] = (double)End_reward;
	for(int i=0;i<num_episodes;i++)
	{
		int start_of_episode = rand() % (num_states);
		int current = start_of_episode;
		while (current!=End)
		{
			int next = policy[current];
			Gosal g = gosals[current][next];
			double reward = (double)give_reward(g);
			reward_of_one_iteration[current] = reward_of_one_iteration[current] + 
				alpha*(reward+gama*reward_of_one_iteration[next] - reward_of_one_iteration[current]);
			current = next;
		}
	}
}
void TD0(int num_episodes,int num_iterations)
{
	initialize_action_values();
	for(int i=0;i<num_iterations;i++)
	{
		TD_one_iteration(num_episodes);

		//.......miangin giry............
		for(int i=0;i<num_states;i++)
		{
			int num = states[i].num_returns;
			states[i].state_value = (states[i].state_value*(double)num + reward_of_one_iteration[i])/(double)(num+1);
			states[i].num_returns++;
		}
	}
}

