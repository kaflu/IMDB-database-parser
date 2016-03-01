#include "stage2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXNAME 128
#define MAXMOVIE 422498
#define MAXSIZE 4222626

node *makedict()
{
	node *inputNode;
	inputNode = (node *) malloc(sizeof(node));

	/* Memory Check */
	if(inputNode == NULL)
	{
		printf("MEMORY ALLOCATION ERROR ON %s ON LINE %d", __FILE__, __LINE__);
		exit(0);
	}

	inputNode->left  = NULL;
	inputNode->right = NULL;
	inputNode->next  = NULL;

	return inputNode;
}

void insert(node *tree, char fullName[], char movieName[])
{	
	if(tree == NULL)
	{
		strcpy(tree->fullName, fullName);
		strcpy(tree->movieName, movieName); 
	}

	else if(strcmp(tree->fullName, fullName) < 0)
	{
		if(tree->left != NULL)
			insert(tree->left, fullName, movieName);
		else
		{
			tree->left = makedict();
			strcpy(tree->left->fullName, fullName);
			strcpy(tree->left->movieName, movieName);
		}
	}

	else if(strcmp(tree->fullName, fullName) > 0)
	{
		if(tree->right != NULL)
			insert(tree->right, fullName, movieName);
		else
		{
			tree->right = makedict();
			strcpy(tree->right->fullName, fullName);
			strcpy(tree->right->movieName, movieName);			
		}
	}

	/* Inserting Duplicates */
	else if(strcmp(tree->fullName, fullName) == 0)
	{
		if(tree->next != NULL)
			insert(tree->next, fullName, movieName);
		else
		{
			tree->next = makedict();
			strcpy(tree->next->fullName, fullName);
			strcpy(tree->next->movieName, movieName);	
		}
	}
 
	else
	{
		printf("There was an error reading in the key \" %s \" so it was skipped.\n", fullName);
	}
}

node *search(char Key[], node *root, int cmp, FILE *outputFile)
{
	while(root != NULL)
	{
		if(strcmp(root->fullName, Key) == 0)
		{
			while(root != NULL)
			{
				printScreenFound(root, cmp);
				printFileFound(root, outputFile);
				root = root->next;
				return root;
			}
		}
		else if(strcmp(root->fullName, Key) < 0)
		{
			cmp++;
			return search(Key, root->left, cmp, outputFile);
		}
		else
		{
			cmp++;
			return search(Key, root->right, cmp, outputFile);
		}
	}

	printScreenNotFound(Key, cmp);
	printFileNotFound(Key, outputFile);

	return NULL;
}

void createBinaryTree(node *temp, FILE *inputMovieData)
{
	char out[MAXSIZE], fullName[MAXNAME], movieName[MAXMOVIE];
	char *delim = ";", *outptr = out;

	while(fgets(out, MAXSIZE, inputMovieData) != NULL)
	{
		outptr = out;
		strcpy(fullName,  strsep(&outptr, delim));
		strcpy(movieName, strsep(&outptr, delim));
		insert(temp, fullName, movieName);
	}
}

void searchTree(node *tree, FILE *outputFile)
{
	int cmp = 0;
	char key[MAXNAME];

	while(fgets(key, MAXNAME, stdin) != NULL)
	{
		key[strcspn(key, "\n")]	= 0;
		search(key, tree, cmp, outputFile);
	}
}

/* Print Functions */
void printScreenFound(node *root, int cmp)
{
	printf("%s --> %d\n", root->fullName, cmp);
}

void printScreenNotFound(char Key[], int cmp)
{
	printf("%s --> %d\n", Key, cmp);
}

void printFileFound(node *root, FILE *outputFile)
{
	fprintf(outputFile, "%s -->%s\n",root->fullName, root->movieName);
}

void printFileNotFound(char Key[], FILE *outputFile)
{
	fprintf(outputFile, "%s --> NOTFOUND\n", Key);
}