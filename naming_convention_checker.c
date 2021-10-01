#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>

#define MAX_LABS 100

typedef struct student
{
	char roll_no[6];
	int marks;
	short int lab[MAX_LABS];
	short int flag;
}student;

void reset_flag_marks(student *s, int total_students)
{
	for(int i=0;i<total_students;i++)
	{
		s[i].flag=0;
		s[i].marks=0;
	}
}
void check_filename(char *filename, char *subject, char *branch, student *s)
{
	int r_no=-1, lab=0, len=0;
	char roll_no[10];
	if(!strncmp(filename,subject,strlen(subject)))
	{
		if(filename[strlen(subject)]=='_')
		{
			len+=strlen(subject)+1;
			if(!strncmp(filename+len,"Lab",3))
			{
				len+=strlen("Lab");
				if(filename[len]=='_')
				{
					len++;
					lab=atoi(filename+len);
					while(isdigit(filename[len]))
						len++;
					if(filename[len]=='_')
					{
						len++;
						if(!strncmp(filename+len,branch,strlen(branch)))
						{
							strcpy(roll_no,filename+len);
							len+=strlen(branch);
							r_no=atoi(filename+len);
							while(isdigit(filename[len]))
								len++;
							if(filename[len]=='\0')
							{
								
								if(s[r_no-1].flag!=1)
								{
								 	s[r_no-1].flag=1;
								 	s[r_no-1].lab[lab-1]=1;
								 	strcpy(s[r_no-1].roll_no,roll_no);
								 	s[r_no-1].marks++;
								}
								else
								{
								 	s[r_no-1].lab[lab-1]=1;
								 	s[r_no-1].marks++;
								}
								return;
							}
						}
					}
				}
			}
		}
	}
	return;
}

void create_file(FILE *fpr, student *s, int total_students, int total_labs)
{
	int i=0;
	for(i=0;i<total_students;i++)
	{
		if(s[i].flag==1)
			fprintf(fpr,"%s --> ",s[i].roll_no);
		else
			fprintf(fpr,"CE%03d --> ",i+1);
		if(s[i].marks>total_labs)
		{
			fprintf(fpr,"More number of files are submitted exceeding total number of labs\n");
			continue;
		}
		s[i].marks-=(total_labs-s[i].marks);
		fprintf(fpr,"%d\n",s[i].marks);
	}
}
int main()
{
	char path[50], subject[10], branch[4] ;
	printf("Enter path of the folder: ");
	scanf("%s", path);
	printf("Enter name of subject like OOP, DSA etc: ");
	scanf("%s",subject);
	printf("Enter name of branch like CE,EC,IT etc: "); //for checking genuine roll_no rest will be ignored in submission
	scanf("%s",branch);
	int total_students=0, total_labs=0;
	printf("Enter number of total labs: ");
	scanf("%d",&total_labs);
	printf("Enter number of total students: ");
	scanf("%d",&total_students);
	student s[total_students];
	reset_flag_marks(s,total_students);
	DIR *folder;
	struct dirent *en;
	short flag=0;
   	folder = opendir(path); //open all or present directory
   	if (folder) 
	{
		while ((en = readdir(folder)) != NULL)
	       	{
			char filename[20];
        		strcpy(filename,en->d_name);
			if( !strcmp(filename,".") || !strcmp(filename,".."))
				continue;
			
			check_filename(filename,subject,branch,s);
			flag=1;

		}
		closedir(folder);	
		if(!flag)
		{
			printf("Given folder is empty\nTry again with right folder\n");
			exit(0);
		}
		FILE *fp=NULL;
		char result_file[20];
		strcpy(result_file,subject);
		strcat(result_file,"_lab_score.txt");
		fp=fopen(result_file,"w");
		create_file(fp,s,total_students,total_labs);
		fclose(fp);
		printf("\nFILE NAME CONTAINING RESULT: %s\n",result_file);
		printf("\nFILE IS CREATED IN CURRENT DIRECTORY\n");
		printf("\n\n*******Exiting program******\n");
	}

		
}
