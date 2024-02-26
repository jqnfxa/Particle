#include <stdio.h>
#include <stdlib.h>
#include "io.h"


bool load_simulation_parameters(struct system_state *state, const char *filename)
{
	if (state == NULL || filename == NULL)
	{
		return false;
	}

	FILE *file = NULL;

	// open the file
	if ((file = fopen(filename, "r")) == NULL)
	{
		perror("Error: cannot open file\n");
		return false;
	}


	// read vector E
	if (fscanf(file, "%lf %lf %lf", &state->E.x, &state->E.y, &state->E.z) != 3)
	{
		perror("Error: failed to read vector E\n");
		fclose(file);
		return false;
	}


	// read vector B
	if (fscanf(file, "%lf %lf %lf", &state->B.x, &state->B.y, &state->B.z) != 3)
	{
		perror("Error: failed to read vector B\n");
		fclose(file);
		return false;
	}


	// read vector r
	if (fscanf(file, "%lf %lf %lf", &state->particle.r.x, &state->particle.r.y, &state->particle.r.z) != 3)
	{
		perror("Error: failed to read vector r\n");
		fclose(file);
		return false;
	}


	// read vector v
	if (fscanf(file, "%lf %lf %lf", &state->particle.v.x, &state->particle.v.y, &state->particle.v.z) != 3)
	{
		perror("Error: failed to read vector v\n");
		fclose(file);
		return false;
	}


	// read q
	if (fscanf(file, "%lf", &state->particle.q) != 1)
	{
		perror("Error: failed to read q\n");
		fclose(file);
		return false;
	}


	// read m
	if (fscanf(file, "%lf", &state->particle.m) != 1)
	{
		perror("Error: failed to read m\n");
		fclose(file);
		return false;
	}


	// read total simulation time
	if (fscanf(file, "%lf", &state->time.total_time) != 1)
	{
		perror("Error: failed to read total time\n");
		fclose(file);
		return false;
	}


	// read time step
	if (fscanf(file, "%lf", &state->time.dt) !=  1)
	{
		perror("Error: failed to read time step\n");
		fclose(file);
		return false;
	}


	// close the file
	fclose(file);
	return true;
}


bool unload_data(struct vector3D *r, struct vector3D *v, const char *filename, double dt)
{
	if (r == NULL || v == NULL || filename == NULL)
	{
		return false;
	}

	FILE *file = NULL;
	int written_size = 0;


	// open the file to write
	if ((file = fopen(filename, "w")) == NULL)
	{
		perror("Error: cannot open file\n");
		return false;
	}


	// dump data
	size_t len = dynarray_length(r);
	double cur = 0;

	for (size_t i = 0; i < len; ++i, cur += dt)
	{
		written_size = fprintf(file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", cur, r[i].x, r[i].y, r[i].z, v[i].x, v[i].y, v[i].z);

		if (written_size < 0)
		{
			perror("Error: failed to write data to\n");
			fclose(file);
			return false;
		}
	}

	fclose(file);
	return true;
}
