#include "../common/common.h"

#define	SIZE		4

typedef enum
{
	RESERVE,
	UP,
	DOWN,
	LEFT,
	RIGHT
}DIRECTION;

int manhattan ( int grid[ SIZE ][ SIZE ],
				int x_blank, int y_blank )
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

int **move ( int grid[ SIZE ][ SIZE ],
			 int x_blank, int y_blank, DIRECTION dir )
{
	int result[ SIZE ][ SIZE ], x, y;
	memcpy ( result, grid, sizeof grid );
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

DIRECTION *solve ( int grid[ SIZE ][ SIZE ],
				   int x_blank, int y_blank )
{

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