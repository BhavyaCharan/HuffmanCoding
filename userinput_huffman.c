#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>

// function to calculate word length 
int codelen(char* code) 
{ 
	int l = 0; 
	while (*(code + l) != '\0') 
		l++; 
	return l; 
}

// function to find fibonacci number 
int fib(int n) 
{ 
	if (n <= 1) 
		return n; 
	return fib(n - 1) + fib(n - 2); 
} 

// Driver code 
int main() 
{ 
	int height;
	int width;
	printf("Enter the height of the image matrix : ");
	scanf("%d",&height);
	printf("Enter the width of the image matrix : ");
	scanf("%d",&width);
	int i,j;
	int** image=(int**)malloc(sizeof(int*)*height);
	for(int i=0;i<height;i++)
	{
		image[i]=(int*)malloc(sizeof(int)*width);
	}
	printf(" ENTER INTENSITY VALUES : \n");
	for(int k=0;k<height;k++)
	{
		for(int l=0;l<width;l++)
		{
			scanf("%d",&image[k][l]);
		}
	}
	
	// Finding the probability 
	// of occurence 
	int hist[256]; 
	for (i = 0; i < 256; i++) 
		hist[i] = 0; 
	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j++) 
		{
			hist[image[i][j]] += 1; 
		}
	}
	
	printf("\n-----------------------------------------------------------------------------------------------------\n\n");
	printf("Input array is => \n");
	for (i = 0; i < height; i++){ 
		for (j = 0; j < width; j++){ 
			printf( "%3d  ", image[i][j]);
		}
		printf("\n");
	}
	
	printf("\nFrequency of each value is => \n");
	for (i = 0; i < height; i++){ 
		for (j = 0; j < width; j++){ 
			printf("%3d  ", hist[image[i][j]]);
		}
		printf("\n");
	}
	
	printf("\n-----------------------------------------------------------------------------------------------------\n\n");
	
	// Finding number of 
	// non-zero occurences 
	int nodes = 0; 
	for (i = 0; i < 256; i++) 
	{
		if (hist[i] != 0) 
			nodes += 1; 
	}
	
	printf("Number of nodes to be present in tree (non-zero intensity values) = %d\n", nodes);
			
	// Calculating minimum probability 
	float p = 1.0, ptemp; 
	for (i = 0; i < 256; i++) 
	{ 	
		if(hist[i]!=0)
		{
			ptemp = (float)(hist[i] / (float)(height*width)); 
			if (ptemp > 0 && ptemp <= p) 
				p = ptemp; 
		
		}
		
	} 

	// Calculating max length 
	// of code word 
	i = 0; 
	while ((1 / p) > fib(i)) 
		i++; 
	int maxcodelen = i - 3;
	
	// Defining Structures pixfreq 
	struct pixfreq 
	{ 
		int pix; 
		float freq; 
		struct pixfreq *left, *right; 
		char code[maxcodelen]; 
	}; 
	
	// Defining Structures 
	// huffcode 
	struct huffcode 
	{ 
		int pix, arrloc; 
		float freq; 
	}; 
	
	// Declaring structs 
	struct pixfreq* pix_freq; 
	struct huffcode* huffcodes; 
	int totalnodes = 2 * nodes - 1; 
	pix_freq = (struct pixfreq*)malloc(sizeof(struct pixfreq) * totalnodes); 
	huffcodes = (struct huffcode*)malloc(sizeof(struct huffcode) * nodes); 
	
	// Initializing 
	j = 0; 
	int totpix = height * width; 
	float tempprob; 
	for (i = 0; i < 256; i++) 
	{ 
		if (hist[i] != 0) 
		{ 
			
			// pixel intensity value 
			huffcodes[j].pix = i; 
			pix_freq[j].pix = i; 
			
			// location of the node 
			// in the pix_freq array 
			huffcodes[j].arrloc = j; 
			
			// probability of occurrence 
			tempprob = (float)hist[i] / (float)totpix; 
			pix_freq[j].freq = tempprob; 
			huffcodes[j].freq = tempprob; 
			
			// Declaring the child of leaf 
			// node as NULL pointer 
			pix_freq[j].left = NULL; 
			pix_freq[j].right = NULL; 
			
			// initializing the code 
			// word as end of line 
			pix_freq[j].code[0] = '\0'; 
			j++; 
		} 
	} 
	
	// Sorting the histogram 
	struct huffcode temphuff; 
	
	// Sorting w.r.t probability 
	// of occurence 
	for (i = 0; i < nodes; i++) 
	{ 
		for (j = i + 1; j < nodes; j++) 
		{ 
			if (huffcodes[i].freq < huffcodes[j].freq) 
			{ 
				temphuff = huffcodes[i]; 
				huffcodes[i] = huffcodes[j]; 
				huffcodes[j] = temphuff; 
			} 
		} 
	} 
	
	printf("\n\nPixel frequency array => \n");
	for (i = 0; i < nodes; i++){
		if (pix_freq[i].code[0] == '\0')
			printf("Index %d ---- Intensity = %d, Frequency = %f Code = NULL\n", i, pix_freq[i].pix, pix_freq[i].freq);
		else
			printf("Index %d ---- Intensity = %d, Frequency = %f Code = %s\n", i, pix_freq[i].pix, pix_freq[i].freq, pix_freq[i].code );
	}
	
	printf("\nSorted huffcode array => \n");
	for (i = 0; i < nodes; i++){
		printf("Index %d ---- Intensity = %d, Frequency = %f Location of this node in pix array = %d\n", i, huffcodes[i].pix, huffcodes[i].freq, huffcodes[i].arrloc);
	}
	
	// Building Huffman Tree 
	float sumprob; 
	int sumpix; 
	int n = 0, k = 0; 
	int nextnode = nodes; 
	
	// Since total number of 
	// nodes in Huffman Tree 
	// is 2*nodes-1
	
	printf("\n\n-----------------------------------------------------------------------------------------------------\n\n");
	printf("\t\tBuilding the huffman tree\n\n"); 
	while (n < nodes - 1) 
	{ 
		
		// Adding the lowest two probabilities 
		sumprob = huffcodes[nodes - n - 1].freq + huffcodes[nodes - n - 2].freq; 
		sumpix = huffcodes[nodes - n - 1].pix + huffcodes[nodes - n - 2].pix; 
		
		// Appending to the pix_freq Array 
		pix_freq[nextnode].pix = sumpix; 
		pix_freq[nextnode].freq = sumprob; 
		pix_freq[nextnode].left = &pix_freq[huffcodes[nodes - n - 2].arrloc]; 
		pix_freq[nextnode].right = &pix_freq[huffcodes[nodes - n - 1].arrloc]; 
		pix_freq[nextnode].code[0] = '\0'; 
		i = 0; 
		
		// Sorting and Updating the 
		// huffcodes array simultaneously 
		// New position of the combined node 
		while (sumprob <= huffcodes[i].freq) 
		{
			i++; 
		}	
		// Inserting the new node 
		// in the huffcodes array 
		for (k = nodes-1; k >= 0; k--) 
		{ 
			if (k == i) 
			{ 
				huffcodes[k].pix = sumpix; 
				huffcodes[k].freq = sumprob; 
				huffcodes[k].arrloc = nextnode; 
			} 
			else if (k > i) 
			
				// Shifting the nodes below 
				// the new node by 1 
				// For inserting the new node 
				// at the updated position k 
				huffcodes[k] = huffcodes[k - 1]; 
			
		}
		n += 1; 
		nextnode += 1; 
	} 
	
	printf("\n\nModified Pixel frequency array => \n");
	for (i = 0; i < nextnode; i++){
		if (pix_freq[i].code[0] == '\0')
			printf("Index %d ---- Intensity = %d, Frequency = %f Code = NULL\n", i, pix_freq[i].pix, pix_freq[i].freq);
		else
			printf("Index %d ---- Intensity = %d, Frequency = %f Code = %s\n", i, pix_freq[i].pix, pix_freq[i].freq, pix_freq[i].code );	
	}
	
	printf("\nModified and sorted Huffcode array => \n");
	for (i = 0; i < nodes; i++){
			printf("Index %d ---- Intensity = %d, Frequency = %f Location of this node in pix array = %d\n", i, huffcodes[i].pix, huffcodes[i].freq, huffcodes[i].arrloc);
	}

	// Assigning Code through 
	// backtracking 
	
	char left1[2]="0";
	char right1[2]="1";
	char* left=left1;
	char* right=right1;
	int index; 

	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("\t\tAssigning of codes\n\n");
	for (i = totalnodes - 1; i >= nodes; i--) 
	{
		printf("checking parent intensity %d\n", pix_freq[i].pix);
		if (pix_freq[i].left != NULL) 
		{
			strcat(pix_freq[i].left->code,pix_freq[i].code);
			strcat(pix_freq[i].left->code,left);
			if (pix_freq[i].code[0] == '\0')
			printf("\tassigning the left child of intensity %d, parent code = NULL, new left child code = %s\n", pix_freq[i].left->pix, pix_freq[i].left->code);
			else
			printf("\tassigning the left child of intensity %d, parent code = %s, new left child code = %s\n", pix_freq[i].left->pix, pix_freq[i].code, pix_freq[i].left->code);
		}
		
		if (pix_freq[i].right != NULL)
		{
			strcat(pix_freq[i].right->code,pix_freq[i].code);
			strcat(pix_freq[i].right->code,right);
			if (pix_freq[i].code[0] == '\0')
			printf("\tassigning the right child of intensity %d, parent code = NULL, new right child code = %s\n", pix_freq[i].left->pix, pix_freq[i].right->code);
			else
			printf("\tassigning the right child of intensity %d, parent code = %s, new right child code = %s\n", pix_freq[i].left->pix, pix_freq[i].code, pix_freq[i].right->code);
		}
	} 
	
	// Printing Huffman Codes 
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("\t\tHuffmann Codes\n\n"); 
	printf("pixel values -> Code\n"); 
	for (i = 0; i < nodes; i++) 
	{
			printf("%d -> %s\n", pix_freq[i].pix, pix_freq[i].code); 
		
	}
} 
