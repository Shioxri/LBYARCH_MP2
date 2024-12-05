copy paste to compile and run
> nasm -f win64 MP2SASM.asm
> gcc -c MP2C.c -o MP2C.obj -m64
> gcc MP2C.obj MP2SASM.obj -o MP2C.exe -m64
> MP2C.exe

Members:
Belardo, Gerard Vito
Yu, Cedric



i.) execution time and short analysis of the performance (found below)
ii.) attached as CorrectnessCheck.png as well as shown on the video
iii.)
Demo Video:
https://drive.google.com/file/d/1nquCxVRIP52pj-v7-YxUhhgKjKT3e05c/view?usp=sharing




Device Used for Testing: Legion 5 16IRX9
Specs:
Processor: 13th Gen Intel(R) Core(TM) i7-13650HX 2.60 GHz
RAM: 16 GB
System: 64-Bit OS, x64-based processor 

The average execution times, measured over 30 runs for different input sizes and pixel value scenarios, are shown in the table:

+-------------------+----------------------------+----------------------------------+
| Input Size        | Same Pixel Values (ns)     | Different Pixel Values (ns)      |
+-------------------+----------------------------+----------------------------------+
| 10 x 10           | 226.67                     | 446.67                           |
| 100 x 100         | 17,366.67                  | 15,033.33                        |
| 1000 x 1000       | 1,125,430.00               | 685,426.67                       |
+-------------------+----------------------------+----------------------------------+

Performance analysis:

The algorithm processes each pixel in the input image by sequentially performing several operations: loading the floating-point value from memory, 
multiplying it by 255 (based on the given specs), using SIMD instructions (mulss), rounding the result with Round-To-Nearest-Ties-To-Even 
(roundss, with 0x00 determining the rounding type), converting it to an integer (cvttss2si), and finally storing the resulting value in the output array. 
Moreover, applying the concepts in our algorithms and complexity course, the algorithm has a linear time complexity of O(n x m), 
where the n x m value represents the total number of pixels/elements in the array.

The execution times show that the performance scales predictably with the image size. Smaller array size such as those 10 x 10 ones tends to have higher 
per pixel costs which could probably stem from register initialization and how the loop was set up. On the other hand, larger arrays, such as the 100 x 100 
ones scales proportionally better with the number or amount of pixels.

Pixel uniformity affects performance differently for small and larger arrays. In other words, smaller arrays leads to faster processing because of simpler 
memory access. While in larger arrays, the access efficiency and time takes up the execution time reduces the impact of uniformity.

Moreover, The program uses SIMD (Single Instruction Multiple Data) to handle floating-point operations more efficiently, which makes it faster. For larger 
images, the program reads and writes pixel data in a straightforward order, which works well with the CPU's cache. But when the image becomes too big to 
fit in the cache, the CPU has to fetch data from slower memory, which slows the program down. 



