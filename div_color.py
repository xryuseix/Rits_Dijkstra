import cv2
import numpy as np
import matplotlib.pyplot as plt

# 元の画像を読み込む
org_img = cv2.imread("./Pictures/plot.png", cv2.IMREAD_COLOR)

# ゼロ埋めの画像配列
if len(org_img.shape) == 3:
    height, width, channels = org_img.shape[:3]
else:
    height, width = org_img.shape[:2]
    channels = 1
zeros = np.zeros((height, width), org_img.dtype)

# RGB分離
img_blue_c1, img_green_c1, img_red_c1 = cv2.split(org_img)

# 画像生成
img_blue_c3 = cv2.merge((img_blue_c1, zeros, zeros))
img_green_c3 = cv2.merge((zeros, img_green_c1, zeros))
img_red_c3 = cv2.merge((zeros, zeros, img_red_c1))

# cv2とpltでRGBの順番が違うから変更
img_r = cv2.cvtColor(img_red_c3, cv2.COLOR_BGR2RGB)
img_g = cv2.cvtColor(img_green_c3, cv2.COLOR_BGR2RGB)
img_b = cv2.cvtColor(img_blue_c3, cv2.COLOR_BGR2RGB)

# 赤のみの画像
plt.imshow(img_r)
plt.show()

# 緑のみの画像
plt.imshow(img_g)
plt.show()

# 青のみの画像
plt.imshow(img_b)
plt.show()
