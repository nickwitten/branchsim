#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <cinttypes>

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
    m_L = sim_conf->L;
    m_P = sim_conf->P;

    m_PcMask = (1 << m_L) - 1;
    m_ShiftMask = (1 << m_P) - 1;

    m_HistoryTable = (uint64_t*)calloc((1 << m_L), sizeof(uint64_t));
    m_PatternTable = (Counter**)malloc(sizeof(Counter*) * (1 << m_P));
    for (int i = 0; i < (1 << m_P); i++) {
        m_PatternTable[i] = new Counter;
    }
}

bool yeh_patt::predict(branch *branch)
{
    uint64_t history_index = (branch->ip >> m_PcMask_bp) & m_PcMask;
    uint64_t pattern_index = m_HistoryTable[history_index];
    return m_PatternTable[pattern_index]->isTaken();
}

void yeh_patt::update_predictor(branch *branch)
{
    uint64_t history_index = (branch->ip >> m_PcMask_bp) & m_PcMask;
    uint64_t pattern_index = m_HistoryTable[history_index];
    uint64_t history = m_HistoryTable[history_index];
    m_HistoryTable[history_index] = ((history << 1) + (uint64_t)(branch->is_taken)) & m_ShiftMask;
    m_PatternTable[pattern_index]->update(branch->is_taken);
}

yeh_patt::~yeh_patt()
{
    free(m_HistoryTable);
    for (int i = 0; i < (1 << m_P); i++) {
        delete m_PatternTable[i];
    }
    free(m_PatternTable);
}


// Perceptron Branch Predictor

void perceptron::init_predictor(branchsim_conf *sim_conf)
{
    m_N = sim_conf->N;
    m_G = sim_conf->G;
    m_PcMask = ((uint64_t)1 << m_N) - 1;
    m_Theta = 1.93 * m_G + 14;

    m_WeightTable = (int64_t*)calloc(((uint64_t)1 << m_N) * (m_G + 1), sizeof(int64_t));
    m_GlobalHistory = 0;
#ifdef DEBUG
    printf("Perceptron: Creating a Perceptron table of %" PRIu64 " perceptrons each with %" PRIu64 " weights\n",((uint64_t)1 << m_N), m_G+1);
    printf("Perceptron: Theta: %" PRIu64 "\n", m_Theta);
#endif
}

bool perceptron::predict(branch *branch)
{
    uint64_t perceptron_ind = (branch->ip >> m_PcMask_bp) & m_PcMask;
    // Calculate the start index of perceptron weights
    uint64_t base_weight_ind = perceptron_ind * (m_G + 1);
    // Perform the dot product between weights and GHR
    int64_t result = dot_product(base_weight_ind);

#ifdef DEBUG
    printf("\tPerceptron: Predicting... \n");
    printf("\t\tPerceptron Table index: 0x%" PRIx64 ", Global History: 0x%" PRIx64 ", Y: %" PRId64 ", Prediction: %d\n", perceptron_ind, m_GlobalHistory, result, (result > 0));
    printf("\t\tw0: %" PRId64 "\n", m_WeightTable[base_weight_ind]);
    printf("\t\tWeights: ");
    for (int i = 0; i < m_G; i++) {
        printf("%" PRId64 ", ", m_WeightTable[base_weight_ind+i+1]);
    }
    printf("\n");
#endif

    if (result > 0) {
        return true;
    } else {
        return false;
    }
}

void perceptron::update_predictor(branch *branch)
{
    uint64_t perceptron_ind = (branch->ip >> m_PcMask_bp) & m_PcMask;
    // Calculate the start index of perceptron weights
    uint64_t base_weight_ind = perceptron_ind * (m_G + 1);
    // Perform the dot product between weights and GHR
    int64_t result = dot_product(base_weight_ind);
    bool prediction = result > 0;
    int64_t abs_result = (result < 0) ? 0 - result : result;  // Absolute value
    if (prediction != branch->is_taken || abs_result < m_Theta) {
        int t = (branch->is_taken) ? 1 : -1;
        // Update bias term
        m_WeightTable[base_weight_ind] = m_WeightTable[base_weight_ind] + t;
        for (uint64_t i = 0; i < m_G; i++) {
            // -1 for not taken and 1 for taken
            int64_t xi = ((m_GlobalHistory >> i) & 1) ? 1 : -1;
            int64_t wi = m_WeightTable[base_weight_ind + i + 1];
            wi = wi + t * xi;
            m_WeightTable[base_weight_ind + i + 1] = wi;
        }
        for (uint64_t i = 0; i < m_G + 1; i++) {
            int64_t wi = m_WeightTable[base_weight_ind + i];
            if (wi > m_Theta) {
                wi = m_Theta;
            } else if (wi < -m_Theta) {
                wi = -m_Theta;
            }
            m_WeightTable[base_weight_ind + i] = wi;
        }
    }
    // Update GHR
    m_GlobalHistory = (m_GlobalHistory << 1) + (int)branch->is_taken;
    m_GlobalHistory = m_GlobalHistory & (((uint64_t)1 << m_G) - 1);

#ifdef DEBUG
    printf("\tPerceptron: Updating based on actual behavior: %d\n", branch->is_taken);
    printf("\t\tNew Global History: 0x%" PRIx64 "\n", m_GlobalHistory);
    printf("\t\tUpdated w0: %" PRId64 "\n", m_WeightTable[base_weight_ind]);
    printf("\t\tUpdated Weights: ");
    for (int i = 0; i < m_G; i++) {
        printf("%" PRId64 ", ", m_WeightTable[base_weight_ind+i+1]);
    }
    printf("\n");
#endif

}

perceptron::~perceptron()
{
    free(m_WeightTable);
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
    sim_stats->total_instructions = branch->inst_num;
    sim_stats->num_branch_instructions += 1;
    if (prediction == branch->is_taken) {
        sim_stats->num_branches_correctly_predicted++;
    } else {
        sim_stats->num_branches_mispredicted++;
    }
}

/**
 *  Function to finish branchsim statistic computations such as prediction rate, etc.
 *
 *  @param stats Pointer to the simulation statistics -- update in this function
*/
void branchsim_finish_stats(branchsim_stats *sim_stats) {
    sim_stats->misses_per_kilo_instructions = sim_stats->num_branches_mispredicted / (sim_stats->total_instructions / 1000.0f);
    sim_stats->fraction_branch_instructions = ((double)sim_stats->num_branch_instructions) / sim_stats->total_instructions;
    sim_stats->prediction_accuracy = ((double)sim_stats->num_branches_correctly_predicted) / sim_stats->num_branch_instructions;
}
