import cv2
import matplotlib.pyplot as plt
import csv

# 画像の読み込み
img = cv2.imread("./Pictures/plot.png", 1)

# 画像の高さ、幅を取得
height = img.shape[0]
width = img.shape[1]

with open('./zip.csv') as f:
    reader = csv.reader(f)
    grid = [row for row in reader]

for i in range(0,len(grid[0])):
    # cv2.drawMarker(img, (int(grid[0][i]), int(grid[1][i])), (255, 0, 0))
    cv2.putText(img, str(i), (int(grid[0][i]), int(grid[1][i])), cv2.FONT_HERSHEY_COMPLEX, 0.7, (255, 0, 0), thickness=2)

# 画像の表示
plotimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(plotimg)
plt.show()