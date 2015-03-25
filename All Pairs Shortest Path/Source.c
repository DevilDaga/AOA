#include "../common/common.h"

void main ( )
{
	int **graph, **A;
	M_ALLOCATE ( graph, 1 );
	M_ALLOCATE ( A, 1 );
	size_t i, j, k, n;
	PF ( "Enter the number of vertices:\t" );
	SCANI ( n );
	input_graph_matrix ( graph, n );
	blank_graph ( A, n );
	LOOP ( i, n )
		memcpy ( A[ i ], graph[ i ], n * sizeof ( int ) );
	replace_in_graph ( A, n, 0, 8000 );
	LOOP ( i, n )
	{
		LOOP ( j, i )
			LOOP ( k, n )
			A[ j ][ i ] = A[ i ][ j ] = min ( A[ i ][ j ], A[ i ][ k ] + A[ k ][ j ] );
		A[ i ][ i ] = 0;
	}
	puts ( "All pairs shortest path matrix:" );
	print_graph_matrix ( A, n );
	getchar ( );
}