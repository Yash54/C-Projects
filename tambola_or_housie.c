#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3
#define COL 11
#define MAX 90
#define MIN 1

void fill(int arr[ROW][COL+1],int min, int max);
void print(int arr[ROW][COL+1]);
void checker(int ticket[ROW][COL+1], int num, int player_no, char name[][10]);

typedef struct list
{
	char result[30];
	int flag;
}list;

list s[8];

int result_flag=0;

int main()
{
	int player_cnt=0, i=0, flag=0, num=0;
	printf("Enter number of players:");
	scanf("%d", &player_cnt);
	char name[player_cnt][10];
	for(i=0;i<player_cnt;i++)
	{
		printf("Enter name of player%d: ",i+1);
		scanf("%*c%[^\n]", name[i]);

	}
	int ticket[player_cnt][ROW][COL+1]; //last column will contain number of crossed entries of each row


	srand(time(0));  //seeding the current time of the system when program is executed

	printf("Creating your tickets....\n");
	for(i=0;i<player_cnt;i++)
	{
		fill(ticket[i],MIN,MAX);
		printf("Displaying ticket of player%d: %s\n", i+1, name[i]);
		print(ticket[i]);
	}

	
	for(i=0;i<8;i++)
	{
		s[i].flag=0;
	}
	
	int result_count=0;
	int *counter=(int *)calloc(1000,sizeof(int));

	printf("Hold your ticket...\nStarting game and calling numbers...\n");
	while(result_count!=90)
	{	
		flag=0;
		num=(rand()%(MAX-MIN+1))+MIN;
		while(!flag)
		{
			if(counter[num]<1)
			{
				flag=1;
				counter[num]++;
				result_count++;
			}
			else
			{
				num=(rand()%(MAX-MIN+1))+MIN;
			}
		}
		printf("%d\n",num);
		for(i=0;i<player_cnt;i++)
		{
			checker(ticket[i],num,i,name);
		}

	}


	printf("\n\t\t####  WINNER LIST  ####\n\n");
	for(i=0;i<8;i++)
	{
		printf("\t\t%s\n",s[i].result);
	}
	printf("\n\t\t###### GAME OVER ######\n");
	return 0;
}

void print(int arr[ROW][COL+1])
{
	int i=0, j=0;
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void fill(int arr[ROW][COL+1],int min, int max)
{
	int i=0, j=0, seed=rand(), num=0, flag=0, count=0;
	int *counter=NULL;
	counter=(int *)calloc(1000,sizeof(int));
	srand(seed);
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			flag=0;
			num=(rand()%(max-min+1))+min;
			while(!flag)
			{
				if(counter[num]<=count)
				{
					flag=1;
					counter[num]++;
				}
				else
				{
					num=(rand()%(max-min+1))+min;
				}

			}
			arr[i][j]=num;
		}
		arr[i][j]=0;
	}
	free(counter);
}


void checker(int ticket[ROW][COL+1], int num, int player_no, char name[][10])
{
	int i=0, j=0, sum=0;
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(num==ticket[i][j])
			{
				ticket[i][j]=-1;
				ticket[i][COL]++;
				break;
			}
		}
	}
	sum=ticket[0][COL]+ticket[1][COL]+ticket[2][COL];

	//first five strike
	if(5==sum && s[0].flag!=1)
	{
		s[0].flag=1;
		sprintf(s[0].result, "First 5 strike: %s",name[player_no]);
		result_flag++;

	}


	//condition for corner and corner with star
	if(ticket[0][COL]>=2 && ticket[ROW-1][COL]>=2 && (s[1].flag!=1 || s[2].flag!=1) )
	{
		if(ticket[0][0]==-1 && ticket[0][COL-1]==-1 && ticket[ROW-1][0]==-1  && ticket[ROW-1][COL-1]==-1 && (s[1].flag!=1 || s[2].flag!=1) )
		{
			s[1].flag=1;
			sprintf(s[1].result, "CORNER: %s", name[player_no]);
			result_flag++;

			if(ticket[ROW/2][COL/2]==-1 && s[2].flag!=1)
			{
				s[2].flag=1;
				sprintf(s[2].result, "CORNER WITH STAR: %s", name[player_no]);
				result_flag++;
			}
		}
	}
	
	//first and second house
	if(sum==ROW*COL)
	{
		if(s[6].flag!=1)
		{
			s[6].flag=1;
			sprintf(s[6].result, "FIRST HOUSE: %s" ,name[player_no]);
			result_flag++;
		}
		else
		{
			sprintf(s[7].result, "SECOND HOUSE: %s" , name[player_no]);
			result_flag++;
		}
	}
	
	//for different rows
	if(ticket[0][COL]==COL && s[3].flag!=1)	
	{
		s[3].flag=1;
		sprintf(s[3].result, "FIRST ROW: %s", name[player_no]);
		result_flag++;
	}
	if(ticket[1][COL]==COL && s[4].flag!=1)	
	{
		s[4].flag=1;
		sprintf(s[4].result, "SECOND ROW: %s", name[player_no]);
		result_flag++;
	}
	if(ticket[2][COL]==COL && s[5].flag!=1)	
	{
		s[5].flag=1;
		sprintf(s[5].result, "THIRD ROW: %s", name[player_no]);
		result_flag++;
	}
}
