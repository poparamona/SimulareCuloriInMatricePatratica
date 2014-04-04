#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 32000


int distanta(int i1,int i2,int j1,int j2)
{
	int d = i1 - i2, d2 = j1 - j2;
	
	if(abs(d) >= abs(d2))
	{
		return abs(d);
	}
	
	return abs(d2);
}

void print(int N,int *matrix)
{
	
	printf("\n");
	int i,j;
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			printf("%d ", matrix[i*N+j]);
		}
		
		printf("\t\t");
		for(j=0; j<N; j++)
		{
			printf("%d ", matrix[N*N+i*N+j]);
		}
		printf("\n");
	}
}


int main(int argc, const char* argv[]){

	char *fisin, *fisout;
	int nr_saptamani, N, Nc, i, j, k, i2, j2;
	FILE * fin;
	FILE * fout;
	
	nr_saptamani = atoi(argv[1]);
	fisin = (char *)malloc(20);
	fisout = (char *)malloc(20);
	
	strcpy(fisin, argv[2]);
	strcpy(fisout,argv[3]);
	
	fin = fopen(fisin, "r");
	fout = fopen(fisout, "w");
	
	if(!fin)
	{
		perror("Eroare1");
		return -1;
	}
	
	if(!fout)
	{
		perror("Eroare2");
		return -2;
	}
	
	fscanf(fin,"%d",&N);
	fscanf(fin,"%d",&Nc);
	
	int matrix[2][N][N];
	int mat_act=0;
	int mat_temp=1;
	
	int nr_culori[Nc];
	int dist_min[Nc];
	
	int flag=0, x=0, y;
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			fscanf(fin, "%d ", &matrix[mat_act][i][j]);
			matrix[mat_temp][i][j] = 0;
		}
	}
	
	
	k=0;
	int i3;
	while(k < nr_saptamani+1)
	{
		for(i=0; i<Nc; i++)
		{
			nr_culori[i]=0;
		}
		
		for(i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
			{		
				for(i3=0; i3<Nc; i3++)
				{
					dist_min[i3]=MAX;
				}		
				nr_culori[matrix[mat_act][i][j]]++;
				for(i2=0; i2<N; i2++)
				{
					for(j2=0; j2<N; j2++)
					{
						if(i==i2 && j==j2)
						{
						}
						else
						{
						if(distanta(i,i2,j,j2)<dist_min[matrix[mat_act][i2][j2]])
							{
								dist_min[matrix[mat_act][i2][j2]]=distanta(i,i2,j,j2);
							}
						}
					}
				}
				int ind,max=0;
				for(i3=0; i3<Nc; i3++)
				{
					if(dist_min[i3]>max && dist_min[i3]!=32000)
					{
						max=dist_min[i3];
						ind = i3;
					}
				}
				matrix[mat_temp][i][j] = ind;
			}
		}
		
		if(k!=0)
		{
			for(i=0; i<Nc; i++)
			{
				fprintf(fout,"%d ", nr_culori[i]);
			}
			fprintf(fout,"\n");
		}
		
		mat_temp = (k)%2;
		mat_act = (k+1)%2;
		k++;
	}
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			fprintf(fout,"%d ", matrix[mat_temp][i][j]);
		}
		fprintf(fout, "\n");
	}
	
	free(fisin);
	fisin = NULL;
	free(fisout);
	fisout = NULL;
	
	fclose(fin);
	fclose(fout);
	return 0;
}
