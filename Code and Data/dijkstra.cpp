#include "externs.h"
#define inf 999999

bool visited[100];
double dist[100];
double mean_reward(Gosal g)
{
	int num = g.num_probs;
	double avg = 0;
	for(int i=0;i<num;i++)
	{
		avg = avg + g.poisons[i].prob*g.poisons[i].value;
	}
	return avg;
}
void dijkstra()
{
	int source = start;
	for(int i=0;i<num_states;i++)
	{
		visited[i] = false;
		dist[i] = inf;
	}
	dist[source] = 0;
	int current = source;
	while(current!=End)
	{
		visited[current] = true;
		state s = states[current];
		for(int i=0;i<4;i++)
		{
			if(states[current].value_of_action[i]!=-1)
			{
				int next = return_next_state(current, i);
				double new_dist = dist[current] + mean_reward(gosals[current][next]);
				if(new_dist <dist[next])
				{
					dist[next] = new_dist;
					previous[next] = current;
				}
			}
		}
		double min_dist = inf;
		int next = -1;
		for(int i=0;i<num_states;i++)
		{
			if(dist[i]<min_dist && !visited[i])
			{
				min_dist = dist[i];
				next = i;
			}
		}
		current = next;
	}
}
