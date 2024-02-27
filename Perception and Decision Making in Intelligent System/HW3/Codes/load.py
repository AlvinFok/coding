import numpy as np
from PIL import Image
from time import sleep
import numpy as np
import math
import os
import shutil
import habitat_sim
from habitat_sim.utils.common import d3_40_colors_rgb
import cv2
import json

# This is the scene we are going to load.
# support a variety of mesh formats, such as .glb, .gltf, .obj, .ply
### put your scene path ###

test_scene = os.path.expanduser("~/Downloads/Replica_Dataset/apartment_0/habitat/mesh_semantic.ply")
path = os.path.expanduser("~/Downloads/Replica_Dataset/apartment_0/habitat/info_semantic.json")

#global test_pic
#### instance id to semantic id 
with open(path, "r") as f:
    annotations = json.load(f)

id_to_label = []
instance_id_to_semantic_label_id = np.array(annotations["id_to_label"])
for i in instance_id_to_semantic_label_id:
    if i < 0:
        id_to_label.append(0)
    else:
        id_to_label.append(i)
id_to_label = np.asarray(id_to_label)
# print(id_to_label)
targets_label = {'refrigerator':67, 'rack':66, 'cushion':29, 'lamp':47, 'cooktop':32}
target_label = None
######

sim_settings = {
    "scene": test_scene,  # Scene path
    "default_agent": 0,  # Index of the default agent
    "sensor_height": 1.5,  # Height of sensors in meters, relative to the agent
    "width": 512,  # Spatial resolution of the observations
    "height": 512,
    "sensor_pitch": 0,  # sensor pitch (x rotation in rads)
}

# This function generates a config for the simulator.
# It contains two parts:
# one for the simulator backend
# one for the agent, where you can attach a bunch of sensors

def transform_rgb_bgr(image):
    
    return image[:, :, [2, 1, 0]]

def transform_depth(image):
    depth_img = (image / 10 * 255).astype(np.uint8)
    return depth_img

def transform_semantic(semantic_obs):
    semantic_img = Image.new("P", (semantic_obs.shape[1], semantic_obs.shape[0]))
    semantic_img.putpalette(d3_40_colors_rgb.flatten())
    semantic_img.putdata((semantic_obs.flatten() % 40).astype(np.uint8))
    semantic_img = semantic_img.convert("RGB")
    semantic_img = cv2.cvtColor(np.asarray(semantic_img), cv2.COLOR_RGB2BGR)
    return semantic_img

def make_simple_cfg(settings):
    # simulator backend
    sim_cfg = habitat_sim.SimulatorConfiguration()
    sim_cfg.scene_id = settings["scene"]
    

    # In the 1st example, we attach only one sensor,
    # a RGB visual sensor, to the agent
    rgb_sensor_spec = habitat_sim.CameraSensorSpec()
    rgb_sensor_spec.uuid = "color_sensor"
    rgb_sensor_spec.sensor_type = habitat_sim.SensorType.COLOR
    rgb_sensor_spec.resolution = [settings["height"], settings["width"]]
    rgb_sensor_spec.position = [0.0, settings["sensor_height"], 0.0]
    rgb_sensor_spec.orientation = [
        settings["sensor_pitch"],
        0.0,
        0.0,
    ]
    rgb_sensor_spec.sensor_subtype = habitat_sim.SensorSubType.PINHOLE

    #depth snesor
    depth_sensor_spec = habitat_sim.CameraSensorSpec()
    depth_sensor_spec.uuid = "depth_sensor"
    depth_sensor_spec.sensor_type = habitat_sim.SensorType.DEPTH
    depth_sensor_spec.resolution = [settings["height"], settings["width"]]
    depth_sensor_spec.position = [0.0, settings["sensor_height"], 0.0]
    depth_sensor_spec.orientation = [
        settings["sensor_pitch"],
        0.0,
        0.0,
    ]
    depth_sensor_spec.sensor_subtype = habitat_sim.SensorSubType.PINHOLE

    #semantic snesor
    semantic_sensor_spec = habitat_sim.CameraSensorSpec()
    semantic_sensor_spec.uuid = "semantic_sensor"
    semantic_sensor_spec.sensor_type = habitat_sim.SensorType.SEMANTIC
    semantic_sensor_spec.resolution = [settings["height"], settings["width"]]
    semantic_sensor_spec.position = [0.0, settings["sensor_height"], 0.0]
    semantic_sensor_spec.orientation = [
        settings["sensor_pitch"],
        0.0,
        0.0,
    ]
    semantic_sensor_spec.sensor_subtype = habitat_sim.SensorSubType.PINHOLE

    # agent
    agent_cfg = habitat_sim.agent.AgentConfiguration()

    agent_cfg.sensor_specifications = [rgb_sensor_spec, depth_sensor_spec, semantic_sensor_spec]
    ##################################################################
    ### change the move_forward length or rotate angle
    ##################################################################
    agent_cfg.action_space = {
        "move_forward": habitat_sim.agent.ActionSpec(
            "move_forward", habitat_sim.agent.ActuationSpec(amount=0.01) # 0.01 means 0.01 m
        ),
        "turn_left": habitat_sim.agent.ActionSpec(
            "turn_left", habitat_sim.agent.ActuationSpec(amount=1.0) # 1.0 means 1 degree
        ),
        "turn_right": habitat_sim.agent.ActionSpec(
            "turn_right", habitat_sim.agent.ActuationSpec(amount=1.0)
        ),
    }

    return habitat_sim.Configuration(sim_cfg, [agent_cfg])


cfg = make_simple_cfg(sim_settings)
sim = habitat_sim.Simulator(cfg)

# initialize an agent
agent = sim.initialize_agent(sim_settings["default_agent"])

# Set agent state
agent_state = habitat_sim.AgentState()

# obtain the default, discrete actions that an agent can perform
# default action space contains 3 actions: move_forward, turn_left, and turn_right
action_names = list(cfg.agents[sim_settings["default_agent"]].action_space.keys())
print("Discrete action space: ", action_names)





def make_video():
    num = len(os.listdir('rgb'))

    frame = cv2.imread('rgb/1.png')
    height, width, layers = frame.shape
    fourcc = cv2.VideoWriter_fourcc(*'MJPG')
    video = cv2.VideoWriter('Observation.avi', fourcc, 40, (width,height))

    i = 0
    for i in range(1,num+1):
        video.write(cv2.imread('rgb/%d.png' % i))
        print("########", i, "/", num, "########")
        i += 1

    cv2.destroyAllWindows()
    video.release()

def navigateAndSee(action="", steps=1):
    if action in action_names:

        observations = sim.step(action)

        img = transform_rgb_bgr(observations["color_sensor"])
        img_semantic = id_to_label[observations["semantic_sensor"]]

        target_location = np.where(img_semantic == target_label)
        mask = np.array((0, 0, 255), dtype = np.uint8)

        for x, y in zip(target_location[0], target_location[1]):
            img[x,y] = (cv2.addWeighted(img[x,y], 0.8, mask, 0.2, 1.0)).reshape(3)

        cv2.imshow("RGB", img)
        cv2.imwrite("rgb/%s.png" % str(steps), img)

        agent_state = agent.get_state()
        sensor_state = agent_state.sensor_states['color_sensor']
        # print("camera pose: x y z rw rx ry rz")
        # print(sensor_state.position[0],sensor_state.position[1],sensor_state.position[2],  sensor_state.rotation.w, sensor_state.rotation.x, sensor_state.rotation.y, sensor_state.rotation.z)

def start_navigate(navigate, target_name):
    try:
        shutil.rmtree("rgb")
    except:
        pass
    finally:
        os.mkdir("rgb")

    global target_label
    target_label = targets_label[target_name]
  
    agent_state.position = np.array([navigate[0][1], 0., navigate[0][0]])  # agent in world space
    agent.set_state(agent_state)
    
    action = "move_forward"
    navigateAndSee(action)

    pre_vector = (-1., 0.)
    cur_vector = np.subtract(navigate[1], navigate[0])

    print("=================Start Navigation=================")
    steps = 1
    
    for i in range(1,len(navigate)):
        print("=================", i, "/", len(navigate),"=================")
        
        cur_vector = np.subtract(navigate[i], navigate[i-1])
        
        cos = np.dot(pre_vector, cur_vector) / (np.linalg.norm(pre_vector) * np.linalg.norm(cur_vector))
        degree = int(round(math.acos(cos)/math.pi*180, 0))
        length = int(np.linalg.norm(cur_vector)*100)  # cm

        cross_product = np.cross(pre_vector, cur_vector)    # decide turn left or right        

        if cross_product > 0:
            action = 'turn_left'
        elif cross_product < 0:
            action = 'turn_right'

        while degree:
            navigateAndSee(action, steps)
            # print("action: ", action)
            degree -= 1
            steps += 1

        while length:
            navigateAndSee('move_forward', steps)  
            # print("action: FORWARD")
            length -= 1
            steps += 1

        pre_vector = cur_vector

    print("=================Start Making Video=================")
    make_video()


if __name__ == '__main__':
    file = open("../Map/path.txt")
    path = [(float(i.split(",")[0]), float(i.split(",")[1].replace("\n", ""))) for i in file.readlines()]
    print(path)
    start_navigate(path, "refrigerator")
