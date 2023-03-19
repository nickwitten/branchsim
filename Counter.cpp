#include "Counter.hpp"
#include <cstdint>

// ===================================================================
// Documentation for these methods are in the header file, Counter.hpp
// ===================================================================

Counter::Counter(uint64_t width) {
    m_Width = width;
    m_WeaklyTaken = 1 << (m_Width - 1); // weakly taken state is 2^(width-1)
    m_WeaklyNotTaken = m_WeaklyTaken - 1;
    m_MaxValue = (1 << m_Width) - 1;
    m_Val = m_WeaklyNotTaken;
}

void Counter::update(bool taken) {
    if (taken) {
        // If it's at the saturation point don't increment
        m_Val = (m_Val < m_MaxValue) ? m_Val + 1: m_Val;
    } else {
        // If it's at the saturation point don't increment
        m_Val = (m_Val > 0) ? m_Val - 1 : m_Val;
    }
}

uint64_t Counter::get() {
    return m_Val;
}

bool Counter::isTaken() {
    if (m_Val >= m_WeaklyTaken) {
        return true;
    } else {
        return false;
    }
}

void Counter::setCount(uint64_t count) {
    m_Val = count;
}

bool Counter::isWeak() {
    if (m_Val == m_WeaklyTaken || m_Val == m_WeaklyNotTaken) {
        return true;
    } else {
        return false;
    }
}

void Counter::reset(bool taken) {
    if (isTaken()) {
        m_Val = m_WeaklyTaken;
    } else {
        m_Val = m_WeaklyNotTaken;
    }
}
