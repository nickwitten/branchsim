#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "branchsim.hpp"

// Perceptron predictor definition
class perceptron : public branch_predictor_base
{

private:

    // TODO: add your fields here
    uint64_t m_N;
    uint64_t m_G;
    uint64_t m_PcMask;  // Use to get index bits out of PC
    const uint64_t m_PcMask_bp = 2; // Offset bit position
    int64_t m_Theta;  // Threshold

    uint64_t m_GlobalHistory;
    int64_t *m_WeightTable;

public:
    // create optional helper functions here

    /* Perform the "dot product" of the GHR with the perceptron weights */
    int64_t dot_product(uint64_t base_weight_ind) {
        int64_t sum = m_WeightTable[base_weight_ind];  // Start the sum with the bias weight
        for (uint64_t i = 0; i < m_G; i++) {
            // -1 for not taken and 1 for taken
            int64_t xi = ((m_GlobalHistory >> i) & 1) ? 1 : -1;
            // Multiply by corresponding weight
            sum += m_WeightTable[base_weight_ind + i + 1] * xi;
        }
        return sum;
    }

    void init_predictor(branchsim_conf *sim_conf);

    // Return the prediction
    bool predict(branch *branch);

    // Update the branch predictor state
    void update_predictor(branch *branch);

    // Cleanup any allocated memory here
    ~perceptron();
};

#endif
