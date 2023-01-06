
#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include <stdbool.h>
#include <stdlib.h>




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
void swapp (struct process * , struct process *);
struct process *copy(struct process *);
void display(struct process *header);
void schedulingMethod (int );
void fcfsScheduling();
void sjfScheduling ();
void priorityScheduling();
void roundrobinScheduling();
void showOutput(struct process*);

//__________________________Variables____________________________

char* input  ;
char* output  ;
int counter = 0;
double average =0 ;
int quantum ; 
bool preemptive = 0 ; 
struct process *header =NULL;
bool fcfs;
bool sjf  ;
bool priority;
bool roundrobin;



//__________________________Main_Function_________________________


int main (int args , char* argv[]){

     
     int opt;
     
     while((opt = getopt(args , argv , "f:o:")) != -1 )
     {

        switch (opt){
            case 'f' : input= optarg ; break;
            case 'o' : output= optarg  ;break ;
            default : printf("\nplease enter a valid form of input! ") ;break ; 
        }

     }

       
  
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
			       fscanf(file, "%d:%d:%d\n", &burst, &arrival, &priority);
                   header = insertBack(header , arrival , burst , priority);
			       counter++;
		        }
	       }

         fclose(file);

        
         
		printf("1)Scheduling Method(none) \n2)Preemptive Mode(OFF/ON)\n3)showResult\n4)End Program \n type:");
		int choice ;
		scanf("%1d", &choice);

        switch (choice)
		{
		case 1 :
		      int mode; 
			  printf("\n1)none \n2)first come first serve \n3)shortest job first\n4)priority scheduling\n5)Round Robin\ntype:");
			  scanf("%1d" , &mode);
			  schedulingMethod (mode);
			break;

		case 2 :
			  preemptive = true;
			break;

		case 3 :
		display(header);
			break;

		case 4 :
			 showOutput(header);
			break;

		default:
		  printf("wrong choice!!!!");
			break;
		}		 

    

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


struct process *insertBack(struct process *h, int burst , int arrival, int priority)
{
	struct process *temp = createProcess( burst, arrival, priority);
	struct process *ht;

	
	if (h == NULL)
	{
		h = temp;
		return h;
	}

	ht = h;

	while (ht->next != NULL) 
		ht = ht->next;

	ht->next = temp;
	
	return h;
}

//_____________________________deleteFront_______________________________


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

//____________________________deleteAfter_______________________________

void deleteAfter(struct process *afternode){

	struct process *t ;

	if(afternode->next == NULL || afternode == NULL)
	  return;

	t=afternode->next;
	afternode->next=t->next;
	free(t);
}

//___________________________Display____________________________________

void display(struct process *h)
{
	struct process *temp = h ;

while (temp != NULL)
{
	printf("%d  %d  %d \n" ,temp->at , temp->bt, temp->pr );
	temp=temp->next;
}



}

//_______________________Scheduling Method______________________________

void schedulingMethod (int m){


switch (m)
{
    case 1:  
	break;

	case 2 :  
	   fcfsScheduling();
	break;

	case 3 :
	   sjfScheduling();  
	break;

	case 4 :  
	   priorityScheduling();
	break;

	case 5 :  
	   roundrobinScheduling();
	break;


    default:
	printf("ops !!! wrong choice ! ");
	break;
}

}



//___________________________fcfs_______________________________________

void fcfsScheduling(){

int timer =0;
double avg , sum ; 

struct process *f = copy (header);
struct process *t1 =f;
struct process *t2 =f;

while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  
	 f=f->next; 
}
//finding the avg waiting time 
while (t1 != NULL)
{


	timer += t1->bt ;
    t1->tt = timer ;
	

	t1->wt = (timer - t1->bt) - t1->at  ;
	sum += t1->wt ;
	t1=t1->next ;
}



avg = sum / counter ;
printf("average of fcfs : %f" , avg);


//sendout(t2 , avg );








}

//___________________________sjf________________________________

void sjfScheduling (){

if (preemptive==0){


int timer = 0;

double avg , sum ; 

struct process *f = copy (header);
struct process *t1 =f;
struct process *t2 =f;

while ( f->next != NULL)
{
	if (f->bt > f->next->bt){
     swapp (f , f->next);

	}
	  

	 f=f->next; 
}


while (t1 != NULL){

   if (t1->at <= timer ){
	 timer += t1->bt ;
	 t1->tt = timer ;
	 t1 = t1->next;
   }else {
	swapp ( t1 , t1->next);
   if (t1->at <= timer ){
      timer += t1->bt ;
	  t1->tt = timer ;
	  t1 = t1->next;
   }else {
	swapp ( t1 , t1->next);
   if (t1->at <= timer ){
      timer += t1->bt ;
	  t1->tt = timer ;
	  t1 = t1->next;
   }

}

}
}

timer = 0;
while (t2 != NULL)
{


	timer += t2->bt ;
    t2->tt = timer ;
	

	t2->wt = (timer - t2->bt) - t2->at  ;
	sum += t2->wt ;
	t2=t2->next ;
}

avg = sum / counter ;

printf("average of sjf : %f" , avg);






}else{





}

}

//_________________________priority______________________________

void priorityScheduling(){

if (preemptive==0){
  


  

}else{





}


}

//________________________round robin_____________________________

void roundrobinScheduling(){

printf("enter the time quamtum ");
scanf("%1d" , &quantum);



}


//________________________show output____________________________________

void showOutput(struct process *h){




    FILE *f = fopen(output, "w");
    fprintf(f , "working ! ");
	fclose(f);


    exit(0);

}

//____________________________swap______________________________

void swapp (struct process *h, struct process *afternode){

int a = h->at ;
int b = h->bt ;
int c = h->pr ;

h->at = afternode->at ;
h->bt = afternode->bt;
h->pr= afternode->pr;

afternode->at = a ;
afternode->bt = b;
afternode->pr = c; 

}

//___________________________Copy______________________________________

struct process* copy(struct process *h){


  if (h==NULL)
    return h ;
  else {

   struct process *t= (struct process *)malloc(sizeof(struct process));
   t->at = h->at ;
   t->bt = h->bt ;
   t->pr = h->pr ;


   t->next = copy(h->next);
   return t ;
  }

}

