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
    const uint64_t m_PcMask = (1 << 12) - 1;
    const uint64_t m_PcMask_bp = 2;
    yeh_patt *m_YehPattPredictor;
    perceptron *m_PerceptronPredictor;
    Counter **m_CounterTable;


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
