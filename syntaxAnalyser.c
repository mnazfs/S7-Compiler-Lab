#include<stdio.h>

int j = 0;
char input[25];

int E();
int E1();
int T();
int T1();
int F();

void main()
{
	printf("Enter input: ");
	scanf("%s", input);
	
	if(E() == 1 && input[j] == '\0')
		printf("\nInput is accepted\n");
	else
		printf("\nInput is rejected\n");
}

int E()
{
	printf("Expanding E -> TE1\n");
	if(T() == 1) {
		if(E1() == 1)
			return 1;
		else
			return 0;
	} else 
		return 0;
}

int E1()
{
	if(input[j] == '+') {
		printf("Expanding E1 -> +TE1\n");
		printf("Consuming +\n");
		j++;
		if(T() == 1) {
			if(E1() == 1)
				return 1;
			else
				return 0;
		} else
			return 0;
	} else {
		printf("Expanding E1 -> eps\n");
		return 1;
	}
}

int T()
{
	printf("Expanding T -> FT1\n");
	if(F() == 1) {
		if(T1() == 1)
			return 1;
		else
			return 0;
	} else
		return 0;
}

int T1()
{
	if(input[j] == '*') {
		printf("Expanding T1 -> *FT1\n");
		printf("Consuming *\n");
		j++;
		if(F() == 1) {
			if(T1() == 1)
				return 1;
			else
				return 0;
		} else
			return 0;
	} else {
		printf("Expanding T1 -> eps\n");
		return 1;
	}
}

int F()
{
	if(input[j] == '(') {
		printf("Expanding F -> (E)\n");
		printf("Consuming (\n");
		j++;
		if(E() == 1) {
			if(input[j] == ')') {
				printf("Consuming )\n");
				j++;
				return 1;
			} else
				return 0;
		} else
			return 0;
	} else if(input[j] == 'i') {
		printf("Expanding F -> i\n");
		printf("Consuming i\n");
		j++;
		return 1;
	} else
		return 0;
}

