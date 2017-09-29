#ifndef EMMAIonPhysicsMessenger_h
#define EMMAIonPhysicsMessenger_h 1

class EMMAIonPhysics;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

#include "G4UImessenger.hh"
#include "globals.hh"

/*!
 \file
 \brief This header file contains deals with user commands relating to ionic physics processes.

 As explained in the "G4UImessenger.hh" file, it is necessary for the user to to create his(her) own
 derivative class if (s)he wishes to define commands (for EMMA).
 This file is responsible for deleting commands, delivering commands to destination classes, defining global G4 variables specific to EMMA,
 and replying the current values of the parameters (again as described the "G4UImessenger.hh" source file)
 This is one of four similar EMMA headers, each titled "EMMA...Messenger.hh," which serves the same above purpose for different aspects of the EMMA simulation:
 see "EMMADetectorConstMessenger," "EMMAEventActionMessenger," "EMMAIonPhysicsMessenger," and "EMMAPrimaryGeneratorMessenger."
*/

class EMMAIonPhysicsMessenger: public G4UImessenger
{
public:
  EMMAIonPhysicsMessenger(EMMAIonPhysics* ionphys);
  ~EMMAIonPhysicsMessenger();
  void SetNewValue(G4UIcommand * command,G4String newValues);
  G4String GetCurrentValue(G4UIcommand * command);

private:
  EMMAIonPhysics * fTarget;

private: //commands
  G4UIdirectory * reactionDirectory;

private: //commands
  G4UIcmdWithADoubleAndUnit* fcsCmd;
  G4UIcmdWithADouble *fZ1Cmd,*fA1Cmd, *fZ2Cmd,*fA2Cmd, *fZ3Cmd,*fA3Cmd, *fZ4Cmd,*fA4Cmd;
  G4UIcmdWithADoubleAndUnit* fqmaxCmd;
  G4UIcmdWithABool* fAddProcessCmd;

};

#endif
