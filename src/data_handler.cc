#include "data_handler.hpp"

// Implementation of methods defined in data_handler.hpp
data_handler::data_handler()
{
    // Allocating on heap
    data_array = new std::vector<data *>;
    test_data = new std::vector<data *>;
    training_data = new std::vector<data *>;
    validation_data = new std::vector<data *>;
}
data_handler::~data_handler()
{
    // Free dynamically allocated stuff
}

// Data and label files are read separately since they are separated
void data_handler::read_feature_vector(std::string path); // Reads input data, receives a string as argument which contians the path to the data file
void data_handler::read_feature_labels(std::string path);
void data_handler::split_data(); // Performs train, test and vlaidation split
void data_handler::count_classes();

uint32_t data_handler::convert_tolittle_endian(const unsigned char *bytes);

// Allow to return the actual data sets
std::vector<data *> *data_handler::get_training_data();
std::vector<data *> *data_handler::get_test_data();
std::vector<data *> *data_handler::get_validaiton_data();