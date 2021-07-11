#include "data.hpp"

// Implements the methods defined in data.hpp

data::data()
{
    // By initializing to uint8_t we do not have to do it in the for loop on data_handler right after
    // getting the file header
    feature_vector = new std::vector<uint8_t>;
}
data::~data()
{

}
void data::set_feature_vector(std::vector<uint8_t> *vect)
{
    feature_vector = vect;
}
void data::append_to_feature_vector(uint8_t val)
{
    feature_vector->push_back(val);
}
void data::set_label(uint8_t val)
{
    label = val;
}
void data::set_enumerated_label(int val)
{
    enum_label = val;
}

int data::get_feature_vector_size()
{
    return feature_vector->size();
}
uint8_t data::get_label()
{
    return label;
}
uint8_t data::get_enumerated_label()
{
    return enum_label;
}

std::vector<uint8_t> *data::get_feature_vector()
{
    return feature_vector;
}