#include <stdio.h>            
#include <stdlib.h>
#include <string.h>
// you can use additional headers as needed

typedef struct node {
	char  name[64];       // node's name string
	char  type;
	struct node *child, *sibling, *parent;
} NODE;


NODE *root; 
NODE *cwd;
char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "reload",
               "save", "quit", 0};  // fill with list of commands
// other global variables


int initialize() {
	root = (NODE *)malloc(sizeof(NODE));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = 0;
	root->child = 0;
	root->type = 'D';
	cwd = root;
	printf("Filesystem initialized!\n");
}

int main() {
	initialize();
	// other initialization as needed

	while(1) {
		printf("Enter command: ");
		// complete implementations
        char input[100];
        fgets(input, sizeof(input),stdin);

        // beggining tokenizing by spaces
        char *tokenizer = strtok(input, " ");
        if (tokenizer != NULL){
            char *user_cmd = tokenizer;
        }

        tokenizer = strtok(NULL, " ");
        char *user_arg_one = tokenizer;
	}
}

int find_command(char* user_command)
{
    int i = 0;
    while(cmd[i]){
        if (strcmp(user_command, cmd[i])==0){
            return i;
        }
        i++;
    }
    return -1;
}

