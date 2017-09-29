extern double kin, ang, angx, comx, comy, exx, why;

/*! \file
 \brief  This file is part of an addition implemented in August 2017 to print more information to the output files.
         It simply declares all the new variables to print more detailed particle information in fp_beam.dat. See this file for more details.
 */

/* As a brief explanation, the way the (meaningful) user outputs work are as such (also detailed in Naomi Galinski's documentation 1.7):
   - As the particle leaves the target, PrimaryGeneratorAction.cc opens data files called postTarget_beam.dat and fp_beam.dat (found in Userdir/Results)
   - The file EMMASteppingAction.cc writes four pieces of information to the postTarget_beam.dat file: the
     particle's kinetic energy, angle off the beam axis, x position, and y position. All four values describe the particle right after leaving the target.
   - The particle passes through the spectrometer.
   - The file DriftChamberHit.cc writes the same four pieces of information to the file fp_beam.dat - these now describe the particle as it hits the focal plane.
   - ROOT uses fp_beam.dat and creates most of its histograms and plots.

   While I was trying to get the simulation to reproduce the preliminary test results formed by an argon beam scattering off a thick gold foil, which produced
   two peaks of Ar 13+ and Ar 14+, the simulation showed some strange results in terms of the focal plane distribution. To pinpoint the cause of the inaccuracies, I decided to
   match each particle that hit the focal plane with its respective information as it left the target, to see if there were any relationships between
   how the particle left the target and where it ended up on the focal plane. Since many more particles left the target than hit the focal plane, this was not as
   simple as matching them up one by one. (for a more detailed account of my ongoing battle with this simulation problem refer to the EMMA documentation I wrote)

   Hence the variables declared in this file are simply assigned the values of the post-target data from postTarget_beam.dat and then printed together with its corresponding
   focal plane data in fp_beam.dat. Thus the focal plane data are matched with corresponding post target data, and the position of the focal plane hits can be
   examined to the n-th degree.

   Anyways, in addition to printing the four pieces of information already given by EMMASteppingAction.cc, I added several more pieces to help in both my analysis
   and perhaps for useful future applications.

   It helps to know that the simulation and its variables uses a cartesian coordinate system with the xy plane being the plane of the target and the z axis being the
   beam axis. The particle leaving the target is modeled by a vector whose three components are given and printed in EMMASteppingAction.cc.

   Anyhow, here are the definitions for the variables I've added (remember, all of them apply to the particle just after leaving the target):
        kin - kinetic energy of the particle (in MeV)
        ang - angle relative to beam axis (or relative to the normal to the target plane) (in deg.)
        exx - x component where the particle left the target (in cm)
        why - y component where the particle left the target (in cm)
   And here are three more I've added that may be useful (more can be easily calculated and added, especially if you're willing to make larger scale changes to the code!)
        angx - the angle of the particle leaving the target in the xy plane (the 3D vector projected to the 2D xy plane, and the angle formed with the z axis)
        comx - the x component of the vector modeling the particle
        comy - the y component of the vector modeling the particle
*/
