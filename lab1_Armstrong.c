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

        // beginning tokenizing by spaces
        char *tokenizer = strtok(input, " ");
        if (tokenizer != NULL){
            char *user_cmd = tokenizer;
        }
        else{
            continue; //next iteration of loop if no command is entered
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

void ex_mkdir(struct node *cur_dir, char *args){
    //TODO: implement mkdir functionality
}

void ex_rmdir(struct node *cur_dir, char *args){
    //TODO: implement rmdir functionality
}

void ex_ls(struct node *cur_dir){
    //TODO: implement ls functionality
}

void ex_cd(struct node *cur_dir, char *args){
    //TODO: implement cd functionality
}

void ex_pwd(struct node *cur_dir){
    //TODO: implement pwd functionality
}

void ex_reload(struct node *cur_dir, char *args){
    //TODO: implement reload functionality
}

void ex_save(struct node *cur_dir, char *args){
    //TODO: implement save functionality
}

void ex_quit(){
    //TODO: implement save functionality
}