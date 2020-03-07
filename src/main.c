#include <stdio.h>
#include <stdlib.h>

#include "nbc.h"

static struct nbc_vector *load_training_data()
{
    struct nbc_vector *res = calloc(NBC_VECTORS_COUNT, sizeof(struct nbc_vector));

    res[0] = (struct nbc_vector) { 0, { 6.00, 180, 12 } };
    res[1] = (struct nbc_vector) { 0, { 5.92, 190, 11 } };
    res[2] = (struct nbc_vector) { 0, { 5.58, 170, 12 } };
    res[3] = (struct nbc_vector) { 0, { 5.92, 165, 10 } };
    res[4] = (struct nbc_vector) { 1, { 5.00, 100, 6  } };
    res[5] = (struct nbc_vector) { 1, { 5.50, 150, 8  } };
    res[6] = (struct nbc_vector) { 1, { 5.42, 130, 7  } };
    res[7] = (struct nbc_vector) { 1, { 5.75, 150, 9  } };

    return res;
}

int main(void)
{
    /*
    Future usage:

    struct nbc *classifier = nbc_create(nb_classes, nb_features);
    nbc_vector_add(id_class, list);
    nbc_vector_add(id_class, list);
    nbc_vector_add(id_class, list);
    unsigned res = nbc_predict(list);
    nbc_destroy(classifier);
    */

    // Declare the testing sample
    struct nbc_vector sample = { 0, { 6.00, 130, 8 } };

    // Load dataset
    struct nbc_vector *data = load_training_data();

    // Call the classifier
    int res = nbc_classify(sample, data);

    // Show the class with the greater probability
    char* classes_label[] = { "male", "female" };
    printf("Predicted class of sample: '%s'.\n", classes_label[res]);

    free(data);
    return 0;
}
