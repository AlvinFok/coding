#%%
from typing import final
import open3d
import os
import copy
import numpy as np
import time

path = "Data/first floor"
def get_point_cloud_list():
    point_clouds = []
    file_list = os.listdir(os.path.join(path,"rgb"))
    # print(file_list)
    file_list = sorted(file_list, key=lambda x: int(x.split(".")[0]))
    for index, file in enumerate(file_list):
        # print(os.path.join(path,"rgb",file))
        rgb_image = open3d.io.read_image(os.path.join(path,"rgb",file))
        depth_image = open3d.io.read_image(os.path.join(path, "depth",file))
        rgbd_image = open3d.geometry.RGBDImage.create_from_color_and_depth(rgb_image, depth_image,convert_rgb_to_intensity=False)
        camera = open3d.camera.PinholeCameraIntrinsic(512,512, 256, 256, 256, 256)
        point_cloud = open3d.geometry.PointCloud.create_from_rgbd_image(rgbd_image, camera).transform([ [ 1,0,0,0], [0,-1,0,0], [0,0,-1,0], [0,0,0,1] ])
        point_clouds.append(point_cloud)

    return point_clouds

def draw_registration_result(source, target, transformation):
    source_temp = copy.deepcopy(source)
    target_temp = copy.deepcopy(target)
    # source_temp.paint_uniform_color([1, 0.706, 0])
    # target_temp.paint_uniform_color([0, 0.651, 0.929])
    source_temp.transform(transformation)
    open3d.visualization.draw_geometries([source_temp, target_temp])

def preprocess_point_cloud(pcd, voxel_size):
    # print(":: Downsample with a voxel size %.3f." % voxel_size)
    pcd_down = pcd.voxel_down_sample(voxel_size)

    radius_normal = voxel_size * 2
    # print(":: Estimate normal with search radius %.3f." % radius_normal)
    pcd_down.estimate_normals(
        open3d.geometry.KDTreeSearchParamHybrid(radius=radius_normal, max_nn=30))

    radius_feature = voxel_size * 5
    # print(":: Compute FPFH feature with search radius %.3f." % radius_feature)
    pcd_fpfh = open3d.pipelines.registration.compute_fpfh_feature(
        pcd_down,
        open3d.geometry.KDTreeSearchParamHybrid(radius=radius_feature, max_nn=100))
    return pcd_down, pcd_fpfh

def prepare_dataset(source, target, voxel_size):
    # print(":: Load two point clouds and disturb initial pose.")

    source_down, source_fpfh = preprocess_point_cloud(source, voxel_size)
    target_down, target_fpfh = preprocess_point_cloud(target, voxel_size)
    return source, target, source_down, target_down, source_fpfh, target_fpfh

def execute_fast_global_registration(source_down, target_down, source_fpfh,
                                     target_fpfh, voxel_size):
    distance_threshold = voxel_size * 0.5
    # print(":: Apply fast global registration with distance threshold %.3f" % distance_threshold)
    result = open3d.pipelines.registration.registration_fast_based_on_feature_matching(
        source_down, target_down, source_fpfh, target_fpfh,
        open3d.pipelines.registration.FastGlobalRegistrationOption(
            maximum_correspondence_distance=distance_threshold))
    return result

def get_transformation(source , target):
    voxel_size = 0.00003  # means 5cm for this dataset
    
    source, target, source_down, target_down, source_fpfh, target_fpfh = prepare_dataset(source, target, voxel_size)

    result_fast = execute_fast_global_registration(source_down, target_down,
                                               source_fpfh, target_fpfh,
                                               voxel_size)
    # print(result_fast)

    threshold = voxel_size * 0.4
    trans_init = result_fast.transformation
    reg_p2p = open3d.pipelines.registration.registration_icp(
    source, target, threshold, trans_init,
    open3d.pipelines.registration.TransformationEstimationPointToPoint())
    print(reg_p2p)
    # draw_registration_result(source, target, reg_p2p.transformation)
    return reg_p2p.transformation

def get_ground_truth_trajectory(): 
    file = open(os.path.join(path,"GT_pose.txt"))
    points = []
    for index, line in enumerate(file.readlines()):
        x,y,z,rw,rx,ry,rz = line.split()
        # print(x,y,z)
        point = [x,y,z]
        points.append(point)
        

    # colors = [[0, 0, 0] for i in range(len(true_lines))]
    # true_line_set = open3d.geometry.LineSet(
    #     points=open3d.utility.Vector3dVector(points),
    #     lines=open3d.utility.Vector2iVector(true_lines),
    # )
    # true_line_set.colors = open3d.utility.Vector3dVector(colors)
    # return true_line_set
    return points

def pose2lineset(point, color):
    lines = np.arange(len(point)-1)
    lines = np.vstack((lines, lines+1)).T
    line_set = open3d.geometry.LineSet()
    line_set.points = open3d.utility.Vector3dVector(point)
    line_set.lines = open3d.utility.Vector2iVector(lines)
    line_set.colors = open3d.utility.Vector3dVector(color)

    return line_set

# %%
point_clouds = get_point_cloud_list()
size = len(point_clouds)
# size = 10
matrix_list = []
final_point_cloud = point_clouds[0]
for i in range(0, size-1):
    print(f"Executing {i+1} to {i}")
    source = point_clouds[i+1]
    target = point_clouds[i]
    transformation = get_transformation(source,target)
    matrix_list.append(transformation)
#%%

ET_point = [[0,0,0]]
trans_matrix = np.identity(4)
bbox = open3d.geometry.AxisAlignedBoundingBox(np.array([-50, -2, -50]).T, np.array([50, 0.6, 50]).T)
for i in range(1, size):
    trans_matrix = np.dot(trans_matrix, matrix_list[i-1])
    ET_point.append(trans_matrix[0:3,3].T)
    point_clouds[i].transform(trans_matrix)
    final_point_cloud += point_clouds[i]
# final_point_cloud = final_point_cloud.crop(bbox)
#%%
pcd = open3d.io.read_point_cloud(os.path.join(path,"3d.pcd"))
GT_point = get_ground_truth_trajectory()
GT_point = np.asarray(GT_point, dtype=np.float32)/10000
GT_point = pose2lineset(GT_point, [[1, 1, 1] for i in range(len(GT_point))])
ET_point = pose2lineset(ET_point, [[1, 0, 0] for i in range(len(ET_point))])

open3d.visualization.draw_geometries([pcd, GT_point, ET_point])
# open3d.visualization.draw_geometries(point_clouds[:size-1])

#%%
open3d.io.write_point_cloud(os.path.join(path,"3d.pcd"), final_point_cloud)
pcd = open3d.io.read_point_cloud(os.path.join(path,"3d.pcd"))
open3d.visualization.draw_geometries([pcd])


#%%
#This part is my implementation code
#%%
import numpy as np
import cv2 as cv
import open3d
from sklearn.neighbors import NearestNeighbors
path = "Data/first floor"

def depth_image_to_point_cloud(rgb_image, depth_image):
    cx, cy, fx, fy = 256, 256, 256, 256
    width, height = rgb_image.shape[:2]
    depth_image = depth_image[...,0]#only need one dimension
    # depth_image = depth_image / 0.1
    valid = (depth_image > 0) & (depth_image < 255)#check invalid value
    z = np.where(valid, depth_image, np.nan)
    # print(z)
    u,v = np.meshgrid(np.arange(width), np.arange(height), sparse=True)
    x = np.where(valid, z * (u - cx) / fx, 0)
    y = np.where(valid, z * (v - cy) / fy, 0)
    
    rgb = (rgb_image/255).reshape(-1,3)
    points = np.dstack((x,y,z)).reshape(-1,3)
    point_cloud = open3d.geometry.PointCloud(open3d.utility.Vector3dVector(points))
    point_cloud.colors = open3d.utility.Vector3dVector(rgb)
    point_cloud.transform([ [ 1,0,0,0], [0,-1,0,0], [0,0,-1,0], [0,0,0,1] ])
    return point_cloud

def get_point_cloud_list_myVersion():
    point_clouds = []
    file_list = os.listdir(os.path.join(path,"rgb"))
    # print(file_list)
    file_list = sorted(file_list, key=lambda x: int(x.split(".")[0]))
    for file in file_list:
        # print(os.path.join(path,"rgb",file))
        rgb_image = cv.imread(os.path.join(path,"rgb",file))
        depth_image = cv.imread(os.path.join(path, "depth",file))
        rgb_image = cv.cvtColor(rgb_image, cv.COLOR_BGR2RGB)
        point_cloud = depth_image_to_point_cloud(rgb_image, depth_image)
        point_clouds.append(point_cloud)

    return point_clouds

def get_new_icp_transformation(source, target):
    mu_source = np.mean(source, axis=1, keepdims=True)
    mu_target = np.mean(target, axis=1, keepdims=True)
    W = target @ source.T
    u, s, vh = np.linalg.svd(W)
    rot = u @ vh
    vec = mu_target - (rot @ mu_source)

    tran = np.eye(4)
    tran[:3, :3] = rot
    tran[:3, 3:] = vec

    return tran

def local_icp(source, target, threshold, tran_init, max_pair_dist, max_itr=30):
    tran = tran_init
    for i in range(max_itr):
        source.transform(tran)
        source_points = np.asarray(source.points)
        target_points = np.asarray(target.points)
        nnbr = NearestNeighbors(n_neighbors=1).fit(target_points)
        distance, target_index = nnbr.kneighbors(source_points, n_neighbors=1, return_distance=True)
        print(distance)
        print(type(target_index))
        target_set = target_points[:,target_index.reshape[-1]]
        error = np.mean(np.linalg.norm(source_points - target_set, axis=0))
        if(error <= threshold):
            break
        valid_pair = np.where(distance.reshape(-1) < max_pair_dist)[0]
        tran = get_new_icp_transformation(source_points[:, valid_pair], target_points[:, valid_pair]) @ tran

def execute_global_registration(source_down, target_down, source_fpfh,
                                target_fpfh, voxel_size):
    distance_threshold = voxel_size * 1.5
    
    result = open3d.pipelines.registration.registration_ransac_based_on_feature_matching(
        source_down, target_down, source_fpfh, target_fpfh, True,
        distance_threshold,
        open3d.pipelines.registration.TransformationEstimationPointToPoint(False),
        3, [
            open3d.pipelines.registration.CorrespondenceCheckerBasedOnEdgeLength(
                0.9),
            open3d.pipelines.registration.CorrespondenceCheckerBasedOnDistance(
                distance_threshold)
        ], open3d.pipelines.registration.RANSACConvergenceCriteria(100000, 0.999))

    return result

def get_transformation_myVersion(source , target):
    
    voxel_size = 0.00003  # means 5cm for this dataset
    
    source, target, source_down, target_down, source_fpfh, target_fpfh = prepare_dataset(source, target, voxel_size)
    
    result_fast = execute_fast_global_registration(source_down, target_down,
                                               source_fpfh, target_fpfh,
                                               voxel_size)
    print(result_fast)

    threshold = voxel_size * 0.4
    trans_init = result_fast.transformation
    tran,_,_ = icp(np.asarray(source.points), np.asarray(target.points), trans_init,tolerance=threshold)
    return tran


def best_fit_transform(A, B):

    # get number of dimensions
    m = A.shape[1]

    # translate points to their centroids
    centroid_A = np.mean(A, axis=0)
    centroid_B = np.mean(B, axis=0)
    AA = A - centroid_A
    BB = B - centroid_B

    # rotation matrix
    H = np.dot(AA.T, BB)
    U, S, Vt = np.linalg.svd(H)
    R = np.dot(Vt.T, U.T)

    # special reflection case
    if np.linalg.det(R) < 0:
       Vt[m-1,:] *= -1
       R = np.dot(Vt.T, U.T)

    # translation
    t = centroid_B.T - np.dot(R,centroid_A.T)

    # homogeneous transformation
    T = np.identity(m+1)
    T[:m, :m] = R
    T[:m, m] = t

    return T, R, t


def nearest_neighbor(src, dst):

    neigh = NearestNeighbors(n_neighbors=1)
    neigh.fit(dst)
    distances, indices = neigh.kneighbors(src, return_distance=True)
    return distances.ravel(), indices.ravel()


def icp(A, B, init_pose=None, max_iterations=20, tolerance=0.001):
    

    # get number of dimensions
    m = A.shape[1]

    # make points homogeneous, copy them to maintain the originals
    src = np.ones((m+1,A.shape[0]))
    dst = np.ones((m+1,B.shape[0]))
    src[:m,:] = np.copy(A.T)
    dst[:m,:] = np.copy(B.T)

    # apply the initial pose estimation
    if init_pose is not None:
        src = np.dot(init_pose, src)

    prev_error = 0

    for i in range(max_iterations):
        # find the nearest neighbors between the current source and destination points
        distances, indices = nearest_neighbor(src[:m,:].T, dst[:m,:].T)

        # compute the transformation between the current source and nearest destination points
        T,_,_ = best_fit_transform(src[:m,:].T, dst[:m,indices].T)

        # update the current source
        src = np.dot(T, src)

        # check error
        mean_error = np.mean(distances)
        if np.abs(prev_error - mean_error) < tolerance:
            break
        prev_error = mean_error

    # calculate final transformation
    T,_,_ = best_fit_transform(A, src[:m,:].T)

    return T, distances, i
#%%
point_clouds = get_point_cloud_list()
size = len(point_clouds)
# size = 10
matrix_list = []
final_point_cloud = point_clouds[0]
for i in range(0, size-1):
    print(f"Executing {i+1} to {i}")
    source = point_clouds[i+1]
    target = point_clouds[i]
    transformation = get_transformation_myVersion(source,target)
    matrix_list.append(transformation)

ET_point = [[0,0,0]]
trans_matrix = np.identity(4)
bbox = open3d.geometry.AxisAlignedBoundingBox(np.array([-50, -2, -50]).T, np.array([50, 0.6, 50]).T)
for i in range(1, size):
    trans_matrix = np.dot(trans_matrix, matrix_list[i-1])
    point_clouds[i].transform(trans_matrix)
    ET_point.append(trans_matrix[0:3,3].T)
    final_point_cloud += point_clouds[i]
# %%
open3d.io.write_point_cloud(os.path.join(path,"self.pcd"), final_point_cloud)
pcd = open3d.io.read_point_cloud(os.path.join(path,"self.pcd"))
open3d.visualization.draw_geometries([pcd])
