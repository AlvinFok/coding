## Training segmentation model
- hrnetv2
- 1000 training images
- batch_size_per_gpu: 6
-  num_epoch: 50
-  epoch_iters: 100
-  Model trained on apartment_0's training result
   -  ![model2 result](/HW2/readme/model1.png)
- Model trained on apartment_0's val result 
   - ![model2 val result](/HW2/readme/1-1.png)
-  Model trained on apartment_0's training result
   -  ![model2 result](/HW2/readme/model2.png)
- Model trained on apartment_0's val result 
   - ![model2 val result](/HW2/readme/2-2.png)

## How to run the program
- You need to have this file structure as follows
```
data
|
└───rgb
|   |   1.png
|   |   2.png
|   |   3.png
|
└───model1
|   |   1.png
|   |   2.png
|   |   3.png
|
└───model2
|   |   1.png
|   |   2.png
|   |   3.png
|
└───truth
|   |   1.png
|   |   2.png
|   |   3.png

```

## Custom voxel down
![voxel](/HW2/readme/voxel.png)

## Result
- Semantic map (trained on other scenes)
- ![](/HW2/readme/mode1_result.png)
- Semantic map (trained on apartment_0)
- ![](readme/model2_result.png)
- Semantic map (ground truth)
- ![](readme/truth_result.png)