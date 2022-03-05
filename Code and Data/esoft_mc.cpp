#include "externs.h"
//...Variables....................
double reward[100][4];
bool is_visited_action[100][4];
//..........................................

//Policy Evaluation Part........................................................
void policy_evaluation(int start_of_episode)
{
	for(int i=0;i<num_states;i++)
	{
		for(int j=0;j<4;j++)
			is_visited_action[i][j] = false;
	}

	//...........calculate Returns(s,a)........................
	int current_state = start_of_episode;
	int current_action = states[current_state].selected_action;
	int next_state = states[current_state].next_state;
	int next_action = states[next_state].selected_action;
	reward[current_state][current_action] = 0;
	double temp_gama =1;
	while (next_state!=End)
	{

		Gosal g  = gosals[current_state][next_state];
		double r =(double) give_reward(g);
		reward[next_state][next_action] = reward[current_state][current_action]+temp_gama*r;

		current_state = next_state;
		current_action = next_action;
		next_state = states[current_state].next_state;
		next_action = states[next_state].selected_action;
		if(next_state==End)
			reward[current_state][current_action] = reward[current_state][current_action]+temp_gama*End_reward;
		temp_gama = temp_gama*gama;
	}

	int End_action = current_action;
	int End_state = current_state;
	current_state = start_of_episode;
	current_action = states[current_state].selected_action;
	temp_gama = 1;
	while (current_state!=End)
	{
		if(!is_visited_action[current_state][current_action])
		{
			double r = reward[current_state][current_action] = (reward[End_state][End_action]-
				reward[current_state][current_action]) ;

			if(current_state==End_state)
				r = End_reward +(double) give_reward(gosals[current_state][states[current_state].next_state]);
			else
				r = r/temp_gama;

			int num = states[current_state].num_action_returns[current_action];
			states[current_state].value_of_action[current_action] =
				(states[current_state].value_of_action[current_action]*(double)num+r)/(double)(num+1);
			states[current_state].num_action_returns[current_action]++;

			is_visited_action[current_state][current_action] = true;
		}
		current_state = states[current_state].next_state;
		current_action = states[current_state].selected_action;
		temp_gama = temp_gama*gama;
	}

}
//..............................................................................


//.......Policy Improvemet Part.................................................
int best_action(state s)
{
	double max_val =0;
	int best_action =0;
	for(int i=0;i<4;i++)
	{
		if(s.value_of_action[i]>max_val)
		{
			max_val = s.value_of_action[i];
			best_action = i;
		}
	}
	return best_action;
}
void policy_improvement(int start_of_episode)
{
	int current = start_of_episode;
	while (current!=End)
	{
		state *s = &states[current];
		int a = best_action(*s);
		for(int j=0;j<4;j++)
		{
			if(s->value_of_action[j]!=-1)
			{
				if(j==a)
					s->prob_of_action[j] = 1-epsilon+(epsilon/double(s->num_actions));
				else
					s->prob_of_action[j] = (epsilon/double(s->num_actions));
			}
		}
		current = states[current].next_state;
	}
}
//............................................................................
void esoft_mc(int num_episodes,int num_iterations)
{
	initialize_action_values();
	for(int i=0;i<num_iterations;i++)
	{
		for(int j=0;j<num_episodes;j++)
		{
			int start_of_episode = generate_one_episode();
			//if(j==2210)
              //  printf("%d %d\n",i,j);
			policy_evaluation(start_of_episode);
			policy_improvement(start_of_episode);
		}
	}
}
