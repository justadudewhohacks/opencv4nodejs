### How to run the code

Command line usage for object detection using YOLOv3 

* Python

  * Using CPU

    * A single image:
 ```bash
 ts-node object_detection_yolo.ts --image=bird.jpg --device 'cpu'
 ```

    * A video file:
 ```bash
 ts-node object_detection_yolo.ts --video=run.mp4 --device 'cpu'
 ```

  * Using GPU

    * A single image:
 ```bash
 ts-node object_detection_yolo.ts --image=bird.jpg --device 'gpu'
 ```

    * A video file:
 ```bash
 ts-node object_detection_yolo.ts --video=run.mp4 --device 'gpu'
 ```
