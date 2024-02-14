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

NODE* find_node(NODE* search_root, char* path){
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

void separate_path(const char *path, char *dirname, char *basename){
    const char *final_slash = strrchr(path, '/');
    if (final_slash != NULL){
        int index = (int)(final_slash - path);
        strncpy(dirname, path, index);
        dirname[index] = '\0';
        strcpy(basename, final_slash + 1);
    }else{
        strcpy(basename, path);
        dirname[0] = '\0';
    }
}

void ex_mkdir(NODE *cur_dir, const char *args){
    int args_len = (int)strlen(args);
    char pathname[100];
    char basename[100];
    separate_path(args, pathname, basename);
    if (pathname[0] == '\0') {
        NODE *path_node = find_node(cur_dir, pathname);
        if (path_node == NULL){
            printf("ERROR: Path not found!\n");
            return;
        }
        if (path_node->type == 'D'){
            if (path_node->child == NULL){
                //creating new node
                NODE *new_node;
                new_node = (NODE*)malloc(sizeof(NODE));
                if (path_node == NULL){
                    printf("Memory Allocation Failed.\n");
                    return;
                }
                strcpy(new_node->name, basename);
                new_node->type = 'D';
                new_node->child = NULL;
                new_node->parent = path_node;
                new_node->sibling = NULL;
                path_node->child = new_node;
            }else{
                NODE *search_node = path_node->child;
                while (search_node != NULL){
                    if (strcmp(search_node->name, basename) == 0){
                        printf("Error: Directory already exists.");
                        return;
                    }
                    if (search_node->sibling == NULL){
                        //Make new node
                        NODE *new_node;
                        new_node = (NODE*)malloc(sizeof(NODE));
                        if (path_node == NULL){
                            printf("Memory Allocation Failed.\n");
                            return;
                        }
                        strcpy(new_node->name, basename);
                        new_node->type = 'D';
                        new_node->child = NULL;
                        new_node->parent = path_node;
                        new_node->sibling = NULL;
                        search_node->sibling = new_node;
                        break;
                    }
                    search_node = search_node->sibling;
                }
            }
        }else{
            printf("ERROR: Not a Directory\n");
        }
    }
}

void ex_rmdir(NODE *cur_dir, char *args){
    //TODO: implement rmdir functionality
}

void ex_ls(NODE *cur_dir){
    NODE *current = NULL;
    if (cur_dir != NULL){
        current = cur_dir->child;
    }
    if (current == NULL){
        return;
    }
    while(current != NULL){
        printf("%c %s\n", current->type, current->name);
        current = current->sibling;
    }
}

void ex_cd(NODE *cur_dir, char *args){
    NODE* temp;
    if (args[0] == '/'){
        temp = find_node(root, args+1);
    } else {
        temp = find_node(cwd, args+1);
    }

    if(temp == NULL){
        printf("Error: Not a valid directory.\n");
    } else if (temp->type == 'F'){
        printf("Not a directory\n");
    } else {
        cwd = temp;
    }
}

void pwd_recursive(NODE *pwd_root){
    if (pwd_root == NULL){
        return;
    }

    if (pwd_root->parent != root){
        pwd_recursive(pwd_root->parent);
        printf("/");
    }
    printf("%s", pwd_root->name);
    if (pwd_root->child != NULL){
        printf("/");
        pwd_recursive(pwd_root->child);
    }
}

void ex_pwd(NODE *cur_dir){
    pwd_recursive(cur_dir);
    printf("\n");
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
            //if no input continue with loop
            if (tokenizer[0] == '\n')
                continue;
            user_cmd = tokenizer;
            //Removing newline at end of input if it is there
            int cmd_length = (int)strlen(user_cmd);
            if (user_cmd[cmd_length-1] == '\n'){
                user_cmd[cmd_length-1] = '\0';
            }
        }
        else{
            continue; //next iteration of loop if no command is entered
        }

        tokenizer = strtok(NULL, " ");
        char *user_arg_one = tokenizer;
        if(user_arg_one != NULL) {
            //removing newline if it exists
            int user_arg_one_length = (int) strlen(user_arg_one);
            if (user_arg_one_length > 0 && user_arg_one[user_arg_one_length - 1] == '\n') {
                user_arg_one[user_arg_one_length - 1] = '\0';
            }
        }

        // Verify input and find command
        int cmd_index = find_command(user_cmd);
        if (cmd_index == -1){
            printf("Error: Command Not Found!\n");
            continue;
        }

        //TODO: implement calling the necessary functions
        switch(cmd_index){
            case 0:
                if (user_arg_one != NULL){
                    if (user_arg_one[0] == '/'){
                        ex_mkdir(root, user_arg_one);
                    } else {
                        ex_mkdir(cwd, user_arg_one);
                    }
                }else{
                    printf("Error: NO ARGUMENTS");
                }
                break;
            case 1:
                //rmdir
                break;
            case 2:
                //ls
                ex_ls(cwd);
                break;
            case 3:
                //cd
                ex_cd(cwd,user_arg_one);
                break;
            case 4:
                //pwd
                ex_pwd(cwd);
                break;
            case 5:
                //reload
                break;
            case 6:
                //save
                break;
            case 7:
                //quit
                break;
            default:
                printf("Error: Command not recognized.\n");
                continue;
        }
	}
}

