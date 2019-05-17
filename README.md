# What this is all about
Dear traveller You might not find question here for thy answer is 42 but hopefully some helpful information about hardware 842 compression executed on a Ultra96 board. The implementation uses the programmable logic chip provided on this board to accelerate the compression process. The codefragments executet on the fpga hardware are written in Vivado hls and compiled with the sdSoc suite to be embedded in the boards execution environment.

## Build process and repository structure
Developing in a high level synthesis dialect leads to long compilation and preparation times till the change undertaken will be visible on the actual hardware. To facility the process, I applied a three stages workflow:
* implement a new function using the vivado hls. The code must be hls compliant c++ and will be completely executed and debugged on development host. The code can be found here: https://github.com/stiXits/842_cstage
* Move code to an sdSoc project configured for the fpga simulation step. Compiling for the simulation step is significantly faster than compiling for actual hardware. Sdsoc demands some narrower constraints to the code as the vivado hls testbench simulation. Especially data flow between functions and memory usage will be shaped in this step. The initial programm altered for this stage is managed by this repository.
* Compile the code for the actual fpga hardware. Allthough most of the hardware compatibility can be reached within the simulation phase, some issues are not spotted within the simulation phase. Those will be treated in thins step. Afterwards, the compiled binary can be transferred by Jtag to the Ultra96 board and run through sdSoc debugging interface.

## Environmental details
* https://www.researchgate.net/publication/4230004_Data_compression_with_restricted_parsings
* http://zedboard.org/product/ultra96-v2-development-board
* http://zedboard.org/product/ultra96-usb-jtaguart-pod
* https://www.xilinx.com/products/design-tools/vivado/integration/esl-design.html
* https://www.xilinx.com/products/design-tools/software-zone/sdsoc.html

## How to build and run
