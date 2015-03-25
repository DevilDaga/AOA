#pragma once
#include <malloc.h>
#include <stdlib.h>

typedef struct forest_node_s
{
	int key;
	struct forest_node_s *parent;
	int rank;
} forest_node;

forest_node *MakeSet ( int value )
{
	forest_node *node = calloc ( 1, sizeof *node );
	node->key = value;
	return node;
}

void Union ( forest_node *node1, forest_node *node2 )
{
	if ( node1->rank > node2->rank )
		node2->parent = node1;
	else if ( node2->rank > node1->rank )
		 node1->parent = node2;
	else
	{
		node2->parent = node1;
		node1->rank++;
	}
}

forest_node *FindSet ( forest_node *node )
{
	forest_node *temp, *root = node;
	while ( root->parent != NULL )
		root = root->parent;
	// Update the parent pointers
	while ( node->parent != NULL )
	{
		temp = node->parent;
		node->parent = root;
		node = temp;
	}
	return root;
}