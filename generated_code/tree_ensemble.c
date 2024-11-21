#include <stdio.h>

float predict(float *features, int n_features) {
    if (n_features < 3) {
        return -1.0;
    }
    if (features[2] > 0.500000) {
    if (features[0] > 104.334698) {
    return 2;
}
else {
    return 1;
}
}
else {
    if (features[0] > 152.747917) {
    return 0;
}
else {
    return 0;
}
}

}

int main() {
    float features[] = {0.0, 0.0, 0.0};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\n", predict(features, n_features));
    return 0;
}
