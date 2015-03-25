#include "../common/common.h"

typedef struct edge_s
{
	int u, v, w;
}edge;

int compare ( const void *x, const void *y )
{
	return ( ( (edge*) x )->w - ( (edge*) y )->w );
}

void main ( )
{
	int **graph, **mst;
	size_t n, m, i, j, k = 0, *visited;
	edge *edges;
	PF ( "Enter the number of vertices:\t" );
	SCANI ( n );
	M_ALLOCATE ( graph, n );
	M_ALLOCATE ( mst, n );
	C_ALLOCATE ( visited, n );
	PF ( "1:\tInput using Adjacency matrix\n2:\tInput using edge endpoints\nChoice:\t" );
	SCANI ( i );
	if ( i == 1 )
		m = input_graph_matrix ( graph, n );
	else
		m = input_graph_edge ( graph, n, 0, 1 );
	M_ALLOCATE ( edges, m + 1 );
	LOOP ( i, n )
	{
		LOOP ( j, i )
		{
			if ( graph[ i ][ j ] )
			{
				edges[ k ].u = i;
				edges[ k ].v = j;
				edges[ k++ ].w = graph[ i ][ j ];
			}
		}
	}
	qsort ( edges, k, sizeof *edges, &compare );
	replace_in_graph ( graph, n, 0, 9999 );
	blank_graph ( mst, n );
	visited[ 0 ] = 1;
	LOOP ( i, k )
	{
		edge e = edges[ i ];
		if ( !( visited[ e.u ] ^ visited[ e.v ] ) )
			continue;
		mst[ e.u ][ e.v ] = mst[ e.v ][ e.u ] = e.w;
		visited[ e.u ] = visited[ e.v ] = 1;
		i = -1;			// Would be much faster with a 'min heap'.
	}
	puts ( "Edges in MST:" );
	print_graph_edges ( mst, n, 0 );
	getchar ( );
}