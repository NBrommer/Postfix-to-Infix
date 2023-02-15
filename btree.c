/*
Nathan Brommersma
ID: 1196739
November 11th 2022

Description:
This program takes an argument of a POSTFIX string and then 
puts it into a binary tree. The binary tree is created by using
a stack to build up the tree as the string is looped through. 
Finally the new tree is printed out in INFIX notation.
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACKSIZE 100

typedef struct binaryTree {

	char data[4];
	struct binaryTree *left;
	struct binaryTree *right;

}binaryTree;

typedef struct Stack {
	int top;
	struct binaryTree * tree[STACKSIZE];
}theStack;

//Checks if stack is empty
int empty(theStack *stack){
	return(stack->top == -1);
}

//Pushes tree to stack
void push(theStack *stack, struct binaryTree* theTree){
	//Push tree onto stack
	if (stack->top == STACKSIZE - 1) {
		printf("Stack overflow\n");
		exit(1);
	} else {
		stack->tree[++(stack->top)] = theTree;
	}
	return;
}

//pops tree off stack
struct binaryTree* pop(theStack *stack){
	//pop tree off of stack
	if(empty(stack)){
		printf("Stack underflow\n");
		exit(1);
	}
	return(stack->tree[stack->top--]);
}

//Creates new branch for tree and initializes branches to NULL
struct binaryTree* newTree(char dataNew[5]) {
	struct binaryTree* theNewTree;
	theNewTree = malloc(sizeof(struct binaryTree) * 1);

	//puts data into tree
	strcpy(theNewTree->data, dataNew);

	//makes theNewTree left and right null
	theNewTree->left = NULL;
	theNewTree->right = NULL;

	return theNewTree;
} 

//Recursive function to print out the tree in infix notation
void printTreeInfix(struct binaryTree* theTree) {

	//If statement skips printing if branch is empty
	if(theTree != NULL){

		//print bracket if operator
		if (theTree->data[0] == '+' || theTree->data[0] == '-' 
			|| theTree->data[0] == '*' || theTree->data[0] == '/') {

			printf("(");
		}

		//Recursive function call to print left and right trees
		printTreeInfix(theTree->left);
		printf("%s", theTree->data);
		printTreeInfix(theTree->right);

		//Prints bracket if operator
		if (theTree->data[0] == '+' || theTree->data[0] == '-' 
			|| theTree->data[0] == '*' || theTree->data[0] == '/'){

			printf(")");
		}
	}
	return;
}

int main (int argc, char * argv[]){

	//Initialize everything
	int i;
	int j;

	char data[4];

	struct binaryTree *ptr;
	struct binaryTree *popLeft;
	struct binaryTree *popRight;

	struct Stack stack;

	//Set bottom of stack
	stack.top = -1;

	//Returns if there are too many arguments
	if(argc > 2) {
		printf("Too many arguments!\n");
		return 0;
	}

	//Returns if there are no arguements\


	
	if(argc == 1) {
		printf("Needs an argument!\n");
		return 0;
	}

	//This loop goes through the whole postfix string and creates the expression tree
	for(i = 0; i < strlen(argv[1]); i++) {

		//Makes data empty
		for(j = 0; j < 5; j++){
			data[j] = '\0';
		}

		//If x variable push to stack
		if(argv[1][i] == 'x' || argv[1][i] == 'X'){
			data[0] = argv[1][i];
			i = i + 1;
			data[1] = argv[1][i];
			data[2] = '\0';
			ptr = newTree(data);
			push(&stack, ptr);
			i = i + 1;

		//if digit push to stack
		} else if(isdigit(argv[1][i]) != 0) {
			data[0] = argv[1][i];
			i = i + 1;
			data[1] = argv[1][i];
			i = i + 1;
			data[2] = argv[1][i];
			i = i + 1;
			data[3] = argv[1][i];
			data[4] = '\0';
			ptr = newTree(data);
			push(&stack, ptr);
			i = i + 1;
		//If operator, pop last two trees and attach to operator branch
		} else if(argv[1][i] == '+' || argv[1][i] == '-' 
			|| argv[1][i] == '*' || argv[1][i] == '/') {
			data[0] = argv[1][i];
			ptr = newTree(data);
			popRight = pop(&stack);
			popLeft = pop(&stack);
			ptr->right = popRight;
			ptr->left = popLeft;
			push(&stack, ptr);
			i = i + 1;
		}
	}

	//Print out expression recursively
	ptr = pop(&stack);
	printTreeInfix(ptr);
	printf("\n");

	return 1;
}