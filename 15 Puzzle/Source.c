#include "../common/common.h"

#define	SIZE		4U

typedef enum
{
	RESERVE	=	0,
	UP,
	DOWN,
	LEFT,
	RIGHT
}DIRECTION;

typedef struct
{
	int **grid;
	int cost;
}node;

#define PARENT(x)		((size_t)((x) / 2))
#define LCHILD(x)		(2 * (x))
#define RCHILD(x)		(2 * (x) + 1)

void min_heapify ( node *heap, size_t i, size_t n )
{
	size_t l = LCHILD ( i ),
		r = RCHILD ( i ),
		largest;
	if ( l < n && heap[ l ].cost < heap[ i ].cost )
		largest = l;
	else
		largest = i;
	if ( r < n && heap[ r ].cost < heap[ largest ].cost )
		largest = r;
	if ( largest != i )
	{
		swap ( heap + i, heap + largest, sizeof *heap );
		min_heapify ( heap, largest, n );
	}
}

void insert ( node *heap, size_t n, node ele )
{
	heap[ n ] = ele;
	while ( heap[ n ].cost > heap[ PARENT ( n ) ].cost )
	{
		swap ( heap + n, heap + PARENT ( n ), sizeof *heap );
		n = PARENT ( n );
	}
}

node extract ( node *heap, size_t n )
{
	node result = heap[ 0 ];
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

int **move ( int **grid, int x_blank, int y_blank, DIRECTION dir )
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
			x = x_blank;
			y = ( y_blank + SIZE - 1 ) % SIZE;
			break;
		case DOWN:
			x = x_blank;
			y = ( y_blank + SIZE + 1 ) % SIZE;
			break;
		case LEFT:
			x = ( x_blank + SIZE - 1 ) % SIZE;
			y = y_blank;
			break;
		case RIGHT:
			x = ( x_blank + SIZE + 1 ) % SIZE;
			y = y_blank;
			break;
	}
	swap ( &result[ x ][ y ], &result[ x_blank ][ y_blank ],
		   sizeof **grid );
	return result;
}

DIRECTION *solve ( int **grid, int x_blank, int y_blank )
{
	size_t k = 0, top = 0;
	DIRECTION *result;
	int ***stack;
	M_ALLOCATE ( stack, 1024 );
	C_ALLOCATE ( result, 256 );
	stack[ top++ ] = grid;
	return result;
}

void main ( )
{
	int grid[ SIZE ][ SIZE ] = { 0 },
		x = 0, y = 0, i, j;
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
}