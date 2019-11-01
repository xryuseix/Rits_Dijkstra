import cv2
import numpy as np
import matplotlib.pyplot as plt
import csv

# 赤色判定
def isred(x,y,z):
    x += 1
    y += 1
    z += 1
    xy = abs(x/y - 1)
    yz = abs(y/z - 1)
    zx = abs(z/x - 1)
    if xy < 0.05 and zx > 0.5 and yz > 0.5:
        return True
    else:
        return False
     

# 元の画像を読み込む
org_img = cv2.imread("./Pictures/plot.png", cv2.IMREAD_COLOR)

# 画像の高さと幅
h, w, _ = org_img.shape

# 赤色の画像の座標
redX = []
redY = []

for y in range(0,int(h)):
    for x in range(0,int(w)):
        pixelValue = org_img[y, x]
        if isred(pixelValue[0], pixelValue[1], pixelValue[2]):
            # print('(' + str(x) + ', ' + str(y) + ') ' + 'pixelValue = ' + str(pixelValue))
            redX.append(x)
            redY.append(y)
        else:
            continue

with open('./pixel.csv', 'w') as f:
    writer = csv.writer(f)
    writer.writerow(redX)
    writer.writerow(redY)