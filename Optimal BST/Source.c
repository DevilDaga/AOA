#include "../common/common.h"

typedef struct
{
	int key;
	float cost;
}item_t;

int compare ( const void *x, const void *y )
{
	return ( ( (item_t*) x )->key - ( (item_t*) y )->key );
}

void sort_keys ( int *keys, float *freq, size_t n )
{
	size_t i;
	item_t *items = malloc ( n * sizeof *items );
	LOOP ( i, n )
	{
		items[ i ].key = keys[ i ];
		items[ i ].cost = freq[ i ];
	}
	qsort ( items, n, sizeof *items, &compare );
	LOOP ( i, n )
	{
		keys[ i ] = items[ i ].key;
		freq[ i ] = items[ i ].cost;
	}
}

typedef struct node_s
{
	struct node_s *left, *right;
	int key;
}node;

node *create_node ( int key )
{
	node *result;
	C_ALLOCATE ( result, 1 );
	result->key = key;
	return result;
}

node *construct_obst ( int **roots, int*keys, size_t left, size_t right )
{
	size_t index_root = roots[ left ][ right ];
	node *root;
	if ( left == right )
		return create_node ( keys[ left ] );
	root = create_node ( keys[ index_root ] );
	if ( index_root != left )
		root->left = construct_obst ( roots, keys, left, index_root - 1 );
	if ( index_root != right )
		root->right = construct_obst ( roots, keys, index_root + 1, right );
	return root;
}

void print_bst ( node *head, size_t n )
{
	node **M_ALLOCATE ( q, n );
	size_t i = 0, size = 0;
#define PUSHBACK(x)		q[ size++ ] = (x)
	PF ( "The root is:\t%d\n", head->key );
	PUSHBACK ( head );
	while ( i != n )
	{
		node *cur = q[ i++ ];
		if ( cur->left )
		{
			PF ( "%-4d left->\t%d\n", cur->key, cur->left->key );
			PUSHBACK ( cur->left );
		}
		if ( cur->right )
		{
			PF ( "%-4d right->\t%d\n", cur->key, cur->right->key );
			PUSHBACK ( cur->right );
		}
	}
}

node *build_table ( float **table, int *keys, float *freq, size_t n, float *cost )
{
	size_t l, i, j, r;
	float **M_ALLOCATE ( w, n );
	int **M_ALLOCATE ( roots, n );
	LOOP ( i, n )
	{
		w[ i ] = calloc ( n, sizeof **w );
		roots[ i ] = calloc ( n, sizeof **roots );
		w[ i ][ i ] = table[ i ][ i ] = freq[ i ];
	}
	for ( l = 1; l != n; ++l )
	{
		LOOP ( i, n - l )
		{
			int root = 0;
			j = i + l;
			table[ i ][ j ] = 3.4e37f;
			w[ i ][ j ] = w[ i ][ j - 1 ] + freq[ j ];
			for ( r = i; r != j + 1; ++r )
			{
				float r_cost =
					( ( r != 0 ) ? table[ i ][ r - 1 ] : 0 ) +
					table[ r + 1 ][ j ] +
					w[ i ][ j ];
				if ( r_cost < table[ i ][ j ] )
				{
					table[ i ][ j ] = r_cost;
					root = r;
				}
			}
			roots[ i ][ j ] = root;
		}
	}
	*cost = table[ 0 ][ n - 1 ];
	return construct_obst ( roots, keys, 0, n - 1 );
}

node *make_obst ( int *keys, float *freq, size_t n, float *cost )
{
	size_t i;
	float **M_ALLOCATE ( table, n + 1 );
	LOOP ( i, n + 1 )
		table[ i ] = calloc ( n, sizeof **table );
	return build_table ( table, keys, freq, n, cost );
}

void main ( )
{
	size_t i, n;
	int *keys, sum = 0;
	float *p, cost;
	node *head;
	PF ( "Enter the number of keys:\t" );
	SCANI ( n );
	M_ALLOCATE ( keys, n );
	M_ALLOCATE ( p, n );
	puts ( "Enter the keys and costs:" );
	LOOP ( i, n )
		SF ( "%d %f", &keys[ i ], &p[ i ] );
	sort_keys ( keys, p, n );
	head = make_obst ( keys, p, n, &cost );
	PF ( "Optimal cost:\t%-5.2f\n", cost );
	print_bst ( head, n );
	getchar ( );
}