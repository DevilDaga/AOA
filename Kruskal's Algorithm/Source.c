#include "../common/common.h"
#include "../common/union_find.h"

typedef struct
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
	edge *edges;
	forest_node **sets;
	size_t n, m, i, j;
	PF ( "Enter the number of vertices:\t" );
	SCANI ( n );
	M_ALLOCATE ( graph, n );
	M_ALLOCATE ( mst, n );
	M_ALLOCATE ( sets, n );
	PF ( "1:\tInput using Adjacency matrix\n2:\tInput using edge endpoints\nChoice:\t" );
	SCANI ( i );
	if ( i == 1 )
		m = input_graph_matrix ( graph, n );
	else
		m = input_graph_edge ( graph, n, 0, 1 );
	blank_graph ( mst, n );
	M_ALLOCATE ( edges, 2 * m );
	m = 0;
	LOOP ( i, n )
	{
		sets[ i ] = MakeSet ( i );
		LOOP ( j, n )
		{
			if ( graph[ i ][ j ] )
			{
				edges[ m ].u = i;
				edges[ m ].v = j;
				edges[ m++ ].w = graph[ i ][ j ];
			}
		}
	}
	qsort ( edges, m, sizeof *edges, &compare );
	LOOP ( i, m )
	{
		forest_node *u = FindSet ( sets[ edges[ i ].u ] ),
			*v = FindSet ( sets[ edges[ i ].v ] );
		if ( u != v )
		{
			mst[ edges[ i ].u ][ edges[ i ].v ] =
				mst[ edges[ i ].v ][ edges[ i ].u ] = edges[ i ].w;
			Union ( u, v );
		}
	}
	puts ( "Edges in MST:" );
	print_graph_edges ( mst, n, 0 );
	getchar ( );
}