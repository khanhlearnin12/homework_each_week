#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define max 100

struct Mystack{
    int top;
    char a[max];

    bool IsEmpty();
    bool IsFull();
    void Push(char);
    char Pop();
    Mystack();
};

bool Quote (const char*);
Mystack transformstr(char* , char*);

int main(){
    FILE *fptr1 ;
    FILE *fptr2;

    char str1[max];
    // char str2[max];
    char transformed1[max];
    // char transformed2[max];

    fptr1 = fopen("input.txt","r");
    if(fptr1 == NULL)
    {
        printf("this file can't be opened");
        return 1;
    }

    fptr2 = fopen("output.txt","w");
    if (fptr2 == NULL)
    {
        printf("fptr2 file can't be open \n");
        fclose(fptr1);
        return 1;
    }

    while (fgets(str1,sizeof(str1),fptr1))
    {
        Mystack stack = transformstr (str1 , transformed1);

        while(!stack.IsEmpty()){
            fprintf(fptr2, "%c", stack.Pop());
        }
        // fprintf(fptr2, "%s", transformed1);
    }
    
    printf("the code is already print out in output.file");

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}

Mystack::Mystack(){
    top = -1;
}

bool Mystack::IsEmpty(){
    if (top < 0)
        return true;
    else 
        return false;
}

bool Mystack::IsFull(){
    if (top >= max-1)
        return true;
    else 
        return false;
}

void Mystack::Push(char ch){
    if (IsFull())
    {
        printf("stack is full");
        exit(1);
    }
    top++;
    a[top] = ch;
}

char Mystack::Pop(){
    char ch;
    if (IsEmpty())
    {
        printf("stack is empty");
        exit(1);
    }
    ch = a[top];
    top--;
    return ch;
}

Mystack transformstr(char* str, char* transformed) {
    Mystack stack;
    bool foundFirstE = false;
    
    int len = strlen(str) - 1;
    if (str[len] == '\n') {
        len--;
    }

    for (int i = len; i >= 0; i--) { 
        bool check = false;
        if (str[i] == 's'){
            for (int j = i - 1; j >= 0; j--) {
                if (str[j] == 's') {
                    break;
                }
                else if (str[j] == 'e') {
                    i = j;
                    check = true;
                    break;
                }
            }
        }

        if (check) continue;

        stack.Push(str[i]);
    }
    
    return stack;
}
