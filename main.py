import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("data.txt", sep=",", header=None)
plt.scatter(data[0], data[1])
plt.title("Single vs. Double Dose")
plt.xlabel("Half-life (days)")
plt.ylabel("Concentration")
plt.show()
