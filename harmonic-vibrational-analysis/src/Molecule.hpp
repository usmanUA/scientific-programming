

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"
#include "../Eigen/Core"
using namespace std;

typedef	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix;

inline	double	atomic_mass[] = {
	0.000000,
	1.007825,
	4.002603,  
	6.015123,
	9.012183,
	11.009305,
	12.000000,
	14.003074,
	15.994914,
	18.998403,
	19.992440,
	22.989769,
};

class	Molecule
{
	public:
		Molecule(string filename, int q);
		~Molecule();

	// NOTE: Attributes of a molecule
		int	natoms;
		int	charge;
		vector<int>	zvals;
		vector<vector<double> >	geom;
		string	point_group;
		double	**H;
		Matrix	eigenvals;

	// NOTE: Molecule members
		void	print_geom();
		void	save_hessian( const char *filename );
		void	mass_weight_hessian( void );
		void	diagonalize_mw_hessian( void );
		void	harmonic_vibrational_frequencies( void );
};
