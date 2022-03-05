#include "externs.h"

//..........Initialize state values..............
void initialize_action_values()
{
	//up:0 down:1 left:2 right:3
	for(int i=0;i<num_states;i++)
	{
		states[i].num_actions = 0;
	}
	for(int i=0;i<num_states;i++)
	{
		states[i].selected_action = -1;
		states[i].next_state = -1;
		//Action up............................
		if(i < n*(n-1))//alowed
		{
			states[i].num_actions ++;
			states[i].value_of_action[0] = 0;
		}
		else//not
			states[i].value_of_action[0] = -1;
		//......................................

		//Action down...........................
		if (i>=n)//alowed
		{
			states[i].num_actions++;
			states[i].value_of_action[1] = 0;
		}
		else//not
			states[i].value_of_action[1] = -1;
		//......................................

		//Action left...........................
		if (i%n!=0)//alowed
		{
			states[i].num_actions++;
			states[i].value_of_action[2] = 0;
		}
		else//not
			states[i].value_of_action[2] = -1;
		//......................................

		//Action Right...........................
		if (i%n!=n-1)//alowed
		{
			states[i].num_actions++;
			states[i].value_of_action[3] = 0;
		}
		else//not
			states[i].value_of_action[3] = -1;
		//.......................................

		states[i].state_value = 0;
		states[i].num_returns = 0;
	}
	for(int i=0;i<num_states;i++)
	{
		for(int j=0;j<4;j++)
			{
				if(states[i].value_of_action[j]==-1)
					states[i].prob_of_action[j] = 0;
				else
					states[i].prob_of_action[j] = double(1)/double(states[i].num_actions);
                //printf("%d %f",i,states[i].prob_of_action[j]);
			}
		//printf("%d\n",states[i].num_actions);
	}
}
//..............................................................................

int return_action(state s)
{
	double r = std::max(rand() / float(RAND_MAX)-0.01,0.0);
    //printf("%f\n",r);
	double sum = 0;
	for(int i=0;i<4;i++)
	{
	    //printf("%f\n", s.prob_of_action[i]);
		double prob_val = s.prob_of_action[i];
		if (r>=sum && r<=sum+prob_val && prob_val!=0)
			return i;
		sum = sum + prob_val;
	}
}
int return_next_state(int state, int action)
{
	int next_state;
	if(action == 0)//if up
		next_state = state + n;
	if(action == 1)// if down
		next_state = state -n;
	if(action==2)// if left
		next_state = state-1;
	if(action == 3)//if right
		next_state = state+1;
	return next_state;
}
int generate_one_episode()
{
	int start_of_episode = rand() % (num_states);
	int current = start_of_episode;
	while(current!=End)
	{
		state current_state = states[current];
		int a = return_action(current_state);
		int next = return_next_state(current,a);
		states[current].next_state = next;
		states[current].selected_action = a;
		current = next;

	}
	return start_of_episode;
}
void print_output_b(FILE * fout)
{
	fprintf(fout,"\n(State,action)\tValue policy\n");
	fprintf(fout,".............................\n");
	for(int i=0;i<num_states;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(states[i].value_of_action[j]!=-1)
			{
				char dir [10];
				if(j==0)
					strcpy(dir,"Up");
				else if(j==1)
					strcpy(dir,"Down");
				else if(j==2)
					strcpy(dir,"Left");
				else
					strcpy(dir,"Right");

				fprintf(fout,"(%d,%s)\t\t%.3f %.3f\n",i+1,dir,states[i].value_of_action[j],states[i].prob_of_action[j]);
			}
		}
	}
	fprintf(fout,"\n");
}
