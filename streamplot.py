import matplotlib.pyplot as plt
import numpy as np
import matplotlib.gridspec as gridspec

x,y,ex,ey = np.loadtxt('efield.txt',unpack=True)
n = int(np.sqrt(ex.size))
X = np.reshape(x, (n,n))
Y = np.reshape(y, (n,n))
Ex = np.reshape(ex, (n,n))
Ey = np.reshape(ey, (n,n))

fig = plt.figure(figsize=(8, 8))
ax0 = fig.add_subplot(111)
ax0.streamplot(X, Y, Ex, Ey)
ax0.set_title('Electric Field Lines')

plt.tight_layout()
plt.show()
