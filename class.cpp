#include<stdio.h> 
#include<stdlib.h>

#define MAX_SIZE 12

struct node {
    int data;
    node* link;
};

struct equivalence{
    node* seq[MAX_SIZE];
    void eqRead(const char* ); //qɮŪơAåBxs? seq }C
    void add(int, int); //sW?YơC
    void ShowList( ); //??e}CY쵲CC
    void ShowClass(); //??eC
    equivalence()
    {
        for(int i=0;i<MAX_SIZE;i++)
        {
            seq[i] = NULL;
        }
    }
};

//======================================
int main()
{
	equivalence e;
	e.eqRead("input.txt");
	e.ShowList();
	printf("\nEquivalence Classes:\n");
	e.ShowClass();
	return 0;
}

//======================================
void equivalence::eqRead(const char *filename)
{
	int a,b;
	FILE *fptr=fopen(filename,"r");
	
	while(!feof(fptr))
	{
		fscanf(fptr,"%d %d",&a, &b);
		//printf("%d %d\n",a, b);
		add(a, b);		
	}
	
}
//======================================
void equivalence::add(int a, int b)
{
	node *ptr=NULL;
	ptr=(node*)malloc(sizeof(node));
	ptr->data=b;
	ptr->link=NULL;
	
	ptr->link=seq[a];
	seq[a]=ptr;

	ptr=(node*)malloc(sizeof(node));
	ptr->data=a;
	ptr->link=NULL;
	
	ptr->link=seq[b];
	seq[b]=ptr;	
}
//======================================
void equivalence::ShowList()
{
	node* ptr=NULL;
	for(int i=0;i<MAX_SIZE;i++)
	{
		printf("seq[%2d]->",i);
		ptr=seq[i];
		while(ptr!=NULL)
		{
			printf("%2d->",ptr->data);
			ptr=ptr->link;
		}
		printf("\b\b  \n");
	}
}
//======================================

void equivalence::ShowClass() {
    bool visited[MAX_SIZE] = {false};
    int classNum = 1;
    
    for(int i = 0; i < MAX_SIZE; i++) {
        if(!visited[i] && seq[i] != NULL) {
            printf("New Class: %d ", i);
            visited[i] = true;
            
            // Use a queue-like approach to find all connected nodes
            int queue[MAX_SIZE];
            int front = 0, rear = 0;
            queue[rear++] = i;
            
            while(front < rear) {
                int current = queue[front++];
                node* ptr = seq[current];
                
                while(ptr != NULL) {
                    if(!visited[ptr->data]) {
                        printf("%d ", ptr->data);
                        visited[ptr->data] = true;
                        queue[rear++] = ptr->data;
                    }
                    ptr = ptr->link;
                }
            }
            
            printf("\n");
            classNum++;
        }
    }
}


