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

NODE* findNode(NODE* search_root, char* path){
    NODE *current = search_root;
    char* tokenizer = strtok(path, "/");

    while(tokenizer != NULL){
        if(strcmp(current->name,tokenizer)==0){
            tokenizer = strtok(NULL,"/");
            //does not move to child if token is found and next token to search is NULL
            //this keeps it on the correct found node
            if (tokenizer != NULL){
                //Token found move to child nodes
                current = current->child;
            }
        }
        else{
            //token not found yet move to siblings
            current = current->sibling;
        }

        if (current == NULL){
            // path does not exist
            return NULL;
        }
    }
    //returns found node or returns null if not found
    return current;
}

void ex_mkdir(NODE *cur_dir, char *args){
    //TODO: implement mkdir functionality
}

void ex_rmdir(NODE *cur_dir, char *args){
    //TODO: implement rmdir functionality
}

void ex_ls(NODE *cur_dir){
    //TODO: implement ls functionality
}

void ex_cd(NODE *cur_dir, char *args){
    //TODO: implement cd functionality
}

void ex_pwd(NODE *cur_dir){
    //TODO: implement pwd functionality
}

void ex_reload(NODE *cur_dir, char *args){
    //TODO: implement reload functionality
}

void ex_save(NODE *cur_dir, char *args){
    //TODO: implement save functionality
}

void ex_quit(){
    //TODO: implement save functionality
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
        char *user_cmd;
        if (tokenizer != NULL){
            user_cmd = tokenizer;
        }
        else{
            continue; //next iteration of loop if no command is entered
        }

        tokenizer = strtok(NULL, " ");
        char *user_arg_one = tokenizer;

        // Verify input and find command
        int cmd_index = find_command(user_cmd);
        if (cmd_index == -1){
            printf("Error: Command Not Found!");
            continue;
        }

        //TODO: implement calling the necessary functions
        switch(cmd_index){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            default:
                printf("Error: Command not recognized.");
                continue;
        }
	}
}

