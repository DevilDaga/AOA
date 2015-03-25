#include "../common/common.h"

void GetMinMax ( int *a, int l, int b, int *min, int *max )
{
	int mid, minLeft, maxLeft, minRight, maxRight;
	if ( l == b - 1 )
	{
		*min = *max = a[ l ];
		return;
	}
	mid = ( l + b ) / 2;
	GetMinMax ( a, l, mid, &minLeft, &maxLeft );
	GetMinMax ( a, mid, b, &minRight, &maxRight );
	*min = min( minLeft, minRight );
	*max = max( maxLeft, maxRight );
}

void main ( )
{
	int N = 699, *a, i, min, max;
	M_ALLOCATE ( a, N );
	srand ( (unsigned) clock ( ) );
	LOOP ( i, N )
		a[ i ] = rand ( ) % 10000;
	GetMinMax ( a, 0, N, &min, &max );
	PF ( "Minimum :\t%d\nMaximum :\t%d\n", min, max );
	getchar ( );
}