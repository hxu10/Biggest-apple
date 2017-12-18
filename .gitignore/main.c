#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define S 100
#define TIMES 1000000
#define MINTURN 100
#define MAXTURN 100
#define STEP 1
#define pi 3.141592659

static double applerange[S];

int ran(int seed)
{
    int  num;
    num=16807*(seed%127773)-2836*(seed/127773);
    if (num<0) num=num+2147483647;
    return num;
}

int measurepick(double pick)
{
    int rank,i;
	rank = 1;
	for(i=0;i<S;i++)
    {
	    if (applerange[i]> pick) rank++;
	}
    return rank;

}

double gauss(int i)
{
	double x,y,z;
    x = i*1.0/2147483647;
	i = ran(i);
	y = i*2.0 /2147483647*pi;

	z = sqrt(-2*log(x))*cos(y);
    
    return 1 + 0.1 * z;

}




int main()
{
    int i,j,t,choose;
	int turn,first,last;

	double size,expect,pick,avesize,maxsize;

	FILE *fp;
	fp = fopen("data.txt","w");

    printf("input seed\n");
	scanf("%d",&i);
    
	for (turn=MINTURN;turn<=MAXTURN;turn+=STEP)
	{
        first = 0;
		last = 0;
		avesize = 0;


		for(t=0;t<TIMES;t++)
		{
			expect=0;
			pick = 0;

			maxsize = 0;



		    for(j=0;j<S;j++)
			{
				i = ran(i);
         //		size = i*1.0/2147483647;
				size = gauss(i);
				applerange[j] = size;
                if(size>maxsize) maxsize = size;


			    if(j<turn)
				{
				   if(size>expect) expect=size;
				}
                else if(j>=turn && j<S-1)
				{
					if(size>expect && pick ==0 ) {pick = size;choose=j+1;}
				}
				else if(j==S-1)
				{
					if(pick == 0) {pick = size; choose = j+1;}
				}


			
			
			}
            
		//	rank = measurepick(pick);
     //   	printf("pick  %lf, expect %lf, max %lf\n",pick,expect,maxsize);
	//		cumrank += rank;

			avesize += pick;

			if( fabs(pick - maxsize)<0.000001 ) {first++;;}
			if(choose== S) last++;
		
		    
		
		
		
		
		}
		avesize = avesize * 1.0 / TIMES ;

		printf("turn %d, ave %lf, first times %d  last times %d\n", turn, avesize, first,last);
		fprintf(fp,"%d\t %lf\t %d\t %d\n", turn, avesize, first,last);
	
	
	
	}


    return 0;

















    return 0;
}
