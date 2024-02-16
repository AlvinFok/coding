'''
code reference
https://github.com/MarcoForte/knn-matting/blob/master/knn_matting.py
https://github.com/dingzeyuli/knn-matting/blob/master/src/knn_matting_scribble_rgb.m
https://github.com/dingzeyuli/knn-matting/blob/master/src/knn_matting_scribble_hsv.m
'''

#%%
import numpy as np
import sklearn.neighbors
import scipy.sparse
import warnings
import matplotlib.pyplot as plt
import cv2
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--color_space", "-c",default="RGB" )
parser.add_argument("--input")
args = parser.parse_args()
#%%
def knn_matting(image, trimap, color_space='RGB', my_lambda=100):
    [m, n, c] = image.shape
    if(color_space == "HSV"):
        image = cv2.cvtColor(image, cv2.COLOR_RGB2HSV)#change image color space to HSV
    image, trimap = image / 255.0, trimap / 255.0
    foreground = (trimap == 1.0).astype(int)
    background = (trimap == 0.0).astype(int)
    all_constraints = foreground + background#Combine confirmed foreground and background into a image

    print("Finding KNN")
    nbrs_num  = 10
    a, b = np.unravel_index(np.arange(m*n), (m,n))
    if(color_space == "HSV"):#Using difference feature for each color space
        h,s,v =cv2.split(image)
        feature = np.append( (np.reshape(np.cos(h), (m*n)),   np.reshape(np.sin(h), (m*n)),   np.reshape(s, (m*n)),   np.reshape(v, (m*n))) , [a, b] /np.sqrt(m*m + n*n), axis=0).T#X(i) = (cos(h), sin(h), s, v, x, y)
    else:
        feature = np.append(np.reshape(image, (m*n, c)).T, [a, b] /np.sqrt(m*m + n*n), axis = 0 ).T#X(i)
    ####################################################
    #       find KNN for the given image
    ####################################################
    nbrs = sklearn.neighbors.NearestNeighbors(n_neighbors=nbrs_num, n_jobs=-1).fit(feature)
    knn_indices = nbrs.kneighbors(feature)[1]#Find X(j) with KNN

    ####################################################
    #       compute the affinity matrix A
    #       and all other stuff needed
    ####################################################
    print("Calculating affinity matrix A")
    row_index = np.repeat(np.arange(m*n), nbrs_num)#X(i)'s indices
    # print(row_index)
    col_index = np.reshape(knn_indices, (m*n*nbrs_num))#X(j)'s indices
    kernel = 1 - np.linalg.norm(feature[row_index] - feature[col_index], axis=1)/ (c+2)#||X(i) - X(j)|| / C
    A = scipy.sparse.coo_matrix((kernel, (row_index, col_index)), shape=(m*n, m*n))
    # print(type(A))
    ####################################################
    #       solve for the linear system
    #       note that you may encounter en error
    #       if no exact solution exists
    ####################################################
    D = scipy.sparse.diags(np.ravel(A.sum(axis=1)))
    L = D-A
    # print(all_constraints.shape)
    D = scipy.sparse.diags(np.ravel(all_constraints))
    v = np.ravel(foreground)#a binary vector of pixel indices corresponding to user markups for a given layer
    c = 2*my_lambda*np.transpose(v)
    H = 2*(L + my_lambda*D)#H = 2* (L + lambda*D)

    print('Solving linear system')
    warnings.filterwarnings('error')
    alpha = []
    try:
        alpha = np.minimum(np.maximum(scipy.sparse.linalg.spsolve(H, c), 0), 1).reshape(m, n)
    except Warning:#Cannot find solution
        x = scipy.sparse.linalg.lsqr(H, c)
        alpha = np.minimum(np.maximum(x[0], 0), 1).reshape(m, n)
    return alpha

if __name__ == '__main__':
    image_Name = args.input

    image = cv2.imread(f'./image/{image_Name}.png')
    trimap = cv2.imread(f'./trimap/{image_Name}.png', cv2.IMREAD_GRAYSCALE)
    
    alpha = knn_matting(image, trimap, args.color_space)
    alpha = alpha[:, :, np.newaxis]
    alpha = alpha * 255
    cv2.imwrite(f"./alpha/{image_Name}_{args.color_space}.png", alpha)
    ####################################################
    #       pick up your own background image, 
    #       and merge it with the foreground
    ####################################################
    alpha = cv2.imread(f"./alpha/{image_Name}_{args.color_space}.png", cv2.IMREAD_GRAYSCALE)
    [m, n] = alpha.shape
    
    background = cv2.imread("./background/background.jpeg")
    background = cv2.resize(background, (n,m))
    
    image = cv2.imread(f'./image/{image_Name}.png')

    ret, ma1 = cv2.threshold(alpha, 170, 255, cv2.THRESH_BINARY_INV)
    fg1 = cv2.bitwise_and(background,background,mask=ma1)
        
    ret, ma2 = cv2.threshold(alpha, 170, 255, cv2.THRESH_BINARY)
    fg2 = cv2.bitwise_and(image,image,mask = ma2)
    image = cv2.add(fg1, fg2)
    cv2.imwrite(f"./result/{image_Name}_{args.color_space}.png", image)

    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)#BGR to RGB for display
    plt.imshow(image)
    plt.axis("off")
    plt.show()
    
    
    
