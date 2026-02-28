
Progress Through Screen shots 

1. 2026-01-23 ( sphere and triangle intersection )
![Screenshot 2026-01-23 012757.png](assets/media/Screenshot%202026-01-23%20012757.png)
2. 2026-01-23 (multiple reflections)
![Screenshot 2026-01-23 234930.png](assets/media/Screenshot%202026-01-23%20234930.png)
3. 2026-01-24 ( custom geometry file format ,BVH)
![Screenshot 2026-01-24 211750.png](assets/media/Screenshot%202026-01-24%20211750.png)
4. 2026-01-25 ( Path tracing , solve the rendering equation using monte carlo)
![Screenshot 2026-02-17 233034.png](assets/media/Screenshot%202026-02-17%20233034.png)


ToDo List
1. improve BVH struct size and reduce random memory accesses for better cache performance

#Requirements 

CMake ≥ 3.20
C++ compiler with C++20 support(gcc 11+ or clang 14+)
Make

#Setup

git clone <repo-url>
cd PathTracer

mkdir build 
cd build 

cmake..
make 

this will produce an executable in build/PathTracer

output image will be written to assets/output.ppm


