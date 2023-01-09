# you will need to install cv2
# Run "pip3 install opencv-python" in CLI
import cv2
import sys
filename = sys.argv[1]

import os
if os.path.exists("spriteData.txt"):
    os.remove("spriteData.txt")

img = cv2.imread('../assets/' + filename, cv2.IMREAD_UNCHANGED)
img = cv2.cvtColor(img, cv2.COLOR_BGRA2RGBA)
dimensions = img.shape
f = open("spriteData.txt", "a")
f.write(str(dimensions[0]))
f.write("\n")
f.write(str(dimensions[1]))
f.write("\n")
for x in range(dimensions[0]):
    for y in range(dimensions[1]):
        f.write(str(img[x,y][0]))
        f.write("\n")
        f.write(str(img[x,y][1]))
        f.write("\n")
        f.write(str(img[x,y][2]))
        f.write("\n")
        f.write(str(img[x,y][3]))
        f.write("\n")
f.close()