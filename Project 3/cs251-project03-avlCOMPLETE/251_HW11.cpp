/* main.c */

/*
* AVL complete insert with rebalancing:
*/

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "avl.h"


//
// Returns true (non-zero value) if the given binary tree is a 
// binary search tree; returns false (0) if not.
//
#define _TRUE  1
#define _FALSE 0

int _allSubtreeValuesAreLess(AVLNode *root, AVLKey key, int *value)
{
	if (root == NULL)
		return _TRUE;
	else
	{
		*value = *value + (root->Key * (root->Height + 1));

		return root->Key < key &&
			_allSubtreeValuesAreLess(root->Left, key, value) &&
			_allSubtreeValuesAreLess(root->Right, key, value);
	}
}

int _allSubtreeValuesAreGreater(AVLNode *root, AVLKey key, int *value)
{
	if (root == NULL)
		return _TRUE;
	else
	{
		*value = *value + (root->Key * (root->Height + 1));

		return root->Key > key &&
			_allSubtreeValuesAreGreater(root->Left, key, value) &&
			_allSubtreeValuesAreGreater(root->Right, key, value);
	}
}

int isBST(AVLNode *root, int *value)
{
	if (root == NULL)
		return _TRUE;
	else
	{
		return _allSubtreeValuesAreLess(root->Left, root->Key, value) &&
			_allSubtreeValuesAreGreater(root->Right, root->Key, value) &&
			isBST(root->Left, value) &&
			isBST(root->Right, value);
	}
}


//
// Returns true (non-zero value) if the given binary tree is an 
// AVL tree; returns false (0) if not.
//
int __height(AVLNode *cur)
{
	if (cur == NULL)
		return -1;
	else
		return cur->Height;
}

int __max2(int x, int y)
{
	return (x > y) ? x : y;
}

int _checkAllSubtreeHeights(AVLNode *root, int *value)
{
	if (root == NULL)
		return _TRUE;
	else
	{
		// let's also make sure the heights are correctly computed:
		int hl = __height(root->Left);
		int hr = __height(root->Right);
		int H = 1 + __max2(hl, hr);

		*value = *value + (root->Height + 1);

		return (H == root->Height) &&
			(abs(__height(root->Left) - __height(root->Right)) <= 1) &&
			_checkAllSubtreeHeights(root->Left, value) &&
			_checkAllSubtreeHeights(root->Right, value);
	}
}

int isAVL(AVLNode *root, int *value)
{
	if (root == NULL)
		return _TRUE;
	else
	{
		return isBST(root, value) &&
			_checkAllSubtreeHeights(root, value);
	}
}


//
// Builds the tree from the input stream.
//
AVL *BuildTree(FILE *input)
{
	AVL  *tree;
	int   key, returnValue;

	tree = AVLCreate();

	fscanf(input, "%d", &key);

	while (key != 0)  // until we see EOF marker
	{
		printf(">> Inserting (%d,%d)...", key, -1);

		returnValue = AVLInsert(tree, key, -1);

		if (returnValue)
			printf("returned=TRUE\n");
		else
			printf("returned=FALSE\n");

		fscanf(input, "%d", &key);
	}

	// done:
	return tree;
}


void PrintOneNode(AVLNode *cur)
{
	printf("(%d,%d)@%d ", cur->Key, cur->Value, cur->Height);
}


int main()
{
	AVL  *tree;
	FILE *input;
	int   key, returnValue;

	input = stdin;

	tree = BuildTree(input);

	AVLPrintPreorder(tree, PrintOneNode);

	fscanf(input, "%d", &key);

	printf(">> Inserting (%d,%d)...", key, -1);

	returnValue = AVLInsert(tree, key, key);

	if (returnValue)
		printf("returned=TRUE\n");
	else
		printf("returned=FALSE\n");

	AVLPrintPreorder(tree, PrintOneNode);

	int value = 0;
	printf("** IsBST? %s", (isBST(tree->Root, &value) ? "yes" : "no"));
	printf(", %d\n", value);

	value = 0;
	printf("** IsAVL? %s", (isAVL(tree->Root, &value) ? "yes" : "no"));
	printf(", %d\n", value);

	return 0;
}
