#ifndef NBN_H
#define NBC_H

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define NBC_CLASSES_COUNT  2
#define NBC_FEATURES_COUNT 3
#define NBC_VECTORS_COUNT  8

struct nbc_class
{
    unsigned vectors[NBC_VECTORS_COUNT];
    unsigned vectors_count;

    float means[NBC_FEATURES_COUNT];
    float variances[NBC_FEATURES_COUNT];
};

struct nbc_vector
{
    unsigned class_id;
    float features[NBC_FEATURES_COUNT];
};

unsigned nbc_classify(struct nbc_vector sample, struct nbc_vector *data);

#endif /* ! NBC_H */
