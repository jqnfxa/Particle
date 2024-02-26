#ifndef TIME_H
#define TIME_H

#include <stddef.h>


struct time
{
	double total_time;
	double dt;
	size_t time_step;
};

#endif // TIME_H
