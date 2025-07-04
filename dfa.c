#include<stdio.h>
#include<string.h>

int n, m, f, fStates[10], transition[10][10];
char symbols[10];

int simulateDFA(char input[])
{
	int currState = 0, k = 0;
	while(input[k] != '\0') {
		//Checking for invalid symbols
		int index = -1;
		for(int i = 0; i < m; ++i)
			if(input[k] == symbols[i]) {
				index = i;
				break;
			}
		if(index == -1) {
			printf("\nString contains invalid symbol(s)\n");
			return 0; //Exit if input is invalid
		}
		
		currState = transition[currState][index];
		k++;
	}
	
	//Checking if it reached final state
	int accept = 0;
	for(int i = 0; i < f; ++i)
		if(currState == fStates[i]) {
			accept = 1;
			break;
		}
		
	return accept;
}

void main()
{
	printf("Enter number of states: ");
	scanf("%d", &n);
	
	printf("\nEnter number of input symbols: ");
	scanf("%d", &m);
	printf("Enter input  alphabets: ");
	scanf("%s", symbols);
		
	printf("\nEnter number of final states: ");
	scanf("%d", &f);
	printf("Enter the final states: ");
	for(int i = 0; i < f; ++i)
		scanf("%d", &fStates[i]);
		
	printf("\nEnter transition details:\n");
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			printf("From q%d for %c : ", i, symbols[j]);
			scanf("%d", &transition[i][j]);
		}
	
	while(1) {
		char string[10];
		printf("\nEnter input string or 'exit' for exiting: ");
		scanf("%s", string);
		
		if((strcmp(string, "exit")) == 0)
			break;
			
		int accept = simulateDFA(string);
		
		if(accept)
			printf("\nString is accepted\n");
		else
			printf("\n String is rejected\n");
	}
}
