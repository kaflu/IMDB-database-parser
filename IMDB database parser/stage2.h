#ifndef __stage2__
#define __stage2__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXNAME 128
#define MAXMOVIE 422498
#define MAXSIZE 4222626	

/* Structure of node for binary tree */
typedef struct node
{
	char fullName[MAXNAME];
	char movieName[MAXMOVIE];	
	struct node *left;
	struct node *right;
	struct node *next;
}node;

/* Allocates memory for a struct of type node */
node *makedict();

/* Inserts the datafields into the node */
void insert(node *tree, char fullName[], char movieName[]);

/* Searches the tree for the key and counts number of comparisons */
node *search(char Key[], node *root, int cmp, FILE *outputFile);

/* Function to initialise the binary tree */
void createBinaryTree(node *temp, FILE *inputMovieData);

/* Function to initialise the search */
void searchTree(node *tree, FILE *outputFile);

/* Print functions */
void printScreenFound(node *root, int cmp);
void printScreenNotFound(char Key[], int cmp);
void printFileFound(node *root, FILE *outputFile);
void printFileNotFound(char Key[], FILE *outputFile);

#endif //stage2.h