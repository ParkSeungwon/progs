import matplotlib.pyplot as plt
import numpy as np

w = input()
h = input()
rgb = np.zeros((w,h,4))

for x in range(w) :
    for y in range(h):
        for i in range(4): 
            rgb[x][y][i] = input()

plt.imshow(rgb)
plt.show()
