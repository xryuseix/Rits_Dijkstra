import cv2
import matplotlib.pyplot as plt
import csv

# 画像の読み込み
img = cv2.imread("./Pictures/plot.png", 1)

# 画像の高さ、幅を取得
height = img.shape[0]
width = img.shape[1]

# 座標を取得
with open('./zip.csv') as f:
    reader = csv.reader(f)
    grid = [row for row in reader]

isedge = False

# 辺を取得
with open('./edge.csv') as f:
    reader = csv.reader(f)
    inputedge = [row for row in reader]
    if inputedge != []:
        isedge = True

print("isedge",str(isedge))

if isedge:
    edge = inputedge

# 頂点番号の描画
for i in range(0,len(grid[0])):
    cv2.putText(img, str(i), (int(grid[0][i]), int(grid[1][i])), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), thickness=2)

if isedge:
    print("DRAW")
    print(edge)
    # 現在貼っている辺を追加
    for i in range(0,len(edge[0])):
        cv2.line(plotimg, (int(grid[0][int(edge[0][i])]), int(grid[1][int(edge[0][i])])), (int(grid[0][int(edge[1][i])]), int(grid[1][int(edge[1][i])])), (50, 255, 255), thickness=2, lineType=cv2.LINE_AA)

# 画像の表示
plotimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(plotimg)
plt.pause(1)

WriteEdge = [[0] * 1 for i in range(2)]

while True:
    # 頂点番号の描画
    for i in range(0,len(grid[0])):
        cv2.putText(plotimg, str(i), (int(grid[0][i]), int(grid[1][i])), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), thickness=2)

    print("張りたい辺の両端の頂点を空白区切りで入力(-1 -1で終了)：")
    From, To = map(int, input().split())

    if From == -1 or To == -1:
        WriteEdge = edge
        break
    if not isedge:
        edge = [[0] * 1 for i in range(2)]
        edge[0][0] = From
        edge[1][0] = To
        isedge = True
    else:
        edge[0].append(From)
        edge[1].append(To)

    # 現在貼っている辺を追加
    for i in range(0,len(edge[0])):
        cv2.line(plotimg, (int(grid[0][int(edge[0][i])]), int(grid[1][int(edge[0][i])])), (int(grid[0][int(edge[1][i])]), int(grid[1][int(edge[1][i])])), (255, 255, 50), thickness=2, lineType=cv2.LINE_AA)

    plt.imshow(plotimg)
    plt.pause(1)

# 出力
with open('./edge.csv', 'w') as f:
    writer = csv.writer(f)
    writer.writerow(WriteEdge[0])
    writer.writerow(WriteEdge[1])

# サンプルケース
# 0,1,1,1,2,2,2,2,3,3,4,4,5,5,6,6,7,8,8,8,09,10,11,12,12,14,15
# 1,2,4,5,3,4,5,6,5,6,5,8,6,9,10,9,8,9,4,12,10,13,12,13,15,15,16
