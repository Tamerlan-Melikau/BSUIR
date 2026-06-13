import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score

hours = np.array([1,2,3,4,5,6,7,8,9,10,12,14,16,18,20]).reshape(-1,1)
n = len(hours)

scores = 3 + 0.25 * hours.ravel() + np.random.normal(0, 0.8, n)
scores = np.clip(scores, 1, 10)

model1 = LinearRegression().fit(hours, scores)
print(f"Одиночная: Оценка = {model1.coef_[0]:.2f} * Часы + {model1.intercept_:.2f}")
print(f"R² = {r2_score(scores, model1.predict(hours)):.4f}\n")

absences = np.random.poisson(2, n)
X_multi = np.column_stack([hours.ravel(), absences])
scores_multi = 3 + 0.2 * hours.ravel() - 0.25 * absences + np.random.normal(0, 0.5, n)
scores_multi = np.clip(scores_multi, 1, 10)

model2 = LinearRegression().fit(X_multi, scores_multi)
print(f"Множественная: R² = {r2_score(scores_multi, model2.predict(X_multi)):.4f}")
print(f"Коэффициенты: Часы={model2.coef_[0]:.2f}, Пропуски={model2.coef_[1]:.2f}")