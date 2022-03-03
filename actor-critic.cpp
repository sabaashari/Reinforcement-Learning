#include "externs.h"
#define inf -40
//initialize..........
void initialize_method()
{
	initialize_action_values();
	for(int i=0;i<num_states;i++)
	{
		for(int j=0;j<4;j++)
		{
			if((states[i].value_of_action[j]!=-1))
			{
				int next = return_next_state(i,j);
				if(next==End)
					states[i].preference[j] = End_reward;
				else
					states[i].preference[j] = 0;
			}
			else
				states[i].preference[j] = inf;
		}
		//printf("%f",states[i].state_value);
	}
	states[End].state_value =(double) End_reward;
	policy_update();
	dijkstra();
}
void policy_update()
{
	for(int s=0;s<num_states;s++)
	{
		double sum_prob = 0;
		for(int a=0;a<4;a++)
		{
			if(states[s].value_of_action[a]!=-1 && states[s].preference[a]<0)
			{
				sum_prob = sum_prob + exp(states[s].preference[a]+End_reward);

			}
			else if(states[s].value_of_action[a]!=-1)
				sum_prob = sum_prob + exp(states[s].preference[a]);
		}
		for(int a=0;a<4;a++)
		{
			//printf("‌Before: %f",states[s].preference[a]);
			if(states[s].value_of_action[a]==-1)
				states[s].prob_of_action[a] = 0;
			else if(states[s].value_of_action[a]!=-1 && states[s].preference[a]<0)
			{
				states[s].prob_of_action[a] = exp(states[s].preference[a]+End_reward)/sum_prob;

			}
			else if(states[s].value_of_action[a]!=-1)
				states[s].prob_of_action[a] = exp(states[s].preference[a])/sum_prob;

            //printf("%f %f",states[s].preference[a],states[s].prob_of_action[a]);
		}
		//printf("\n");
	}
}
int return_action(int current_state,int next_state)
{
	for(int a=0;a<4;a++)
	{
		int s = return_next_state(current_state, a);
		if(s==next_state)
		{
			return a;
		}
	}
}
double prob_optimal_path()
{
	int t = End;
	double prob = 1;
	while(t!=start)
	{
		int s = previous[t];
		int a = return_action(s,t);
		//printf("%f\n",states[s].prob_of_action[a]);
		prob = std::min(prob,states[s].prob_of_action[a]);
		t = s;
	}
	return prob;
}
void actor_critic_one_episode(int start_of_episode)
{
	int current = start_of_episode;
	while (current!=End)
	{

		/**********Update State Value************************/
		int next = states[current].next_state;
		Gosal g = gosals[current][next];
		double delta = (double)give_reward(g) +(gama*states[next].state_value-states[current].state_value);
		states[current].state_value = states[current].state_value + delta;
		//printf("%f\n",delta);
		/***************************************************/

		/*************Update Preferences********************/
		int action = states[current].selected_action;
		//printf("before:%f\n",states[current].preference[action]);
		states[current].preference[action] = states[current].preference[action] + beta*delta;
		states[current].value_of_action[action] = states[current].value_of_action[action] + beta*delta;
		//printf("After:%f\n",states[current].preference[action]);
		/***************************************************/

		current = next;
	}
	policy_update();

}
void actor_critic(int num_iterations)
{
    //printf("%f",beta);
	optimal_prob = 0;
	beta = 0.1;
	initialize_method();
	//printf("%f\n",End_reward);
	//printf("%d",num_iterations);
	for(int i=0;i<num_iterations;i++)
	{
		//while(optimal_prob<0.9)
		//{
			int start_of_episode = generate_one_episode();
			actor_critic_one_episode(start_of_episode);
			optimal_prob = prob_optimal_path();
			printf("%f\n",optimal_prob);
		//}
	}
}
