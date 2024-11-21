#include <stdio.h>
#include <math.h>

float sigmoid(float z) {
    return 1.0 / (1.0 + exp(-z));
}

float predict(float *features, int n_features) {
    if (n_features < 3) {
        return -1.0;
    }
    float z = 2.293482;
    z += features[0] * -0.001603;
    z += features[1] * -0.332230;
    z += features[2] * -1.997263;
    return sigmoid(z);
}

int main() {
    float features[] = {0.0, 0.0, 0.0};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\n", predict(features, n_features));
    return 0;
}
