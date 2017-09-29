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
// $Id: EMMAEventActionMessenger.hh,v 1.6 2006-06-29 16:31:06 gunter Exp $
// --------------------------------------------------------------
//
#ifndef EMMAEventActionMessenger_h
#define EMMAEventActionMessenger_h 1

class EMMAEventAction;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"


/*! \file
 \brief
    This file is responsible for deleting commands, delivering commands to destination classes, defining global G4 variables specific to EMMA,
    and replying the current values of the parameters (again as described the "G4UImessenger.hh" source file) regarding the event action (from the primary generator)

    This header file contains classes built upon the base class created in the G4 header "G4UImessenger.hh."
    As explained in the "G4UImessenger.hh" file, it is necessary for the user to to create his(her) own
    derivative class if (s)he wishes to define commands (for EMMA).
    This is one of four similar EMMA headers, each titled "EMMA...Messenger," which serves the same above purpose for different aspects of the EMMA simulation:
    see "EMMADetectorConstMessenger," "EMMAEventActionMessenger," "EMMAIonPhysicsMessenger," and "EMMAPrimaryGeneratorMessenger."
*/



class EMMAEventActionMessenger: public G4UImessenger
{
  public:
    EMMAEventActionMessenger(EMMAEventAction* mpga);
    ~EMMAEventActionMessenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    EMMAEventAction* target;

  private: //commands
    G4UIcmdWithAnInteger*  verboseCmd;

};

#endif


