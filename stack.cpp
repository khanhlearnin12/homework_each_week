#include<stdio.h>
#include<stdlib.h>


#define MAX 100

struct Mystack{
	int top;
	char a[MAX];
	
	bool IsEmpty();
	bool IsFull();
	void Push(char);
	char Pop();
	
	Mystack();
};

bool Quote (const char*);

int main(){
	FILE *fptr;
	char str[100];
	
	Mystack s;
	s.Push(']');
	s.Push(')');
	s.Push('(');
	printf("%c",s.Pop());
	printf("%c",s.Pop());
	printf("%c\n",s.Pop());
	

	fptr = fopen("A1(1).txt","r"); 
	while (!feof(fptr)) {
		fscanf(fptr,"%s\n",str);
		printf("s\n",str);
		if(Quote(str))
			printf("Correct\n ");
		else
			printf("Error\n ");
		system ("pause");
	}
	fclose(fptr);
	return 0;
}


//================================
Mystack::Mystack(){
	top = -1;   
	
}
//================================
bool Mystack::IsFull(){
	if(top >= MAX-1)
		return true;
	else 
		return false;
}
//================================
bool Mystack::IsEmpty(){
	if(top < 0)
		return true;
	else 
		return false;
}
//================================
void Mystack::Push(char p){
	if(IsFull()){
		printf("the stack is full");
		exit(1);
	}
	top++;
	a[top] = p; 
}
//================================
char Mystack::Pop(){
	char p;
	if(IsEmpty()){
		printf("the stack is empty");
		exit(1);
	}
	p = a[top];
	top--;
	return p;
}
bool Quote(const char* str){
	Mystack s1;
	int i= 0;
	char ch;
	while (str[i] != '\0'){
		if(str[i]=='('||str[i]=='['||str[i]=='{'){
			s1.Push(str[i]);
		}
		else
		{
			if(!s1.IsEmpty())
			{
				ch = s1.Pop();
				if(str[i]==')'&&ch!='(')
					return false;
				if(str[i]==']'&&ch!='[')
					return false;
				if(str[i]=='}'&&ch!='{')
					return false;
			}
			else
				return false;
		}
		i++;
	}
	if(!s1.IsEmpty())
		return false;
	return true;
}
