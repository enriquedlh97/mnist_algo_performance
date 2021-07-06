#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <fstream>  // Used for reading file input and output
#include "stdint.h" // Used for the uint8 data type
#include "data.hpp"
#include <vector> // Used for dynamic array
#include <string>
#include <map>           // Used for mapping class labels to enumerated values.  Although it is stored in the data container,
                         // it is important to be able to access it quickly.
#include <unordered_set> // Used for keeping track of the indexes as the data is split between train, test and validation sets.

// Contians logic for reading and splitting the data as well as counting the number of unique classes and some other fucnitonalities
class data_handler
{
    // Vector of a data pointer to a data container and all turned into a pointer to a data array
    std::vector<data *> *data_array; // Contians all fo the data before split
    std::vector<data *> *training_data;
    std::vector<data *> *test_data;
    std::vector<data *> *validation_data;

    int num_classes = 0;
    int feature_vector_size = 0;
    std::map<uint8_t, int> class_map;

    // Defines the data splits
    const double TRAIN_SET_PERCENT = 0.75;
    const double TEST_SET_PERCENT = 0.20;
    const double VALIDATION_SET_PERCENT = 0.05;

public:
    data_handler();  // Constructor
    ~data_handler(); // Destructor

    // Data and label files are read separately since they are separated
    void read_feature_vector(std::string path); // Reads input data, receives a string as argument which contians the path to the data file
    void read_feature_labels(std::string path);
    void split_data(); // Performs train, test and vlaidation split
    void count_classes();

    uint32_t convert_tolittle_endian(const unsigned char *bytes);

    // Allow to return the actual data sets
    std::vector<data *> *get_training_data();
    std::vector<data *> *get_test_data();
    std::vector<data *> *get_validaiton_data();
};

#endif