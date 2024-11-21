#include <stdio.h>

float predict(float *features, int n_features) {
    if (n_features < 3) {
        return -1.0;
    }
    float result = -8152.937710;
    result += features[0] * 717.258370;
    result += features[1] * 36824.195974;
    result += features[2] * 101571.840022;
    return result;
}

int main() {
    float features[] = {0.0, 0.0, 0.0};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\n", predict(features, n_features));
    return 0;
}
