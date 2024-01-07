import matplotlib.pyplot as plt
from Point import Point
import operator


pointSize = int(input('Please input number of points:'))
pointsList = Point.randomPoints(pointSize)
vetexs = Point.findConvexHull(pointsList)


plt.figure(figsize=(10, 10))
plt.scatter([i.x for i in pointsList], [i.y for i in pointsList])
pointShow = pointSize

for i in range(1, len(vetexs)):
    plt.plot([vetexs[i-1].x, vetexs[i].x], [vetexs[i-1].y, vetexs[i].y], color='r')

plt.xticks([])
plt.yticks([])
plt.show()
