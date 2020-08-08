import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

x,y,v = np.loadtxt('potential.txt',unpack=True)
n = int(np.sqrt(v.size))

V = np.reshape(v, (n,n))
X = np.reshape(x, (n,n))
Y = np.reshape(y, (n,n))

plt.figure(figsize=(10,10))
plt.subplot(111)

levels = np.arange(-1, 1, 0.1)
plt.contour(X, Y, V, levels)
plt.show()
