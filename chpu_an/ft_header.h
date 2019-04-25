#pragma once

#ifndef FT_HEADER
# define FT_HEADER

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
void	parsing					(double *x, double *y, double *z);
void	xyz_string_to_double	(std::string string, double *x, double *y, double *z);
double	*XYZ_string_to_double	(std::string string, double *x, double *y, double *z, double *result, double all_pogr[6]);

#endif FT_HEADER