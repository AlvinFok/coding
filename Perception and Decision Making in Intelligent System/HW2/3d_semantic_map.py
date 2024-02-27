#%%
import open3d
import os
import numpy as np
import copy
#%%

def get_point_cloud_list(path, floder):
    point_clouds = []
    file_list = os.listdir(os.path.join(path, floder))
    file_list = sorted(file_list, key=lambda x: int(x.split(".")[0]))
    # print(file_list)
    for index, file in enumerate(file_list):
        # print(os.path.join(path,"rgb",file))
        rgb_image = open3d.io.read_image(os.path.join(path, floder, file))
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

def generate_point_cloud(path):
    point_clouds_rgb = get_point_cloud_list(path, "rgb")
    size = len(point_clouds_rgb)
    # size = 10
    matrix_list = []
    # final_point_cloud = point_clouds[0]
    for i in range(0, size-1):
        print(f"Executing {i+1} to {i}")
        source = point_clouds_rgb[i+1]
        target = point_clouds_rgb[i]
        transformation = get_transformation(source,target)
        matrix_list.append(transformation)


    trans_matrix = np.identity(4)
    # bbox = open3d.geometry.AxisAlignedBoundingBox(np.array([-50, -2, -50]).T, np.array([50, 0.6, 50]).T)
    point_clouds_model1 = get_point_cloud_list(path, "model1")
    point_clouds_model2 = get_point_cloud_list(path, "model2")
    point_clouds_truth = get_point_cloud_list(path, "truth")
    print("Transforming")
    point_clouds_model1_all = point_clouds_model1[0]
    point_clouds_model2_all = point_clouds_model2[0]
    point_clouds_truth_all = point_clouds_truth[0]
    point_clouds_rgb_all = point_clouds_rgb[0]
    for i in range(1, size):
        trans_matrix = np.dot(trans_matrix, matrix_list[i-1])
        point_clouds_model1[i].transform(trans_matrix)
        point_clouds_model2[i].transform(trans_matrix)
        point_clouds_truth[i].transform(trans_matrix)
        point_clouds_rgb[i].transform(trans_matrix)

        point_clouds_model1_all += point_clouds_model1[i]
        point_clouds_model2_all += point_clouds_model2[i]
        point_clouds_truth_all += point_clouds_truth[i]
        point_clouds_rgb_all += point_clouds_rgb[i]
    bbox = open3d.geometry.AxisAlignedBoundingBox(np.array([-50, -0.000168519, -50]).T, np.array([50, 0, 50]).T)
    open3d.io.write_point_cloud(os.path.join(path,"rgb.pcd"), point_clouds_rgb_all.crop(bbox))
    open3d.io.write_point_cloud(os.path.join(path,"model1.pcd"), point_clouds_model1_all.crop(bbox))
    open3d.io.write_point_cloud(os.path.join(path,"model2.pcd"), point_clouds_model2_all.crop(bbox))
    open3d.io.write_point_cloud(os.path.join(path,"truth.pcd"), point_clouds_truth_all.crop(bbox))

#%%

path = os.path.expanduser("~/Downloads/Data/first floor/")
generate_point_cloud(path)
# %%
import open3d
import numpy as np
path = os.path.expanduser("~/Downloads/Data/first floor/")
bbox = open3d.geometry.AxisAlignedBoundingBox(np.array([-50, -0.000168515, -50]).T, np.array([50, 0, 50]).T)
pcd = open3d.io.read_point_cloud(os.path.join(path,"truth.pcd"), format="pcd")
print(pcd.get_axis_aligned_bounding_box())
# print(bbox)
pcd =pcd.crop(bbox)
open3d.visualization.draw_geometries([pcd])
# %%
import open3d
import numpy as np
pcd = open3d.io.read_point_cloud(os.path.join(path,"turth.pcd"), format="pcd")
points = np.asarray(pcd.points).T
print(points.shape)
voxel_size=10
nb_vox=np.ceil((np.max(points, axis=0) - np.min(points, axis=0))/voxel_size)
non_empty_voxel_keys, inverse, nb_pts_per_voxel = np.unique(((points - np.min(points, axis=0)) // voxel_size).astype(int), axis=0, return_inverse=True, return_counts=True)
idx_pts_vox_sorted=np.argsort(inverse)
voxel_grid={}
grid_barycenter,grid_candidate_center=[],[]
last_seen=0
for idx,vox in enumerate(non_empty_voxel_keys):
    voxel_grid[tuple(vox)]= points[idx_pts_vox_sorted[last_seen:last_seen+nb_pts_per_voxel[idx]]]
    grid_barycenter.append(np.mean(voxel_grid[tuple(vox)],axis=0))
    grid_candidate_center.append(
   voxel_grid[tuple(vox)][np.linalg.norm(voxel_grid[tuple(vox)] -
   np.mean(voxel_grid[tuple(vox)],axis=0),axis=1).argmin()])
    last_seen+=nb_pts_per_voxel[idx]
#%%
print(np.asarray(grid_barycenter).shape)
print(np.asarray(grid_candidate_center).shape)
print(grid_candidate_center[0])
# %%
import open3d
import numpy as np
path = os.path.expanduser("~/Downloads/Data/first floor/")
def voxel_filter(point_cloud, leaf_size):
    filtered_points = []
    
    
    point_cloud = point_cloud.T
    # print(point_cloud.shape)
    # print(np.max(point_cloud[0]), np.min(point_cloud[0]))
    x_max, x_min = np.max(point_cloud[0]), np.min(point_cloud[0])
    y_max, y_min = np.max(point_cloud[1]), np.min(point_cloud[1])    
    z_max, z_min = np.max(point_cloud[2]), np.min(point_cloud[2])
    point_cloud = point_cloud.T
    
    size_r = leaf_size
    
    Dx = (x_max - x_min)/size_r
    Dy = (y_max - y_min)/size_r
    Dz = (z_max - z_min)/size_r
    
    h = list()
    
    for i in range(len(point_cloud)):
        hx = np.floor((point_cloud[i][0] - x_min)/size_r)
        hy = np.floor((point_cloud[i][1] - y_min)/size_r)
        hz = np.floor((point_cloud[i][2] - z_min)/size_r)
        h.append(hx + hy*Dx + hz*Dx*Dy)
    
    h = np.array(h)
    h_indice  = np.argsort(h)   
    h_sorted = h[h_indice]      
    count = 0 
    
    for i  in range(len(h_sorted)-1):      
        if h_sorted[i] == h_sorted[i+1]:   
            continue
        else:
            point_idx = h_indice[count: i+1]
            filtered_points.append(np.mean(point_cloud[point_idx],axis=0))   
            count = i
            

    filtered_points = np.array(filtered_points, dtype=np.float64)
    return filtered_points

import open3d
import numpy as np
pcd = open3d.io.read_point_cloud(os.path.join(path,"rgb.pcd"), format="pcd")
points = np.asarray(pcd.points)
print(points.shape)
points = voxel_filter(points,0.05)
print(points.shape)
point_cloud_o3d_filter = open3d.geometry.PointCloud()
point_cloud_o3d_filter.points = open3d.utility.Vector3dVector(points)
open3d.visualization.draw_geometries([point_cloud_o3d_filter])
# %%
