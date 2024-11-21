import joblib
import sys
import pandas as pd 
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier

PATH_CSV = "/Users/misterfacile/epita/SCIA/S9/MLOps/ML_C/ML_Embarqu-_C/houses.csv"

def build_model():
    df = pd.read_csv(PATH_CSV)
    X = df[['size', 'nb_rooms', 'garden']]
    y = df['price']
    
    model = LinearRegression()
    model.fit(X, y)
    joblib.dump(model, "models/linear_reg.joblib")

    # Discrétiser `y` pour la classification
    y_class = pd.qcut(y, q=3, labels=[0, 1, 2])  # Découpe en 3 catégories par défaut

    model = DecisionTreeClassifier(max_depth=2)
    model.fit(X, y_class)
    joblib.dump(model, "models/tree_ensemble.joblib")
    print("Decision Tree Classifier model saved.")


    model = LogisticRegression(max_iter=1000)
    model.fit(X, y_class)
    joblib.dump(model, "models/logistic_reg.joblib")
    print("Logistic Regression model saved.")
    
    # Train a Random Forest Classifier
    model = RandomForestClassifier(n_estimators=10, max_depth=3, random_state=42)
    model.fit(X, y_class)
    joblib.dump(model, "models/random_forest.joblib")
    print("Random Forest Classifier model saved.")

def transpile_linear_regression(model, output_file):
    coefficients = model.coef_
    intercept = model.intercept_

    c_code = f"""#include <stdio.h>

float predict(float *features, int n_features) {{
    if (n_features < {len(coefficients)}) {{
        return -1.0;
    }}
    float result = {intercept:.6f};
"""
    for i, coef in enumerate(coefficients):
        c_code += f"    result += features[{i}] * {coef:.6f};\n"
    c_code += """    return result;
}

int main() {
    float features[] = {""" + ", ".join("0.0" for _ in range(len(coefficients))) + """};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\\n", predict(features, n_features));
    return 0;
}
"""
    with open(output_file, "w") as f:
        f.write(c_code)
    print(f"Linear regression model transpiled to {output_file}")

def transpile_logistic_regression(model, output_file):
    """Transpile a logistic regression model to C code."""
    from math import exp

    coefficients = model.coef_[0]
    intercept = model.intercept_[0]

    c_code = f"""#include <stdio.h>
#include <math.h>

float sigmoid(float z) {{
    return 1.0 / (1.0 + exp(-z));
}}

float predict(float *features, int n_features) {{
    if (n_features < {len(coefficients)}) {{
        return -1.0;
    }}
    float z = {intercept:.6f};
"""
    for i, coef in enumerate(coefficients):
        c_code += f"    z += features[{i}] * {coef:.6f};\n"
    c_code += """    return sigmoid(z);
}

int main() {
    float features[] = {""" + ", ".join("0.0" for _ in range(len(coefficients))) + """};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\\n", predict(features, n_features));
    return 0;
}
"""
    with open(output_file, "w") as f:
        f.write(c_code)
    print(f"Logistic regression model transpiled to {output_file}")

def transpile_decision_tree(model, output_file):
    """Transpile a decision tree model to C code."""
    tree = model.tree_
    feature = tree.feature
    threshold = tree.threshold
    children_left = tree.children_left
    children_right = tree.children_right

    def build_tree_code(node):
        if children_left[node] == children_right[node]:  # Leaf
            return f"return {int(tree.value[node].argmax())};\n"
        left_code = build_tree_code(children_left[node])
        right_code = build_tree_code(children_right[node])
        return (
            f"if (features[{feature[node]}] > {threshold[node]:.6f}) {{\n"
            f"    {right_code}}}\n"
            f"else {{\n"
            f"    {left_code}}}\n"
        )

    c_code = f"""#include <stdio.h>

float predict(float *features, int n_features) {{
    if (n_features < {max(feature) + 1}) {{
        return -1.0;
    }}
    {build_tree_code(0)}
}}

int main() {{
    float features[] = {{""" + ", ".join("0.0" for _ in range(max(feature) + 1)) + """};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\\n", predict(features, n_features));
    return 0;
}
"""
    with open(output_file, "w") as f:
        f.write(c_code)
    print(f"Decision tree model transpiled to {output_file}")

def transpile_decision_tree_code(tree):
    """Generate code for an individual decision tree."""
    tree_data = tree.tree_
    feature = tree_data.feature
    threshold = tree_data.threshold
    children_left = tree_data.children_left
    children_right = tree_data.children_right

    def build_tree_code(node):
        if children_left[node] == children_right[node]:  # Leaf
            return f"    return {int(tree_data.value[node].argmax())};\n"
        left_code = build_tree_code(children_left[node])
        right_code = build_tree_code(children_right[node])
        return (
            f"    if (features[{feature[node]}] <= {threshold[node]:.6f}) {{\n"
            f"{left_code}"
            f"    }} else {{\n"
            f"{right_code}"
            f"    }}\n"
        )

    return build_tree_code(0)

def transpile_tree_ensemble(model, output_file):
    """Transpile an ensemble of decision trees to C code with majority voting."""
    estimators = model.estimators_

    c_code = """#include <stdio.h>

// Function prototypes for individual tree predictions
"""
    for idx, estimator in enumerate(estimators):
        c_code += f"float tree_{idx}_predict(float *features, int n_features);\n"

    c_code += """
float predict(float *features, int n_features) {
    int votes[2] = {0, 0}; // Adjust size if you have more classes
"""
    for idx in range(len(estimators)):
        c_code += f"    votes[(int)tree_{idx}_predict(features, n_features)]++;\n"

    c_code += """    // Return the class with the most votes
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

"""
    # Generate code for individual trees
    for idx, estimator in enumerate(estimators):
        tree_code = transpile_decision_tree_code(estimator)
        c_code += f"float tree_{idx}_predict(float *features, int n_features) {{\n{tree_code}}}\n"

    c_code += """
int main() {
    float features[] = {0.0, 0.0, 0.0};  // Replace with your input
    int n_features = sizeof(features) / sizeof(features[0]);
    printf("Prediction: %f\\n", predict(features, n_features));
    return 0;
}
"""

    with open(output_file, "w") as f:
        f.write(c_code)
    print(f"Tree ensemble model transpiled to {output_file}")


def transpile_model(input_file, output_file):
    model = joblib.load(input_file)
    model_type = type(model).__name__

    if model_type == "LinearRegression":
        transpile_linear_regression(model, output_file)
    elif model_type == "LogisticRegression":
        transpile_logistic_regression(model, output_file)
    elif model_type == "DecisionTreeClassifier":
        transpile_decision_tree(model, output_file)
    elif model_type == "RandomForestClassifier":
        transpile_tree_ensemble(model, output_file)
    else:
        print(f"Model type {model_type} not supported.")

if __name__ == "__main__":
    build_model()
    if len(sys.argv) != 3:
        print("Usage: python transpiler.py <model_file.joblib> <output_file.c>")
    else:
        transpile_model(sys.argv[1], sys.argv[2])
