Jordan Coffland and Mohammed Bataineh Huffman Encoding
------------------------------------------------------
File List: hcompress.c, linkedList.c, linkedList.h, hcompress.h
To run: Put all of these files in a directory together, naviagate to the directory, run the command 
$ gcc hcompress.c linkedList.c  -o hcompress
followed by ./hcompress -e 'fileName'

Things we got working:
createFreqTable: 
	This was probably our most comfortable part of the assignment. We malloced 128 tnodes and then
 	incremented the weight of the tnode at the same spot as the ascii value of the char.

createHuffmanTree:
	Then we handed that to create huffman tree which walked through the list picking out all of the nodes that 
	had a weight > 0. We used the greedy algorithm until we were down to one final parent node.

encode :
	This works by using some bit manipulation using &. Our biggest problem was flipping the bits before we 
	handed it off to the buffer, which we used bit-masking to flip the order of. The buffer then put it in the .huf file.

Things we did not get working:

encode(Continued):
	Although we did a good job of putting the codes into the file, we struggled to find a way to signify the end
 	of the file and store the tree in the file.  This made it impossible to decode since we could not pass the tree 
	back into the file.

decode:
	 If we would have been able to do decode we would have followed the code down the tree following the
	left child if it was 1 and a right if the number was a 0. Once we got to a leaf we would finally have put the
 	letter of that tnode into the file, repeating until we found the end of file char.