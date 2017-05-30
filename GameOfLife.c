#include <stdio.h>
#include "mpi.h"
#include <math.h>
#define INVALID -1


int evaluate(short** prevA2D, short** currentA2D, int n)
{
	int i,j,sum, alive = 0 ;
	for(i = 1; i<n + 1;i++)		
		for(j = 1; j< n + 1; j++)
		{
			sum = 0;
			int k,l;
			for(k = -1; k<2 ; k++)
				for(l = -1 ; l<2 ; l++)
					if(!(k == 0 && l == 0))
						sum += prevA2D [i+k][j+l];
					
			if((sum < 2 || sum > 3))
				currentA2D [i][j] = 0;
			else if(sum == 2)
				currentA2D [i][j] = prevA2D [i][j];
			else if(sum == 3)
				currentA2D [i][j] = 1;	
			
		if(currentA2D [i][j] == 1)
			alive ++;		
		}
			
		return alive;			
}


int main( argc, argv )
int  argc;
char **argv;
{
    int rank, size;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

   double t1,t2;

	if(rank == 0)
	{
		t1 = MPI_Wtime();
	}
    
	int mysize = (int) (500/sqrt(size));
	
	short ** mygameAreaA2D;
    mygameAreaA2D = (short **) calloc(mysize + 2 , sizeof(short*));
    short i,j;
    for(i = 0 ; i< mysize + 2; i++)
        mygameAreaA2D [i] = (short *) calloc(mysize + 2 , sizeof(short));
        
        
    short ** myprevgameAreaA2D;
    myprevgameAreaA2D = (short **) calloc(mysize + 2 , sizeof(short*));
    for(i = 0 ; i< mysize + 2; i++)
        myprevgameAreaA2D [i] = (short *) calloc(mysize + 2 , sizeof(short));
		
	if(rank == 0)
	{
	   //[[## root process mus set initial pattern, others have all zero in their parts
	   mygameAreaA2D[6][2] 	    = myprevgameAreaA2D[6][2]  	= 1;
       mygameAreaA2D[6][3]  	= myprevgameAreaA2D[6][3]  	= 1;
       mygameAreaA2D[7][2]  	= myprevgameAreaA2D[7][2]  	= 1;
       mygameAreaA2D[7][3]  	= myprevgameAreaA2D[7][3]  	= 1;
       mygameAreaA2D[6][12]  	= myprevgameAreaA2D[6][12] 	= 1;
       mygameAreaA2D[7][12]     = myprevgameAreaA2D[7][12] 	= 1;
       mygameAreaA2D[8][12]  	= myprevgameAreaA2D[8][12] 	= 1;
       mygameAreaA2D[5][13]     = myprevgameAreaA2D[5][13] 	= 1;
       mygameAreaA2D[9][13]  	= myprevgameAreaA2D[9][13] 	= 1;
       mygameAreaA2D[4][14]  	= myprevgameAreaA2D[4][14] 	= 1;
       mygameAreaA2D[10][14] 	= myprevgameAreaA2D[10][14]	= 1;
       mygameAreaA2D[4][15]  	= myprevgameAreaA2D[4][15] 	= 1;
       mygameAreaA2D[10][15] 	= myprevgameAreaA2D[10][15]	= 1;
       mygameAreaA2D[7][16]  	= myprevgameAreaA2D[7][16] 	= 1;
       mygameAreaA2D[5][17]  	= myprevgameAreaA2D[5][17] 	= 1;
       mygameAreaA2D[9][17]  	= myprevgameAreaA2D[9][17] 	= 1;
       mygameAreaA2D[6][18]  	= myprevgameAreaA2D[6][18] 	= 1;
       mygameAreaA2D[7][18]  	= myprevgameAreaA2D[7][18] 	= 1;
       mygameAreaA2D[8][18]  	= myprevgameAreaA2D[8][18] 	= 1;
       mygameAreaA2D[7][19]  	= myprevgameAreaA2D[7][19] 	= 1;
       mygameAreaA2D[4][22]  	= myprevgameAreaA2D[4][22] 	= 1;
       mygameAreaA2D[5][22]  	= myprevgameAreaA2D[5][22] 	= 1;
       mygameAreaA2D[6][22]  	= myprevgameAreaA2D[6][22] 	= 1;
       mygameAreaA2D[4][23]  	= myprevgameAreaA2D[4][23] 	= 1;
       mygameAreaA2D[5][23]  	= myprevgameAreaA2D[5][23] 	= 1;
       mygameAreaA2D[6][23]  	= myprevgameAreaA2D[6][23] 	= 1;
       mygameAreaA2D[3][24]  	= myprevgameAreaA2D[3][24] 	= 1;
       mygameAreaA2D[7][24]  	= myprevgameAreaA2D[7][24] 	= 1;
       mygameAreaA2D[2][26]  	= myprevgameAreaA2D[2][26] 	= 1;
       mygameAreaA2D[3][26]  	= myprevgameAreaA2D[3][26] 	= 1;
       mygameAreaA2D[7][26]  	= myprevgameAreaA2D[7][26] 	= 1;
       mygameAreaA2D[8][26]  	= myprevgameAreaA2D[8][26] 	= 1;
       mygameAreaA2D[4][36]  	= myprevgameAreaA2D[4][36] 	= 1;
       mygameAreaA2D[5][36]  	= myprevgameAreaA2D[5][36] 	= 1;
       mygameAreaA2D[4][37]  	= myprevgameAreaA2D[4][37] 	= 1;
       mygameAreaA2D[5][37]  	= myprevgameAreaA2D[5][37] 	= 1;
	}
	
	int up,down,right,left;

	int local_result, result ;
	
	int sqrtofproc = (int) sqrt(size);

	int rownum,colnum;

 	int count = 0;

	rownum  = rank/sqrtofproc;
	colnum = rank % sqrtofproc;

	//[[## check valid neighbours of processor
	// count holds the number of request that will be made(both for receive and send)
	if(rownum == 0)	up = INVALID;
	else 	{  up  =  rank - sqrtofproc; count +=2; }
	
	if(rownum == sqrtofproc -1)	down =  INVALID;
	else  {down  =  rank + sqrtofproc; count +=2; }

	if(colnum == 0)	left = INVALID;
	else { left =  rank -1; count +=2; }

	if(colnum == sqrtofproc -1 ) right = INVALID;
	else { right = rank + 1; count +=2; }

	// -------------  adjust num of step to run from here ----------
	int numrun = 1600;
	//--------------------------------------------------------------
	
	while(numrun)
	{
		int cnt = 0;

		MPI_Request*      req;
       	MPI_Status*       status;

		req    = (MPI_Request *) malloc(count *  sizeof(MPI_Request ));
		status = (MPI_Status  *) malloc(count * sizeof(MPI_Status ));

		if(up != INVALID)
		{
			//send to up
			MPI_Isend(&myprevgameAreaA2D[1][1],mysize,MPI_SHORT,up,0,MPI_COMM_WORLD,req + cnt); 
			
			cnt ++;

			//receive from up
			MPI_Irecv(&myprevgameAreaA2D[0][1],mysize,MPI_SHORT,up,0,MPI_COMM_WORLD,req + cnt);
	
			cnt ++;
		}
	
		if(down != INVALID)
		{
			//send to down
			MPI_Isend(&myprevgameAreaA2D[mysize][1],mysize,MPI_SHORT,down,0,MPI_COMM_WORLD,req + cnt); 

			cnt ++;

			//receive from down
			MPI_Irecv(&myprevgameAreaA2D[mysize + 1][1],mysize,MPI_SHORT,down,0,MPI_COMM_WORLD,req + cnt);

			cnt ++;
		}

		short * tempsendright = (short *) calloc(mysize , sizeof(short));
		short * temprecvright = (short *) calloc(mysize , sizeof(short));
		if(right  != INVALID)
		{     
			for(i =  1; i < mysize + 1; i++)
					tempsendright [i-1] = myprevgameAreaA2D [i][mysize];
			//send to right
			MPI_Isend(tempsendright,mysize,MPI_SHORT,right,0,MPI_COMM_WORLD,req + cnt); 

			cnt ++;

			//receive from right
			MPI_Irecv(temprecvright,mysize,MPI_SHORT,right,0,MPI_COMM_WORLD,req + cnt);

			cnt ++;
		}

		short * tempsendleft = (short *) calloc(mysize , sizeof(short));
		short * temprecvleft = (short *) calloc(mysize , sizeof(short));
		if(left != INVALID)
		{
			for(i = 1; i < mysize + 1; i++)
				tempsendleft [i-1] = myprevgameAreaA2D [i][1];
			//send to left
			MPI_Isend(tempsendleft,mysize,MPI_SHORT,left,0,MPI_COMM_WORLD,req + cnt); 

			cnt ++;

			//receive from left
			MPI_Irecv(temprecvleft,mysize,MPI_SHORT,left,0,MPI_COMM_WORLD,req + cnt);

			cnt ++;
		}


		 MPI_Waitall(cnt, req, status);
               
		if(right != INVALID)
		{       
			for(i = 1; i<mysize +1 ; i++)
				myprevgameAreaA2D[i][mysize + 1] = temprecvright [i-1];
     	}

		if(left != INVALID)
		{
			for(i = 1; i<mysize +1 ; i++)
				myprevgameAreaA2D [i][0] = temprecvleft [i-1];
		}

			
		local_result  =  evaluate(myprevgameAreaA2D,mygameAreaA2D,mysize);

		free(req);
		free(status);

		for(i = 1; i<mysize + 1;i++)		
			for(j = 1; j< mysize + 1; j++)
				myprevgameAreaA2D [i][j] = mygameAreaA2D[i][j];

		numrun --;
	}

		// Reduce the result at the root node and print result
		MPI_Reduce(&local_result, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		if(rank == 0)
	{
		t2 = MPI_Wtime();
		printf(" result = %d   TimeConsumed = %f\n", result, t2-t1);
	}
		
		
    MPI_Finalize();
    return 0;
}
