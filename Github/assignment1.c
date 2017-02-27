#include <mpi.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char ** argv)
{
	int rank = 0;
	char data [] = "Hello ";
	int count = 0;
	count = strlen(token);

	cout<<"Count is "<<count<<endl;
	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		MPI_Send(data, count, MPI_CHAR, 1, 999, MPI_COMM_WORLD);
		MPI_Recv(data, count, MPI_CHAR, 2, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout<<"I am process 0 and i received the following data from process 2 " <<endl<<data<<endl;
	}
	else if (rank == 1)
	{
		MPI_Recv(data, count, MPI_CHAR, 0, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout<<"I am process 1 and i received the following data from process 0 " <<endl<<data<<endl;
		strcpy(data, "1");
		MPI_Send(data, count, MPI_CHAR, 2, 999, MPI_COMM_WORLD);
	}
	else if (rank == 2)
	{
		MPI_Recv(data, count, MPI_CHAR, 1, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout<<"I am process 2 and i received the following data from process 1 " <<endl<<data<<endl;
		strcpy(data, "2");
		MPI_Send(data, count, MPI_CHAR, 0, 999, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}	
