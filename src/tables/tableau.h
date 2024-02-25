#ifndef TABLEAU_H
#define TABLEAU_H

#include <stddef.h>
#include <stdbool.h>


struct butcher_tableau
{
	double **a;
	double *b;

	// number of steps
	size_t s;
};

bool RK4_classic(struct butcher_tableau *tableau);
bool create_butcher_tableau(struct butcher_tableau *tableau, size_t order);
void destroy_tableau(struct butcher_tableau *tableau);


#endif // TABLEAU_H
