#include <stdlib.h>
#include <math.h>
#include <err.h>

#include "nbc.h"

static float normal_distribution_probability(float f, float m, float v)
{
    return exp((-(f - m) * (f - m)) / (2 * v)) / sqrtf(2 * M_PI * v);
}

static struct nbc_class *init_classes(struct nbc_vector *data)
{
    struct nbc_class *res = calloc(NBC_CLASSES_COUNT, sizeof(struct nbc_class));
    if (!res)
        errx(1, "Cannot allocate memory.");

    // Initialize classes
    for (unsigned c = 0; c < NBC_CLASSES_COUNT; c++)
    {
        for (unsigned v = 0; v < NBC_VECTORS_COUNT; v++)
        {
            if (data[v].class_id != c)
                continue;
            res[c].vectors[res[c].vectors_count++] = v;
        }
    }

    return res;
}

static void compute_normal_distribution_params(
        struct nbc_class *classes,
        struct nbc_vector *data
)
{
    for (unsigned c = 0; c < NBC_CLASSES_COUNT; c++)
    {
        for (unsigned f = 0; f < NBC_FEATURES_COUNT; f++)
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
}

static unsigned compute_probabilities(
        struct nbc_vector sample,
        struct nbc_class *classes
)
{
    float max = 0;
    unsigned res = 0;
    for (unsigned c = 0; c < NBC_CLASSES_COUNT; c++)
    {
        float tmp = 1.0f / NBC_CLASSES_COUNT;
        for (unsigned f = 0; f < NBC_FEATURES_COUNT; f++)
            tmp *= normal_distribution_probability(sample.features[f],
                    classes[c].means[f],
                    classes[c].variances[f]);

        if (tmp > max)
        {
            max = tmp;
            res = c;
        }
    }

    return res;
}

unsigned nbc_classify(struct nbc_vector sample, struct nbc_vector *data)
{
    struct nbc_class *classes = init_classes(data);

    // Compute normal distribution parameters for each feature of each class
    compute_normal_distribution_params(classes, data);

    // Compute probability for each class
    unsigned res = compute_probabilities(sample, classes);

    free(classes);
    return res;
}
