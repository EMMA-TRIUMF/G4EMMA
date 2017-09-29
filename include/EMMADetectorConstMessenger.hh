//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: A01DetectorConstMessenger.hh,v 1.4 2006-06-29 16:30:32 gunter Exp $
// --------------------------------------------------------------
//
#ifndef EMMADetectorConstMessenger_h
#define EMMADetectorConstMessenger_h 1

class EMMADetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;

#include "G4UImessenger.hh"
#include "globals.hh"


/*!
 \file
 \brief This header file contains deals with user commands relating to detector construction.

 As explained in the "G4UImessenger.hh" file, it is necessary for the user to to create his(her) own
 derivative class if (s)he wishes to define commands (for EMMA).
 This file is responsible for deleting commands, delivering commands to destination classes, defining global G4 variables specific to EMMA,
 and replying the current values of the parameters (again as described the "G4UImessenger.hh" source file)
 This is one of four similar EMMA headers, each titled "EMMA...Messenger.hh," which serves the same above purpose for different aspects of the EMMA simulation:
 see "EMMADetectorConstMessenger," "EMMAEventActionMessenger," "EMMAIonPhysicsMessenger," and "EMMAPrimaryGeneratorMessenger."
*/


class EMMADetectorConstMessenger: public G4UImessenger
{
public:
  EMMADetectorConstMessenger(EMMADetectorConstruction* mpga);
  ~EMMADetectorConstMessenger();

public:
  void SetNewValue(G4UIcommand * command,G4String newValues);
  G4String GetCurrentValue(G4UIcommand * command);

private:
  EMMADetectorConstruction * target;

private: //commands
  G4UIdirectory * mydetDirectory;

private: //commands
  G4UIcmdWithADouble*  centralZCmd;
  G4UIcmdWithADouble*  centralACmd;
  G4UIcmdWithADouble*  centralQCmd;
  G4UIcmdWithADoubleAndUnit*  centralECmd;
  G4UIcmdWithoutParameter*  updategeoCmd;

};

#endif


