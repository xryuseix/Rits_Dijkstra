import cv2
import matplotlib.pyplot as plt

print("現在地，行き先の順に入力：")
From, To = map(int, input().split())

# 入力された値を格納するだけの配列
input = [[]]

# 頂点のX,Y座標
vx = []
vy = []

# 最短経路を取得
with open('./path.csv') as f:
    for s_line in f:
        s_tmp = s_line.rstrip('\n').split(',')
        int_tmp = [int(x) for x in s_tmp]
        input.append(int_tmp)

# 各頂点の座標を取得
cnt = 0
with open('./zip.csv') as f:
    for s_line in f:
        s_tmp = s_line.rstrip('\n').split(',')
        int_tmp = [int(x) for x in s_tmp]
        if cnt == 0:
            vx = int_tmp
        else:
            vy = int_tmp
        cnt += 1

# 辺の集合
efrom = []
eto = []
# 張るべき辺を取得
cnt = 0
with open('./edge.csv') as f:
    for s_line in f:
        s_tmp = s_line.rstrip('\n').split(',')
        int_tmp = [int(x) for x in s_tmp]
        if cnt == 0:
            efrom = int_tmp
        else:
            eto = int_tmp
        cnt += 1

# 先頭の空要素を削除
input.pop(0)

# 頂点数
V = input[-1][0] + 1

# 経路を追加
path = [[[] for i in range(V)] for j in range(V)]
for i in input:
    path[i[0]][i[-1]].append(i)

# 画像の読み込み
img = cv2.imread("./Pictures/plot.png", 1)

# 現在貼っている辺を追加
for i in range(0,len(efrom)):
    cv2.line(img, (vx[efrom[i]], vy[efrom[i]]), (vx[eto[i]], vy[eto[i]]), (255, 255, 0), thickness=1, lineType=cv2.LINE_AA)

# 矢印の描画([From][To][0]の最後の0は謎)
for i in range(0, len(path[From][To][0]) - 1):
    cv2.arrowedLine(img, (vx[path[From][To][0][i]], vy[path[From][To][0][i]]), (vx[path[From][To][0][i + 1]], vy[path[From][To][0][i + 1]]), (0, 255, 0), thickness=3)
# 頂点番号の描画
for i in range(0,V):
    cv2.putText(img, str(i), (int(vx[i]), int(vy[i])), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), thickness=2)

# 画像の表示
plotimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(plotimg)
plt.subplots_adjust(left=0, right=1, bottom=0, top=1)
plt.show()