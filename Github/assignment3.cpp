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
	char token [100]=" ";			//to store messages
	char temp [100]=" ";			//temprary array
	int initiator = 0;			//to store initiator
	int world_size = 0;			//to store the total number of processess (communicator size)
	int count = 0;				//number of elements in token array
	int dummy = 0;				//dummy variable
	int wantToLead = 0;			//to store the choice of a process to lead (random number)
	int electedLeader = -1;			//to store the rank of elected leader

	MPI_Init(&argc, &argv);

	count = sizeof(token);

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);		//getting size of communicator
	//cout<<"WORLD SIZE IS "<<world_size<<endl;

	//srand(time(NULL));
	initiator = rand() % world_size;			//random initiator
	
	//cout<<"INITIATOR IS "<<initiator<<endl;
	
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);			//getting rank of a process
	

	if(initiator == rank)
	{
		strcpy(temp, " ");
		sprintf(temp,"%d",rank);
		strcat(token, temp);
		strcat(token, " ");				//concatinating rank of a process to token array
		
		dummy = (rank+1) % world_size;
 		MPI_Send(token, count, MPI_CHAR, dummy, 123, MPI_COMM_WORLD);		//sending token
		if (rank == 0)								//check if rank of process is zero
			dummy = world_size - 1;
		else
			dummy = (rank-1) % world_size;
		MPI_Recv(token, count, MPI_CHAR, dummy, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		//receiving token
		cout<<"I am process "<< rank <<" and i received the following token from process "<<dummy<<endl;
		cout<<token<<endl;

		
		//Getting the leader
		char * pars = strtok(token, " ");
		
		while (pars)
		{
			if (atoi(pars) > electedLeader)
			{
				electedLeader = atoi(pars);
			}
			pars = strtok(NULL, " ");
		}
		cout<<"ELECTED LEADER IS "<<electedLeader<<endl;
	}
	else 
	{
		if (rank == 0)							//check if rank of process is zero
			dummy = world_size - 1;
		else
			dummy = (rank-1) % world_size;
		MPI_Recv(token, count, MPI_CHAR, dummy, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//dummy = (rank-1) % world_size;
		cout<<"I am process "<< rank <<" and i received the following  token from process "<<dummy<<endl;
		cout<<token<<endl;
		srand(time(NULL));
		wantToLead = rand () % 2;
		if (wantToLead == 1)				//generating random number if its 1 write to token array rank of process
		{
			strcpy(temp, " ");
			sprintf(temp,"%d",rank);
			strcat(token, temp);
			strcat(token, " ");
		}
		else
		{
			strcpy(temp, " ");
		}
		dummy = (rank+1) % world_size;
		MPI_Send(token, count, MPI_CHAR, dummy, 123, MPI_COMM_WORLD);
	}

	
	MPI_Bcast(&electedLeader, 1, MPI_INT, initiator, MPI_COMM_WORLD);	//After selecting leader initiator broadcast rank of leader 
	cout<<"process : " <<rank<<" message from initiator"<<electedLeader<<endl;
	strcpy(token, "Thankyou ");
	MPI_Bcast(token, 11, MPI_CHAR, electedLeader, MPI_COMM_WORLD);		//Elected leader broadcast thankyou message to all processess
	cout<<"process : "<<rank<<" message from elected leader"<<token<<endl;

	

	MPI_Finalize();
	return 0;
}	
