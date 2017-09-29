//
// Created from BuildGeometry program
//

/**
 \file
 \brief BGField1-7 are 7 almost identical headers that define 7 similar classes derived from "EMMAElementField.hh."
 They each descibe an EM field that is part of EMMA.

 There are 7 header files to reflect the 7 fields used in EMMA: the Q Q E M E Q Q set up.
 This is evident in the history of the document; before "EMMAElementField.hh" was developed for general EM fields,
 old G4 headers like "G4MagneticField" and "G4ElectricField" were used.
 */
#ifndef BGField7_H
#define BGField7_H 1
#include "globals.hh"
#include "G4MagneticField.hh"

#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"

#include "EMMAElementField.hh"



// global variables
extern G4double currentCharge; // EMMASteppingAction.cc
extern G4double userCharge; // EMMAPrimaryGeneratorAction.cc


//class BGField7 : public G4MagneticField


class BGField7 : public EMMAElementField
{
public:
  //offset coordinates are of the x and z location of where the field begins in reference to
  //the world logical volume
  //BGField7(G4double xoffset, G4double zoffset,G4double zbefore,G4double zafter);
   BGField7(G4double xoffset, G4double zoffset,G4double zbefore,G4double zafter, G4LogicalVolume*, G4ThreeVector);
  ~BGField7();

  // instead you can limit the size

  virtual G4double GetLength() { return DBL_MAX; }
  virtual G4double GetWidth() { return DBL_MAX; }
  virtual G4double GetHeight() { return DBL_MAX; }

  // AddFieldValue() adds the field for this element into the field[].
  // Point() is in global coordinates.

  virtual void AddFieldValue( const G4double Point[3], G4double field[6]) const;

 // virtual void GetFieldValue( const double Point[3], G4double *Bfield) const;

private:
  double data[75], offset[3];
  G4int i;
  G4double Pi;
  G4double FieldStrength_0;

public:
  G4double GetFieldStrength() { return data[13]; };
  void ScaleFieldStrength( G4double msf ) { data[13] = msf * FieldStrength_0 ; };

};
#endif
