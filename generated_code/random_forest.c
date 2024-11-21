#include <stdio.h>

// Function prototypes for individual tree predictions
float tree_0_predict(float *features, int n_features);
float tree_1_predict(float *features, int n_features);
float tree_2_predict(float *features, int n_features);
float tree_3_predict(float *features, int n_features);
float tree_4_predict(float *features, int n_features);
float tree_5_predict(float *features, int n_features);
float tree_6_predict(float *features, int n_features);
float tree_7_predict(float *features, int n_features);
float tree_8_predict(float *features, int n_features);
float tree_9_predict(float *features, int n_features);

float predict(float *features, int n_features) {
    int votes[2] = {0, 0}; // Adjust size if you have more classes
    votes[(int)tree_0_predict(features, n_features)]++;
    votes[(int)tree_1_predict(features, n_features)]++;
    votes[(int)tree_2_predict(features, n_features)]++;
    votes[(int)tree_3_predict(features, n_features)]++;
    votes[(int)tree_4_predict(features, n_features)]++;
    votes[(int)tree_5_predict(features, n_features)]++;
    votes[(int)tree_6_predict(features, n_features)]++;
    votes[(int)tree_7_predict(features, n_features)]++;
    votes[(int)tree_8_predict(features, n_features)]++;
    votes[(int)tree_9_predict(features, n_features)]++;
    // Return the class with the most votes
    int max_votes = 0;
    int predicted_class = -1;
    for (int i = 0; i < 2; i++) { // Adjust range if you have more classes
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    return predicted_class;
}

float tree_0_predict(float *features, int n_features) {
    if (features[0] <= 161.063980) {
    if (features[1] <= 2.500000) {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    return 1;
    }
    } else {
    if (features[2] <= 0.500000) {
    return 1;
    } else {
    return 1;
    }
    }
    } else {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    if (features[0] <= 178.037811) {
    return 2;
    } else {
    return 1;
    }
    }
    }
}
float tree_1_predict(float *features, int n_features) {
    if (features[2] <= 0.500000) {
    if (features[0] <= 143.167648) {
    return 0;
    } else {
    if (features[0] <= 160.237038) {
    return 1;
    } else {
    return 0;
    }
    }
    } else {
    if (features[1] <= 2.500000) {
    if (features[0] <= 106.834705) {
    return 1;
    } else {
    return 2;
    }
    } else {
    return 2;
    }
    }
}
float tree_2_predict(float *features, int n_features) {
    if (features[1] <= 1.500000) {
    if (features[0] <= 191.000160) {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    return 1;
    }
    } else {
    return 1;
    }
    } else {
    if (features[2] <= 0.500000) {
    if (features[1] <= 2.500000) {
    return 0;
    } else {
    return 0;
    }
    } else {
    if (features[0] <= 103.348949) {
    return 1;
    } else {
    return 2;
    }
    }
    }
}
float tree_3_predict(float *features, int n_features) {
    if (features[2] <= 0.500000) {
    if (features[1] <= 2.500000) {
    return 0;
    } else {
    if (features[0] <= 115.455276) {
    return 0;
    } else {
    return 1;
    }
    }
    } else {
    if (features[0] <= 104.334698) {
    return 1;
    } else {
    if (features[1] <= 1.500000) {
    return 1;
    } else {
    return 2;
    }
    }
    }
}
float tree_4_predict(float *features, int n_features) {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    if (features[1] <= 1.500000) {
    return 1;
    } else {
    if (features[0] <= 106.680542) {
    return 1;
    } else {
    return 2;
    }
    }
    }
}
float tree_5_predict(float *features, int n_features) {
    if (features[1] <= 1.500000) {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    if (features[0] <= 163.171494) {
    return 1;
    } else {
    return 0;
    }
    }
    } else {
    if (features[2] <= 0.500000) {
    if (features[0] <= 152.747917) {
    return 0;
    } else {
    return 0;
    }
    } else {
    if (features[1] <= 2.500000) {
    return 2;
    } else {
    return 2;
    }
    }
    }
}
float tree_6_predict(float *features, int n_features) {
    if (features[1] <= 2.500000) {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    if (features[1] <= 1.500000) {
    return 1;
    } else {
    return 2;
    }
    }
    } else {
    if (features[0] <= 160.237038) {
    if (features[0] <= 116.219181) {
    return 0;
    } else {
    return 1;
    }
    } else {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    return 2;
    }
    }
    }
}
float tree_7_predict(float *features, int n_features) {
    if (features[0] <= 104.334698) {
    if (features[1] <= 2.500000) {
    return 1;
    } else {
    return 0;
    }
    } else {
    if (features[2] <= 0.500000) {
    if (features[1] <= 2.500000) {
    return 0;
    } else {
    return 0;
    }
    } else {
    if (features[0] <= 117.690784) {
    return 2;
    } else {
    return 0;
    }
    }
    }
}
float tree_8_predict(float *features, int n_features) {
    if (features[2] <= 0.500000) {
    return 0;
    } else {
    if (features[1] <= 1.500000) {
    return 1;
    } else {
    if (features[0] <= 103.348949) {
    return 1;
    } else {
    return 2;
    }
    }
    }
}
float tree_9_predict(float *features, int n_features) {
    if (features[0] <= 215.751328) {
    if (features[1] <= 2.500000) {
    if (features[0] <= 97.175110) {
    return 0;
    } else {
    return 1;
    }
    } else {
    if (features[0] <= 108.068787) {
    return 2;
    } else {
    return 0;
    }
    }
    } else {
    return 2;
    }
}

int main() {
    float features[] = {0.0, 0.0, 0.0};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\n", predict(features, n_features));
    return 0;
}
