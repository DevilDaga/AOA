#include "../common/common.h"

void print_subset ( int *solution, size_t n )
{
	size_t i;
	static int c = 0;
	PF ( "%-4d:\t", ++c );
	LOOP ( i, n )
		PF ( "%-4d", solution[ i ] );
	LF;
}

void backtrack ( int *nums, size_t at, size_t n, int *solution, size_t subset_size, int sumrequired )
{
	if ( sumrequired == 0 )
	{
		print_subset ( solution, subset_size );
		return;
	}
	else if ( sumrequired < 0 || at == n )
		return;
	backtrack ( nums, at + 1, n, solution, subset_size, sumrequired );
	solution[ subset_size++ ] = nums[ at ];
	backtrack ( nums, at + 1, n, solution, subset_size, sumrequired - nums[ at ] );
}

void subset_sum ( int *nums, size_t n, int sum )
{
	int *M_ALLOCATE ( solution, n );
	qsort ( nums, n, sizeof *nums, &comparator_nondecreasing_int );
	backtrack ( nums, 0, n, solution, 0, sum );
}

void main ( )
{
	int *nums, sum;
	size_t i, n;
	PF ( "Enter the number of elements:\t" );
	SCANI ( n );
	M_ALLOCATE ( nums, n );
	puts ( "Enter the elements:" );
	LOOP ( i, n )
		SCANI ( nums[ i ] );
	PF ( "Enter the required sum:\t" );
	SCANI ( sum );
	puts ( "Solution:" );
	subset_sum ( nums, n, sum );
	getchar ( );
}