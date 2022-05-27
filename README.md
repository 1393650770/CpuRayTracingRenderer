
# CpuRayTracingRenderer
<pre>
github.com/AlDanial/cloc v 1.92  T=0.17 s (275.6 files/s, 31855.9 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C/C++ Header                    24            603            263           2809
C++                             24            343            170           1360
-------------------------------------------------------------------------------
SUM:                            48            946            433           4169
-------------------------------------------------------------------------------
</pre>

## How To Build This Project
You should download the Cmake from this link:
https://cmake.org/

And you should download the Vcpkg from this link:
https://github.com/microsoft/vcpkg

( I also push the Vcpkg tools into the project . You can use it easily. )

And then , I will show how to build this project by Cmake GUI . You can see the operation instruction in the follow picture . Good luck to you building it .

![image](https://github.com/1393650770/CpuRayTracingRenderer/blob/main/image/operation_instruction_picture.png)
## Show The Render Result [1 Spp]
DIFFUSE MATERIAL:
![image](https://github.com/1393650770/CpuRayTracingRenderer/blob/main/image/result-Level-DIFFUSE.png)
PBR MATERIAL:
![image](https://github.com/1393650770/CpuRayTracingRenderer/blob/main/image/result-Level-PBR.png)
## Feature(Already done)


### ① My Math Library --- TinyGlm
### ---Library Supported Data Types : Vec2 Vec3 Vec4 Mat4
#### Vector Supported :
 - [x] Template
 - [x] Add / Sub / Div / Mul
 - [x] Dot / Cross
 - [x] Normalize / Length

#### Matrix Supported :
 - [x] Template
 - [x] Add/ Sub / Div / Mul
 - [x] Cofactor / Adjoint
 - [x] Transpose / Inverse
 - [x] Multiply with vector
### ② Multithreading Acceleration Rendering
 - [x] Thread Pool
 - [x] Message Queue
### ③ Light Transport Algorithm
 - [x] Path Tracing
### ④ Space Accelerating Structurer
 - [x] BVH
### ⑤ Object
 - [x] Sphere
 - [x] Rectangle
 - [x] Triangle
 - [x] MeshTriangle
### ⑥ Material
 - [x] Diffuse
 - [x] Microfacet BRDF
### ⑦ Sampling
 - [x] Cos-Weighted Importance Sampling
 - [x] BRDF Importance Sampling
### ⑧ Light
 - [x] SphereLight (PointLight)
 - [x] AreaLight
### ⑨ Camera
 - [x] Perspective Camera

### ⑩ Tool
 - [x] Toon-mapping
 - [x] NormalSpace To WorldSpace
 - [x] Random number generator

## Feature(To done list)
### ① Light Transport Algorithm
 - [ ] BDPT, Bidirectional Path Tracing
 - [ ] MLT, Metropolis Light Transport
 - [ ] SPPM, Stochastic Progress Photon Mapping
### ② Space Accelerating Structurer
 - [ ] SAH
 - [ ] Octree
### ③ Object(Maybe will do)
 - [ ] OBJLoader
 - [ ] Texture
### ④ Material
 - [ ] Dielectrics
 - [ ] BSSRDF 
### ⑤ Sampling
 - [ ] Importance Sampling
 - [ ] Multiple Importance Sampling
### ⑥ Post process
 - [ ] TAA
### ⑦ Tool




