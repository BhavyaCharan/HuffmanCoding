There are two codes -

1) userinput_huffman.c - Allows the user to enter an array (equivalent to an image matrix) for them to see how huffman codes are generated for the values present in the matrix. In the image matrix these values represent the intensity values.
  
2) huffman.c - Performs actual image compression on the image "huff3.bmp".
This code only works on images in the bmp format (as it uses the specific formatting of bmp images to extract specifications about the size of the image, etc). The image and the code must be present in the same folder. Both the codes can be compiled normally using the command "gcc huffman.c -o huffman" and run using "./huffman". 
The code first reads the specifications of the image such as its size, offset for the actual data, etc. Then the intensity values of every pixel is read and stored in the 2d array - image. 
Next a histogram of the different intensity values is generated. The data of every node is stored in the structures - huffcode and pixfreq. The nodes in the tree will contain those intensity values which have non zero frequencies. Initially the data is filled into an array of these structures. Then the huffcode array is sorted in decreasing order. After this, the huffman tree is built by combining the nodes with the smallest proability(last two nodes of huffcode array) and creating a new node with the probability as the sum of the two children nodes. This is done till there is only one node left (root with a probability 1). Once the tree is built, the codes for each node () are assigned starting from the parent. The left child is assigned a value of 0 and right is 1. This is done by concatenating the code of parent node with 0 or 1 for either child and progressing downwards.
These codes are now used to represent the intensity of each pixel. This method ensures that the more frequent intensities will get a shorter code as compared to the less frequently occuring intensities. This reduces the space required to store data.

The output of the code is a new file with the encoded image. The codes for the corresponding intensities is also printed to stdout.
