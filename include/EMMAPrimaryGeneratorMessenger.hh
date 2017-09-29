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
// $Id: EMMAPrimaryGeneratorMessenger.hh,v 1.4 2006-06-29 16:31:37 gunter Exp $
// --------------------------------------------------------------
//
#ifndef EMMAPrimaryGeneratorMessenger_h
#define EMMAPrimaryGeneratorMessenger_h 1

class EMMAPrimaryGeneratorAction;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"

/*! \file
 \brief
    This file is responsible for deleting commands, delivering commands to destination classes, defining global G4 variables specific to EMMA,
    and replying the current values of the parameters (again as described the "G4UImessenger.hh" source file) regarding the primary generator (of the events)

    This header file contains classes built upon the base class created in the G4 header "G4UImessenger.hh."
    As explained in the "G4UImessenger.hh" file, it is necessary for the user to to create his(her) own
    derivative class if (s)he wishes to define commands (for EMMA).
    This is one of four similar EMMA headers, each titled "EMMA...Messenger," which serves the same above purpose for different aspects of the EMMA simulation:
    see "EMMADetectorConstMessenger," "EMMAEventActionMessenger," "EMMAIonPhysicsMessenger," and "EMMAPrimaryGeneratorMessenger."
*/


class EMMAPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  EMMAPrimaryGeneratorMessenger(EMMAPrimaryGeneratorAction* mpga);
  ~EMMAPrimaryGeneratorMessenger();

public:
  void SetNewValue(G4UIcommand * command,G4String newValues);
  G4String GetCurrentValue(G4UIcommand * command);

private:
  EMMAPrimaryGeneratorAction * target;
  G4UIdirectory * reactionDirectory;

private: //commands
  G4UIcmdWithADouble  *beamZCmd, *beamACmd, *beamChargeCmd;
  G4UIcmdWithADoubleAndUnit*  energyCmd;
  G4UIcmdWithADouble*  sigmaEngCmd;
  G4UIcmdWithADoubleAndUnit*  AngCmd;
  G4UIcmdWithADoubleAndUnit*  transEmittanceCmd;
  G4UIcmdWithADoubleAndUnit*  beamSpotDiameterCmd;
  G4UIcmdWithABool  *doPrepareCmd, *doBeamCmd, *doReactionCmd;
  G4UIcmdWithAnInteger* nEventsCmd;
  G4UIcmdWithADouble *fZ1Cmd,*fA1Cmd, *fZ2Cmd,*fA2Cmd, *fZ3Cmd,*fA3Cmd, *fZ4Cmd,*fA4Cmd;
  G4UIcmdWithADoubleAndUnit *fqminCmd,*fqmaxCmd;
  G4UIcmdWithADouble *fCharge3Cmd;
  G4UIcmdWithADoubleAndUnit *fExcitationEnergy3Cmd;

};

#endif


