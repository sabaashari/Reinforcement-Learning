#include "externs.h"
int compare(const void *a, const void *b)
{
	Poison *p = (Poison *)a;
	Poison *q = (Poison *)b;
	if ((p->prob - q->prob) >0)
		return 1;
	return 0;
}
void read_first_line(FILE *fin)
{
	char q[4];

	fscanf(fin,"%d",&num_questions);
	for(int i=0;i<num_questions;i++)
	{
		fscanf(fin,"%s",q);
		questions[i].number = strdup(q);
		if(strcmp(q,"Q22")==0)
		{
			fscanf(fin,"%f %d",&delta,&questions[i].iterations );
		}
		else
		{
			fscanf(fin,"%d %d",&questions[i].episodes,&questions[i].iterations);
		}
	}
}
void read_input(FILE *fin)
{
	int i,j;
	read_first_line(fin);
	fscanf(fin,"%d %d %d %d",&m,&n,&num_states,&num_gosals);
	fscanf(fin,"%d %d",&start,&End);
	End = End-1;
	start = start-1;
	int n1,n2,num_probs;
	for(i=0;i<num_gosals;i++)
	{
		fscanf(fin,"%d %d %d",&n1,&n2,&num_probs);
		gosals[n1-1][n2-1].num_probs = gosals[n2-1][n1-1].num_probs = num_probs;
		for(j=0;j<num_probs;j++)
		{
			float prob;
			int value;
			fscanf(fin,"%f %d",&prob,&value);
			gosals[n2-1][n1-1].poisons[j].prob = gosals[n1-1][n2-1].poisons[j].prob = prob;
			gosals[n2-1][n1-1].poisons[j].value = gosals[n1-1][n2-1].poisons[j].value = value;
		}
		qsort(&gosals[n1-1][n2-1].poisons[0],num_probs,sizeof(Poison),compare);
	}
	for(i=0;i<num_states;i++)
	{
		fscanf(fin,"%d",&policy[i]);
		policy[i] = policy[i] - 1;
	}
	policy[End] = -1;
}
