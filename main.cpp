#include "globals.h"
int main()
{
	FILE * fin = fopen ("In-out\\input.txt","r");
	read_input(fin);
	fclose(fin);

	FILE *fout = fopen("In-out\\output.txt","w");
    //printf("%f\n",RAND_MAX);
	for(int q=0;q<num_questions;q++)
	{
		fprintf(fout,"%s\n",questions[q].number);
		if(!strcmp(questions[q].number,"Q11"))
		{
			first_visit_mc(questions[q].episodes,questions[q].iterations);
			print_output_a(fout);
		}
		if(!strcmp(questions[q].number,"Q12"))
		{
			esoft_mc(questions[q].episodes,questions[q].iterations);
			print_output_b(fout);
		}
		if(!strcmp(questions[q].number,"Q21"))
		{
			TD0(questions[q].episodes,questions[q].iterations);
			print_output_a(fout);
		}
		if(!strcmp(questions[q].number,"Q22"))
		{
			actor_critic(questions[q].iterations);
			fprintf(fout,"OPtimal Prob:%f\n",optimal_prob);
			print_output_b(fout);
		}
	}
	fclose(fout);
	return 0;
}
