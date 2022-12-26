
#include<stdio.h>
#include<getopt.h>
#include<string.h>




struct process{

int at ; //arrival time
int bt;  // burst time
int pr;  //priority
int tt ; //turnaround time
int wt ; //waiting time


struct process* next ;

};
//__________________________Functions____________________________



struct process *createProcess( int, int, int);
struct process *insertBack(struct process *, int, int, int);
struct process *deleteFront(struct process *);
void display(struct process *header);

//__________________________Variables____________________________

char* input , output ;
double average =0 ;



//__________________________Main_Function_________________________


int main (int args , char* argv[]){

     
     int opt;
	 struct process *header ;
     int counter = 0;

     while((opt = getopt(args , argv , "f:o:")) != -1 )
     {

        switch (opt){
            case 'f' : input= optarg ; break;
            case 'o' : output= optarg  ;break ;
            default : printf("\nplease enter a valid form of input! ") ;break ; 
        }

     }

       //now we need to open the file
  
         FILE *file = fopen(input,"r");
  
	      if (feof(file))
	       {
		       printf("\nyour input file is empty!!!");
		       exit(1);
	       }
	       else
	       {
		       while (!feof(file)) 
		        {
			       int arrival, burst, priority;
			       fscanf(input, "%d:%d:%d\n", &arrival, &burst, &priority);
                   insertBack(header , arrival , burst , priority);
			       counter++;
		        }
	       }

         fclose(file);

    

}


//_____________________________________________________________________



//________________________________create________________________________

struct process *createProcess( int arrival, int burst,  int priority)
{
	struct process  *temp;

	temp = (struct process *)malloc(sizeof(struct process));
	


	temp->at = arrival;
	temp->bt = burst;
	temp->pr = priority;
	temp->tt = 0;
	temp->wt = 0;
	
	

	return temp;
}

//_______________________________insert_________________________________


struct process *insertBack(struct process *header, int burst , int arrival, int priority)
{
	struct process *temp = createProcess( burst, arrival, priority);
	struct process *ht;

	
	if (header == NULL)
	{
		header = temp;
		return header;
	}

	ht = header;

	while (ht->next != NULL) 
		ht = ht->next;

	ht->next = temp;
	return header;
}

//______________________________delete_______________________________


struct process *deleteFront(struct process *header)
{
	struct process *temp;

	if (header == NULL)
	{
		return header;
	}

	temp = header;
	header = header->next;
	free(temp);
	return header;
}

//___________________________Display______________________________________

void display(struct process *header)
{
	struct process *temp = header;
	while (temp != NULL)
	{
		printf("details : %d %d %d %d \n" , temp->at , temp->bt , temp->pr , temp->tt);

	
		temp = temp->next;
	}

}