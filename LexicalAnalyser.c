#include<stdio.h>
#include<string.h>
#include<ctype.h>

void main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("Command line inputs not given\n");
		return;
	}
	
	char ch, ch1, lexeme[25];
	char keywords[17][10] = {"int", "float", "double", "char", "void", "main", "if", "else", "for", "while", "do", "printf", "scanf", "stdio.h", "string.h", "stdlib.h", "conio.h"};
	int line = 1, slno = 1;
	
	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
	
	printf("Sl No\tLexeme\tToken\t\tLine No\n-----------------------------------------------\n");
	
	while((ch = fgetc(fp1)) != EOF) {
		if(ch == ' '||ch == '\t');
		
		else if(ch == '\n')
			line++;	
			
		else if(ch == ';') {
			printf("%d\t%c\tSemi-colon\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '+'||ch == '-'||ch == '*'||ch == '/') {
			printf("%d\t%c\tArith_op\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '{'||ch == '['||ch == '(') {
			printf("%d\t%c\tOpen_bracket\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '}'||ch == ']'||ch == ')') {
			printf("%d\t%c\tClose_bracket\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '&'||ch == ':'||ch == ',') {
			printf("%d\t%c\tSpecial_char\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '=') {
			if((ch1 = fgetc(fp1)) == '=')
				printf("%d\t%c%c\tRelat_op\t\t%d\n", slno, ch, ch1, line);
			else {
				printf("%d\t%c\tAssign_op\t\t%d\n", slno, ch, line);
				ungetc(ch1, fp1);
			}
			slno++;
		}
		
		else if(ch == '<'||ch == '>'||ch == '!') {
			if((ch1 = fgetc(fp1)) == '=')
				printf("%d\t%c%c\tRelat_op\t\t%d\n", slno, ch, ch1, line);
			else {
				printf("%d\t%c\tRelat_op\t\t%d\n", slno, ch, line);
				ungetc(ch1, fp1);
			}
			slno++;
		}
		
		else if(isdigit(ch)) {
			int i = 0, flag = 0;
			lexeme[i++] = ch;
			ch1 = fgetc(fp1);
			
			while(isdigit(ch1)||ch == '.') {
				lexeme[i++] = ch1;
				if(ch1 == '.')
					flag = 1;
				ch1 = fgetc(fp1);
			}
			
			lexeme[i] == '\0';
			ungetc(ch1, fp1);
			
			if(flag)
				printf("%d\t%s\tFloat_point\t\t%d\n", slno, lexeme, line);
			else
				printf("%d\t%s\tNumber\t\t%d\n", slno, lexeme, line);
			slno++;
			memset(lexeme, '\0', sizeof(lexeme));
		}
		
		else if(isalpha(ch)) {
			int i = 0, flag = 0;
			lexeme[i++] = ch;
			ch1 = fgetc(fp1);
			
			while(isalpha(ch1)||ch == '.'||ch == '_'||isdigit(ch)) {
				lexeme[i++] = ch1;
				ch1 = fgetc(fp1);
			}
			
			lexeme[i] == '\0';
			ungetc(ch1, fp1);
			
			for(int j = 0; j < 17; j++)
				if(strcmp(keywords[j], lexeme) == 0) {
					flag = 1;
					break;
				}
				
			if(flag)
				printf("%d\t%s\tKeyword   \t\t%d\n", slno, lexeme, line);
			else
				printf("%d\t%s\tIdentifier\t\t%d\n", slno, lexeme, line);
			slno++;
			memset(lexeme, '\0', sizeof(lexeme));
		}
		
		else {
			printf("%d\t%c\tUnrecognized\t\t%d\n", slno, ch, line);
			slno++;
		}
	}
	
	fclose(fp1);
	fclose(fp2);
}
