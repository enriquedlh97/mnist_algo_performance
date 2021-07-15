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
// Essentially builds the data array with the feature vectors
void data_handler::read_feature_vector(std::string path) // Reads input data, receives a string as argument which contians the path to the data file
{
    uint32_t header[4];                 // array of size 4. |MAGIC|NUM IMAGES|ROW SIZE|COL SIZE|
    unsigned char bytes[4];             // char is a one byte size. Four of this allow to read all the 32 bits
    FILE *f = fopen(path.c_str(), "r"); // "r" indicates we open it in read mode
    if (f)                              // If the file pointer is not null, continue
    {
        for (int i = 0; i < 4; i++) // Less than four because we know that the header contians 4 values
        {
            if (fread(bytes, sizeof(bytes), 1, f))
            {
                header[i] = convert_to_little_endian(bytes);
            }
        }
        printf("Donde getting input file header.\n");
        int image_size = header[2] * header[3]; // Image size
        for (int i = 0; i < header[1]; i++)     // Iterates over the numbe rof images
        {
            // While we iterate over number of images we need to iterate ove the next image size elemnts in that file
            data *d = new data(); // Initializes new data container

            // This is because we need a one element array of size 8 bits
            uint8_t element[1];
            for (int j = 0; j < image_size; j++)
            {
                if (fread(element, sizeof(element), 1, f))
                {
                    d->append_to_feature_vector(element[0]);
                }
                else
                {
                    printf("Error reading from file.\n");
                    exit(1);
                }
            }
            data_array->push_back(d); // data_array just stores a pointer to the object
        }
        printf("Success. %lu feature vectors were read and saved.\n", data_array->size());
    }
    else
    {
        // This prins if there is no file pointer
        printf("Could not find file.\n");
        exit(1);
    }
}
void data_handler::read_feature_labels(std::string path)
{
    uint32_t header[2];                 // array of size 2. |MAGIC|NUM IMAGES|
    unsigned char bytes[2];             // char is a one byte size. Two of this allow to read all bits
    FILE *f = fopen(path.c_str(), "r"); // "r" indicates we open it in read mode
    if (f)                              // If the file pointer is not null, continue
    {
        for (int i = 0; i < 2; i++) // Less than four because we know that the header contians 4 values
        {
            if (fread(bytes, sizeof(bytes), 1, f))
            {
                header[i] = convert_to_little_endian(bytes);
            }
        }
        printf("Donde getting label file header.\n");
        for (int i = 0; i < header[1]; i++) // Iterates over the number of images
        {
            uint8_t element[1];
            if (fread(element, sizeof(element), 1, f))
            {
                data_array->at(i)->set_label(element[0]);
            }
            else
            {
                printf("Error reading from file.\n");
                exit(1);
            }
        }
        printf("Successfully read and saved label.\n", data_array->size());
    }
    else
    {
        // This prins if there is no file pointer
        printf("Could not find file.\n");
        exit(1);
    }
}
void data_handler::split_data() // Performs train, test and vlaidation split
{
    // The data is used stored once even though there are three arrays. That is because we work with pointers essentially passing pointers
    // to the correposnding parts of the original array

    // Used for keeping track of the used indices
    std::unordered_set<int> used_indexes;
    int train_size = data_array->size() * TRAIN_SET_PERCENT;
    int test_size = data_array->size() * TEST_SET_PERCENT;
    int valid_size = data_array->size() * VALIDATION_SET_PERCENT;

    // Training data
    int count = 0;
    while (count < train_size)
    {
        int rand_index = rand() % data_array->size(); // Generates number between 0 and data_array->size() - 1
        // Then, we check if used_indexes contains this value
        if (used_indexes.find(rand_index) == used_indexes.end())
        {
            // If the iterator is at the end, then that means that the value was not found and it can be used
            training_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index); // Marks it as used so that it can no longer be used
            count++;
        }
    }

    // Test data
    count = 0;
    while (count < test_size)
    {
        int rand_index = rand() % data_array->size(); // Generates number between 0 and data_array->size() - 1
        // Then, we check if used_indexes contains this value
        if (used_indexes.find(rand_index) == used_indexes.end())
        {
            // If the iterator is at the end, then that means that the value was not found and it can be used
            test_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index); // Marks it as used so that it can no longer be used
            count++;
        }
    }

    // Validation data
    count = 0;
    while (count < valid_size)
    {
        int rand_index = rand() % data_array->size(); // Generates number between 0 and data_array->size() - 1
        // Then, we check if used_indexes contains this value
        if (used_indexes.find(rand_index) == used_indexes.end())
        {
            // If the iterator is at the end, then that means that the value was not found and it can be used
            validation_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index); // Marks it as used so that it can no longer be used
            count++;
        }
    }

    printf("Training Data Size: %lu.\n", training_data->size());
    printf("Test Data Size: %lu.\n", test_data->size());
    printf("Validation Data Size: %lu.\n", validation_data->size());
}
void data_handler::count_classes()
{
    // Essentially stores the values in a map of
    int count = 0;
    for (unsigned i = 0; i < data_array->size(); i++)
    {
        // If we find a key in the map that equals the current label then we do nothing;
        // otherwise, then the label is not in the map
        if (class_map.find(data_array->at(i)->get_label()) == class_map.end())
        {
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enumerated_label(count);
            count++;
        }
    }
    num_classes = count;
    printf("Successfully extratec %d unique calsses.\n", num_classes);
}

uint32_t data_handler::convert_to_little_endian(const unsigned char *bytes)
{
    // The 0th byte is shifted to the left. Its 8 bits are shifted to the left 24 bits. Essentially, the 0th byte becomes the third byte
    // Then, the second byte is shifted to the left 16 bits
    return (uint32_t) ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
}

// These methods allow to return the actual data sets
std::vector<data *> *data_handler::get_training_data()
{
    return training_data;
}
std::vector<data *> *data_handler::get_test_data()
{
    return test_data;
}
std::vector<data *> *data_handler::get_validaiton_data()
{
    return validation_data;
}