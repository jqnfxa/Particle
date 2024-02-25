#include <stdlib.h>
#include "tableau.h"


bool RK4_classic(struct butcher_tableau *tableau)
{
	if (tableau == NULL || !create_butcher_tableau(tableau, 4))
	{
		return false;
	}

	tableau->a[1][0] = 0.5;
	tableau->a[2][1] = 0.5;
	tableau->a[3][2] = 1.0;

	tableau->b[0] = 1.0 / 6.0;
	tableau->b[1] = 1.0 / 3.0;
	tableau->b[2] = 1.0 / 3.0;
	tableau->b[3] = 1.0 / 6.0;

	return true;
}


bool create_butcher_tableau(struct butcher_tableau *tableau, size_t order)
{
	if (tableau == NULL || order == 0)
	{
		return false;
	}

	// TODO: use memset instead?
	tableau->s = order;
	tableau->a = NULL;
	tableau->b = NULL;


	// attempt to allocate space for b coefficients
	tableau->b = (double *)malloc(sizeof(double) * tableau->s);
	if (tableau->b == NULL)
	{
		destroy_tableau(tableau);
		return false;
	}


	// attempt to allocate space for a coefficients
	tableau->a = (double **)calloc(tableau->s, sizeof(double *));
	if (tableau->a == NULL)
	{
		destroy_tableau(tableau);
		return false;
	}


	// attempt to allocate space for a[i] row
	for (size_t row = 1; row < tableau->s; ++row)
	{
		tableau->a[row] = (double *)calloc(row, sizeof(double));
	}

	if (tableau->a[tableau->s - 1] == NULL)
	{
		destroy_tableau(tableau);
		return false;
	}

	return true;
}


void destroy_tableau(struct butcher_tableau *tableau)
{
	if (tableau == NULL)
	{
		return;
	}

	if (tableau->a != NULL)
	{
		for (size_t i = 1; i < tableau->s; ++i)
		{
			free(tableau->a[i]);
		}
	}

	free(tableau->a);
	free(tableau->b);

	tableau->s = 0;
	tableau->a = NULL;
	tableau->b = NULL;
}
