/*
** TO-DO
** - Clean code, dynamic, library, makefile
** - Go deeper in maths
** - Use OpenMP
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define CLASSES_COUNT 2
#define FEATURES_COUNT 3
#define VECTORS_COUNT 8

struct class
{
    unsigned id;
    unsigned vectors[VECTORS_COUNT];
    unsigned vectors_count;

    float means[FEATURES_COUNT];
    float variances[FEATURES_COUNT];
};

struct vector
{
    unsigned class_id;
    float features[FEATURES_COUNT];
};

static struct vector *load_training_data()
{
    struct vector *res = calloc(VECTORS_COUNT, sizeof(struct vector));

    res[0] = (struct vector) { 0, { 6.00, 180, 12 } };
    res[1] = (struct vector) { 0, { 5.92, 190, 11 } };
    res[2] = (struct vector) { 0, { 5.58, 170, 12 } };
    res[3] = (struct vector) { 0, { 5.92, 165, 10 } };
    res[4] = (struct vector) { 1, { 5.00, 100, 6  } };
    res[5] = (struct vector) { 1, { 5.50, 150, 8  } };
    res[6] = (struct vector) { 1, { 5.42, 130, 7  } };
    res[7] = (struct vector) { 1, { 5.75, 150, 9  } };

    return res;
}

static float normal_distribution_probability(float f, float m, float v)
{
    return exp((-(f - m) * (f - m)) / (2 * v)) / sqrtf(2 * M_PI * v);
}

int main(void)
{
    // Load dataset
    struct vector *data = load_training_data();

    // Declare the testing sample
    struct vector sample = { 0, { 6.00, 130, 8 } };

    // Compute mean and variance for each class and for each feature
    char* classes_label[] = { "male", "female" };
    struct class *classes = calloc(CLASSES_COUNT, sizeof(struct class));

    // Initialize classes
    for (unsigned c = 0; c < CLASSES_COUNT; c++)
    {
        classes[c].id = c;
        for (unsigned v = 0; v < VECTORS_COUNT; v++)
        {
            if (data[v].class_id != c)
                continue;
            classes[c].vectors[classes[c].vectors_count++] = v;
        }
    }

    // Compute normal distribution parameters for each feature of each class
    for (unsigned c = 0; c < CLASSES_COUNT; c++)
    {
        for (unsigned f = 0; f < FEATURES_COUNT; f++)
        {
            unsigned count = 0;

            for (unsigned v = 0; v < classes[c].vectors_count; v++)
            {
                unsigned v_id = classes[c].vectors[v];
                classes[c].means[f] += data[v_id].features[f];
                count++;
            }
            classes[c].means[f] /= count;

            for (unsigned v = 0; v < classes[c].vectors_count; v++)
            {
                unsigned v_id = classes[c].vectors[v];
                classes[c].variances[f] += pow(data[v_id].features[f] - classes[c].means[f], 2);
            }
            classes[c].variances[f] /= (count - 1);
        }
    }

    // Compute probability for each class
    float max = 0;
    unsigned res = 0;
    for (unsigned c = 0; c < CLASSES_COUNT; c++)
    {
        float tmp = 0.5;
        for (unsigned f = 0; f < FEATURES_COUNT; f++)
            tmp *= normal_distribution_probability(sample.features[f],
                    classes[c].means[f],
                    classes[c].variances[f]);

        if (tmp > max)
        {
            max = tmp;
            res = c;
        }
    }

    // Show the class with the greater probability
    printf("Predicted class of sample: '%s'.\n", classes_label[res]);

    free(data);
    free(classes);
    return 0;
}
