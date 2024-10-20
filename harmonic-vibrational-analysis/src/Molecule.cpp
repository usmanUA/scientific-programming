
#include "Molecule.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

Molecule::Molecule(string filename, int q)
{
	this->charge = q;
	ifstream	input(filename);

	assert(input.good());
	input >> this->natoms;
	cout << "Number of atoms: " << this->natoms << endl;
	this->geom.resize(this->natoms, vector<double>(3));
	this->zvals.resize(this->natoms);
	for (int i = 0; i < this->natoms; i++)
	{
		input >> this->zvals[i] >> this->geom[i][0] >> this->geom[i][1] >> this->geom[i][2];
	}
	input.close();
}

Molecule::~Molecule()
{
	for (int i = 0; i < natoms*3; i++) {
		delete []this->H[i];
	}
	delete this->H;
}

void	Molecule::print_geom()
{
	cout << this->natoms << endl;
	for (unsigned int i = 0; i < this->natoms; i++)
	{
		printf("%d %20.12f %20.12f %20.12f\n", zvals[i], geom[i][0], geom[i][1], geom[i][2]);
	}
}

void	Molecule::save_hessian( char *filename )
{
	this->H = new double* [natoms*3];
	FILE	*file;
//"../input/h2o_hessian.txt"
	file = fopen(filename, "r");
	if (!file) {
		perror("Could not open the file\n");
		exit(1);
	}
	for (int i = 0; i < natoms*3; i++) {
		this->H[i] = new double [natoms*3];
	}
	for (int i = 0; i < natoms*3; i++) {
		for (int j = 0; j < natoms; j++) {
			if (fscanf(file, "%lf %lf %lf", &this->H[i][3*j], &this->H[i][3*j+1], &this->H[i][3*j+2]) != 3) {
				cout << " Something wrong with the file\n";
				fclose(file);
				exit(1);
			};
		}
	}
	fclose(file);
}

void	Molecule::mass_weight_hessian( void )
{
	cout << endl;
	cout << "\t ";
	for (int i = 0; i < natoms*3; i++) {
		printf("%d\t      ", i+1);
	}
	printf("\n\n");
	int i_atom, j_atom;
	for (int i = 0; i < natoms*3; i++) {
		printf("%d\t ", i+1);
		i_atom = i/3;
		for (int j = 0; j < natoms*3; j++) {
			j_atom = j/3;
			this->H[i][j] /= sqrt(atomic_mass[zvals[i_atom]]*atomic_mass[zvals[j_atom]]);
			printf("%10.7f  ", this->H[i][j]);
		}
		printf("\n\n");
	}
}

void	Molecule::diagonalize_mw_hessian( void )
{
	cout << endl;
	Matrix	I(9,9);
	
	for (int i = 0; i < natoms*3; i++) {
		for (int j = 0; j < natoms*3; j++) {
			I(i,j) = H[i][j];
		}
	}
	Eigen::SelfAdjointEigenSolver<Matrix> solver(I);
	Matrix eigenvecs = solver.eigenvectors();
	Matrix eigenvals = solver.eigenvalues();
	cout << eigenvals << endl;
}

void	Molecule::harmonic_vibrational_frequencies( void )
{

}

