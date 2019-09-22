process.env.OPENCV4NODES_DEBUG_REQUIRE = true

if (!require('opencv4nodejs')) {
  throw new Error('failed to require opencv4nodejs')
}