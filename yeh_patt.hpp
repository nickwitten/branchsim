#ifndef YEHPATT_H
#define YEHPATT_H

#include "branchsim.hpp"
#include "Counter.hpp"

// Yeh-Patt predictor definition
class yeh_patt : public branch_predictor_base
{

private:

    // TODO: add your fields here
    uint64_t m_L;
    uint64_t m_P;
    uint64_t m_PcMask;  // Use to get index bits out of PC
    const uint64_t m_PcMask_bp = 2; // Offset bit position
    uint64_t m_ShiftMask;  // Use to simulate only P bits in shift registers
    uint64_t *m_HistoryTable;
    Counter **m_PatternTable;

public:
    // create optional helper functions here

    void init_predictor(branchsim_conf *sim_conf);

    // Return the prediction
    bool predict(branch *branch);

    // Update the branch predictor state
    void update_predictor(branch *branch);

    // Cleanup any allocated memory here
    ~yeh_patt();
};

#endif
