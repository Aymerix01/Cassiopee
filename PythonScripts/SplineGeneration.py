import unreal
# import numpy as np
import cv2 as cv
import sys
import json

def convImageToSplinePoints(file, outputFile, pointsProp = 0.02):
    baseIm = cv.imread(file)
    image = cv.cvtColor(baseIm, cv.COLOR_BGR2GRAY)
    contours, _ = cv.findContours(image, 
                                  mode = cv.RETR_TREE,
                                  method = cv.CHAIN_APPROX_SIMPLE)
    # print(contours)

    i = 0
    dic = {"lakes": []}
    dic["dim"] = {"x" : image.shape[0], "y" : image.shape[1]}
    for i in range(len(contours)):
        array = [[k for k in f[0]] for f in contours[i]]
        dic["lakes"].append([{"x" : int(array[j][1]), "y" : int(array[j][0])} for j in range(0, len(array), int(1/pointsProp))])


    print("Lakes : ", sys.getsizeof(dic))
    print(dic)
    with open(outputFile + ".json", "w") as f:
        json.dump(dic, f)