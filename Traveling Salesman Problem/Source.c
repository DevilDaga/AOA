#include "../common/common.h"

size_t compute ( int **A, size_t n, size_t size,
			  int **graph, int **p, int start, int set )
{
	size_t masked, result = INT_MAX, i;
	if ( A[ start ][ set ] != -1 )
		return A[ start ][ set ];
	LOOP ( i, n )
	{
		masked = set & ( ~( 1 << i ) );		// Removing 'i' from the set
		if ( masked != set )				// In case 'i' was never in the set
		{
			size_t cur_cost = graph[ start ][ i ] +
				compute ( A, n, size, graph, p, i, masked );
			if ( cur_cost < result )
			{
				result = cur_cost;
				p[ start ][ set ] = i;
			}
		}
	}
	return A[ start ][ set ] = result;
}

void build_path ( int **p, size_t size, int *path )
{
	int x = 0, c = 0;
	int masked = ( size - 2 );		// All elements except the first
	while ( x != -1 )
	{
		path[ c++ ] = x;
		masked &= ~( 1 << x );		// Removing 'x' from the set
		x = p[ x ][ masked ];
	}
	path[ c ] = 0;
}

size_t TSP ( int **graph, size_t n, int *path )
{
	size_t i, j, size = 1 << n, result;
	int **A, **p;
	assert ( n < 8 * sizeof ( int ) );
	M_ALLOCATE ( A, n );			// Half the entries are still redundant.
	M_ALLOCATE ( p, n );			// Here too.
	// A[ i ][ S ] is the length of shortest path from 'i' visiting all vertices in S and ending at 1
	LOOP ( i, n )
	{
		A[ i ] = malloc ( size * sizeof **A );
		p[ i ] = malloc ( size * sizeof **p );
		LOOP ( j, size )
			A[ i ][ j ] = p[ i ][ j ] = -1;
		A[ i ][ 0 ] = graph[ i ][ 0 ];
	}
	result = compute ( A, n, size, graph, p, 0, size - 2 ); // Exclude our "home" vertex
	build_path ( p, size, path );
	return result;
}

void print_path ( int *path, size_t n )
{
	size_t i;
	LOOP ( i, n + 1 )
		PF ( "%-3d", path[ i ] + 1 );
	LF;
}

void main ( )
{
	size_t n, cost;
	int **graph, *path;
	PF ( "Enter the number of cities:\t" );
	SCANI ( n );
	M_ALLOCATE ( graph, n );
	M_ALLOCATE ( path, n + 1 );
	input_graph_matrix ( graph, n );
	cost = TSP ( graph, n, path );
	PF ( "Tour cost:\t%-4d\n", cost );
	PF ( "Tour:\t\t" );
	print_path ( path, n );
	getchar ( );
}