#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct polynomial{
	int coef;                       //多項式的係數
	int expon;                      //多項式的指數
};

struct MyPoly{
	polynomial terms[MAX];          //多項式陣列
	int size;                       //多項式大小
	MyPoly();                       //建構子 初始化 size = 0
	MyPoly(const char*);            //建構子 讀入檔案
	
	void ShowPoly();                //印出多項式內容
	MyPoly Add(MyPoly);             //多項式相加
	void SingleMult(int);           //將多項式乘上一係數
	int Lead_Exp();                 //回傳多項式中最大指數的次方
	void Attach(int, int);          //新增 1 個項式到多項式中
	void Remove(int);               //刪除多項式中的某一指數
	void ReadFile(const char* filename);

    // 作業2
	// MyPoly Mult(MyPoly);         //多項式相乘
};

int main(){
	MyPoly A;
	//printf("%d\n",A.size); 
	MyPoly B;
	MyPoly C;

	B.ReadFile("B1.txt");
	C.ReadFile("B2.txt");
	//MyPoly C; 
	B.ShowPoly();
	A.Attach(5, 10);
	A.ShowPoly();
	system("pause");
	A.Attach(10, 8);
	A.ShowPoly();
	system("pause");
	A.Attach(2, 2);
	A.ShowPoly();
	system("pause");
	A.Attach(8, 12);
	A.ShowPoly();
	
	B.ShowPoly();
	C.ShowPoly();
	
	MyPoly D;
	D=B.Add(C);
	D.ShowPoly(); 

	return 0;
} 

MyPoly::MyPoly()
{
	size=0;
}

MyPoly::MyPoly(const char* filename)
{
	FILE *fptr;
	fptr=fopen(filename,"r");
	
	while(!feof(fptr))
	{
		fscanf(fptr, "%d %d", &terms[size].coef, &terms[size].expon);
		size++;
	}
	fclose(fptr);	
}

void MyPoly::ReadFile(const char* filename)
{
	FILE *fptr;
	fptr=fopen(filename,"r");
	
	while(!feof(fptr))
	{
		fscanf(fptr, "%d %d", &terms[size].coef, &terms[size].expon);
		size++;
	}
	fclose(fptr);	
}

void MyPoly::ShowPoly()
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%dX^%d+",terms[i].coef, terms[i].expon);
	}
	//printf("%dX^%d",terms[i].coef, terms[i].expon);
	printf("\b \n");
}

void MyPoly::SingleMult(int num)
{
	for(int i=0;i<size;i++)
	{
		terms[i].coef=terms[i].coef * num;
	}
	
}
MyPoly MyPoly::Add(MyPoly B)
{
	MyPoly D;
	int index1=0, index2=0;
	while(index1<size && index2< B.size)
	{
		if(terms[index1].expon>B.terms[index2].expon) //case 1 >
		{
			D.Attach(terms[index1].coef, terms[index1].expon);
			index1++;	
		}	
		else if(terms[index1].expon<B.terms[index2].expon) //case 2 <
		{
			D.Attach(B.terms[index2].coef, B.terms[index2].expon);
			index2++;				
		}
		else
		{
			int sum=terms[index1].coef + B.terms[index2].coef; //case 3 if equal
			//printf("%d\n",sum);
			if(sum)
			{
				D.Attach(sum, terms[index1].expon);
				index1++;
				index2++;
			}
		}
	}
	//printf("%d %d\n",index1, index2);
	for(int i=index1;i < size;i++)
		D.Attach(terms[index1].coef, terms[index1].expon);
	for(int i=index2;i < B.size;i++)
		D.Attach(B.terms[index2].coef, B.terms[index2].expon);	
	return D;
	
	
}

int MyPoly::Lead_Exp()
{
	if(size==0)
		return -1;
	else
		return terms[0].expon;
}

void MyPoly::Attach(int coef, int expon)	
{
	int position=0;
	int i;
	
	if(size==0)
	{
		terms[0].coef=coef;
		terms[0].expon=expon;		
	}
	else
	{		
		for(i=0;i<size;i++)
		{
			if(terms[i].expon<expon)
			{
				position=i;
				break;
			}							
		}
		position=i;
		for(i=size;i>position;i--)
		{
			terms[i]=terms[i-1];
		}
		terms[position].coef=coef;
		terms[position].expon=expon;
	}
	size++;
	
}
void MyPoly::Remove(int num)
{
	
}

// MyPoly MyPoly::Mult(MyPoly B)
// {
    
// }

