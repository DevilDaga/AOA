#include "../common/common.h"

#define SIZE	4U

typedef enum
{
	RESERVE	=	0,
	UP		=	1,
	DOWN	=	2,
	LEFT	=	3,
	RIGHT	=	4
}DIRECTION;

typedef struct node_s
{
	struct node_s *parent;
	int **grid, x, y;
	int cost;
}node;

node *make_node ( int **grid, int x, int y, int cost, node *p )
{
	node *result;
	M_ALLOCATE ( result, 1 );
	result->grid = grid;
	result->cost = cost;
	result->x = x;
	result->y = y;
	result->parent = p;
	return result;
}

#define PARENT(x)		((size_t)((x) / 2))
#define LCHILD(x)		(2 * (x))
#define RCHILD(x)		(2 * (x) + 1)

void min_heapify ( node **heap, size_t i, size_t n )
{
	size_t l = LCHILD ( i ),
		r = RCHILD ( i ),
		largest;
	if ( l < n && heap[ l ]->cost < heap[ i ]->cost )
		largest = l;
	else
		largest = i;
	if ( r < n && heap[ r ]->cost < heap[ largest ]->cost )
		largest = r;
	if ( largest != i )
	{
		swap ( heap + i, heap + largest, sizeof *heap );
		min_heapify ( heap, largest, n );
	}
}

void insert ( node **heap, size_t n, node *ele )
{
	heap[ n ] = ele;
	while ( heap[ n ]->cost > heap[ PARENT ( n ) ]->cost )
	{
		swap ( heap + n, heap + PARENT ( n ), sizeof *heap );
		n = PARENT ( n );
	}
}

node *extract ( node **heap, size_t n )
{
	node *result = heap[ 0 ];
	heap[ 0 ] = heap[ n - 1 ];
	min_heapify ( heap, 0, n - 1 );
	return result;
}

int manhattan ( int **grid, int x_blank, int y_blank )
{
	int result = 0, i, j;
	LOOP ( i, SIZE )
	{
		LOOP ( j, SIZE )
		{
			int x, y;
			x = ( grid[ i ][ j ] - 1 ) / SIZE;
			y = ( grid[ i ][ j ] - 1 ) % SIZE;
			result += mod ( x - i ) + mod ( y - j );
		}
	}
	i = grid[ x_blank ][ y_blank ] - 1;
	j = i % SIZE;
	i = i / SIZE;
	result -= ( mod ( x_blank - i ) + mod ( y_blank - j ) );
	return result;
}

int **move ( int **grid, int *x_blank, int *y_blank, DIRECTION dir )
{
	int **result, x, y, i;
	M_ALLOCATE ( result, SIZE );
	LOOP ( i, SIZE )
	{
		C_ALLOCATE ( result[ i ], SIZE );
		memcpy ( result[ i ], grid[ i ], SIZE * sizeof **grid );
	}
	switch ( dir )
	{
		case UP:
			if ( *x_blank == 0 )
				return NULL;
			x = *x_blank - 1;
			y = *y_blank;
			break;
		case DOWN:
			if ( *x_blank == SIZE - 1 )
				return NULL;
			x = *x_blank + 1;
			y = *y_blank;
			break;
		case LEFT:
			if ( *y_blank == 0 )
				return NULL;
			x = *x_blank;
			y = *y_blank - 1;
			break;
		case RIGHT:
			if ( *y_blank == SIZE - 1 )
				return NULL;
			x = *x_blank;
			y = *y_blank + 1;
			break;
	}
	swap ( &result[ x ][ y ], &result[ *x_blank ][ *y_blank ],
		   sizeof **grid );
	*x_blank = x;
	*y_blank = y;
	return result;
}

node *solve ( int **grid, int x_blank, int y_blank )
{
	size_t k = 0, top = 0;
	node **heap, *T;
	M_ALLOCATE ( heap, 1024 );
	M_ALLOCATE ( T, 1 );
	T = make_node ( grid, x_blank, y_blank,
					manhattan ( grid, x_blank, y_blank ),
					NULL );
	if ( T->cost == 0 )
		return T;
	insert ( heap, k++, T );
	while ( 1 )
	{
		int i;
		node *E = extract ( heap, k-- );
		for ( i = 1; i != 5; ++i )
		{
			node *X;
			int x = E->x, y = E->y;
			int **child = move ( E->grid, &x, &y, i );
			int cost;
			if ( !child )
				continue;
			C_ALLOCATE ( X, 1 );
			cost = manhattan ( child, x, y );
			X = make_node ( grid, x, y, cost, E );
			if ( cost == 0 )
				return X;		// Solution found
			insert ( heap, k++, X );
		}
	}
	return NULL;
}

void main ( )
{
	int **grid, x = 0, y = 0, i, j;
	M_ALLOCATE ( grid, SIZE );
	blank_graph ( grid, SIZE );
	puts ( "Enter the grid (0 for blank tile):" );
	LOOP ( i, SIZE )
	{
		LOOP ( j, SIZE )
		{
			SCANI ( grid[ i ][ j ] );
			if ( grid[ i ][ j ] == 0 )
			{
				x = i;
				y = j;
			}
		}
	}
	solve ( grid, x, y );
	getchar ( );
	getchar ( );
}