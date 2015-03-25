#include "../common/common.h"

void display ( int *board, size_t n )
{
	size_t i, j;
	LOOP ( i, n )
	{
		LOOP ( j, n )
			PF ( "-----" );
		PF ( "--\n|" );
		LOOP ( j, n )
			if ( j != board[ i ] )
				PF ( "|   |" );
			else
				PF ( "| Q |" );
		puts ( "|" );
	}
	LOOP ( j, n )
		PF ( "-----" );
	puts ( "--\n" );
}

int check ( int *board, int x, int y )
{
	int i;
	LOOP ( i, x )
		if ( y == board[ i ] ||
			 ( i - x ) == ( board[ i ] - y ) ||
			 ( x - i ) == ( board[ i ] - y ) )
			return 0;
	return 1;
}

int solve ( int *board, size_t n, size_t row )
{
	size_t i;
	if ( row < n )
	{
		LOOP ( i, n )
		{
			if ( check ( board, row, i ) )
			{
				board[ row ] = i;
				if ( solve ( board, n, row + 1 ) )
					return 1;
			}
		}
	}
	else
		return 1;
	return 0;
}

int nqueens ( int *board, size_t n )
{
	return solve ( board, n, 0 );
}

void main ( )
{
	int *board;
	size_t n;
	printf ( "Enter the no. of queens:\t" );
	SCANI ( n );
	C_ALLOCATE ( board, n );
	if ( nqueens ( board, n ) )
		display ( board, n );
	getchar ( );
}