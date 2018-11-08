
Some nominal values for EMMA: 

Energy acceptance: +25% -17%
m/q acceptance: +/- 3.5%
mass dispersion in focal plane: 10 mm/%
angular acceptance: +/- 3.6 deg by +/- 3.6 deg (15 msr)

Nov. 5 Update: - Energy spectrum reading is implemented. To utilise it, 
go to UserDir where the rest of the input files are located. The 
spectrum, energySpectrum.dat, is located there. Note: it is currently 
configured to ignore the energy input information (beam energy and 
energy spread) in beam.dat. The energy spectrum reading also only 
affects beam simulations, and not anything else like alphasource. 

Nov. 8 Update: - Now, you can switch between if you read energy from a 
user-defined spectrum (see above) or use the default gaussian energy that's 
already implemented in beam.dat. 
To change this option, simply change the last (9th) line in beam.dat to 
SPEC or GAUS. It is set to SPEC by default. 
