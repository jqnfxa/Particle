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


/**
 * @brief creates butcher tableau for given order
 * @param tableau output structure
 * @param order order of tableau
 * @return `true` if tableau successfully created and `false` otherwise
 */
bool create_butcher_tableau(struct butcher_tableau *tableau, size_t order);


/**
 * @brief clean up allocated memory
 * @param tableau tableau to clean
 */
void destroy_tableau(struct butcher_tableau *tableau);


#endif // TABLEAU_H
