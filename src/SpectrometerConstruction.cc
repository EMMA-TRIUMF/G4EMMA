// *********************************************** //
//      Modified by N. Galinski (July 2014):
// BGField classes objects need dimensions as input parameters.
// Extra slits added for EDs and MD
// *********************************************** //
// Added Pipe 1 end caps and detector end caps to minimize scattering out of the spectrometer on pipe 1 and pipes 11 & 12
//  - Alex Wen (July/August 2017)
// *********************************************** //
//
//

/*! \file
 \brief
  This source file builds the elements in the whole EMMA spectrometer apart from the detectors and fields.
  All the pipes, walls, and other geometries are built here. Refer to this file if any structural changes are required for the simulation.
  */

#include "SpectrometerConstruction.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ProductionCutsTable.hh"
#include "G4SubtractionSolid.hh"

#include "EMMAGlobalField.hh"
#include "EMFieldDebugger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4Region.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RegionStore.hh"

#include "G4UserLimits.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4UnitsTable.hh"

#include "G4Transform3D.hh"


#include <fstream> //Stream class to both read and write from/to files
using namespace std;
#include <stdlib.h>     /* abort, NULL */

#include "BGField1.hh"
#include "BGField2.hh"
#include "BGField3.hh"
#include "BGField4.hh"
#include "BGField5.hh"
#include "BGField6.hh"
#include "BGField7.hh"

// Global variable
G4double zQ1begins;   // z-coordinate of upstream edge of Q1
G4double zQ4ends;     // z-coordinate of downstream edge of Q4
G4double zAnode;     // z-coordinate of focal plane (Anode)
G4double zFocalPlane;

// Global variable
G4double zQ1ends; //z location at beginning and end of element
G4double zQ2ends;
G4double zQ3ends;
G4double zQ2begins;
G4double zQ3begins;
G4double zQ4begins;
G4double zQ1fieldbegins; //z location at beginning and end of field (field extends beyond width of element)
G4double zQ2fieldbegins;
G4double zQ2fieldends;
G4double zQ3fieldbegins;
G4double zQ4fieldbegins;
G4double zQ4fieldends;
G4double zED1fieldbegins;
G4double xED1fieldends;
G4double zED1fieldends;
G4double xMDfieldbegins;
G4double zMDfieldbegins;
G4double xMDfieldends;
G4double zMDfieldends;
G4double xED2fieldbegins;
G4double zED2fieldbegins;
G4double zED2fieldends;
G4double xED1center; //center coordinates of circle that defines shape and position of dipole
G4double zED1center;
G4double xED2center;
G4double zED2center;
G4double rED; //radius of circle that defines shape and position of dipole
G4double xMDcenter;
G4double zMDcenter;
G4double rMD;
G4double Q1before; // Distance field extends before and after the quads and dipoles
G4double Q2before;
G4double ED1before;
G4double MDbefore;
G4double ED2before;
G4double Q3before;
G4double Q4before;
G4double Q1after;
G4double Q2after;
G4double ED1after;
G4double MDafter;
G4double ED2after;
G4double Q3after;
G4double Q4after;
G4double Pipe4z;
G4double Pipe4HL;
G4double Pipe7HL;

G4String fieldFileName; //used in EMFieldDebugger.cc
extern G4String UserDir; // EMMAapp.cc

SpectrometerConstruction::SpectrometerConstruction(){;}

//************************************************************************************//
//If you change any logical names in the constructor of this class make sure you change
//them in EMMASteppingAction.cc
//************************************************************************************//



SpectrometerConstruction::SpectrometerConstruction(G4Material* Vacuum, G4Material* Wall, G4LogicalVolume* SpecWorldLogical,
						   G4double Pipe1length)
:fCheckOverlaps(true)
{
  	// If you don't care about checking overlaps of G4VPhysicalVolume uncomment following
  	fCheckOverlaps=false;

  	// read user input for Slits
  	ReadUserInput();

<<<<<<< HEAD
  	// Slit half thicknesses
  	slitshth = 1*mm; //arbitrary thickness
  
  	// Create a region for the IonGasModel
  	G4RegionStore::GetInstance()->FindOrCreateRegion("vacuumRegion");
  	G4Region* vacuumRegion = G4RegionStore::GetInstance()->GetRegion("vacuumRegion",false);
  	vacuumRegion->SetProductionCuts(
      	G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts());
  
  	//User Limits
  	G4double minStep = 0.0001 * mm; //Integrator minstep
  
  	// Visualization attributes
  	WallVisAtt = new G4VisAttributes(G4Colour(0.5,0.0,0.5)); //purple
  	WallVisAtt->SetVisibility(true);
  	BeamLineVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0)); //pink
  	BeamLineVisAtt->SetVisibility(true);
  	PoleVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //red
  	PoleVisAtt->SetVisibility(true);
  	BendingVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //red
  	BendingVisAtt->SetVisibility(true);
  	SlitsVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0)); //yellow
  	SlitsVisAtt->SetVisibility(true);
  	//worldVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0)); //pink
  	//worldVisAtt->SetVisibility(true);

  	// Create rotation matrices
  	G4RotationMatrix* Rotate0 = new G4RotationMatrix();
  	Rotate0->rotateY(0*deg);
  	G4RotationMatrix* RotateTube = new G4RotationMatrix();
  	RotateTube->rotateX(-90*deg);
  	G4RotationMatrix* RotateTube2 = new G4RotationMatrix();
  	RotateTube2->rotateX(90*deg);
=======
  // Slit half thicknesses
  slitshth = 1*mm; //arbitrary thickness

  // Create a region for the IonGasModel
  G4RegionStore::GetInstance()->FindOrCreateRegion("vacuumRegion");
  G4Region* vacuumRegion = G4RegionStore::GetInstance()->GetRegion("vacuumRegion",false);
  vacuumRegion->SetProductionCuts(
      G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts());

  //User Limits
  G4double minStep = 0.0001 * mm; //Integrator minstep

  // Visualization attributes
  WallVisAtt = new G4VisAttributes(G4Colour(0.5,0.0,0.5)); //purple
  WallVisAtt->SetVisibility(true);
  BeamLineVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0)); //pink
  BeamLineVisAtt->SetVisibility(true);
  PoleVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //red
  PoleVisAtt->SetVisibility(true);
  BendingVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //red
  BendingVisAtt->SetVisibility(true);
  SlitsVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0)); //yellow
  SlitsVisAtt->SetVisibility(true);
  //worldVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0)); //pink
  //worldVisAtt->SetVisibility(true);

  // Create rotation matrices
  G4RotationMatrix* Rotate0 = new G4RotationMatrix();
  Rotate0->rotateY(0*deg);
  G4RotationMatrix* RotateTube = new G4RotationMatrix();
  RotateTube->rotateX(-90*deg);
  G4RotationMatrix* RotateTube2 = new G4RotationMatrix();
  RotateTube2->rotateX(90*deg);
>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b


	//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//
	//
	//     Fix drift space lengths and magnetic effective field lengths
	//
	G4double Pipe1HL = Pipe1length/2.0;      // drift length, original value: 22.75/2 = 11.375cm
	G4double Q1HL = 13.977/2*cm;		//mag. eff. field half length
	G4double Q1apt = 3.1*cm;	//radius of apeture of vacuum chamber
	G4double Pipe2HL = 3.5/4*cm;	// this is divided by 4 because the the physical length (7 cm) is actually constructed from two pipes (2 and 3)
	G4double Q2HL = 29.881/2*cm;	//mag. eff. field half length
	G4double Q2apt = 6.75*cm;
	Pipe4HL = 37.23/4*cm;  // see above comment about division by 4
	G4double Pipe5HL = Pipe4HL;
	G4double wallThick = 1*cm;	//arbitrary thickness of vacuum chamber walls
	G4double rbigpipe = 13.75*cm; //arbitrary size

	//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//
    //
    // Pipe 1 end caps (Alex Wen, July 2017)
    //
    // This part is added to minimize the unwanted scattering of particles outside of the spectrometer (which slows down the simulation speed).
    // After hitting the target the recoils have a tendency to scatter out of the two ends of pipe1, where there are no walls.
    // This simply adds walls on either end of pipe1 so that scattering doesn't end up everywhere.
    //
    // The construction of the upstream end cap is a cylinder (Pipe1Cap1) exactly like Pipe1Wall, with a disk (Pipe1Cap2) on the end capping it.
    // The construction of the downstream (Pipe1Cap3) end cap is a disk with hole in it to allow the particles to pass through.
    // The caps are just walls like the rest of the walls.
    //
    //
    //
    // Pipe1Cap1
    G4VSolid* Pipe1Cap1Solid = new G4Tubs("Pipe1Cap1Tub",rbigpipe,rbigpipe+wallThick,2*cm,0*deg,360*deg);
	G4LogicalVolume* Pipe1Cap1Logical = new G4LogicalVolume(Pipe1Cap1Solid,Wall,"Pipe1Cap1Logical", 0,0,0);
	G4double Pipe1Cap1z = -1*cm;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe1Cap1z),Pipe1Cap1Logical,"Pipe1Cap1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
    //
    // Pipe1Cap2
    G4VSolid* Pipe1Cap2Solid = new G4Tubs("Pipe1Cap2Tub",0*cm,rbigpipe+wallThick,1*cm,0*deg,360*deg);
	G4LogicalVolume* Pipe1Cap2Logical = new G4LogicalVolume(Pipe1Cap2Solid,Wall,"Pipe1Cap2Logical", 0,0,0);
	G4double Pipe1Cap2z = Pipe1Cap1z-1.5*cm;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe1Cap2z),Pipe1Cap2Logical,"Pipe1Cap2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
    //
	// Pipe1Cap3
	G4VSolid* Pipe1Cap3Solid = new G4Tubs("Pipe1Cap3Tub",Q1apt+wallThick,rbigpipe+wallThick,1*cm,0*deg,360*deg);
	G4LogicalVolume* Pipe1Cap3Logical = new G4LogicalVolume(Pipe1Cap3Solid,Wall,"Pipe1Cap3Logical", 0,0,0);
	G4double Pipe1Cap3z = zQ1begins+0.5*cm;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe1Cap3z),Pipe1Cap3Logical,"Pipe1Cap3Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	//
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//
    //
    //
    // Detector End Caps (July 2017)
    //
    // Added to address a problem similar to the one regarding Pipe1. Because there were no caps or walls on the ends of the pipes near the detectors,
    // the particles had a tendency to exit EMMA. Not only does this slow down simulation speed, it also sometimes enabled the particles to leave
    // the pipe before the third or fourth quad magnet and then reenter just before the detectors and still be detected, causing highly unusual and unpredictable patterns, especially
    // detecting Ar 14+ ions when the detector was tuned to detecting 13.5+ (in order to recreate the results of the initial calibration tests - Ar --> Au)
    //
    // To fix this problem disks were again added to the exposed fronts and backs of different parts of the tubes.
    //
    // Specifically, a cap was added to the back (downstream) end of Pipe 11 right before Q3, and another cap was added to the front end of Pipe 12 after Q4.
    // Special care was taken to ensure that these caps were strictly exterior, and did not affect the particle travel in any way.
		//
    // See sections Pipe11Cap and Pipe12Cap later on in this file.
    //
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//

	// Pipe1
	G4VSolid* Pipe1Solid = new G4Tubs("Pipe1Tub",0*cm,rbigpipe,Pipe1HL,0*deg,360*deg);
	// Pipe1Wall
	G4VSolid* Pipe1WallSolid = new G4Tubs("Pipe1WallTub",rbigpipe,rbigpipe+wallThick,Pipe1HL,0*deg,360*deg);
	G4LogicalVolume* Pipe1WallLogical = new G4LogicalVolume(Pipe1WallSolid,Wall,"Pipe1WallLogical", 0,0,0);
	G4double Pipe1z = zQ1begins-Pipe1HL;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe1z),Pipe1WallLogical,"Pipe1WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);

	// Q1
	G4VSolid* Q1Solid = new G4Tubs("Q1Tub",0*cm,Q1apt,Q1HL,0*deg,360*deg);
	// Q1Wall
	G4VSolid* Q1WallSolid = new G4Tubs("Q1WallTub",Q1apt,Q1apt+wallThick,Q1HL,0*deg,360*deg);
	G4LogicalVolume* Q1WallLogical = new G4LogicalVolume(Q1WallSolid,Wall,"Q1WallLogical",0,0,0);
	G4double Q1z = Pipe1z+Pipe1HL+Q1HL;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Q1z),Q1WallLogical,"Q1WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q1WallLogical->SetVisAttributes(PoleVisAtt);

	// Pipe2
	G4VSolid* Pipe2Solid = new G4Tubs("Pipe2Tub",0*cm,Q1apt,Pipe2HL,0*deg,360*deg);
	// Pipe2Wall
	G4VSolid* Pipe2WallSolid = new G4Tubs("Pipe2WallTub",Q1apt,Q1apt+wallThick,Pipe2HL,0*deg,360*deg);
	G4LogicalVolume* Pipe2WallLogical = new G4LogicalVolume(Pipe2WallSolid,Wall,"Pipe2WallLogical", 0,0,0);
	G4double Pipe2z = Q1z+Q1HL+Pipe2HL;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe2z),Pipe2WallLogical,"Pipe2WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);

	//Create Union for field element
	G4ThreeVector Q1off(0*cm,0,Pipe1HL+Q1HL);
	G4UnionSolid* Q1a = new G4UnionSolid("Q1a", Pipe1Solid, Q1Solid, Rotate0, Q1off);  // last argument gives the displacement of the second solid
	G4ThreeVector Pipe2off(0*cm,0*cm,Pipe1HL+2*Q1HL+Pipe2HL);
	G4UnionSolid* Q1Union = new G4UnionSolid("Q1", Q1a, Pipe2Solid, Rotate0, Pipe2off);
	// Create Field for Q1
	zQ1fieldbegins = Pipe1z - Pipe1HL;
<<<<<<< HEAD
    	Q1before=Pipe1HL*2;
    	Q1after=Pipe2HL*2;
    
    	G4int nvar = 8; //nav set for all B and E fields
	
=======
    Q1before=Pipe1HL*2;
    Q1after=Pipe2HL*2;

    G4int nvar = 8; //nav set for all B and E fields

>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	G4LogicalVolume* Q1Logical = new G4LogicalVolume(Q1Union,Vacuum,"Q1Logical");

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Q1Logical);
	Q1Logical->SetRegion(vacuumRegion);
	G4double Q1Solidz = Pipe1z;

	Field1 = new BGField1(0,zQ1fieldbegins,Q1before,Q1after,Q1Logical,G4ThreeVector(0*cm,0*cm,Q1Solidz)); //see BGField1.cc for 	description of input parameters

	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Q1Solidz),Q1Logical,"Q1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q1Logical->SetVisAttributes(BendingVisAtt);

	 //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
  	//
  	//                                                 Aperture
 	//
  	//    Aperture (aluminum)
  	//
  	G4VSolid* apertureOuterSolid = new G4Box("apertureOuterSolid",5*cm,5*cm,1.*um); // arbitrarily thin.
  	G4VSolid* apertureHole = new G4Box("apertureHole",4.185*cm,4.185*cm,1.*cm); // arbitrarily thick.
  	G4SubtractionSolid* apertureSolid = new G4SubtractionSolid("apertureSolid", apertureOuterSolid, apertureHole, 0, G4ThreeVector(0,0,0));
  	G4LogicalVolume* apertureLogical = new G4LogicalVolume(apertureSolid,Wall,"apertureLogical",0,0,0); // make out of gold for now, will later have to declare aluminium.
  	G4double zAperture = -43.95*mm;
  	//new G4PVPlacement(0,G4ThreeVector(0.,0.,zAperture),apertureLogical,"aperturePhys",Q1Logical,0,0,fCheckOverlaps);  
  	G4cout << "Aperture Location: " << Q1Solidz + zAperture << G4endl;
  	//
 	//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>




	// Pipe3
	G4VSolid* Pipe3Solid = new G4Tubs("Pipe3Tub",0*cm,Q1apt,Pipe2HL,0*deg,360*deg);
	// Pipe3Wall
	G4VSolid* Pipe3WallSolid = new G4Tubs("Pipe3WallTub",Q1apt,Q1apt+wallThick,Pipe2HL,0*deg,360*deg);
	G4LogicalVolume* Pipe3WallLogical = new G4LogicalVolume(Pipe3WallSolid,Wall,"Pipe3WallLogical", 0,0,0);
	G4double Pipe3z = Pipe2z+2*Pipe2HL;
<<<<<<< HEAD
=======
	G4cout<<"Pipe3z: " << Pipe3z << G4endl;
>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe3z),Pipe3WallLogical,"Pipe3WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//Pipe3WallLogical->SetVisAttributes(WallVisAtt);
	G4double Q2SubHL = (437.89-(Pipe3z+Pipe2HL))/2;

  /*
	Q1/Q1 Beam Pipe modifications:
	The geometry is modified here. In the real spectrometer, the beam-pipe that passes through Q1 and Q2 have a narrow first
	half (mostly passing through Q1) and a wider second half (mostly passing through Q2). However, the field lengths of Q1
	and Q2 do not match up exactly to the narrow/wide parts of the beam pipe. For acceptance purposes, it's important to
	accurately model the end of the narrow part of the beam-pipe, because that can directly influence the acceptance.
	The narrow part of the beam-pipe happens to end a little bit into the effective field length of Q2, so in the simulation
	geometry, a subtraction soli is made to model the Q2 field volume so that the narrow beam-pipe can extend into the Q2
	volume to its realistic extent.
	Pipe3 Wall Extension is the narrow beam-pipe extension into the Q2 region, and Q2 is a subtraction solid.
	*/

	// Pipe3 Wall Extension
	G4VSolid* Pipe3WallExtSolid = new G4Tubs("Pipe3WallExtTub",Q1apt,Q1apt+wallThick,Q2SubHL,0*deg,360*deg);
	G4LogicalVolume* Pipe3WallExtLogical = new G4LogicalVolume(Pipe3WallExtSolid,Wall,"Pipe3WallExtLogical", 0,0,0);
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe3z+Pipe2HL+Q2SubHL),Pipe3WallExtLogical,"Pipe3WallExtPhysical",SpecWorldLogical,0,0,fCheckOverlaps);


		// debugging
		G4cout << "Start of Q1: " << Q1z - Q1HL << G4endl;
		G4cout << "End of Q1: " << Q1z + Q1HL << G4endl;
		G4cout << "End of Q1 pipe segment: " << Pipe3z+Pipe2HL << G4endl;
		G4cout << "End of pipe3 extension (clipping boundary): " << Pipe3z+Pipe2HL+(2*Q2SubHL) << G4endl;


	// Q2
	G4VSolid* Q2Sub = new G4Tubs("Q2SubTub",Q1apt,Q1apt+wallThick,Q2SubHL,0*deg,360*deg);
	G4VSolid* Q2Cyl = new G4Tubs("Q2TubCyl",0*cm,Q2apt,Q2HL,0*deg,360*deg);
	G4ThreeVector Q2Suboff(0*cm,0*cm,-Q2HL+Q2SubHL);
	G4SubtractionSolid* Q2Solid = new G4SubtractionSolid("Q2TubCyl-Q1SubTub",Q2Cyl,Q2Sub,Rotate0,Q2Suboff);

	// Q2Wall
	G4VSolid* Q2WallSolid = new G4Tubs("Q2WallTub",Q2apt,Q2apt+wallThick,Q2HL,0*deg,360*deg);
	G4LogicalVolume* Q2WallLogical = new G4LogicalVolume(Q2WallSolid,Wall,"Q2WallLogical",0,0,0);
	G4double Q2z = Pipe3z+Pipe2HL+Q2HL;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Q2z),Q2WallLogical,"Q2WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q2WallLogical->SetVisAttributes(PoleVisAtt);

	//debugging
	G4cout << "Start of Q2: " << Q2z - Q2HL << G4endl;
	G4cout << "End of Q2: " << Q2z + Q2HL << G4endl;


	// Pipe4
	G4VSolid* Pipe4Solid = new G4Tubs("Pipe4Tub",0*cm,Q2apt,Pipe4HL,0*deg,360*deg);
	// Pipe4Wall
	G4VSolid* Pipe4WallSolid = new G4Tubs("Pipe4WallTub",Q2apt,Q2apt+wallThick,Pipe4HL,0*deg,360*deg);
	G4LogicalVolume* Pipe4WallLogical = new G4LogicalVolume(Pipe4WallSolid,Wall,"Pipe4WallLogical", 0,0,0);
<<<<<<< HEAD
	Pipe4z = Q2z+Q2HL+Pipe4HL;	
=======
	 Pipe4z = Q2z+Q2HL+Pipe4HL;
>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe4z),Pipe4WallLogical,"Pipe4WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//Pipe4WallLogical->SetVisAttributes(WallVisAtt);


	//Create Union for field element
	zQ2fieldbegins = Pipe3z - Pipe2HL;
<<<<<<< HEAD
    	Q2before=Pipe2HL*2;
    	Q2after=Pipe4HL*2;
    
=======
    Q2before=Pipe2HL*2;
    Q2after=Pipe4HL*2;

>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	G4ThreeVector Q2off(0*cm,0,Pipe2HL+Q2HL);
	G4UnionSolid* Q2a = new G4UnionSolid("Q2a", Pipe3Solid, Q2Solid, Rotate0, Q2off);
	G4ThreeVector Pipe4off(0*cm,0*cm,Pipe2HL+2*Q2HL+Pipe4HL);
	G4UnionSolid* Q2Union = new G4UnionSolid("Q2", Q2a, Pipe4Solid, Rotate0, Pipe4off);
	// Create Field for Q2

	Q2Logical = new G4LogicalVolume(Q2Union,Vacuum,"Q2Logical");

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Q2Logical);
	Q2Logical->SetRegion(vacuumRegion);
	G4double Q2Solidz = Pipe3z;

	Field2 = new BGField2(0,zQ2fieldbegins,Q2before,Q2after,Q2Logical,G4ThreeVector(0*cm,0*cm,Q2Solidz)); //see BGField2.cc for description of input parameters

	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Q2Solidz),Q2Logical,"Q2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q2Logical->SetVisAttributes(BendingVisAtt);

    	//used in EMFieldDebugger.cc
    	zQ2fieldends = Pipe4z + Pipe4HL;

 	// Pipe5
	G4VSolid* Pipe5Solid = new G4Tubs("Pipe5Tub",0*cm,Q2apt,Pipe5HL,0*deg,360*deg);
	// Pipe5Wall
	G4VSolid* Pipe5WallSolid = new G4Tubs("Pipe5WallTub",Q2apt,Q2apt+wallThick,Pipe5HL,0*deg,360*deg);
	G4LogicalVolume* Pipe5WallLogical = new G4LogicalVolume(Pipe5WallSolid,Wall,"Pipe5WallLogical", 0,0,0);
	G4double Pipe5z = Pipe4z+Pipe4HL+Pipe5HL;
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe5z),Pipe5WallLogical,"Pipe5WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//Pipe5WallLogical->SetVisAttributes(WallVisAtt);


	// If there is a problem with the position of the EDIP the problem is most likely in the start angle
	G4double x0=500*cm; //radius of the curvature of ED1
	G4double EDhw = 6.25*cm; //ED width
	G4double EDhh = 20*cm; //ED height
	G4double ED1angle = 20*deg; //ED bending angle
	G4double ED1z = Pipe5z+Pipe5HL;			//z position of ED1
	G4double EDendz = x0*sin(ED1angle);	//central z distance at end of ED1
	G4double EDendx = -(x0-x0*cos(ED1angle));	//central x distance at end of ED1
	// same values apply to ED2!

	G4cout << "ED1 center: " << ED1z << endl;

	//
	//  G4Tubs Member Data:
	//  - fRMin  Inner radius
	//  - fRMax  Outer radius
	//  - fDz  half length in z
	//  - fSPhi  The starting phi angle in radians,
	//    adjusted such that fSPhi+fDPhi<=2PI, fSPhi>-2PI
	//  - fDPhi  Delta angle of the segment.


	// ED1
	G4VSolid* ED1Solid = new G4Tubs("ED1Tub",x0-EDhw,x0+EDhw,EDhh,360*deg,ED1angle);

	// ED1 Walls:
	// Wall 1: x<0 (down) [EAST]
	G4VSolid* ED1Wall1Solid = new G4Tubs("ED1Wall1Tub", x0-EDhw-wallThick, x0-EDhw, EDhh+wallThick, 360*deg, ED1angle);
	G4LogicalVolume* ED1Wall1Logical = new G4LogicalVolume(ED1Wall1Solid,Wall,"ED1Wall1Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0,0*cm,ED1z),ED1Wall1Logical,"ED1Wall1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	// Wall 2: x>0 (up)   [WEST]
	G4VSolid* ED1Wall2Solid = new G4Tubs("ED1Wall2Tub", x0+EDhw, x0+EDhw+wallThick, EDhh+wallThick, 360*deg, ED1angle);
	G4LogicalVolume* ED1Wall2Logical = new G4LogicalVolume(ED1Wall2Solid,Wall,"ED1Wall2Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0,0*cm,ED1z),ED1Wall2Logical,"ED1Wall2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	// Wall 3: y>0 (into screen)   [CENTRE OF EARTH]
	G4VSolid* ED1Wall3Solid = new G4Tubs("ED1Wall3Tub", x0-EDhw, x0+EDhw, wallThick/2.0, 360*deg, ED1angle);
	G4LogicalVolume* ED1Wall3Logical = new G4LogicalVolume(ED1Wall3Solid,Wall,"ED1Wall3Logical", 0,0,0);
	new G4PVPlacement(RotateTube, G4ThreeVector(-x0, EDhh+wallThick/2.0, ED1z), ED1Wall3Logical,"ED1Wall3Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	// Wall 4: y<0 (out of screen)    [HEAVENS]
	G4VSolid* ED1Wall4Solid = new G4Tubs("ED1Wall4Tub", x0-EDhw, x0+EDhw, wallThick/2.0, 360*deg, ED1angle);
	G4LogicalVolume* ED1Wall4Logical = new G4LogicalVolume(ED1Wall4Solid,Wall,"ED1Wall4Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0, -(EDhh+wallThick/2.0), ED1z), ED1Wall4Logical,"ED1Wall4Physical",SpecWorldLogical,0,0,fCheckOverlaps);
    	ED1Wall1Logical->SetVisAttributes(BendingVisAtt);
    	ED1Wall2Logical->SetVisAttributes(BendingVisAtt);
    	ED1Wall3Logical->SetVisAttributes(BendingVisAtt);
    	ED1Wall4Logical->SetVisAttributes(BendingVisAtt);

	// Create rotation matrix
	G4RotationMatrix* Rotate1 = new G4RotationMatrix();
	Rotate1->rotateY(20*deg);

	// Rectangular aperture slit after ED1
	G4double xapth = 12.5/2*cm;
	G4double yapth = 40/2*cm;
	G4double slitshout = 20*cm; //width of aluminum plate extending out
	G4double slitshx,slitshy;
	G4ThreeVector displace,posED1slit,posED1slit2;

    	posED1slit[0]=EDendx;
    	posED1slit[1]=0;
    	posED1slit[2]=Pipe5z+Pipe5HL+EDendz;

	slitshx=slitshout;
	slitshy=yapth+slitshout*2;
	G4VSolid* cover1 = new G4Box("cover2",slitshx,slitshy,slitshth);
	slitshx=xapth;
	slitshy=slitshout;
	G4VSolid* cover2 = new G4Box("cover1",slitshx,slitshy,slitshth);
	displace[0] = -xapth*2-slitshout*2;
	displace[1] = 0*cm;
	displace[2] = 0;
	G4UnionSolid* coverX = new G4UnionSolid("coverX", cover1, cover1, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = yapth+slitshout;
	displace[2] = 0;
	G4UnionSolid* coverXY = new G4UnionSolid("coverXY", coverX, cover2, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = -yapth-slitshout;
	displace[2] = 0;
	G4UnionSolid* cover = new G4UnionSolid("cover", coverXY, cover2, Rotate0, displace);
	posED1slit2[0] = posED1slit[0]+slitshth*sin(ED1angle)+(xapth+slitshout)*cos(ED1angle);
	posED1slit2[1] = 0*cm;
	posED1slit2[2] = posED1slit[2]-slitshth*cos(ED1angle)+(xapth+slitshout)*sin(ED1angle);
	G4LogicalVolume* ED1SlitLogical = new G4LogicalVolume(cover,Wall,"ED1SlitLogical",0,0,0);
	new G4PVPlacement(Rotate1,posED1slit2,ED1SlitLogical,"ED1SlitPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	ED1SlitLogical->SetVisAttributes(SlitsVisAtt);

	//      Modified by N. Galinski (Feb 2014):
	// *********************************************** //
	// Half length of pipes 6-9:
	// (Entire section is 122.50 cm long)
	//G4double ED1MDsep = 122.50*cm; //length of 2 pipes + slits
	//check that Pipe6HL+Pipe7HL+Pipe1MDHL = Pipe8HL+Pipe9HL+Pipe2MDHL = 122.50*cm
	G4double Pipe6HL = 59.64/2*cm;
		 Pipe7HL = 20.26/2*cm;
	G4double Pipe1MDHL = 42.6/2*cm;
	G4double Pipe2MDHL = 42.6/2*cm;
	G4double Pipe8HL = 18.77/2*cm;
	G4double Pipe9HL = 61.13/2*cm;
	G4double Pipe6angle=ED1angle;
	G4double angle = ED1angle;	//same as Pipe6angle and ED1angle
	G4ThreeVector dummy;

	// *********************************************** //
	// Positioning of pipe 6:
	G4ThreeVector posPipe6;
	posPipe6[0] = posED1slit[0]-Pipe6HL*sin(Pipe6angle);
	posPipe6[1] = 0*cm;
	posPipe6[2] = posED1slit[2]+Pipe6HL*cos(Pipe6angle);


 	// *********************************************** //
	// Positioning at end of pipe6 = position of front (not middle) of slit1:
	G4ThreeVector posSlits1;
	posSlits1[0] = posPipe6[0]-Pipe6HL*sin(Pipe6angle);
	posSlits1[1] = 0*cm;
	posSlits1[2] = posPipe6[2]+Pipe6HL*cos(Pipe6angle);


	// *********************************************** //
	// Positioning of pipe 7:
	G4ThreeVector posPipe7;
	posPipe7[0] = posSlits1[0]-2*slitshth*sin(Pipe6angle)-(Pipe7HL-2*slitshth)*sin(Pipe6angle);
	posPipe7[1] = 0*cm;
	posPipe7[2] = posSlits1[2]+2*slitshth*cos(Pipe6angle)+(Pipe7HL-2*slitshth)*cos(Pipe6angle);
<<<<<<< HEAD
	
=======

	G4cout << "PopPipe7 (x,z) : (" << posPipe7[0] << ", " << posPipe7[2] << ")" << G4endl;


>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	// *********************************************** //
	// Positioning of rectangular aperture slit before MD:
	G4ThreeVector posslit1MD;
	posslit1MD[0] = posPipe7[0]-(Pipe7HL-2*slitshth)*sin(Pipe6angle)-slitshth*sin(Pipe6angle);
	posslit1MD[1] = 0*cm;
	posslit1MD[2] = posPipe7[2]+(Pipe7HL-2*slitshth)*cos(Pipe6angle)+slitshth*cos(Pipe6angle);

	// *********************************************** //
	// Positioning of vacuum pipe wall before MD:
	G4ThreeVector posPipe1MD;
	posPipe1MD[0] = posslit1MD[0]-slitshth*sin(Pipe6angle)-Pipe1MDHL*sin(Pipe6angle);
	posPipe1MD[1] = 0*cm;
	posPipe1MD[2] = posslit1MD[2]+slitshth*cos(Pipe6angle)+Pipe1MDHL*cos(Pipe6angle);


	// *********************************************** //
	// MD position
	// (40 deg circumference is 69.813 cm long)
	G4double MDr = 100*cm; //radius of the curvature of MD
	G4double MDangle = 40*deg;
	G4double MDhh = 6*cm;
	G4double MDhw = 20*cm;
	G4double MDmidz = MDr*sin(MDangle/2);	//z length between middle and edge of MD EFL

	G4double xMD = posPipe1MD[0] - Pipe1MDHL*sin(angle) - (MDr - MDr*cos(MDangle/2)) + MDr;
	G4double zMD = posPipe1MD[2] + Pipe1MDHL*cos(angle) + MDmidz;

	// *********************************************** //
	// Translation vectors for creation and placement of union Pipe7-MD-Pipe8:
	G4ThreeVector MDoff,Pipe2MDoff;
	MDoff[0] = MDr;
	MDoff[1] = 0*cm;
	MDoff[2] = Pipe1MDHL;
	Pipe2MDoff[0]=-(-MDr * (1-cos(MDangle)) - Pipe2MDHL*sin(MDangle));
	Pipe2MDoff[1]=0*cm;
	Pipe2MDoff[2]=Pipe1MDHL + MDr * sin(MDangle) + Pipe2MDHL*cos(MDangle);

	// *********************************************** //
	// Positioning of vacuum pipe wall after MD:
	G4ThreeVector posPipe2MD;
	posPipe2MD[0] = xMD+(Pipe2MDHL*sin(angle) + (MDr - MDr*cos(MDangle/2)) - MDr);
	posPipe2MD[1] = 0*cm;
	posPipe2MD[2] = zMD+MDmidz+Pipe2MDHL*cos(Pipe6angle);

	// *********************************************** //
	// Positioning of rectangular aperture slit before MD:
	G4ThreeVector posslit2MD;
	posslit2MD[0] = posPipe2MD[0]+Pipe2MDHL*sin(Pipe6angle)+slitshth*sin(Pipe6angle);
	posslit2MD[1] = 0*cm;
	posslit2MD[2] = posPipe2MD[2]+Pipe2MDHL*cos(Pipe6angle)+slitshth*cos(Pipe6angle);

	// *********************************************** //
	// Positioning of pipe 8:
	G4ThreeVector posPipe8;
	posPipe8[0] = posslit2MD[0]+slitshth*sin(Pipe6angle)+(Pipe8HL-2*slitshth)*sin(Pipe6angle);
	posPipe8[1] = 0*cm;
	posPipe8[2] = posslit2MD[2]+slitshth*cos(Pipe6angle)+(Pipe8HL-2*slitshth)*cos(Pipe6angle);

	// *********************************************** //
	// Positioning of front of (not middle) slits2:
	G4ThreeVector posSlits2;
	posSlits2[0] = posPipe8[0]+(Pipe8HL-2*slitshth)*sin(Pipe6angle);
	posSlits2[1] = 0*cm;
	posSlits2[2] = posPipe8[2]+(Pipe8HL-2*slitshth)*cos(Pipe6angle);

	// *********************************************** //
	// Positioning of pipe 9:
	G4ThreeVector posPipe9;
	posPipe9[0] = posSlits2[0]+2*slitshth*sin(Pipe6angle)+Pipe9HL*sin(Pipe6angle);
	posPipe9[1] = 0*cm;
	posPipe9[2] = posSlits2[2]+2*slitshth*cos(Pipe6angle)+Pipe9HL*cos(Pipe6angle);

	// *********************************************** //
	// Positioning of ED2 slit:
	G4ThreeVector posED2slit;
	posED2slit[0] = posPipe9[0]+Pipe9HL*sin(Pipe6angle)+slitshth*sin(Pipe6angle);
	posED2slit[1] = 0*cm;
	posED2slit[2] = posPipe9[2]+Pipe9HL*cos(Pipe6angle)+slitshth*cos(Pipe6angle);

	// *********************************************** //
	// Translation vector for creation of union Pipe5-ED1-Pipe6:
	G4ThreeVector ED1off,Pipe6off;
	ED1off[0] = -x0;
	ED1off[1] = 0*cm;
	ED1off[2] = Pipe5HL;
	Pipe6off[0] = EDendx-(Pipe6HL*sin(Pipe6angle));
	Pipe6off[1] = 0*cm;
	Pipe6off[2] = Pipe5HL+EDendz+Pipe6HL*cos(Pipe6angle);

	// *********************************************** //
	// Fix drift space lengths and magnetic effective field lengths
	//
	G4double Pipe10HL=26.84/4*cm;
	G4double Pipe11HL=Pipe10HL;
	G4double Q3apt1HL=9.65/2*cm;
	G4double Q3HL=29.882/2*cm;	//mag. eff. field hal length
	G4double Q3apt = 6.75*cm;
	G4double Q3apt2HL=3./2*cm;
	G4double Q4HL = 40.179/2*cm; //mag. eff. field half length
	G4double Q4apt = 18.5/2*cm;
	G4double Pipe12HL=20.92/2*cm;
	G4double Pipe13HL = 3.2/2*cm;
	G4double Pipe14HL = 3.32/2*cm;   // original value: 11.73cm, then 6.64, now 3.92

	// *********************************************** //
	// Translation vectors for creation and placement of union Pipe9-ED2-Pipe10:
	G4ThreeVector ED2off,Pipe10off;
	ED2off[0] = -x0;
	ED2off[1] = 0*cm;
	ED2off[2] = -Pipe10HL;
	Pipe10off[0] = EDendx-Pipe9HL*sin(Pipe6angle);
	Pipe10off[1] = 0*cm;
	Pipe10off[2] = -Pipe10HL-EDendz-Pipe9HL*cos(Pipe6angle);

	// *********************************************** //
	//	END modification


	// Pipe6
	G4VSolid* Pipe6Solid = new G4Tubs("Pipe6Tub", 0*cm, rbigpipe, Pipe6HL, 0*deg, 360*deg);
	// Pipe6Wall
	G4VSolid* Pipe6WallSolid = new G4Tubs("Pipe6WallTub", rbigpipe, rbigpipe+wallThick, Pipe6HL, 0*deg, 360*deg);
	G4LogicalVolume* Pipe6WallLogical = new G4LogicalVolume(Pipe6WallSolid, Wall, "Pipe6WallLogical", 0,0,0);
	new G4PVPlacement(Rotate1, posPipe6, Pipe6WallLogical, "Pipe6WallPhysical", SpecWorldLogical,0,0,fCheckOverlaps);

	//Create Union for field element
	// Create rotation matrix for following pipe
	G4RotationMatrix* RotateED1 = new G4RotationMatrix();
	RotateED1->rotateY(20*deg);
	G4UnionSolid* ED1a = new G4UnionSolid("ED1a", Pipe5Solid, ED1Solid, RotateTube, ED1off);
	G4UnionSolid* ED1Union = new G4UnionSolid("ED1", ED1a, Pipe6Solid, RotateED1, Pipe6off);

	// Create Field for ED1
	zED1fieldbegins = Pipe5z - Pipe5HL;
<<<<<<< HEAD
    	ED1before=Pipe5HL*2;
    	ED1after=Pipe6HL*2;
    
=======
	G4cout << "ED1 curve begins: " << Pipe5z + Pipe5HL << G4endl;
    ED1before=Pipe5HL*2;
    ED1after=Pipe6HL*2;

>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	G4LogicalVolume* ED1Logical = new G4LogicalVolume(ED1Union,Vacuum,"ED1Logical");

	Field3 = new BGField3(0,zED1fieldbegins,ED1before,ED1after,ED1Logical,G4ThreeVector(0*cm,0*cm,Pipe5z)); //see BGField3.cc for description of input parameters

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(ED1Logical);
	ED1Logical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe5z),ED1Logical,"ED1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	ED1Logical->SetVisAttributes(BendingVisAtt);



    	//used in EMFieldDebugger.cc
    	xED1fieldends =  posPipe6[0] - Pipe6HL*sin(Pipe6angle);
    	zED1fieldends =  posPipe6[2] + Pipe6HL*cos(Pipe6angle);

	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>
	//	     Build SLITS 1 at Pipe6-Pipe7 boundary
	//
	G4String nameSolid1 = "Slits1Solid";
	G4String nameLogical1 = "Slits1Logical";
	G4String namePhys1 = "Slits1Phys";

	buildSlits( SpecWorldLogical, nameSolid1, nameLogical1, namePhys1,
		    slitshth, angle, posSlits1,insert_hSlits1, hAperture1);
	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>



	// Pipe7
	G4VSolid* Pipe7Solid = new G4Tubs("Pipe7Tub", 0*cm, rbigpipe, Pipe7HL-2*slitshth, 0*deg, 360*deg);
	Pipe7Logical = new G4LogicalVolume(Pipe7Solid, Vacuum, "Pipe7Logical", 0,0,0);
	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Pipe7Logical);
	Pipe7Logical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate1, posPipe7, Pipe7Logical, "Pipe7Physical", SpecWorldLogical,0,0,fCheckOverlaps);
	// Pipe7Wall
	G4VSolid* Pipe7WallSolid = new G4Tubs("Pipe7WallTub", rbigpipe, rbigpipe+wallThick, Pipe7HL-2*slitshth, 0*deg, 360*deg);
	G4LogicalVolume* Pipe7WallLogical = new G4LogicalVolume(Pipe7WallSolid, Wall, "Pipe7WallLogical", 0,0,0);
	new G4PVPlacement(Rotate1, posPipe7, Pipe7WallLogical, "Pipe7WallPhysical", SpecWorldLogical,0,0,fCheckOverlaps);

	// Rectangular aperture slit before MD
	xapth = 20.5/2*cm;
	yapth = 9.2/2*cm;
	G4ThreeVector posslit1MD2;

	slitshx=slitshout;
	slitshy=yapth+slitshout*2;
	cover1 = new G4Box("cover2",slitshx,slitshy,slitshth);
	slitshx=xapth;
	slitshy=slitshout;
	cover2 = new G4Box("cover1",slitshx,slitshy,slitshth);
	displace[0] = -xapth*2-slitshout*2;
	displace[1] = 0*cm;
	displace[2] = 0;
	coverX = new G4UnionSolid("coverX", cover1, cover1, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = yapth+slitshout;
	displace[2] = 0;
	coverXY = new G4UnionSolid("coverXY", coverX, cover2, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = -yapth-slitshout;
	displace[2] = 0;
	cover = new G4UnionSolid("cover", coverXY, cover2, Rotate0, displace);
	posslit1MD2[0] = posslit1MD[0]+(xapth+slitshout)*cos(ED1angle);
	posslit1MD2[1] = 0*cm;
	posslit1MD2[2] = posslit1MD[2]+(xapth+slitshout)*sin(ED1angle);
	G4LogicalVolume* MDSlit1Logical = new G4LogicalVolume(cover,Wall,"MDSlit1Logical",0,0,0);
	new G4PVPlacement(Rotate1,posslit1MD2,MDSlit1Logical,"MDSlit1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	MDSlit1Logical->SetVisAttributes(SlitsVisAtt);

	// Pipe1MD
	G4VSolid* Pipe1MDSolid = new G4Tubs("Pipe1MDTub", 0*cm, rbigpipe, Pipe1MDHL, 0*deg, 360*deg);
	// Pipe1MD
	G4VSolid* Pipe1MDWallSolid = new G4Tubs("Pipe1MDWallTub", rbigpipe, rbigpipe+wallThick, Pipe1MDHL, 0*deg, 360*deg);
	G4LogicalVolume* Pipe1MDWallLogical = new G4LogicalVolume(Pipe1MDWallSolid, Wall, "Pipe1MDWallLogical", 0,0,0);
	new G4PVPlacement(Rotate1, posPipe1MD, Pipe1MDWallLogical, "Pipe1MDWallPhysical", SpecWorldLogical,0,0,fCheckOverlaps);


	// If there is a problem with the position of the EDIP the problem is most likely in the start angle
	// MD
	G4VSolid* MDSolid = new G4Tubs("MDTub",MDr-MDhw,MDr+MDhw,MDhh,140*deg,MDangle);

	// MDWalls:
	G4VSolid* MDWall1Solid = new G4Tubs("MDWall1Tub",MDr-MDhw-wallThick,MDr-MDhw,MDhh+wallThick,160*deg,MDangle);
	G4LogicalVolume* MDWall1Logical = new G4LogicalVolume(MDWall1Solid,Wall,"MDWall1Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(xMD,0*cm,zMD),MDWall1Logical,"MDWall1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
   	G4VSolid* MDWall2Solid = new G4Tubs("MDWall2Tub",MDr+MDhw,MDr+MDhw+wallThick,MDhh+wallThick,160*deg,MDangle);
	G4LogicalVolume* MDWall2Logical = new G4LogicalVolume(MDWall2Solid,Wall,"MDWall2Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(xMD,0*cm,zMD),MDWall2Logical,"MDWall2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	G4VSolid* MDWall3Solid = new G4Tubs("MDWall3Tub",MDr-MDhw,MDr+MDhw,wallThick/2,160*deg,MDangle);
	G4LogicalVolume* MDWall3Logical = new G4LogicalVolume(MDWall3Solid,Wall,"MDWall3Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(xMD,MDhh+wallThick/2.0,zMD),MDWall3Logical,"MDWall3Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	G4VSolid* MDWall4Solid = new G4Tubs("MDWall4Tub",MDr-MDhw,MDr+MDhw,wallThick/2,160*deg,MDangle);
	G4LogicalVolume* MDWall4Logical = new G4LogicalVolume(MDWall4Solid,Wall,"MDWall4Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(xMD,-(MDhh+wallThick/2.0),zMD),MDWall4Logical,"MDWall4Physical",SpecWorldLogical,0,0,fCheckOverlaps);
    	MDWall1Logical->SetVisAttributes(BendingVisAtt);
    	MDWall2Logical->SetVisAttributes(BendingVisAtt);
    	MDWall3Logical->SetVisAttributes(BendingVisAtt);
    	MDWall4Logical->SetVisAttributes(BendingVisAtt);

	G4RotationMatrix* Rotate2 = new G4RotationMatrix();
	Rotate2->rotateY(-20*deg);

	// Pipe2MD
	G4VSolid* Pipe2MDSolid = new G4Tubs("Pipe2MDTub", 0*cm, rbigpipe, Pipe2MDHL, 0*deg, 360*deg);
	// Pipe2MD
	G4VSolid* Pipe2MDWallSolid = new G4Tubs("Pipe2MDWallTub", rbigpipe, rbigpipe+wallThick, Pipe2MDHL, 0*deg, 360*deg);
	G4LogicalVolume* Pipe2MDWallLogical = new G4LogicalVolume(Pipe2MDWallSolid, Wall, "Pipe2MDWallLogical", 0,0,0);
	new G4PVPlacement(Rotate2, posPipe2MD, Pipe2MDWallLogical, "Pipe2MDWallPhysical", SpecWorldLogical,0,0,fCheckOverlaps);

	// Create Union for field element
	// Create rotation matrix for following pipe
	G4RotationMatrix* RotateMD = new G4RotationMatrix();
	RotateMD->rotateY(-40*deg);
	G4UnionSolid* MDa = new G4UnionSolid("MDa", Pipe1MDSolid, MDSolid, RotateTube, MDoff);
	G4UnionSolid* MDUnion = new G4UnionSolid("MD", MDa, Pipe2MDSolid, RotateMD, Pipe2MDoff);

	// Create Field for MD
    	xMDfieldbegins = posPipe1MD[0] + Pipe1MDHL*sin(Pipe6angle);
    	zMDfieldbegins = posPipe1MD[2] - Pipe1MDHL*cos(Pipe6angle);
    	MDbefore=Pipe1MDHL*2;
    	MDafter=Pipe2MDHL*2;

	G4LogicalVolume* MDLogical = new G4LogicalVolume(MDUnion,Vacuum,"MDLogical");

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(MDLogical);
	MDLogical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate1, posPipe1MD, MDLogical, "MDPhysical", SpecWorldLogical, 0,0,fCheckOverlaps);
	MDLogical->SetVisAttributes(BendingVisAtt);

	Field4 = new BGField4(xMDfieldbegins,zMDfieldbegins,MDbefore,MDafter,MDLogical,posPipe1MD); //see BGField4.cc for description of input parameters

	//used in EMFieldDebugger.cc
	xMDfieldends = posPipe2MD[0] + Pipe2MDHL*sin(Pipe6angle);
    	zMDfieldends = posPipe2MD[2] + Pipe2MDHL*cos(Pipe6angle);

	// Rectangular aperture slit after MD
	xapth = 20.5/2*cm;
	yapth = 9.2/2*cm;
	G4ThreeVector posslit2MD2;

	slitshx=slitshout;
	slitshy=yapth+slitshout*2;
	cover1 = new G4Box("cover2",slitshx,slitshy,slitshth);
	slitshx=xapth;
	slitshy=slitshout;
	cover2 = new G4Box("cover1",slitshx,slitshy,slitshth);
	displace[0] = -xapth*2-slitshout*2;
	displace[1] = 0*cm;
	displace[2] = 0;
	coverX = new G4UnionSolid("coverX", cover1, cover1, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = yapth+slitshout;
	displace[2] = 0;
	coverXY = new G4UnionSolid("coverXY", coverX, cover2, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = -yapth-slitshout;
	displace[2] = 0;
	cover = new G4UnionSolid("cover", coverXY, cover2, Rotate0, displace);
	posslit2MD2[0] = posslit2MD[0]+(xapth+slitshout)*cos(ED1angle);
	posslit2MD2[1] = 0*cm;
	posslit2MD2[2] = posslit2MD[2]-(xapth+slitshout)*sin(ED1angle);
	G4LogicalVolume* MDSlit2Logical = new G4LogicalVolume(cover,Wall,"MDSlit2Logical",0,0,0);
	new G4PVPlacement(Rotate2,posslit2MD2,MDSlit2Logical,"MDSlit2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	MDSlit2Logical->SetVisAttributes(SlitsVisAtt);

	// Pipe8
	G4VSolid* Pipe8Solid = new G4Tubs("Pipe8Tub",0*cm, rbigpipe, Pipe8HL-2*slitshth, 0*deg, 360*deg);
	Pipe8Logical = new G4LogicalVolume(Pipe8Solid, Vacuum, "Pipe8Logical", 0,0,0);
	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Pipe8Logical);
	Pipe8Logical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate2, posPipe8, Pipe8Logical, "Pipe8Physical", SpecWorldLogical,0,0,fCheckOverlaps);
	// Pipe8Wall
	G4VSolid* Pipe8WallSolid = new G4Tubs("Pipe8WallTub", rbigpipe, rbigpipe+wallThick, Pipe8HL-2*slitshth, 0*deg, 360*deg);
	G4LogicalVolume* Pipe8WallLogical = new G4LogicalVolume(Pipe8WallSolid,Wall,"Pipe8WallLogical", 0,0,0);
	new G4PVPlacement(Rotate2, posPipe8, Pipe8WallLogical, "Pipe8WallPhysical", SpecWorldLogical, 0,0,fCheckOverlaps);

	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>
	//	     Build SLITS 2 at Pipe8-Pipe9 boundary
	//
	G4String nameSolid2 = "Slits2Solid";
	G4String nameLogical2 = "Slits2Logical";
	G4String namePhys2 = "Slits2Phys";
	buildSlits( SpecWorldLogical, nameSolid2, nameLogical2, namePhys2,
		    slitshth, -angle, posSlits2,insert_hSlits2, hAperture2);
	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>



	// Pipe9
	G4VSolid* Pipe9Solid = new G4Tubs("Pipe9Tub",0*cm,rbigpipe,Pipe9HL,0*deg,360*deg);
	// Pipe9Wall
	G4VSolid* Pipe9WallSolid = new G4Tubs("Pipe9WallTub",rbigpipe,rbigpipe+wallThick,Pipe9HL,0*deg,360*deg);
	G4LogicalVolume* Pipe9WallLogical = new G4LogicalVolume(Pipe9WallSolid,Wall,"Pipe9WallLogical", 0,0,0);
	new G4PVPlacement(Rotate2,posPipe9,Pipe9WallLogical,"Pipe9WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);

	// Rectangular aperture slit before ED2
	xapth = 12.5/2*cm;
	yapth = 40/2*cm;
	G4ThreeVector posED2slit2;

	slitshx=slitshout;
	slitshy=yapth+slitshout*2;
	cover1 = new G4Box("cover2",slitshx,slitshy,slitshth);
	slitshx=xapth;
	slitshy=slitshout;
	cover2 = new G4Box("cover1",slitshx,slitshy,slitshth);
	displace[0] = -xapth*2-slitshout*2;
	displace[1] = 0*cm;
	displace[2] = 0;
	coverX = new G4UnionSolid("coverX", cover1, cover1, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = yapth+slitshout;
	displace[2] = 0;
	coverXY = new G4UnionSolid("coverXY", coverX, cover2, Rotate0, displace);
	displace[0] = -xapth-slitshout;
	displace[1] = -yapth-slitshout;
	displace[2] = 0;
	cover = new G4UnionSolid("cover", coverXY, cover2, Rotate0, displace);
	posED2slit2[0] = posED2slit[0]+(xapth+slitshout)*cos(ED1angle);
	posED2slit2[1] = 0*cm;
	posED2slit2[2] = posED2slit[2]-(xapth+slitshout)*sin(ED1angle);
	G4LogicalVolume* ED2SlitLogical = new G4LogicalVolume(cover,Wall,"ED2SlitLogical",0,0,0);
	new G4PVPlacement(Rotate2,posED2slit2,ED2SlitLogical,"ED2SlitPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	ED2SlitLogical->SetVisAttributes(SlitsVisAtt);

	// ED2
	G4VSolid* ED2Solid = new G4Tubs("ED2Tub",x0-EDhw,x0+EDhw,EDhh,340*deg, ED1angle);

	// ED2 Walls
	// Wall 1: x<0 (down)
	G4VSolid* ED2Wall1Solid = new G4Tubs("ED2Wall1Tub",x0-EDhw-wallThick, x0-EDhw, EDhh+wallThick, 340*deg, ED1angle);
	G4LogicalVolume* ED2Wall1Logical = new G4LogicalVolume(ED2Wall1Solid,Wall,"ED2Wall1Logical", 0,0,0);
	G4double ED2z=posPipe9[2]+Pipe9HL*cos(ED1angle)+x0*sin(ED1angle);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0,0*cm,ED2z),ED2Wall1Logical,"ED2Wall1Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	// Wall 2: x>0 (up)
	G4VSolid* ED2Wall2Solid = new G4Tubs("ED2Wall2Tub", x0+EDhw, x0+EDhw+wallThick, EDhh+wallThick, 340*deg, ED1angle);
	G4LogicalVolume* ED2Wall2Logical = new G4LogicalVolume(ED2Wall2Solid,Wall,"ED2Wall2Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0,0*cm,ED2z),ED2Wall2Logical,"ED2Wall2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	// Wall 3: y>0 (into screen)
	G4VSolid* ED2Wall3Solid = new G4Tubs("ED2Wall3Tub", x0-EDhw, x0+EDhw, wallThick/2.0, 340*deg, ED1angle);
	G4LogicalVolume* ED2Wall3Logical = new G4LogicalVolume(ED2Wall3Solid,Wall,"ED2Wall3Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0, EDhh+wallThick/2.0, ED2z), ED2Wall3Logical,"ED2Wall3Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	// Wall 4: y<0 (out of screen)
	G4VSolid* ED2Wall4Solid = new G4Tubs("ED2Wall4Tub", x0-EDhw, x0+EDhw, wallThick/2.0, 340*deg, ED1angle);
	G4LogicalVolume* ED2Wall4Logical = new G4LogicalVolume(ED2Wall4Solid,Wall,"ED2Wall4Logical", 0,0,0);
	new G4PVPlacement(RotateTube,G4ThreeVector(-x0, -(EDhh+wallThick/2.0), ED2z), ED2Wall4Logical,"ED2Wall4Physical",SpecWorldLogical,0,0,fCheckOverlaps);
    	ED2Wall1Logical->SetVisAttributes(BendingVisAtt);
    	ED2Wall2Logical->SetVisAttributes(BendingVisAtt);
    	ED2Wall3Logical->SetVisAttributes(BendingVisAtt);
    	ED2Wall4Logical->SetVisAttributes(BendingVisAtt);


	// Create rotation matrix
	G4RotationMatrix* Rotate3 = new G4RotationMatrix();
	Rotate3->rotateY(0*deg);

	// Pipe10
	G4VSolid* Pipe10Solid = new G4Tubs("Pipe10Tub",0*cm,rbigpipe,Pipe10HL,0*deg,360*deg);
	// Pipe10Wall
	G4VSolid* Pipe10WallSolid = new G4Tubs("Pipe10WallTub",rbigpipe,rbigpipe+wallThick,Pipe10HL,0*deg,360*deg);
	G4LogicalVolume* Pipe10WallLogical = new G4LogicalVolume(Pipe10WallSolid,Wall,"Pipe10WallLogical", 0,0,0);
	G4double Pipe10z = ED2z+Pipe10HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe10z),Pipe10WallLogical,"Pipe10WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//Pipe10WallLogical->SetVisAttributes(WallVisAtt);

	//Create Union for field element
	// Create rotation matrix for following pipe
	G4RotationMatrix* RotateED2 = new G4RotationMatrix();
	RotateED2->rotateY(-20*deg);
	G4UnionSolid* ED2a = new G4UnionSolid("ED2a", Pipe10Solid, ED2Solid, RotateTube, ED2off);
	G4UnionSolid* ED2Union = new G4UnionSolid("ED2", ED2a, Pipe9Solid, RotateED2, Pipe10off);

	// Create Field for ED2
	xED2fieldbegins = posPipe9[0] - Pipe9HL*sin(Pipe6angle);
	zED2fieldbegins = posPipe9[2] - Pipe9HL*cos(Pipe6angle);
    	ED2before=Pipe9HL*2;
    	ED2after=Pipe10HL*2;

	G4LogicalVolume* ED2Logical = new G4LogicalVolume(ED2Union,Vacuum,"ED2Logical");

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(ED2Logical);
	ED2Logical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate0,G4ThreeVector(0*cm,0*cm,Pipe10z),ED2Logical,"ED2Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	ED2Logical->SetVisAttributes(BendingVisAtt);

	Field5 = new BGField5(xED2fieldbegins,zED2fieldbegins,ED2before,ED2after,ED2Logical,G4ThreeVector(0*cm,0*cm,Pipe10z)); //see BGField5.cc for description of input parameters
<<<<<<< HEAD
	
    	//used in EMFieldDebugger.cc
    	zED2fieldends = Pipe10z + Pipe10HL;
=======

    //used in EMFieldDebugger.cc
    zED2fieldends = Pipe10z + Pipe10HL;
    G4cout << "zED2 curve ends: " << Pipe10z - Pipe10HL << G4endl;
>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b

	// Pipe11
	G4VSolid* Pipe11Solid = new G4Tubs("Pipe11Tub",0*cm,rbigpipe,Pipe11HL,0*deg,360*deg);
	// Pipe11Wall
	G4VSolid* Pipe11WallSolid = new G4Tubs("Pipe11WallTub",rbigpipe,rbigpipe+wallThick,Pipe11HL,0*deg,360*deg);
	G4LogicalVolume* Pipe11WallLogical = new G4LogicalVolume(Pipe11WallSolid,Wall,"Pipe11WallLogical", 0,0,0);
	G4double Pipe11z = Pipe10z+Pipe10HL+Pipe11HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe11z),Pipe11WallLogical,"Pipe11WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//Pipe11WallLogical->SetVisAttributes(WallVisAtt);

	//********************************
	// Pipe11Cap (Detector end caps)
	G4VSolid* Pipe11CapSolid = new G4Tubs("Pipe11CapTub",Q3apt+wallThick,rbigpipe+wallThick,0.5*cm,0*deg,360*deg);
	G4LogicalVolume* Pipe11CapLogical = new G4LogicalVolume(Pipe11CapSolid,Wall,"Pipe11CapLogical", 0,0,0);
	G4double Pipe11Capz = Pipe10z+Pipe10HL+Pipe11HL+Pipe11HL+0.5*cm;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe11Capz),Pipe11CapLogical,"Pipe11CapPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//********************************

	// Q3 vacuum pipe extending out before magnet
	G4VSolid* Q3apt1Solid = new G4Tubs("Q3apt1Tub",0*cm,Q3apt,Q3apt1HL,0*deg,360*deg);
	// Q3apt1Wall
	G4VSolid* Q3apt1WallSolid = new G4Tubs("Q3apt1WallTub",Q3apt,Q3apt+wallThick,Q3apt1HL,0*deg,360*deg);
	G4LogicalVolume* Q3apt1WallLogical = new G4LogicalVolume(Q3apt1WallSolid,Wall,"Q3apt1WallLogical", 0,0,0);
	G4double Q3apt1z = Pipe11z+Pipe11HL+Q3apt1HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Q3apt1z),Q3apt1WallLogical,"Q3apt1WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);


	// Q3
	G4VSolid* Q3Solid = new G4Tubs("Q3Tub",0*cm,Q3apt,Q3HL,0*deg,360*deg);
	// Q3Wall
	G4VSolid* Q3WallSolid = new G4Tubs("Q3WallTub",Q3apt,Q3apt+wallThick,Q3HL,0*deg,360*deg);
	G4LogicalVolume* Q3WallLogical = new G4LogicalVolume(Q3WallSolid,Wall,"Q3WallLogical",0,0,0);
	G4double Q3z = Q3apt1z+Q3apt1HL+Q3HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Q3z),Q3WallLogical,"Q3WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q3WallLogical->SetVisAttributes(PoleVisAtt);

	// Q3 vacuum pipe extending out before magnet
	G4VSolid* Q3apt2Solid = new G4Tubs("Q3apt2Tub",0*cm,Q3apt,Q3apt2HL,0*deg,360*deg);
	// Q3apt2Wall
	G4VSolid* Q3apt2WallSolid = new G4Tubs("Q3apt2WallTub",Q3apt,Q4apt+wallThick,Q3apt2HL,0*deg,360*deg);
	G4LogicalVolume* Q3apt2WallLogical = new G4LogicalVolume(Q3apt2WallSolid,Wall,"Q3apt2WallLogical", 0,0,0);
	G4double Q3apt2z = Q3z+Q3HL+Q3apt2HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Q3apt2z),Q3apt2WallLogical,"Q3apt2WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);

	//Create Union for field element
	zQ3fieldbegins = Pipe11z - Pipe11HL;
    	Q3before=Pipe11HL*2+Q3apt1HL*2;
    	Q3after=Q3apt2HL*2;

	G4ThreeVector Q3off(0*cm,0,Pipe11HL+Q3apt1HL);
	G4UnionSolid* Q3ap = new G4UnionSolid("Q3ap", Pipe11Solid, Q3apt1Solid, Rotate3, Q3off);
	Q3off[2]=Q3off[2]+Q3apt1HL+Q3HL;
	G4UnionSolid* Q3a = new G4UnionSolid("Q3a", Q3ap, Q3Solid, Rotate3, Q3off);
	Q3off[2]=Q3off[2]+Q3HL+Q3apt2HL;
	G4UnionSolid* Q3Union = new G4UnionSolid("Q3", Q3a, Q3apt2Solid, Rotate3, Q3off);
	// Create Field for Q3

	Q3Logical = new G4LogicalVolume(Q3Union,Vacuum,"Q3Logical");

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Q3Logical);
	Q3Logical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe11z),Q3Logical,"Q3Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q3Logical->SetVisAttributes(BendingVisAtt);

	 Field6 = new BGField6(0,zQ3fieldbegins,Q3before,Q3after,Q3Logical,G4ThreeVector(0*m,0*cm,Pipe11z)); //see BGField6.cc for description of input parameters


	// Q4
	G4VSolid* Q4Solid = new G4Tubs("Q4Tub",0*cm,Q4apt,Q4HL,0*deg,360*deg);
	// Q4Wall
	G4VSolid* Q4WallSolid = new G4Tubs("Q4WallTub",Q4apt,Q4apt+wallThick,Q4HL,0*deg,360*deg);
	G4LogicalVolume* Q4WallLogical = new G4LogicalVolume(Q4WallSolid,Wall,"Q4WallLogical",0,0,0);
	G4double Q4z = Q3apt2z+Q3apt2HL+Q4HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Q4z),Q4WallLogical,"Q4WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q4WallLogical->SetVisAttributes(PoleVisAtt);

	// Pipe12
	G4VSolid* Pipe12Solid = new G4Tubs("Pipe12Tub",0*cm,rbigpipe,Pipe12HL,0*deg,360*deg);
	// Pipe12Wall
	G4VSolid* Pipe12WallSolid = new G4Tubs("Pipe12WallTub",rbigpipe,rbigpipe+wallThick,Pipe12HL,0*deg,360*deg);
	G4LogicalVolume* Pipe12WallLogical = new G4LogicalVolume(Pipe12WallSolid,Wall,"Pipe12WallLogical", 0,0,0);
	G4double Pipe12z = Q4z+Q4HL+Pipe12HL;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe12z),Pipe12WallLogical,"Pipe12WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//Pipe12WallLogical->SetVisAttributes(WallVisAtt);

	//********************************
	// Pipe12Cap (Detector end cap)
	G4VSolid* Pipe12CapSolid = new G4Tubs("Pipe12CapTub",Q4apt+wallThick,rbigpipe+wallThick,0.5*cm,0*deg,360*deg);
	G4LogicalVolume* Pipe12CapLogical = new G4LogicalVolume(Pipe12CapSolid,Wall,"Pipe12CapLogical", 0,0,0);
	G4double Pipe12Capz = Q4z+Q4HL-0.5*cm;
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe12Capz),Pipe12CapLogical,"Pipe12CapPhysical",SpecWorldLogical,0,0,fCheckOverlaps);
	//********************************

	//Create Union for field element
	zQ4fieldbegins = Q4z - Q4HL;
<<<<<<< HEAD
    	Q4before=0;
    	Q4after=Pipe12HL*2;
    
=======
    Q4before=0;
    Q4after=Pipe12HL*2;

>>>>>>> 328d247d31d8d865b2def4e9637587fef9e7941b
	G4ThreeVector Q4off(0*cm,0,Q4HL+Pipe12HL);
	G4UnionSolid* Q4Union = new G4UnionSolid("Q4", Q4Solid, Pipe12Solid, Rotate3, Q4off);
	// Create Field for Q4

	G4LogicalVolume* Q4Logical = new G4LogicalVolume(Q4Union,Vacuum,"Q4Logical");

	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Q4Logical);
	Q4Logical->SetRegion(vacuumRegion);
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Q4z),Q4Logical,"Q4Physical",SpecWorldLogical,0,0,fCheckOverlaps);
	Q4Logical->SetVisAttributes(BendingVisAtt);

	Field7 = new BGField7(0,zQ4fieldbegins,Q4before,Q4after,Q4Logical,G4ThreeVector(0*cm,0*cm,Q4z)); //see BGField7.cc for description of input parameters

    	//used in EMFieldDebugger.cc
    	zQ4fieldends = Pipe12z+Pipe12HL; //z location at end of field (field extends beyond width of element)

	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>
	//	     Build right SLIT 3 after Pipe12
	//
	G4String nameSolid3 = "Slits3Solid";
	G4String nameLogical3 = "Slits3Logical";
	G4String namePhys3 = "Slits3Phys";
	G4double x = 0*cm;
	G4double y = 0*cm;
	G4double z = Pipe12z + Pipe12HL; //position in front of slit not the center
	G4ThreeVector posSlits3 = G4ThreeVector(x,y,z);

	buildSlitSingle( SpecWorldLogical, nameSolid3, nameLogical3, namePhys3,
		    slitshth, posSlits3,
		    insert_rSlits3, rAperture3, false, 0 );
	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>

	// Pipe13
	G4VSolid* Pipe13Solid = new G4Tubs("Pipe13Tub",0*cm,rbigpipe,Pipe13HL-slitshth,0*deg,360*deg);
	G4LogicalVolume* Pipe13Logical = new G4LogicalVolume(Pipe13Solid, Vacuum, "Pipe13Logical", 0,0,0);
	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Pipe13Logical);
	Pipe13Logical->SetRegion(vacuumRegion);
	G4double Pipe13z = posSlits3[2]+2*slitshth+(Pipe13HL-slitshth);
	new G4PVPlacement(Rotate3, G4ThreeVector(0*cm,0*cm,Pipe13z), Pipe13Logical, "Pipe13Physical", SpecWorldLogical,0,0,fCheckOverlaps);
	// Pipe13Wall
	G4VSolid* Pipe13WallSolid = new G4Tubs("Pipe13WallTub",rbigpipe,rbigpipe+wallThick,Pipe13HL-slitshth,0*deg,360*deg);
	G4LogicalVolume* Pipe13WallLogical = new G4LogicalVolume(Pipe13WallSolid,Wall,"Pipe13WallLogical", 0,0,0);
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe13z),Pipe13WallLogical,"Pipe13WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);

	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>
	//	     Build left SLIT 4 after Pipe13
	//
	G4String nameSolid4 = "Slits4Solid";
	G4String nameLogical4 = "Slits4Logical";
	G4String namePhys4 = "Slits4Phys";
	x = 0*cm;
	y = 0*cm;
	z = Pipe13z + (Pipe13HL-slitshth); //position in front of slit not the center
	G4ThreeVector posSlits4 = G4ThreeVector(x,y,z);

	buildSlitSingle( SpecWorldLogical, nameSolid4, nameLogical4, namePhys4,
		    slitshth, posSlits4,
		    false, 0, insert_lSlits4, lAperture4);
	// <><><><><><><><><><><><><><><><><><><><><><><><><><><>

	// Pipe14
	G4VSolid* Pipe14Solid = new G4Tubs("Pipe14Tub",0*cm,rbigpipe,Pipe14HL-slitshth,0*deg,360*deg);
	G4LogicalVolume* Pipe14Logical = new G4LogicalVolume(Pipe14Solid, Vacuum, "Pipe14Logical", 0,0,0);
	if (vacuumRegion) vacuumRegion->AddRootLogicalVolume(Pipe14Logical);
	Pipe14Logical->SetRegion(vacuumRegion);
	G4double Pipe14z = posSlits4[2]+2*slitshth+(Pipe14HL-slitshth);
	new G4PVPlacement(Rotate3, G4ThreeVector(0*cm,0*cm,Pipe14z), Pipe14Logical, "Pipe14Physical", SpecWorldLogical,0,0,fCheckOverlaps);
	// Pipe14Wall
	G4VSolid* Pipe14WallSolid = new G4Tubs("Pipe14WallTub",rbigpipe,rbigpipe+wallThick,Pipe14HL-slitshth,0*deg,360*deg);
	G4LogicalVolume* Pipe14WallLogical = new G4LogicalVolume(Pipe14WallSolid,Wall,"Pipe14WallLogical", 0,0,0);
	new G4PVPlacement(Rotate3,G4ThreeVector(0*cm,0*cm,Pipe14z),Pipe14WallLogical,"Pipe14WallPhysical",SpecWorldLogical,0,0,fCheckOverlaps);

//------------------------------------------------------------------------------------------//
    	// Used in EMMADetectorConstruction.cc
	zQ1begins = Pipe1length; //Distance to beginning of Q1
	zQ4ends = Q4z + Q4HL; //Distance to end of Q4
	zAnode = posSlits4[2] + slitshth + (66.4)*mm; //Pipe14z+(Pipe14HL-slitshth); // Distance to focal plane (Anode)4
	//zFocalPlane = Pipe14z+(Pipe14HL-sliefltshth);
	zFocalPlane = zQ4ends + 307.6*mm;

//------------------------------------------------------------------------------------------//
    // Use in EMMASteppingAction.cc and EMFieldDebugger.cc for diagnostic purposes
    zQ1ends = Q1z + Q1HL;
    zQ2begins = Q2z - Q2HL;
    zQ2ends = Q2z + Q2HL;
    zQ3begins = Q3z - Q3HL; //z location at beginning of element
    zQ3ends = Q3z + Q3HL; //z location at end of element
    zQ4begins = Q4z - Q4HL;

    xED1center = -x0; //center coordinates of circle that defines shape and position of dipole
    zED1center = ED1z;
    xED2center = -x0;
    zED2center = ED2z;
    rED = x0; //radius of circle that defines shape and position of dipole
    xMDcenter = xMD;
    zMDcenter = zMD;
    rMD = MDr;


    //Calculate E and B fields and write it to file
    G4bool calcEFL=FALSE; //if false the E and B fields will not be written to file
    if(calcEFL){
      fieldFileName = UserDir;
      fieldFileName.append("/Results/fringefields/effFieldOpticalAxis.dat"); //Used in EMMAFieldDebugger.cc
      std::ofstream outfile;
      outfile.open (fieldFileName); //open and close to erase contents of file
      outfile.close();

      //0=Q1, 1=Q2, 2=ED1, 3=MD, 4=ED2, 5=Q3, 6=Q4, 7=custom
      //to calculate fields inside all elements uncomment for loop.
      //for(G4int i=7;i<10;i++){
        //EMFieldDebugger* EMdebug = new EMFieldDebugger(i); // writes field strengths at different positions to file
        //}
      //to calculate field inside one element
      //EMFieldDebugger* EMdebug = new EMFieldDebugger(2);
      //exit(0); // uncomment if you want to program to terminate after writing the fields to file
    }
//------------------------------------------------------------------------------------------//

}

SpectrometerConstruction::~SpectrometerConstruction()
{
}

void SpectrometerConstruction::PrintFieldStrength() // for debugging
{
  // print to monitor
  G4cout << G4endl;
  G4cout << "Field strengths: " << G4endl;
  G4cout << "Q1: " << Field1->GetFieldStrength() << " Tm" << G4endl;
  G4cout << "Q2: " << Field2->GetFieldStrength() << " Tm" << G4endl;
  G4cout << "ED1: " << Field3->GetFieldStrength() << "kV/cm" << G4endl;
  G4cout << "MD: " << Field4->GetFieldStrength() << " Tm" << G4endl;
  G4cout << "ED2: " << Field5->GetFieldStrength() << "kV/cm" << G4endl;
  G4cout << "Q3: " << Field6->GetFieldStrength() << " Tm" << G4endl;
  G4cout << "Q4: " << Field7->GetFieldStrength() << " Tm" << G4endl;
  G4cout << G4endl;
  // print same info to file
  std::ofstream outfile;
  G4String fname = UserDir;
  fname.append("/Results/fieldStrengths.dat");
  outfile.open (fname);
  outfile << "Q1: " << Field1->GetFieldStrength() << " Tm" << G4endl;
  outfile << "Q2: " << Field2->GetFieldStrength() << " Tm" << G4endl;
  outfile << "ED1: " << Field3->GetFieldStrength() << "kV/cm" << G4endl;
  outfile << "MD: " << Field4->GetFieldStrength() << " Tm" << G4endl;
  outfile << "ED2: " << Field5->GetFieldStrength() << "kV/cm" << G4endl;
  outfile << "Q3: " << Field6->GetFieldStrength() << " Tm" << G4endl;
  outfile << "Q4: " << Field7->GetFieldStrength() << " Tm" << G4endl;
  outfile.close();
}



void SpectrometerConstruction::ScaleFieldStrength( G4double msf, G4double esf )
{
  Field1->ScaleFieldStrength( msf );
  Field2->ScaleFieldStrength( msf );
  Field3->ScaleFieldStrength( esf );
  Field4->ScaleFieldStrength( msf );
  Field5->ScaleFieldStrength( esf );
  Field6->ScaleFieldStrength( msf );
  Field7->ScaleFieldStrength( msf );
}




// Read in user specifications for slits
void SpectrometerConstruction::ReadUserInput()
{
  double val;
  string text, line;
  ifstream inputfil;
  G4String filename = UserDir;
  filename.append("/UserInput/slits.dat");
  inputfil.open ( filename, ios::in );
  if ( inputfil.is_open() ) {
    int n=0;
    insert_hSlits1=true; // SLITS 1
	insert_hSlits2=true; // SLITS 2
	insert_rSlits3=true; // SLITS 3 right
	insert_lSlits4=true; // SLITS 4 left
    while ( inputfil.good() ) {
      inputfil >> text;
      if (text=="#") { // skip comments
	    getline (inputfil,line);
      }
      else {
    	n = n+1;
  	    if (text=="OUT") { //slits out
    	    val=200*cm; //very large aperture width
    	    if(n==3||n==4)val=100*cm;
	    }
	    else if (text!="OUT" ) { //slits in with specified width
	      val=atof(text.c_str())*mm;
	    }
        if (n==1) hAperture1 = val; //distance between the two slits
        if (n==2) hAperture2 = val;
        if (n==3) rAperture3 = val; //since right and left slit distances are from z=0 axis
        if (n==4) lAperture4 = val;
        inputfil.ignore(100,'\n');
      }
    }
    inputfil.close();
  }
  else cout << "Unable to open " << "UserInput/slits.dat" << endl;

}



void SpectrometerConstruction::buildSlits( G4LogicalVolume* SpecWorldLogical,
					   G4String nameSolid, G4String nameLogical, G4String namePhys,
					   G4double slitsThick, G4double angle, G4ThreeVector pos,
					   G4bool insert_hSlits, G4double hAper)
{
  G4int nElem;
  G4double z, weightRatio;
  G4String name, symbol;
  G4VSolid *aSlit, *anotherSlit;
  G4ThreeVector displace;

  // rotation matrices
  G4RotationMatrix* Rotate0 = new G4RotationMatrix();
  Rotate0->rotateY(0*deg);
  G4RotationMatrix* rotMat = new G4RotationMatrix();
  rotMat->rotateY(angle);

  // Aluminum
  G4double a = 26.98*g/mole;
  G4Element* elAl = new G4Element(name="Aluminum", symbol="Al", z=13., a);
  G4double density = 2.70*g/cm3;
  G4Material* Aluminum = new G4Material(name="Aluminum", density, nElem=1);
  Aluminum->AddElement(elAl, weightRatio=1.0);


  // Horizontal aperture
  G4double hXHL = 20*cm;  // just some large number
  G4double hYHL = 20*cm;  // ...
  aSlit = new G4Box("aSlit",hXHL,hYHL,slitsThick);
  anotherSlit = new G4Box("anotherSlit",hXHL,hYHL,slitsThick);
  displace[0] = 2*hXHL + hAper;
  displace[1] = 0;
  displace[2] = 0;
  name = "h";
  name.append(nameSolid);
  G4UnionSolid* hSlitsSolid = new G4UnionSolid(name, aSlit, anotherSlit, Rotate0, displace);
  name = "h";
  name.append(nameLogical);
  G4LogicalVolume* hSlitsLogical= new G4LogicalVolume(hSlitsSolid, Aluminum, name, 0,0,0);
  name = "h";
  name.append(namePhys);
  if (insert_hSlits && hAper>=0.) {
    G4ThreeVector hpos;
    G4double dx = -(hXHL+hAper/2)*cos(angle)-slitsThick*sin(angle);
    G4double dz = -(hXHL+hAper/2)*sin(angle)+slitsThick*cos(angle);
    hpos[0] = pos[0] + dx;
    hpos[1] = pos[1];
    hpos[2] = pos[2] + dz;
    new G4PVPlacement( rotMat, hpos, hSlitsLogical, name, SpecWorldLogical,0,0,fCheckOverlaps);
	hSlitsLogical->SetVisAttributes(SlitsVisAtt);
  }

}

void SpectrometerConstruction::buildSlitSingle( G4LogicalVolume* SpecWorldLogical,
		   G4String nameSolid, G4String nameLogical, G4String namePhys,
		   G4double slitsThick, G4ThreeVector pos,
		   G4bool insert_rSlits, G4double rAper,G4bool insert_lSlits, G4double lAper)
{
  G4int nElem;
  G4double z, weightRatio;
  G4String name, symbol;
  G4ThreeVector displace;

  // rotation matrices
  G4RotationMatrix* Rotate0 = new G4RotationMatrix();
  Rotate0->rotateY(0*deg);

  // Aluminum
  G4double a = 26.98*g/mole;
  G4Element* elAl = new G4Element(name="Aluminum", symbol="Al", z=13., a);
  G4double density = 2.70*g/cm3;
  G4Material* Aluminum = new G4Material(name="Aluminum", density, nElem=1);
  Aluminum->AddElement(elAl, weightRatio=1.0);

  // Right slit
  G4double hXHL = 20*cm;  // just some large number
  G4double hYHL = 20*cm;  // ...
  name = "r";
  name.append(nameSolid);
  G4VSolid* rSlitsSolid = new G4Box(name,hXHL,hYHL,slitsThick);
  name = "r";
  name.append(nameLogical);
  G4LogicalVolume* rSlitsLogical= new G4LogicalVolume(rSlitsSolid, Aluminum, name, 0,0,0);
  name = "r";
  name.append(namePhys);
  if (insert_rSlits && rAper>=0.) {
    G4ThreeVector rpos;
    G4double dx = -(hXHL+rAper);
    G4double dz = slitsThick;
    rpos[0] = pos[0] + dx;
    rpos[1] = pos[1];
    rpos[2] = pos[2] + dz;
    new G4PVPlacement( Rotate0, rpos, rSlitsLogical, name, SpecWorldLogical,0,0,fCheckOverlaps);
	rSlitsLogical->SetVisAttributes(SlitsVisAtt);
  }

  // Left slit
  name = "l";
  name.append(nameSolid);
  G4VSolid* lSlitsSolid = new G4Box(name,hXHL,hYHL,slitsThick);
  name = "l";
  name.append(nameLogical);
  G4LogicalVolume* lSlitsLogical= new G4LogicalVolume(lSlitsSolid, Aluminum, name, 0,0,0);
  name = "l";
  name.append(namePhys);
  if (insert_lSlits && lAper>=0.) {
    G4ThreeVector lpos;
    G4double dx = hXHL+lAper;
    G4double dz = slitsThick;
    lpos[0] = pos[0] + dx;
    lpos[1] = pos[1];
    lpos[2] = pos[2] + dz;
    new G4PVPlacement( Rotate0, lpos, lSlitsLogical, name, SpecWorldLogical,0,0,fCheckOverlaps);
	lSlitsLogical->SetVisAttributes(SlitsVisAtt);
  }

}
