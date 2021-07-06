#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

// Data container
class data
{
    std::vector<uint8_t> *feature_vector; // Does not include the class
    uint8_t label;                        // Actual class label
    int enum_label;                       // Used for label encoding, for exmaple, A corresponds to 1, B to 2, etc.

public:
    void set_feature_vector(std::vector<uint8_t> *);
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enumerated_label(int);

    int get_feature_vector_size();
    uint8_t get_label();
    uint8_t get_enumerated_label();

    std::vector<uint8_t> *get_feature_vector();
};

#endif