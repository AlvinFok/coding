def getGoal(points, colors, target:str):
    df = pd.read_csv("./color_coding_semantic_segmentation_classes.xlsx - Sheet1.csv")
    targetList = {row["Name"]:row["Color_Code (R,G,B)"].replace("(", "").replace(")", "") for _, row in df.iterrows()}
    color = targetList[target]
    color = tuple(map(int, color.split(",")))
    colors = colors*255
    
    targetPoints = np.where(np.all(colors == color, axis=1))
    x = points[:,0][targetPoints[0]]
    y = points[:,1][targetPoints[0]]
    plt.scatter(x,y,c='r')
    
    length = x.shape[0]
    sum_x = np.sum(x)
    sum_y = np.sum(y)
    center = (sum_x/length, sum_y/length)
    
    plt.scatter(center[0], center[1], c="black")
    plt.xlim(-3.09137, 6.24393)
    plt.ylim(-4.94901, 9.9124)
    plt.show()
    return center