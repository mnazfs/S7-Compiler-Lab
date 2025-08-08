#include<stdio.h>
#include<string.h>

int n, ind = 0, top = -1, accept = 1;
char terminals[10], input[25], stack[10];
char opTable[10][10] = {
	{'>', '<', '<', '>', '<', '>'},
	{'>', '>', '<', '>', '<', '>'},
	{'<', '<', '<', '=', '<', '>'},
	{'>', '>', '-', '>', '<', '>'},
	{'>', '>', '>', '>', '-', '>'},
	{'<', '<', '<', '<', '<', '-'},
};

int search(char ch)
{
	int p;
	for(int i = 0; i < n; ++i)
		if(ch == terminals[i])
			p = i;
	return p;
}

void main()
{
	printf("Enter number of terminals: ");
	scanf("%d", &n);
	printf("Enter the terminals: ");
	scanf("%s", terminals);
	/*printf("Enter the OP Table\n");
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			printf("%c - %c: ", terminals[i], terminals[j]);
			scanf(" %c", &opTable[i][j]);
		}*/
	
	while(1) {
		printf("Enter input (including $ on both ends) or 'exit' to exit: ");
		scanf("%s", input);
		if(strcmp(input, "exit") == 0)
			break;
	
		stack[++top] = input[ind++];
		while(!(stack[top] == '$' && input[ind] == '$')) {
			printf("%c %c\n", stack[top], input[ind]);
			int x = search(stack[top]);
			int y = search(input[ind]);
			if(opTable[x][y] == '<' || opTable[x][y] == '=')
				stack[++top] = input[ind++];
			else if(opTable[x][y] == '>') {
				int a, b;
				do {
					a = search(stack[top--]);
					b = search(stack[top]);
				}while(!(opTable[a][b] == '<'));
			} else {
				accept = 0;
				break;
			}
		}	
		
		if(accept == 1)
			printf("\nInput accepted\n");
		else
			printf("\nInput rejected\n");
	}
}
