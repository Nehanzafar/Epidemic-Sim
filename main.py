import pandas as pd
import matplotlib.pyplot as plt

data  = pd.read_csv("outputData.csv")


plt.plot(data["time"], data["population"], label="population")
plt.plot(data["time"], data["deaths"], label="deaths")
plt.plot(data["time"], data["sick"], label="sick")
plt.plot(data["time"], data["diseases"], label="diseases")
plt.legend()
plt.show()