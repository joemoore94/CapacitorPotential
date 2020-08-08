import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

x,y,ex,ey = np.loadtxt('efield.txt',unpack=True)
n = int(np.sqrt(ey.size))

Ey = np.reshape(ey, (n,n))
X = np.reshape(x, (n,n))
Y = np.reshape(y, (n,n))

print(Ey)
print(X)
print(Y)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(X, Y, Ey)
plt.show()
