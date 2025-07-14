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
	char keywords[18][10] = {"int", "float", "double", "char", "void", "main", "if", "else", "for", "while", "do", "printf", "scanf", "stdio.h", "string.h", "stdlib.h", "conio.h", "include"};
	int line = 1, slno = 1;
	
	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
	
	printf("Sl No\t\tLexeme\t\tToken\t\tLine No\n-----------------------------------------------\n");
	
	while((ch = fgetc(fp1)) != EOF) {
		if(ch == ' '||ch == '\t');
		
		else if(ch == '\n')
			line++;	
			
		else if(ch == ';') {
			printf("%d\t\t%c\t\tSemi-colon\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '+'||ch == '-'||ch == '*'||ch == '/') {
			printf("%d\t\t%c\t\tArith_op\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '{'||ch == '['||ch == '(') {
			printf("%d\t\t%c\t\tOpen_bracket\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '}'||ch == ']'||ch == ')') {
			printf("%d\t\t%c\t\tClose_bracket\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '&'||ch == ':'||ch == ','||ch == '#') {
			printf("%d\t\t%c\t\tSpecial_char\t\t%d\n", slno, ch, line);
			slno++;
		}
		
		else if(ch == '=') {
			if((ch1 = fgetc(fp1)) == '=')
				printf("%d\t\t%c%c\t\tRelat_op\t\t%d\n", slno, ch, ch1, line);
			else {
				printf("%d\t\t%c\t\tAssign_op\t\t%d\n", slno, ch, line);
				ungetc(ch1, fp1);
			}
			slno++;
		}
		
		else if(ch == '<'||ch == '>'||ch == '!') {
			if((ch1 = fgetc(fp1)) == '=')
				printf("%d\t\t%c%c\t\tRelat_op\t\t%d\n", slno, ch, ch1, line);
			else {
				printf("%d\t\t%c\t\tRelat_op\t\t%d\n", slno, ch, line);
				ungetc(ch1, fp1);
			}
			slno++;
		}
		
		else if(isdigit(ch)) {
			int i = 0, flag = 0;
			lexeme[i++] = ch;
			ch1 = fgetc(fp1);
			
			while(isdigit(ch1)||ch1 == '.') {
				lexeme[i++] = ch1;
				if(ch1 == '.')
					flag = 1;
				ch1 = fgetc(fp1);
			}
			
			lexeme[i] == '\0';
			ungetc(ch1, fp1);
			
			if(flag)
				printf("%d\t\t%s\t\tFloat_point\t\t%d\n", slno, lexeme, line);
			else
				printf("%d\t\t%s\t\tNumber\t\t%d\n", slno, lexeme, line);
			slno++;
			memset(lexeme, '\0', sizeof(lexeme));
		}
		
		else if(isalpha(ch)) {
			int i = 0, flag = 0;
			lexeme[i++] = ch;
			ch1 = fgetc(fp1);
			
			while(isalpha(ch1)||ch1 == '.'||ch1 == '_'||isdigit(ch1)) {
				lexeme[i++] = ch1;
				ch1 = fgetc(fp1);
			}
			
			lexeme[i] == '\0';
			ungetc(ch1, fp1);
			
			for(int j = 0; j < 18; j++)
				if(strcmp(keywords[j], lexeme) == 0) {
					flag = 1;
					break;
				}
				
			if(flag)
				printf("%d\t\t%s\t\tKeyword\t\t%d\n", slno, lexeme, line);
			else
				printf("%d\t\t%s\t\tIdentifier\t\t%d\n", slno, lexeme, line);
			slno++;
			memset(lexeme, '\0', sizeof(lexeme));
		}
		
		else {
			printf("%d\t\t%c\t\tUnrecognized\t\t%d\n", slno, ch, line);
			slno++;
		}
	}
	
	fclose(fp1);
	fclose(fp2);
}
