#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[])
{
	if(argc < 2){
		printf("Command line inputs noot given\n");
		return;
	}
	
	FILE *fp1, *fp2;
	
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
	
	char ch, ch1, ch2;
	while((ch = fgetc(fp1)) != EOF) {
		switch(ch) {
			case ' ':
			case '\t':
			case '\n': break;
			case '/':
				if((ch1 = fgetc(fp1)) == '/')
					while((ch = fgetc(fp1)) != '\n');
				else if(ch1 == '*') {
					ch1 = fgetc(fp1);
					ch2 = fgetc(fp1);
					while(!(ch1 == '*' && ch2 == '/')) {
						ch1 = ch2;
						ch2 = fgetc(fp1);
					}
				} else {
					fputc(ch, fp2);
					ungetc(ch1, fp1);
				}
				break;
			default:
				fputc(ch, fp2);
		}
	}
	
	printf("Whitespaces and Comments from %s is removed and is written into %s\n", argv[1], argv[2]);
	
	fclose(fp1);
	fclose(fp2);
}
