import json 
import matplotlib.pyplot as plt
import numpy as np

def displayJson(jsonPath):
    with open(jsonPath, "r") as f:
        data = json.load(f)
    z = np.zeros((data["dim"]["y"], data["dim"]["x"]))

    for e in data["lakes"]: 
        for k in e:
            z[k["y"]][k["x"]] = 1
    
    plt.imshow(z)

    plt.show()