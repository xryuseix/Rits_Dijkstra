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
    cv2.putText(img, str(i), (int(grid[0][i]), int(grid[1][i])), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), thickness=2)

# 画像の表示
plotimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(plotimg)
plt.pause(1)

while True:
    print("現在地，行き先の順に入力：")# このあたりで辺を書いてもらい，線を書く
    From, To = map(int, input().split())
    if From == 0 and To ==0:
        break

    plt.imshow(plotimg)
    plt.pause(1)
