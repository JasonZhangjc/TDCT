# TDCT: TREE_DES_COMPUTATION_TOOL
A demo of Tree-DES software version 2.0. This program is an educational 
computation tool for efficient state-based supervisory control synthesis 
of discrete-event systems. 

Update:
Bug fixed.

Required tools:
 1. cmake (See here: https://cmake.org/download/)
 2. BuddyBDD library (See here: https://sourceforge.net/projects/buddy/)
 
 To build the project:
 1. Go to build directory.
 2. Run ./build.sh inputDirectory rootFileName.
 3. Then a new folder "results" will be created under the inputDirectory.
 4. In the folder "results": the output.txt contains the open-loop simulation, runtime of the supervisory control synthesis, and the closed-loop simulation; the controlled_behavior.txt contains the BDD Of the supervisory controller using the set notation; other .txt files are control functions of controllable events.

A better version is under development.
