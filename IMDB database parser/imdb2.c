#include "stage2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

int main(int argc, char *argv[])
{
	/* Performance */
	clock_t begin, end;
	double time_spent;
	begin = clock();

	/* Some variables to initialise the input files read */
	FILE *inputMovieData = fopen(argv[1], "r");
	FILE *outputFile         = fopen(argv[2], "w");

	/* Initialise a global tree of type node */
	node *tree = makedict();

	/* Read in the binary tree with data from argv 1 */
	createBinaryTree(tree, inputMovieData);

	/* Search the tree and write the data to a file specified in argv 2 */
	searchTree(tree, outputFile);

	/* Close the files at the end */
	fclose(inputMovieData);
	fclose(outputFile);

	/* Performance Log */
	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("\nEXECUTION TIME: %.5f seconds\n", time_spent);

	return 0;
}
