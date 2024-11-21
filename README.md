# ML Model Transpiler to C

This repository provides a Python-based tool to transpile machine learning models into C code. It allows deploying trained models in embedded systems or other environments where resources are constrained, ensuring compact and efficient inference.

## Supported Models

The tool supports transpilation for the following machine learning models:
- **Linear Regression** (`sklearn.linear_model.LinearRegression`)
- **Logistic Regression** (`sklearn.linear_model.LogisticRegression`)
- **Decision Trees** (`sklearn.tree.DecisionTreeClassifier`)
- **Random Forests** (with majority voting for classification, using `sklearn.ensemble.RandomForestClassifier`)

## Features

- **Automatic Transpilation**: Converts trained models into C code for inference.
- **Lightweight Binaries**: Generates efficient and minimal C code suitable for embedded systems.
- **Easy Compilation**: Outputs standard C code that can be compiled using GCC or other standard compilers.

## Binary Size Comparison

This table shows the sizes of the generated binary executables for different models:

| Model                  | Binary Name       | Binary Size |
|------------------------|-------------------|-------------|
| Linear Regression      | `linear_reg`     | 912 B       |
| Logistic Regression    | `logistic_reg`   | 1,3 KB       |
| Decision Tree          | `tree_ensemble`  | 14 KB       |
| Random Forest | `random_forest` | 2,1 KB       |

## Installation

### Prerequisites
- Python 3.x
- Libraries: `scikit-learn`, `joblib`, `pandas`
- C compiler: GCC or similar

Install the required Python dependencies:
```bash
pip install -r requirements.txt