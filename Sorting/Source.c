#include "../common/common.h"

#define			NUMELEMENTS 100000
#define			NUMDIGITS	5
const int		VERIFY = 0;

// Bubble Sort method which returns time elapsed while sorting
double bubblesort ( int a[ ], int n )
{
	CLOCK_START ( start );
	int i, j;
	LOOP ( i, n - 1 )
		LOOP ( j, n - 1 )
			if ( a[ j ] > a[ j + 1 ] )
				swap ( &a[ j ], &a[ j + 1 ], sizeof ( int ) );
	return TIME_ELAPSED ( start );
}

// Selection Sort method which returns time elapsed while sorting
double selectionsort ( int a[ ], int n )
{
	CLOCK_START ( start );
	int i, j, min, pos;
	LOOP ( i, n - 1 )
	{
		min = a[ pos = i ];
		for ( j = i + 1; j != n; ++j )
			if ( a[ j ] < min )
				min = a[ pos = j ];
		a[ pos ] = a[ i ];
		a[ i ] = min;
	}
	return TIME_ELAPSED ( start );
}

// Insertion Sort method which returns time elapsed while sorting
double insertionsort ( int a[ ], int n )
{
	CLOCK_START ( start );
	int i, j, val;
	LOOP ( i, n - 1 )
	{
		val = a[ i + 1 ];
		RLOOP ( j, i + 1 )
		{
			if ( a[ j ] > val )
				a[ j + 1 ] = a[ j ];
			else
				break;
		}
		a[ j + 1 ] = val;
	}
	return TIME_ELAPSED ( start );
}

void merge ( int x[ ], int lb, int m, int ub )
{
	int i = lb, j = m + 1, k = lb;
	while ( i <= m && j <= ub )
		if ( x[ i ] < x[ j ] )
			x[ k++ ] = x[ i++ ];
		else
			x[ k++ ] = x[ j++ ];
	while ( i <= m )
		x[ k++ ] = x[ i++ ];
	while ( j <= ub )
		x[ k++ ] = x[ j++ ];
}

void mergesort_worker ( int a[ ], int l, int u )
{
	if ( l < u )
	{
		int mid = ( l + u ) / 2;
		mergesort_worker ( a, l, mid );
		mergesort_worker ( a, mid + 1, u );
		merge ( a, l, mid, u );
	}
}

void quicksort_worker ( int a[ ], int low, int high )
{
	int pivot, j, i;
	if ( low < high )
	{
		pivot = i = low;
		j = high;
		while ( i < j )
		{
			while ( ( a[ i ] <= a[ pivot ] ) && ( i < high ) )
				i++;
			while ( a[ j ] > a[ pivot ] )
				j--;
			if ( i < j )
				swap ( &a[ i ], &a[ j ], sizeof ( int ) );
		}
		swap ( &a[ pivot ], &a[ j ], sizeof ( int ) );
		quicksort_worker ( a, low, j - 1 );
		quicksort_worker ( a, j + 1, high );
	}
}

void print_times ( double *times, int n )
{
	int i, mul = 1;
	LOOP ( i, n )
	{
		mul *= 10;
		printf ( "%d\t:\t%.3fs\n",
				 mul,
				 times[ i ] );
	}
}

// Merge Sort method which returns time elapsed while sorting
double mergesort ( int a[ ], int n )
{
	CLOCK_START ( start );
	mergesort_worker ( a, 0, n );
	return TIME_ELAPSED ( start );
}

// Quick Sort method which returns time elapsed while sorting
double quicksort ( int a[ ], int n )
{
	CLOCK_START ( start );
	quicksort_worker ( a, 0, n );
	return TIME_ELAPSED ( start );
}

// Check if array is sorted
int verify ( int a[ ], int n )
{
	int i;
	LOOP ( i, n - 1 )
		if ( a[ i ] > a[ i + 1 ] )
			return 0;
	return 1;
}

void main ( )
{
	int *rand_collection, *a,
		check[ 5 ] = { 0 },		// To verify that the array is sorted
		i, n = 1;
	double
		bubble_times[ NUMDIGITS ],
		selection_times[ NUMDIGITS ],
		insertion_times[ NUMDIGITS ],
		merge_times[ NUMDIGITS ],
		quick_times[ NUMDIGITS ];
	M_ALLOCATE ( rand_collection, NUMELEMENTS );
	M_ALLOCATE ( a, NUMELEMENTS );
	srand ( (unsigned) clock ( ) );
	LOOP ( i, NUMELEMENTS )
		rand_collection[ i ] = rand ( ) % 1000;
	LOOP ( i, NUMDIGITS )
	{
		n = n * 10;
		memcpy ( a, rand_collection, n * sizeof ( int ) );
		bubble_times[ i ] = bubblesort ( a, n );
		if ( VERIFY )
			check[ 0 ] |= verify ( a, n );
		memcpy ( a, rand_collection, n * sizeof ( int ) );
		selection_times[ i ] = selectionsort ( a, n );
		if ( VERIFY )
			check[ 1 ] |= verify ( a, n );
		memcpy ( a, rand_collection, n * sizeof ( int ) );
		insertion_times[ i ] = insertionsort ( a, n );
		if ( VERIFY )
			check[ 2 ] |= verify ( a, n );
		memcpy ( a, rand_collection, n * sizeof ( int ) );
		merge_times[ i ] = mergesort ( a, n );
		if ( VERIFY )
			check[ 3 ] |= verify ( a, n );
		memcpy ( a, rand_collection, n * sizeof ( int ) );
		quick_times[ i ] = quicksort ( a, n );
		if ( VERIFY )
			check[ 4 ] |= verify ( a, n );
	}
	puts ( "Execution times for Bubble Sort:" );
	print_times ( bubble_times, NUMDIGITS );
	puts ( "Execution times for Selection Sort:" );
	print_times ( selection_times, NUMDIGITS );
	puts ( "Execution times for Insertion Sort:" );
	print_times ( insertion_times, NUMDIGITS );
	puts ( "Execution times for Merge Sort:" );
	print_times ( merge_times, NUMDIGITS );
	puts ( "Execution times for Quick Sort:" );
	print_times ( quick_times, NUMDIGITS );
	if ( VERIFY )
		LOOP ( i, 5 )
			PF ( "%d\t", check[ i ] );
	getchar ( );
}

