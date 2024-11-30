copy paste to compile and run
> nasm -f win64 MP2SASM.asm
> gcc -c MP2C.c -o MP2C.obj -m64
> gcc MP2C.obj MP2SASM.obj -o MP2C.exe -m64
> MP2C.exe

Members:
Belardo, Gerard
Yu, Cedric

i.) execution time and short analysis of the performance


The average execution times, measured over 30 runs for different input sizes and pixel value scenarios, are shown in the table:

+-------------------+----------------------------+----------------------------------+
| Input Size        | Same Pixel Values (ns)     | Different Pixel Values (ns)      |
+-------------------+----------------------------+----------------------------------+
| 10 x 10           | 226.67                     | 446.67                           |
| 100 x 100         | 17,366.67                  | 15,033.33                        |
| 1000 x 1000       | 1,125,430.00               | 685,426.67                       |
+-------------------+----------------------------+----------------------------------+

Performance analysis

The algorithm processes each pixel in the input image by sequentially applying several operations: loading the floating-point value from memory, 
multiplying it by 255 using SIMD instructions (mulss), rounding the result to the nearest integer (roundss), converting it to an integer (cvttss2si), 
and storing the resulting value in the output array. Moreover, applying the concepts in our algorithms and complexity course, the algorithm has a 
linear time complexity of O(n x m), where the n x m value represents the total number of pixels.

The execution times show that the performance scales predictably with the image size. Smaller array size such as those 10 x 10 ones tends to have higher 
per pixel costs which could probably stem from register initialization and how the loop was set up. On the other hand, larger arrays, such as the 100 x 100 
ones scales proportionally better with the number or amount of pixels.

Pixel uniformity affects performance differently for small and larger arrays. In better terms, smaller arrays leads to faster processing because of simpler 
memory access. While in larger arrays, the access efficiency and time takes up the execution time reduces the impact of uniformity.

Moreover, The program uses SIMD (Single Instruction Multiple Data) to handle floating-point operations more efficiently, which makes it faster. For larger 
images, the program reads and writes pixel data in a straightforward order, which works well with the CPU's cache. But when the image becomes too big to 
fit in the cache, the CPU has to fetch data from slower memory, which slows the program down. 



