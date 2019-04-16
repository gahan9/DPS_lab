// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementation of 

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>


 
void arr_alloc(int** arr, int r,int c){*arr= malloc(r*c*sizeof(int));}

void arr_init(int* arr, int r, int c, int init){

   int i=0;
    for(i=0;i<r;++i){
        int j=0;
        for(j=0;j<c;++j){

            arr[i*c+j]=init;
        }
    }
}

void printMatrix(int* arr,int r,int c){
    int i = 0;
    for(i=0;i<r;++i){
        int j=0;
        for(j=0;j<c;++j){
            printf("%d, ",arr[i*c+j]);
        }
        printf("\n");
    }
}

void arr_dealloc(int** arr){free(*arr);}

void arr_input(int* arr, int r, int c){
	int i=0;
	for (i = 0; i < r; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			scanf("%d",&arr[i*c+j]);
		}
	}
}

void arr_file_input(FILE *file,int* arr, int r, int c){
	int i=0;
	for (i = 0; i < r; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			fscanf(file,"%d",&arr[i*c+j]);
		}
	}
}

void arr_alloc_input(int** arr_addres, int r,int c){
	 	//allocation
	    arr_alloc(arr_addres,r,c);
	    //input
	    arr_input(*arr_addres,r,c);

}

void arr_alloc_file_input(FILE *file,int** arr_addres, int r,int c){
	 	//allocation
	    arr_alloc(arr_addres,r,c);
	    //input
	    arr_file_input(file,*arr_addres,r,c);

}

void arr_alloc_intit(int** arr_addres, int r, int c, int init){
	 	//allocation
	    arr_alloc(arr_addres,r,c);
	    //initialize
	    arr_init(*arr_addres,r,c,init);
}

int * matrix_multiblication(int* A, int* B, int A_r, int A_c, int B_r, int B_c){
	int *C;
	int C_r= A_r,
		C_c= B_c;

	//allocat C
	arr_alloc(&C,C_r,C_c);
	//multiblaication operation
	int i=0;
	for (i = 0; i < C_r; ++i) {
		int j=0;
		for (j = 0; j < C_c; ++j) {
			int k=0,sum=0;
			for (k = 0; k < A_c; ++k) {
				int A_cell =A[ i * A_c + k ],
					B_cell =B[ k * B_r + j ];
				sum+=( A_cell * B_cell );
			}
			//store result
			C[i*C_c+j]=sum;
		}
	}
	//printMatrix(C,C_r,C_c);
	return C;
}               


/**
 * if A[n*n],B[n*1],C[n*1] is Matrices and AC=B then C=A^-1*B
 * get input one Matrix of (A^-1*B) of size [n*(n+1)]
 * scatter the Matrix between process
 * collect B in each Process
 * GatherAll B in each Process
 * do Multiblication
 **/
int main(int argc, char  *argv[])
{
 	int my_rank;
 	int size ;
 	int tag;
 	int source;
 	int dest ;
 	MPI_Status status;


 	MPI_Init(&argc,&argv);
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
 	MPI_Comm_rank(MPI_COMM_WORLD , &my_rank);
 	 
 	int input = 0 ;
 	int A_r = 0, A_c = 0,
		B_r = 0, B_c = 0;
	int *A,*B,*C;
 	 
	int N ;
 	
 	if(my_rank==0){
 		printf("Welcome to vector Matrix multiplication program! Allgather\n");
		FILE *file= fopen("test.txt","r+"); //readFromFile
		if(file!=NULL){
			
			fscanf(file,"%d",&N);
			 A_r = N ;A_c = N ;
			 B_r = N ;B_c = 1 ;
			// check dimnsions of matrix is divisable by # of process
			if (A_c%size != 0)
		 	{
		 		printf("# of MPI tasks Must Divisble by Matrix dimentions. Quitting...\n");
				MPI_Abort(MPI_COMM_WORLD, 0);
				exit(1);
		 	}
		 	// check that  A  [n*n], B  [n*1]
			if(A_c==B_r && A_c==A_r && B_c == 1){
				arr_alloc_file_input(file,&A,N,(N+1)); 
				arr_alloc(&C,A_r,B_c);			 
			}else{
				printf("not Valid Matrix dimentions");
				MPI_Abort(MPI_COMM_WORLD, 0);
				exit(1);
			}
			fclose(file);
		}else{printf("unable to open file");}
 		printf("------ A ---------\n");
		printMatrix(A , N ,N+1);
		 
 		//scanf("%d",&N);
 
 	}
 	 
 	/* Bcast dimentions*/
 	MPI_Bcast (&A_c, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	MPI_Bcast (&A_r, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	MPI_Bcast (&B_c, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	MPI_Bcast (&B_r, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	// allocations
 	if (my_rank!=0){arr_alloc(&A,A_r,(A_r+1));}
 	// all process allocate B to make GatherAll on it
 	arr_alloc(&B,B_r,B_c);

 	// n is dimention 
 	int n = A_r ;
   
   /**
 	* Scatter A smallA and collect smallB from smallA
 	* 
 	* smallA.size = nRows*n
 	* nRows = n/size ;
 	* 
 	* smallB.size = n/size ;
 	**/

 	//allocate
 	int *smallA , *smallB;
 	int nRows = n/size ;
 	int smallA_size = nRows*(n+1);
 	int smallB_size = n/size ;

 	arr_alloc(&smallA, smallA_size, 1);
 	arr_alloc(&smallB, smallB_size, 1);
 	
 	//Scatter A
 	MPI_Scatter(A,smallA_size,MPI_INT,smallA,smallA_size,MPI_INT,0,MPI_COMM_WORLD);
 	
 	// collect smallB in each process
 	// index : smallB index in smallA
 	int j , index=n ;
 	for ( j = 0; j <= nRows; ++j)
 	{
 		smallB[j] = smallA[index];
 		index+= (n+1) ; 
 	}

 	// printf("\n---------P%d-----smallA-------\n",my_rank);
 	// printMatrix(smallA, 1, smallA_size);


 	// printf("\n---------P%d-----smallB-------\n",my_rank);
 	// printMatrix(smallB, 1, smallB_size);

   /**
   	* make each process AllGather it smallB then all process have the B
   	* prebare matrix B to AllGather the smallB
   	* 
   	* prebare matrix smallC to store the result
   	* smallC.size  = smallB.size = n/size ;  
   	*
   	**/

   	// allocation
	int *smallC ,smallC_size=n/size;
	
	
	arr_alloc(&smallC, smallC_size, 1);
	arr_init(smallC, smallC_size, 1, 0);


	MPI_Allgather( smallB , smallB_size,MPI_INT,B,smallB_size,MPI_INT,MPI_COMM_WORLD);
	

	if (my_rank==0)		
	{
		 printf("\n---------B after Allgather-------\n",my_rank);
 		 printMatrix(B, 1, n);

	}

 
  
 
	j = 0 ; 
	for ( j ; j < nRows; ++j) // for each row in smallA
	{
		int sum = 0 ;
		int j2 = 0 ; 
		for ( j2 = 0; j2 < n; ++j2)
		{
			sum+=(smallA[j2+(j*(n+1))] * B[j2]);
			/*
				smalA[j2+(j*(n+1))]
				  j2 -> go in cloumn
				  (j*(n+1)) -> go in row and skip merged B
			*/
			//printf("P%d: [%d - %d]\n",my_rank,smallA[j2+(j*(n+1))], B[j2] );
			
			
		}
		smallC[j] = sum ;
 	}
 

	// collect smallC
	MPI_Gather(smallC , smallC_size , MPI_INT , C , smallC_size , MPI_INT , 0 , MPI_COMM_WORLD);

	if (my_rank==0)
 	{
 		printf("------ Final C -------\n");
		printMatrix( C, A_r,B_c); 
 	} 


	MPI_Finalize();
 	return 0; 	
}