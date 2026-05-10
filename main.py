import pandas as pd
import matplotlib.pyplot as plt

data  = pd.read_csv("outputData.csv")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

ax1.plot(data["time"], data["population"], label="population")
ax1.plot(data["time"], data["deaths"], label="deaths")
ax1.plot(data["time"], data["sick"], label="sick")
ax1.plot(data["time"], data["diseases"], label="diseases")
ax1.legend()


disease_data = pd.read_csv("./diseaseData.csv")
# Bar graph subplot
ax2.bar(disease_data["Code"], disease_data["Infected"], label="infected")
ax2.bar(disease_data["Code"], disease_data["Killed"], label="killed")
ax2.legend()

plt.show()
