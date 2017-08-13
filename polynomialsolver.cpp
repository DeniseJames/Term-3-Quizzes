#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

vector<double> JMT(vector< double> start, vector <double> end, double T)
{
	/*
	Calculate the Jerk Minimizing Trajectory that connects the initial state
	to the final state in time T. 

	INPUTS

	start - the vehicles start location given as a length three array
	corresponding to initial values of [s, s_dot, s_double_dot]

	end   - the desired end state for vehicle. Like "start" this is a
	length three array corresponding to final values [final_s, final_s_dot, 
	final_s_double_dot]

	T     - The duration, in seconds, over which this maneuver should occur.
	*/
	double T2 = T*T;
	double T3 = T2*T;
	double T4 = T3*T;
	double T5 = T4*T;

	double s_int = start[0];
	double s_int_dot = start[1];
	double s_int_dot_dot = start[2];

	double s_final = end[0];
	double s_final_dot = end[1];
	double s_final_dot_dot = end[2];
	/*
|  T3     T4     T5 |     |alpha[3]|   | s_final - (s_int + s_int_dot*T + 1/2*s_int_dot_dot*T2 |
|                   |     |            |                                                       |
| 3*T2  4*T3   5*T4 |  X  |alpha[4]| = | s_final_dot -(s_int_dot + s_int_dot_dot*T )           |
|                   |     |        |   |                                                       |
| 6*T  12*T2  20*T3 |     |alpha[5]|   |  s_final_dot_dot - s_init_dot_dot
	

	OUTPUT
	an array of length 6, each value corresponding to a coefficent in the polynomial
	s(t) = a_0 + a_1 * t + a_2 * t**2 + a_3 * t**3 + a_4 * t**4 + a_5 * t**5

	[alpha[0], alpha[1], alpha[2] = [s, s_dot, s_double_dot] setting T = 0

	EXAMPLE

	> JMT( [0, 10, 0], [10, 10, 0], 1)
	[0.0, 10.0, 0.0, 0.0, 0.0, 0.0]
	*/
	MatrixXd A(3, 3);
	VectorXd b(3);
	VectorXd x(3);

	A << T3, T4, T5,
		3 * T2, 4 * T3, 5 * T4,
		6 * T, 12 * T2, 20 * T3;

	b << s_final - (s_int + s_int_dot*T + s_int_dot_dot*T2/2.0),
		s_final_dot - (s_int_dot + s_int_dot_dot*T),
		s_final_dot_dot - s_int_dot_dot;

	x = A.colPivHouseholderQr().solve(b);

	std::vector<double> alpha;
	alpha.resize(6);

	// by setting t=0 the following are determined
	alpha[0] = s_int;
	alpha[1] = s_int_dot;
	alpha[2] = s_int_dot_dot/2.0;
	alpha[3] = x[0];
	alpha[4] = x[1];
	alpha[5] = x[2];

	return alpha;

}

bool close_enough(vector< double > poly, vector<double> target_poly, double eps = 0.01) {


	if (poly.size() != target_poly.size())
	{
		cout << "your solution didn't have the correct number of terms" << endl;
		return false;
	}
	for (int i = 0; i < poly.size(); i++)
	{
		double diff = poly[i] - target_poly[i];
		if (abs(diff) > eps)
		{
			cout << "at least one of your terms differed from target by more than " << eps << endl;
			return false;
		}

	}
	return true;
}

struct test_case {

	vector<double> start;
	vector<double> end;
	double T;
};

vector< vector<double> > answers = { { 0.0, 10.0, 0.0, 0.0, 0.0, 0.0 },{ 0.0,10.0,0.0,0.0,-0.625,0.3125 },{ 5.0,10.0,1.0,-3.0,0.64,-0.0432 } };

int main() {

	//create test cases

	vector< test_case > tc;

	test_case tc1;
	tc1.start = { 0,10,0 };
	tc1.end = { 10,10,0 };
	tc1.T = 1;
	tc.push_back(tc1);

	test_case tc2;
	tc2.start = { 0,10,0 };
	tc2.end = { 20,15,20 };
	tc2.T = 2;
	tc.push_back(tc2);

	test_case tc3;
	tc3.start = { 5,10,2 };
	tc3.end = { -30,-20,-4 };
	tc3.T = 5;
	tc.push_back(tc3);

	bool total_correct = true;
	for (int i = 0; i < tc.size(); i++)
	{
		vector< double > jmt = JMT(tc[i].start, tc[i].end, tc[i].T);
		bool correct = close_enough(jmt, answers[i]);
		total_correct &= correct;

	}
	if (!total_correct)
	{
		cout << "Try again!" << endl;
	}
	else
	{
		cout << "Nice work!" << endl;
	}

	return 0;
}