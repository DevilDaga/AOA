#include "../common/common.h"

int buildRRT ( int **players, int **days, int **rrt, int N )		// O ( n^2 )
{
	int i, j, *left, *right, left_pointer, right_pointer, isOdd;
	M_ALLOCATE ( left, N );
	M_ALLOCATE ( right, N );
	if ( ( isOdd = ( N % 2 ) ) )
		++N;
	for ( i = 0; i != N / 2; ++i )				// Trading memory for time in circular rotation
	{
		left[ i ] = i + ( N % 2 ) + N / 2;
		right[ i ] = N - i - 1;
	}
	for ( ; i != N - 1; ++i )
	{
		left[ i ] = i + 1 - N / 2;
		right[ i ] = N - i - 1;
	}
	left_pointer = ( N - 1 ) / 2;
	right_pointer = 0;
#define MOD(x)			( (x) + N - 1 ) % ( N - 1 )
	LOOP ( i, N - 1 )					// days
	{
		rrt[ i ][ 0 ] = right[ right_pointer ];
		rrt[ i ][ right[ right_pointer ] ] = 0;
		if ( isOdd && rrt[ i ][ 0 ] == N - 1 )
			rrt[ i ][ 0 ] = -1;
		for ( j = 1; j != N / 2; ++j )
		{
			int l_index = MOD ( j + left_pointer ),
				r_index = MOD ( j + right_pointer );
			rrt[ i ][ left[ l_index ] ] = right[ r_index ];
			rrt[ i ][ right[ r_index ] ] = left[ l_index ];
			if ( isOdd && right[ r_index ] == N - 1 )
				rrt[ i ][ left[ l_index ] ] = -1;
			if ( isOdd && left[ l_index ] == N - 1 )
				rrt[ i ][ right[ r_index ] ] = -1;
		}
		--left_pointer;
		++right_pointer;
	}
#undef MOD
	return N - 1;
}

void print ( int **grid, int n, int m )
{
	int i, j;
	LOOP ( i, n )
	{
		PF ( "%-4d:  ", i + 1 );
		LOOP ( j, m )
				PF ( "%3d", grid[ j ][ i ] + 1 );
		LF;
	}
}

void main ( )
{
	int **players, **days, **rrt, N, i, num_days;
	PF ( "Enter the number of players:\t" );
	SF ( "%d", &N );
	M_ALLOCATE ( players, N );
	M_ALLOCATE ( days, N );
	M_ALLOCATE ( rrt, N );
	LOOP ( i, N + 1 )
	{
		players[ i ]	= calloc ( N, sizeof **players );
		days[ i ]		= calloc ( N, sizeof **days );
		rrt[ i ]		= calloc ( N, sizeof **rrt );
	}
	num_days = buildRRT ( players, days, rrt, N );
	print ( rrt, N, num_days );
	getchar ( );
}