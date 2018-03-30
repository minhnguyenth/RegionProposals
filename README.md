# Region Proposals Using OpenCv
Region proposal algorithms use segmentation to group different regions with similar aspect like color, texture... 
, 
A region proposal algorithm needs to have very high recall rate in order to be considered effective. That means, it's ok to have false positive bounding boxes as long it catches all tru positive objects.

This implementation is for Selective search, one variant of region proposal methods. The procedure of the SS is as below:

1. Over-segmenting the image based on intensity of the pixels using a graph-based segmentation method by Felzenszwalb and Huttenlocher.
2. Add all bounding boxes corresponding to segmented parts to the list of regional proposals
3. Group adjacent segments based on similarity
4. Go to step 2

Selective search measure similarities between 2 adjacent regions based on color, texture, size and shape.

Credit: learnopencv.org
