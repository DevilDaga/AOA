#include "../common/common.h"

enum
{
	DIAGNOL,
	UP,
	LEFT
};

void buildLCS ( char *x, int **dir, int i, int j, char *lcs, size_t *k )
{
	if ( i == 0 || j == 0 )
		return;
	if ( dir[ i ][ j ] == DIAGNOL )
	{
		buildLCS ( x, dir, i - 1, j - 1, lcs, k );
		lcs[ ( *k )++ ] = x[ i - 1 ];
	}
	else if ( dir[ i ][ j ] == UP )
		buildLCS ( x, dir, i - 1, j, lcs, k );
	else
		buildLCS ( x, dir, i, j - 1, lcs, k );
}

char *getLCS ( char *a, char *b )
{
	size_t n, m, i, j, k = 0, **table, **dir;
	char *result;
	m = strlen ( a );
	n = strlen ( b );
	C_ALLOCATE ( result, min ( m, n ) + 1 );
	M_ALLOCATE ( table, m + 1 );
	M_ALLOCATE ( dir, m + 1 );
	LOOP ( i, m + 1 )
	{
		table[ i ] = calloc ( n + 1, sizeof **table );
		dir[ i ] = calloc ( n + 1, sizeof **dir );
	}
	LOOP ( i, m )
	{
		LOOP ( j, n )
		{
			if ( a[ i ] == b[ j ] )
			{
				table[ i + 1 ][ j + 1 ]	= 1 + table[ i ][ j ];
				dir[ i + 1 ][ j + 1 ]	= DIAGNOL;
			}
			else if ( table[ i ][ j + 1 ] >= table[ i + 1 ][ j ] )
			{
				table[ i + 1 ][ j + 1 ]	= table[ i ][ j + 1 ];
				dir[ i + 1 ][ j + 1 ]	= UP;
			}
			else
			{
				table[ i + 1 ][ j + 1 ]	= table[ i + 1 ][ j ];
				dir[ i + 1 ][ j + 1 ]	= LEFT;
			}
		}
	}
	buildLCS ( a, dir, m, n, result, &k );
	return result;
}

void main ( )
{
	char a[ 256 ], b[ 256 ], *lcs;
	PF ( "Enter the first string: \t" );
	gets ( a );
	PF ( "Enter the second string:\t" );
	gets ( b );
	lcs = getLCS ( a, b );
	PF ( "LCS length:\t%d\n", strlen ( lcs ) );
	PF ( "LCS:\t\t\t%s\n", lcs );
	getchar ( );
}