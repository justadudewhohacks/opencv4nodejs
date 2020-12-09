const cv = require('../');

const findMatchingTemplate = async () => {
  // Load images
  const sourceImgMat = await cv.imreadAsync(`${__dirname}/../data/source.jpg`);
  const subImgMat = await cv.imreadAsync(`${__dirname}/../data/sub-img.jpg`);

  // Match template (the brightest locations indicate the highest match)
  const matched = sourceImgMat.matchTemplate(subImgMat, cv.TM_CCOEFF_NORMED);
  
  // Get all matched data as an array
  let dataList = matched.getDataAsArray();

  const threshold = 0.8;
  for (let y = 0; y < dataList.length; y++) {
    for (let x = 0; x < dataList[y].length; x++) {
    
      // Filter by threshold
      if (dataList[y][x] > threshold) {
      
        // Draw bounding rectangle
        sourceImgMat.drawRectangle(
          new cv.Rect(x, y, subImgMat.cols, subImgMat.rows),
          new cv.Vec3(0, 0, 255),
          2,
          cv.LINE_8
        );
        
      }
    }
  }

  // Open result in new window
  cv.imshow('multiple matches', bigImgMat);
  cv.waitKey();
}

findMatchingTemplate();
