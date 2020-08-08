import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

x,y,v = np.loadtxt('potential.txt',unpack=True)
n = int(np.sqrt(v.size))

V = np.reshape(v, (n,n))
X = np.reshape(x, (n,n))
Y = np.reshape(y, (n,n))

print(V)
print(X)
print(Y)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(X, Y, V)
plt.show()
