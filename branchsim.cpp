#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>

#include "branchsim.hpp"
#include "yeh_patt.hpp"
#include "Counter.hpp"
#include "tournament.hpp"
#include "perceptron.hpp"

// Don't modify this line -- Its to make the compiler happy
branch_predictor_base::~branch_predictor_base() {}


// ******* Student Code starts here *******

// Yeh-Patt Branch Predictor

void yeh_patt::init_predictor(branchsim_conf *sim_conf)
{
    // TODO: implement me
}

bool yeh_patt::predict(branch *branch)
{
    // TODO: implement me
    return false;
}

void yeh_patt::update_predictor(branch *branch)
{
    // TODO: implement me
}

yeh_patt::~yeh_patt()
{
    // TODO: implement me
}


// Perceptron Branch Predictor

void perceptron::init_predictor(branchsim_conf *sim_conf)
{
    // TODO: implement me
}

bool perceptron::predict(branch *branch)
{
    // TODO: implement me
    return false;
}

void perceptron::update_predictor(branch *branch)
{
    // TODO: implement me
}

perceptron::~perceptron()
{
    // TODO: implement me
}


// Tournament Branch Predictor

void tournament::init_predictor(branchsim_conf *sim_conf)
{
    // TODO: implement me
    // Example:
    // perceptron_predictor = new perceptron();
    // perceptron_predictor->init_predictor(sim_conf);
    // yeh_patt_predictor = new yeh_patt();
    // yeh_patt_predictor->init_predictor(sim_conf);
}

bool tournament::predict(branch *branch)
{
    // TODO: implement me
    return false;
}

void tournament::update_predictor(branch *branch)
{
    // TODO: implement me
}

tournament::~tournament()
{
    // TODO: implement me
    // Example:
    // delete perceptron_predictor;
    // delete yeh_patt_predictor;
}


// Common Functions to update statistics and final computations, etc.

/**
 *  Function to update the branchsim stats per prediction. Here we now know the
 *  actual outcome of the branch, so you can update misprediction counters etc.
 *
 *  @param prediction The prediction returned from the predictor's predict function
 *  @param branch Pointer to the branch that is being predicted -- contains actual behavior
 *  @param stats Pointer to the simulation statistics -- update in this function
*/
void branchsim_update_stats(bool prediction, branch *branch, branchsim_stats *sim_stats) {
    // TODO: implement me
}

/**
 *  Function to finish branchsim statistic computations such as prediction rate, etc.
 *
 *  @param stats Pointer to the simulation statistics -- update in this function
*/
void branchsim_finish_stats(branchsim_stats *sim_stats) {
    // TODO: implement me
}
