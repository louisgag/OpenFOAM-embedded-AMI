# OpenFOAM-embedded-AMI
This SolidBodyMotionFvMesh function allows the definition of embedded planar AMI interfaces with constant angular velocities.
It is currently compatible with OpenFOAM-4.x from [OpenFOAM.org](http://www.openfoam.org)
and constitutes an updated version of the code posted on the [forum](www.cfd-online.com/Forums/openfoam-solving/105274-free-slip-moving-wall-bc.html#post509989).
To compile this new AMI motion function, simply put the *dynamicFvMesh* folder into your user directory and run *wmake*.
The test case provided allows testing the functionality, it uses a custom [moving-wall-slip](http://github.com/louisgag/OpenFOAM-moving-wall-slip) boundary condition which can be changed if you prefer not having to install it as well.
