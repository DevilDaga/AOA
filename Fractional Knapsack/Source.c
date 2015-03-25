#include "../common/common.h"

typedef struct
{
	size_t profit, cost;
	char *name;
	float fraction;
}item_t;

int compare ( const void *x, const void *y )
{
	item_t *ix = (item_t*) x,
		*iy = (item_t*) y;
	return (int) ( ( 1. * iy->profit / iy->cost ) -
				   ( 1. * ix->profit / ix->cost ) );
}

void main ( )
{
	size_t cap, n, i, j, profit = 0;
	item_t *items, *knapsack;
	PF ( "Enter the capacity of knapsack:\t" );
	SF ( "%d", &cap );
	PF ( "Enter the number of items:\t" );
	SF ( "%d", &n );
	PF ( "Enter the name, profit and cost for %d items:\n", n );
	M_ALLOCATE ( items, n );
	M_ALLOCATE ( knapsack, n );
	LOOP ( i, n )
	{
		items[ i ].name = (char*) malloc ( 64 );
		items[ i ].fraction = 1.0f;
		SF ( "%s %d %d", items[ i ].name, &items[ i ].profit, &items[ i ].cost );
	}
	qsort ( items, n, sizeof *items, &compare );
	i = j = 0;
	while ( cap && i != n )
	{
		if ( cap > items[ i ].cost )
		{
			cap -= items[ i ].cost;
			knapsack[ j++ ] = items[ i++ ];
		}
		else
		{
			item_t *fractional;
			M_ALLOCATE ( fractional, 1 );
			fractional->name = items[ i ].name;
			fractional->cost = cap;
			fractional->fraction = (float) ( 1. * cap / items[ i ].cost );
			fractional->profit = (size_t) ( fractional->fraction * items[ i ].profit );
			knapsack[ j++ ] = *fractional;
			cap = 0;
		}
	}
	cap = 0;
	puts ( "Number  Name    Fraction   Cost   Profit   Capacity   Total Profit" );
	LOOP ( i, j )
		PF ( "%-3d:    %-6s   %1.3f    %4d    %4d     %4d         %4d\n",
			i + 1,
			knapsack[ i ].name,
			knapsack[ i ].fraction,
			knapsack[ i ].cost,
			knapsack[ i ].profit,
			cap += knapsack[ i ].cost,
			profit += knapsack[ i ].profit
			);
	getchar ( );
}