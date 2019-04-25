#include "ft_header.h"

void	xyz_string_to_double(std::string string, double *x, double *y, double *z)
{

	std::string buff;
	int i(0);

	while (string[i] != '\0')
	{
		if (string[i] == 'X')
		{
			i++;
			while (string[i] != ' ' && string[i] != '\0')
			{
				buff = buff + string[i];
				i++;
			}
			*x = stod(buff);
			buff = "";
		}
		else if (string[i] == 'Y')
		{
			i++;
			while (string[i] != ' ' && string[i] != '\0')
			{
				buff = buff + string[i];
				i++;
			}
			*y = stod(buff);
			buff = "";
		}
		else if (string[i] == 'Z')
		{
			i++;
			while (string[i] != ' ' && string[i] != '\0')
			{
				buff = buff + string[i];
				i++;
			}
			*z = stod(buff);
			buff = "";
		}
		else
			i++;
	}
}

double	*XYZ_string_to_double(std::string string, double *x, double *y, double *z, double *result, double all_pogr[6])
{

	std::string buff;
	double buff_number;
	double *all_pogr_temp;
	int i(0), j(0);

	all_pogr_temp = (double*)malloc(sizeof(double) * 6);
	if (string != "")
	{
		while (j < 6)
		{
			while (string[i] != '\t' && string[i] != ' ' && string[i] != '\0')
			{
				buff = buff + string[i];
				i++;
			}
			all_pogr_temp[j] = stod(buff);
			buff = "";
			i++;
			j++;
		}
		buff_number = sqrt((pow((all_pogr_temp[0] - *x), 2)) + (pow((all_pogr_temp[1] - *y), 2)) + (pow((all_pogr_temp[2] - *z), 2)));
		if (buff_number < *result)
		{
			*result = buff_number;
			return(all_pogr_temp);
			free(all_pogr_temp);
		}
		else
		{
			return(all_pogr);
			free(all_pogr_temp);
		}
	}
}

void	parsing(double *x, double *y, double *z)
{
	std::string string;
	std::ifstream fpogr("pogr.txt");
	int i(0);
	double *all_pogr;
	double result(100000000);
	
	all_pogr = (double*)malloc(sizeof(double) * 6);
	std::getline(fpogr, string);
	while (!fpogr.eof())
	{
		std::getline(fpogr, string);
		std::cout << string << std::endl;
		i = 0;
		while (string[i] != '\0')
		{
			if (string[i] == ',')
				string[i] = '.';
			i++;
		}
		all_pogr = XYZ_string_to_double(string, x, y, z, &result, all_pogr);
	}
	fpogr.close();
	*x = *x - all_pogr[3];
	*y = *y - all_pogr[4];
	*z = *z - all_pogr[5];
	free(all_pogr);
}

int		main(void) 
{

	std::string string;
	std::ifstream fchpu("chpu.txt");
	std::ofstream fout("NewFile.txt");
	double x(0), y(0), z(0);


	while (!fchpu.eof())
	{
		std::getline(fchpu, string);
		if (string[0] == 'G' && string[1] == '9' && string[2] == '1')
		{
			x = 0;
			y = 0;
			z = 0;
			xyz_string_to_double(string, &x, &y, &z);
			parsing(&x, &y, &z);
			if (x != 0 && y != 0 && z != 0)
				fout << "G91 X" << x << " Y" << y << " Z" << z << std::endl;
			else if (y == 0 && z == 0)
				fout << "G91 X" << x << std::endl;
				else if (x == 0 && y == 0)
					fout << "G91 Z" << z << std::endl;
					else if (z == 0 && x == 0)
						fout << "G91 Y" << y << std::endl;
						else if (x == 0)
							fout << "G91 Y" << y << " Z" << z << std::endl;
							else if (y == 0)
								fout << "G91 X" << x << " Z" << z << std::endl;
								else if (z == 0)
									fout << "G91 X" << x << " Y" << y << std::endl;
		}
		else
			fout << string << std::endl;	
	}
	fchpu.close();
	fout.close();
	return (0);
}