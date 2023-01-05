## Training YOLOv3 Object Detector - Snowman

1. Install deps:

```bash
pnpm install
pnpm install -g ts-node typescript @types/node
```

optional 
`export NODE_OPTIONS="-r ts-node/register --no-warnings"`

2. Get the relevant OpenImages files needed to locate images of our interest and OpenImagesV4

```bash
ts-node getDataFromOpenImages_snowman.ts
```

3. Create the train-test split

```bash
ts-node splitTrainAndTest.ts JPEGImages
```

4. Install Darknet, compile it and Get the pretrained model
```
bash
cd ~;
git clone https://github.com/sowson/darknet-vNext;
cd darknet-vNext;
```

edit Makefile first lines:
- GPU=0
- CUDNN=0
- OPENCV=0
- OPENMP=0
- DEBUG=0
enable the option you want

```
make
exit
```

5. Start the training as below, by giving the correct paths to all the files being used as arguments

```bash
wget https://pjreddie.com/media/files/darknet53.conv.74 -O darknet53.conv.74
~/darknet-vNext/darknet detector train darknet.data darknet-yolov3.cfg darknet53.conv.74 > train.log
```

after some time you will get a `./weights/darknet-yolov3_final.weights` files

6. Give the correct path to the modelConfiguration and modelWeights files in object_detection_yolo.py and test any image or video for snowman detection, e.g.

`ts-node object_detection_yolo.ts --image=JPEGImages/f5c2d861f2105ec9.jpg`

ported from [YOLOv3-Training-Snowman-Detector](https://github.com/spmallick/learnopencv/tree/master/YOLOv3-Training-Snowman-Detector)