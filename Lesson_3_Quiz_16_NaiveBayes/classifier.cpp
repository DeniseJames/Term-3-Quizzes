#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "classifier.h"
#include <cassert>
#include <cmath>

/**
* Initializes GNB
*/
GNB::GNB() {

}

GNB::~GNB() {}

void GNB::train(vector<vector<double>> data, vector<string> labels)
{

	/*
	Trains the classifier with N data points and labels.

	INPUTS
	data - array of N observations
	- Each observation is a tuple with 4 values: s, d,
	s_dot and d_dot.
	- Example : [
	[3.5, 0.1, 5.9, -0.02],
	[8.0, -0.3, 3.0, 2.2],
	...
	]

	labels - array of N labels
	- Each label is one of "left", "keep", or "right".
	*/

	assert(data.data());
	const auto dim = data[0].size();

	const auto num_clss = possible_labels.size();

	vector<int> elems_per_class (num_clss, 0);

	priors_prob_.resize(num_clss);
	mean_.resize(num_clss);
	var_.resize(num_clss);

	// initialize by zero
	for (size_t i = 0; i < mean_.size(); i++) {
		for (int d = (int)dim; d-- > 0;) {
			mean_[i].push_back(0.);
			var_[i].push_back(0.);
		}
	}

	// calculate mean per feature
	for (size_t i = 0; i < labels.size(); i++)
	{
		const auto& label = labels[i];
		const auto& data1 = data[i];

		size_t cls_idx = 0;
		for (size_t k = 0; k < num_clss; k++)
			if (label == possible_labels[k]) {
				cls_idx = k;
				break;
			}

		elems_per_class[cls_idx] += 1;
		auto& mean1 = mean_[cls_idx];		
		for (size_t k = 0; k < dim; k++) {
			mean1[k] += data1[k];
		}
	}
	for (size_t i = 0; i < num_clss; i++)
		for (size_t k = 0; k < dim; k++)
			(mean_[i])[k] /= (double)elems_per_class[i];

	// calculate variance per feature (diagonal elements of covariance matrix only)
	for (int i = 0; i < labels.size(); i++)
	{
		const auto& label = labels[i];
		const auto& data1 = data[i];

		size_t cls_idx = 0;
		for (size_t k = 0; k < num_clss; k++)
			if (label == possible_labels[k]) {
				cls_idx = k;
				break;
			}

		const auto& mean1 = mean_[cls_idx];
		auto& var1 = var_[cls_idx];
		for (size_t k = 0; k < dim; k++) {
			double tmp = data1[k] - mean1[k];
			var1[k] += tmp * tmp;
		}
	}
	for (size_t i = 0; i < num_clss; i++)
		for (size_t k = 0; k < dim; k++)
			(var_[i])[k] /= (double)elems_per_class[i];

	// A class's prior may be calculated by assuming equiprobable classes (i.e., priors = 1 / (number of classes)),
	// or by calculating an estimate for the class probability from the training set (i.e., (prior for a given class) = (number of samples in the class) / (total number of samples)) 
	for (size_t i = 0; i < num_clss; i++) {
		priors_prob_[i] = (double)(elems_per_class[i]) / labels.size();
	}
}

string GNB::predict(vector<double> data)
{
	/*
	Once trained, this method is called and expected to return
	a predicted behavior for the given observation.

	INPUTS

	observation - a 4 tuple with s, d, s_dot, d_dot.
	- Example: [3.5, 0.1, 8.5, -0.2]

	OUTPUT

	A label representing the best guess of the classifier. Can
	be one of "left", "keep" or "right".
	"""
	# TODO - complete this
	*/

	const auto dim = data.size();
	const auto num_clss = possible_labels.size();

	// Posterior probability P(Ci)=1/num_clss is the same for all classes; skip it for speedup.

	vector<double> c_prob (num_clss, 1.); // probability per class P(C|X)

	for (size_t i = 0; i < num_clss; i++)
	{
		const auto& mean1 = mean_[i];
		const auto& var1 = var_[i];

		// Skip c_prob because priors  P(Ci)=1/num_clss. 
		//c_prob[i] = priors_prob_[i];

		for (size_t k = 0; k < dim; k++)
		{
			double v = data[k] - mean1[k];
			v = v * v / (2. * var1[k]);
			c_prob[i] *= exp(-v) / sqrt(var1[k]);
		}
	}

	// Associate class with max probability.
	auto max_prob = c_prob[0];
	size_t class_index = 0;
	for (size_t i = 1; i < num_clss; i++) {
		if (c_prob[i] > max_prob) {
			max_prob = c_prob[i];
			class_index = i;
		}
	}

	return this->possible_labels[class_index];

}