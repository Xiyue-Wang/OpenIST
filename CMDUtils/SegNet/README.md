**SegNet** is an utility, based on tiny-dnn, for SegNet-like architecture CNN training,
but it also support single image segmentation as testing option

"Comand line utility for the image segmentation by means of CNN"
"\n To train CNN use:"
"\n -i[dirname]  - directory with training data*"
"\n -o[filename] - name for the output file with trained network"
"\n -e[int] - number of training epoch (ref. to tiny-dnn doc.)"
"\n -m[int] - minibatch size for training (ref. to tiny-dnn doc.)"
"\n -c[int] - to what cols training images should be resized"
"\n -r[int] - to what rows training images should be resized"
"\n -x[int] - desired number of input channels (0 means same as in source)"
"\n -y[int] - desired number of output channels (0 means same as in source)"
"\n To segment image by CNN:"
"\n -n[filename] - name for the file with pretrained network"
"\n -s[filename] - image for segmentation"
"\n -a[filename] - where to save segmented image"
"\nAlex A. Taranov, based on Qt, Opencv and tiny-dnn" 
