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
void data_handler::read_feature_vector(std::string path) // Reads input data, receives a string as argument which contians the path to the data file
{
    uint32_t header[4]; // array of size 4. |MAGIC|NUM IMAGES|ROW SIZE|COL SIZE|
    unsigned char bytes[4]// char is a one byte size. Four of this allow to read all the 32 bits
    FILE *f = fopen(path.c_str(), "r"); // "r" indicates we open it in read mode
    if(f) // If the file pointer is not null, continue
    {
        for(int i = 0; i < 4, i++) // Less than four because we know that the header contians 4 values
        {
            if(fread(bytes, sizeof(bytes), 1, f))
            {
                header[i] = convert_to_little_endian(bytes);
            }
        }
        print("Fonde getting file header.\n");
        int image_Size = header[2] * header[3]; // Image size
        for(int i = 0; i < header[1]; ++) // Iterates over the numbe rof images
        {
            // While we iterate over number of images we need to iterate ove the next image size elemnts in that file
            data *d = new data(); // Initializes new data container
            d->set_feature_vector()
        }
    }   
}
void data_handler::read_feature_labels(std::string path);
void data_handler::split_data(); // Performs train, test and vlaidation split
void data_handler::count_classes();

uint32_t data_handler::convert_tolittle_endian(const unsigned char *bytes);

// Allow to return the actual data sets
std::vector<data *> *data_handler::get_training_data();
std::vector<data *> *data_handler::get_test_data();
std::vector<data *> *data_handler::get_validaiton_data();