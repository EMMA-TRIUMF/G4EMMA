// Created by Matthew Williams
// Adapted from example B2b

/*!
     \file
     \brief This is a parameterisation that describes a series of cylinders (wires) along X.

  The cylinders have equal radius and length.
  They are spaced an equal distance apart, starting from given location.
  This header file defines variables and functions that are designed to be used in addition to the G4 header file "G4VPVParameterisation.hh"
  The file "G4VPVParameterisation.hh," in turn, calls upon other headers that detail materials and other technical aspects of parameterizing.
  Hence this header file adds to the classes and variables already declared in "G4VPVParameterisation.hh" to suit EMMA's needs.
  *Note: this header file also contains a considerable number of dummy classes and functions to get rid of error warnings. (These classes and variables were first introduced in the G4 headers)
*/

#ifndef CathodeWireParameterisation_h
#define CathodeWireParameterisation_h 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Box;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;


class CathodeWireParameterisation : public G4VPVParameterisation
{
  public:

    CathodeWireParameterisation(G4int    noWires,
                              G4double startX,
                              G4double spacing,
                              G4double wireRadius,
                              G4double wireLength );

    virtual ~CathodeWireParameterisation();

    void ComputeTransformation (const G4int copyNo,
                                G4VPhysicalVolume* physVol) const;

    void ComputeDimensions (G4Tubs & CathodeWire, const G4int copyNo, //check this
                            const G4VPhysicalVolume* physVol) const;

  private:  // Dummy declarations to get rid of warnings ...

    void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}

  private:

    G4int    fNoWires;
    G4double fStartX;
    G4double fHalfRadius;        //  The half-radius of each wire
    G4double fSpacing;          //  The distance between the wires' center
    G4double fHalfLength;        //  half-length

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
