#pragma once

#include <vector>
#include <set>
#include "Matrix.h"
#include "MatrixBand.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#ifndef tfloat
#define tfloat double
#endif

using std::vector;

class TopOpt {
public:
    // nelx, nely = number of elements in x and y direction 
    // volfract = volume fraction
    // penal = penalization value
    // rmin = filter radius
    TopOpt(int nelx, int nely, tfloat volfrac, tfloat penal, tfloat rmin, tfloat maxChange = 0.01);
	~TopOpt();

	bool loop(float& compliance, float& volume, float& change);
	const Eigen::MatrixXd& getMatrix()const{ return x; }
	tfloat vTransposeMultMMultV(Eigen::MatrixXd m, tfloat *v);

private:
	int mIter;
	tfloat mMaxChange;
	tfloat mChange;
	Eigen::MatrixXd  xold;
	tfloat mCurCompliance;
	tfloat mCurVolume;
private:
    void FEAnalysis();
    void initKE();
    void meshIndependencyFilter(); // Also known as check
    void optimalityCriteriaBasedOptimization();  // Also known as OC
    vector<int> setDiff(vector<int> &set1, vector<int> &set2);
    void initFreeDofs();
    void defineLoads();
    void calculatePassive();
    void exportResultMatlab(Matrix *x, int iteration);
	void exportResultTxt(Matrix *x, int iteration);
private:

    tfloat objectiveFunctionAndSensitivityAnalyses();
    tfloat interpolate(int x, int y);
    tfloat interpolateDiff(int x, int y);
    int nelx; // number of element along x-axis
    int nely; // number of element along y-axis
    tfloat volfrac; // volume fraction
    tfloat penal;
    tfloat rmin;
	Eigen::MatrixXd x;
	Eigen::MatrixXd xNew;

	Eigen::VectorXd U;

	Eigen::MatrixXd KE; // stiffness matrix
	Eigen::MatrixXd dc;
	Eigen::MatrixXd dcNew;
	Eigen::SparseMatrix<double> K;
	//Eigen::MatrixXd K;
    //MatrixBand K;
    vector<int> passiveNoMaterial;
    vector<int> fixeddofs;
    vector<int> freedofs;
	Eigen::VectorXd F;
	//tfloat *F;
};