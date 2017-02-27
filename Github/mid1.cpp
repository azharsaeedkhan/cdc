// 	author : Azhar Saeed Khan (13-0375)

#include <mpi.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char ** argv)
{
	int rank = 0;				//to store rank of a process
	int world_size = 0;			//to store the total number of processess (communicator size)
	int flag = 0;	

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);		//getting size of communicator
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);			//getting rank of a process
	

	if (rank == 0)
	{
		for (int i=0; i < world_size; i++)
			MPI_Send(&flag, 1, MPI_INT, i, 999, MPI_COMM_WORLD);
		cout<<" process : " <<rank<< " sent "<<endl;
	}
	if (flag == world_size)
		MPI_Recv(&flag, 1, MPI_INT, MPI_ANY_SOURCE, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
	cout<<" I am process : " <<rank<<endl;

	MPI_Finalize();
	return 0;
}	
