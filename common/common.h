#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#define PF					printf
#define SF					scanf
#define LF					puts ( "" )
#define M_ALLOCATE(x,n)		(x) = malloc ( (n) * sizeof *(x) )
#define C_ALLOCATE(x,n)		(x) = calloc ( (n), sizeof *(x) )
#define SCANI(x)			scanf ( "%d", &(x) )
#define	CLOCK_START(x)		clock_t (x) = clock ( )
#define	TIME_ELAPSED(x)		(double) ( ( clock ( ) - (x) ) / CLOCKS_PER_SEC )
#define LOOP(i,n)			for ( (i) = 0; (i) != (n); ++(i) )
#define RLOOP(i,n)			for ( (i) = (n) - 1; (i) != -1; --(i) )
#ifndef min
#define min(a,b)			(((a) < (b) ) ? (a) : (b));
#endif
#ifndef max
#define max(a,b)			(((a) > (b) ) ? (a) : (b));
#endif

void swap ( void *left, void *right, size_t n )
{
	void *temp = malloc ( n );
	memcpy ( temp, left, n );
	memcpy ( left, right, n );
	memcpy ( right, temp, n );
}

int comparator_nondecreasing_int ( const void *x, const void *y )
{
	return ( *(int*) x - *(int*) y );
}

void blank_graph ( int **graph, size_t n )
{
	size_t i;
	LOOP ( i, n )
		graph[ i ] = calloc ( n, sizeof graph );
}

size_t input_graph_matrix ( int **graph, size_t n )
{
	size_t i, j, c = 0;
	blank_graph ( graph, n );
	puts ( "Enter the adjacency matrix:" );
	LOOP ( i, n )
	{
		LOOP ( j, n )
		{
			SF ( "%d", &graph[ i ][ j ] );
			if ( graph[ i ][ j ] )
				++c;
		}
	}
	return c;
}

void replace_in_graph ( int **graph, size_t n, int old, int update )
{
	size_t i, j;
	LOOP ( i, n )
		LOOP ( j, n )
			if ( graph[ i ][ j ] == old )
				graph[ i ][ j ] = update;
}

size_t input_graph_edge ( int **graph, size_t n, int isDirected, int isWeighted )
{
	size_t u, v, w, c = 0;
	blank_graph ( graph, n );
	puts ( "Enter the endpoints ( -1 -1 to stop ):" );
	while ( 1 )
	{
		SF ( "%d %d", &u, &v );
		if ( isWeighted )
			SCANI ( w );
		else
			w = 1;
		if ( u == -1 )
			break;
		++c;
		graph[ u - 1 ][ v - 1 ] = w;
		if ( !isDirected )
			graph[ v - 1 ][ u - 1 ] = w;
	}
	return c;
}

void print_graph_matrix ( int **graph, size_t n )
{
	size_t i, j;
	PF ( "      " );
	LOOP ( i, n )
		PF ( "%-3d", i + 1 );
	LF;
	LOOP ( i, n )
	{
		PF ( "%-3d:  ", i + 1 );
		LOOP ( j, n )
			PF ( "%-3d", graph[ i ][ j ] );
		LF;
	}
}

void print_graph_edges ( int **graph, int n, int isDirected )
{
	size_t i, j, c = 0;
	const char *arrow = ( isDirected ) ? "=>" : "<=>";
	LOOP ( i, n )
		LOOP ( j, ( isDirected ) ? n : i )
			if ( graph[ i ][ j ] )
				PF ( "#%-3d:   %-3d%s  %-3d  weight = %-3d\n",
					++c, i + 1, arrow, j + 1, graph[ i ][ j ] );
}