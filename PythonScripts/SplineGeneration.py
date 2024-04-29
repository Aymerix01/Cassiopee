import unreal
import numpy as np
import cv2 as cv
import sys

def convImageToSplinePoints(file, outputFile):
    baseIm = cv.imread(file)
    image = cv.cvtColor(baseIm, cv.COLOR_BGR2GRAY)
    contours, _ = cv.findContours(image, 
                                  mode = cv.RETR_TREE,
                                  method = cv.CHAIN_APPROX_SIMPLE)
    print(contours)

    i = 0
    for e in contours:
        curFile = outputFile + str(i)
        array = np.array([f[0] for f in e])
        np.save(outputFile, array)
        np.savetxt(outputFile + ".csv", array, delimiter=",")
        i += 1

    print("Size : ", sys.getsizeof(array))
    print(array)

    # np.save(outputFile, array)
    # # For checking
    # np.savetxt(outputFile + ".csv", array, delimiter=",")

    