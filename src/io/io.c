#include <stdio.h>
#include <stdlib.h>
#include "io.h"


bool read_vector3D(struct vector3D *dst, FILE *file)
{
	if (dst == NULL || file == NULL)
	{
		return false;
	}

	return fscanf(file, "%lf %lf %lf", &dst->x, &dst->y, &dst->z) == 3;
}


bool load_simulation_parameters(struct system_state *state, const char *filename)
{
	if (state == NULL)
	{
		return false;
	}


	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Error: cannot open file\n");
		return false;
	}

	// read vector E
	if (!read_vector3D(&state->E, file))
	{
		perror("Error: failed to read vector E\n");
		fclose(file);
		return false;
	}

	// read vector B
	if (!read_vector3D(&state->B, file))
	{
		perror("Error: failed to read vector B\n");
		fclose(file);
		return false;
	}

	// read vector r
	if (!read_vector3D(&state->particle.r, file))
	{
		perror("Error: failed to read vector r\n");
		fclose(file);
		return false;
	}

	// read vector v
	if (!read_vector3D(&state->particle.v, file))
	{
		perror("Error: failed to read vector v\n");
		fclose(file);
		return false;
	}

	// read q and m
	if (fscanf(file, "%lf %lf", &state->particle.q, &state->particle.m) != 2)
	{
		perror("Error: failed to read q and m\n");
		fclose(file);
		return false;
	}

	// read time structure
	if (fscanf(file, "%lf %lf %zu", &state->time.total_time, &state->time.dt, &state->time.time_step) != 3)
	{
		perror("Error: failed to read time\n");
		fclose(file);
		return false;
	}

	// close the file
	fclose(file);

	return true;
}


bool load_butcher_tableau(struct butcher_tableau *tableau, const char *filename)
{
	if (tableau == NULL)
	{
		return false;
	}


	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Error: cannot open file\n");
		return false;
	}

	// Read the order of the method
	if (fscanf(file, "%zu", &tableau->s) != 1)
	{
		fclose(file);
		return false;
	}

	if (!create_butcher_tableau(tableau, tableau->s))
	{
		perror("Error: failed to allocate memory for tableau\n");
		fclose(file);
		return false;
	}

	// Read the 'a' coefficients
	for (size_t i = 1; i < tableau->s; ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			if (fscanf(file, "%lf", &tableau->a[i][j]) != 1)
			{
				destroy_tableau(tableau);
				fclose(file);
				return false;
			}
		}
	}

	// Read the 'b' coefficients
	for (size_t i = 0; i < tableau->s; ++i)
	{
		if (fscanf(file, "%lf", &tableau->b[i]) != 1)
		{
			destroy_tableau(tableau);
			fclose(file);
			return false;
		}
	}

	fclose(file);
	return true;
}


bool setup_simulation(struct system_state *state, const char *input, const char *table)
{
	if (!load_simulation_parameters(state, input))
	{
		return false;
	}

	if (!load_butcher_tableau(&state->tableau, table))
	{
		return false;
	}

	return true;
}


bool unload_data(struct time *time, struct vector3D *r, struct vector3D *v, const char *filename)
{
	if (time == NULL || r == NULL || v == NULL || filename == NULL)
	{
		return false;
	}

	// open the file to write
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		perror("Error: cannot open file\n");
		return false;
	}


	// dump data
	size_t len = dynarray_length(r);
	int written_size = 0;
	double current_time = 0;

	for (size_t i = 0; i < len; ++i, current_time += time->dt * time->time_step)
	{
		written_size = fprintf(file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", current_time, r[i].x, r[i].y, r[i].z, v[i].x, v[i].y, v[i].z);

		if (written_size < 0)
		{
			perror("Error: failed to write data\n");
			fclose(file);
			return false;
		}
	}

	fclose(file);
	return true;
}
