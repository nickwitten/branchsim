#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "branchsim.hpp"
#include "Counter.hpp"
#include "perceptron.hpp"
#include "yeh_patt.hpp"

// Tournament predictor definition
class tournament : public branch_predictor_base
{

private:

    // TODO: add your fields here
    // Try not to reimplement yeh_patt and perceptron!
    // EX:
    // yeh_patt *yeh_patt_predictor;
    // perceptron *perceptron_predictor;


public:
    // create optional helper functions here

    void init_predictor(branchsim_conf *sim_conf);

    // Return the prediction
    bool predict(branch *branch);

    // Update the branch predictor state
    void update_predictor(branch *branch);

    // Cleanup any allocated memory here
    ~tournament();
};

#endif
