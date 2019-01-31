/* 
 * This is a program that parses pages from the site Wikipedia using C’s text processing functions found in <string.h>. 
 * Print the names of all links to other Wikipedia pages that you find to the terminal.
 * links appear in this form:
 * <a href="/wiki/PageName" maybe some junk title="PageName">easy to read description</a>
 */

#define MAXLINELENGTH 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[]){

	char file_name[100];
	//char post_fix[10]=".html";

	if(argc != 2){
		printf("You have to enter only one argument.\n");
		exit(0);
	}
	
	strcpy(file_name, argv[1]);
	//strcat(file_name, post_fix);

	FILE *fptr= fopen(file_name, "r");

	//C library function char *fgets(char *str, int n, FILE *stream) 
	//reads a line from the specified stream and stores it into the string pointed to by str. 
	//It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.

	//open the generated html file
	

	if(fptr != NULL){

		char line[MAXLINELENGTH];		
		//char example_link1[]="<a href=";  
		//char example_link2[]="/wiki/";
		char title_part[]="title=";
		char check_end[]="</a>";
		char full_line[]="<a href=\"/wiki/";
		const char first_occur[] ="\"";

		while(fgets(line, MAXLINELENGTH, fptr) != NULL){
			//strstr--find first occurence of substring, returns a ponter points to the first character of found example_link in line
			char *same_line=line;

			while(same_line != NULL){
				//char *found_link1=strstr(same_line, example_link1);
			    //char *found_link2=strstr(same_line, example_link2);
			    char *check_title=strstr(same_line, title_part);
			    char *check_last=strstr(same_line, check_end);
			    char *check_full=strstr(same_line, full_line);

			    //case when all three conditions met, print the PageName
			    if(check_full && check_last && check_title){

			    	if(check_title<check_last){

			    		char *name1 = check_full + strlen(full_line);

			    		char *name_found_with_wiki = strtok(name1, first_occur);
				        //get the pointer to the start of PageName, only print the PageName
				        //char *name_finally_found = name_found_with_wiki + strlen(example_link2);

				        printf("%s\n", name_found_with_wiki);

			    	}
				    check_last=check_last+strlen(check_end);
				    same_line=check_last;
				//C library function char *strtok(char *str, const char *delim) breaks string str into a series of tokens using the delimiter(the character to stop) delim
				//This function returns a pointer to the first token found in the string. A null pointer is returned if there are no tokens left to retrieve.
				//this will found "/wiki/PageName"
			    }else{
				    same_line=NULL;
			    }
			}	

		}
	}else{
		printf("Can't read from file %s\n", file_name);
		return -1;
	}


	fclose(fptr);

	return 0;
		
}
    
    
    
    

