#include "externs.h"
int generate_poison(Gosal g)
{
	int num_probs = g.num_probs;
	Poison *p  = g.poisons;
	float r = rand() / float(RAND_MAX);
	float sum = 0;
	for(int i=0;i<num_probs;i++)
	{
		float prob_val = p[i].prob;
		if (r>=sum && r<=sum+prob_val)
			return -p[i].value;
		sum = sum + prob_val;
	}
}
int give_reward(Gosal g)
{
	int num_probs = g.num_probs;
	if (num_probs == 0)
		return 0;
	return generate_poison(g);
}
void print_output_a(FILE *fout)
{
	fprintf(fout,"\nState\tValue\n");
	fprintf(fout,".................................\n");
	for(int i=0;i<num_states;i++)
		fprintf(fout,"%d\t%.3f\n",i+1,states[i].state_value);
	fprintf(fout,"\n");
}
