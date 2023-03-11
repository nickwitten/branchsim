#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "branchsim.hpp"

// Perceptron predictor definition
class perceptron : public branch_predictor_base
{

private:

    // TODO: add your fields here

public:
    // create optional helper functions here

    void init_predictor(branchsim_conf *sim_conf);

    // Return the prediction
    bool predict(branch *branch);

    // Update the branch predictor state
    void update_predictor(branch *branch);

    // Cleanup any allocated memory here
    ~perceptron();
};

#endif
