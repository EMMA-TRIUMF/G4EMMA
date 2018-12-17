#include "TROOT.h"
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TCutG.h>

void acceptance_plots() {

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // call the data files
  TFile *ang_file = new TFile("/home/awen/G4EMMA_data/Ang_acceptance_test_10k/Results/GEMMAoutput.root");
  TFile *energy_file = new TFile("/home/awen/G4EMMA_data/Energy_acceptance_1k/Results/GEMMAoutput.root");

  // create a new file in case I want to write anything to save
  TFile *file = new TFile("acceptance_plots.root","RECREATE");

  // call the trees in the data files
  TTree *ang_tree = (TTree*)ang_file->Get("fphits");
  TTree *energy_tree = (TTree*)energy_file->Get("fphits");

  // data variables
  Double_t fp_posX_a, fp_posY_a, tar_angX_a, tar_angY_a;
  Double_t fp_posX_e, fp_posY_e, tar_energy;

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // get the values of the data from the tree and populate our variables
  ang_tree->SetBranchAddress("fp_posX",&fp_posX_a);
  ang_tree->SetBranchAddress("fp_posY",&fp_posY_a);
  ang_tree->SetBranchAddress("target_angX",&tar_angX_a);
  ang_tree->SetBranchAddress("target_angY",&tar_angY_a);
  Int_t nentries = (Int_t)ang_tree->GetEntries();
  energy_tree->SetBranchAddress("fp_posX",&fp_posX_e);
  energy_tree->SetBranchAddress("fp_posY",&fp_posY_e);
  energy_tree->SetBranchAddress("target_Ekin",&tar_energy);
  Int_t pentries = (Int_t)energy_tree->GetEntries();

  // make the histograms to fill
  TH1F* ang_X = new TH1F("X angle","Target X angle",100,-0.1,0.1);
  TH1F* ang_Y = new TH1F("Y angle","Target Y angle",100,-0.1,0.1);
  TH2F* ang_XY = new TH2F("angle distribution","Target angle distribution",100,-0.1,0.1,100,-0.1,0.1);

  TH1F* energy = new TH1F("energy","Target energy distribution",100,50,150);

  // get the max and min values of energy and angles that made it to the focal plane
  Double_t max_e = 100;
  Double_t min_e = 100;
  Double_t max_ang_x = 0;
  Double_t min_ang_x = 0;
  Double_t max_ang_y = 0;
  Double_t min_ang_y = 0;

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // fill the angular acceptance histograms
  for (int i=0; i<nentries; i++) {
    ang_tree->GetEntry(i);
    ang_X->Fill(tar_angX_a);
    ang_Y->Fill(tar_angY_a);
    ang_XY->Fill(tar_angX_a,tar_angY_a);

    //-----------------------------------------------------------------------------------//
    // find min and max angles in the x and y directions
    if (tar_angX_a >= max_ang_x) {
      max_ang_x = tar_angX_a;
    }
    if (tar_angX_a <= min_ang_x) {
      min_ang_x = tar_angX_a;
    }

    if (tar_angY_a >= max_ang_y) {
      max_ang_y = tar_angY_a;
    }
    if (tar_angY_a <= min_ang_y) {
      min_ang_y = tar_angY_a;
    }
    //-----------------------------------------------------------------------------------//

  }

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // fill the energy acceptance histograms
  for (int i=0; i<pentries; i++) {
    energy_tree->GetEntry(i);
    energy->Fill(tar_energy);

    //-----------------------------------------------------------------------------------//
    // find the max and min energy
    if (tar_energy >= max_e) {
      max_e = tar_energy;
    }
    if (tar_energy <= min_e) {
      min_e = tar_energy;
    }
    //-----------------------------------------------------------------------------------//
  }

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

// define cuts based on the max/min values of energy/angle
/*
TCut ct1 = "tar_energy < max_e";
TCut ct2 = "tar_energy > min_e";
TCut ct3 = "tar_angX_a < max_ang_x";
TCut ct4 = "tar_angX_a > min_ang_x";
TCut ct5 = "tar_angY_a < max_ang_y";
TCut ct6 = "tar_angY_a > min_ang_y";

TCut energycut = ct1&&ct2;
TCut angXcut = ct3&&ct4;
TCut angYcut = ct5&&ct6;
TCut angcut = angXcut&&angYcut;
*/

// make a bunch of canvases and display the histograms
TCanvas * c1 = new TCanvas("c1");
ang_X->GetXaxis()->SetTitle("X (rad)");
ang_X->Draw();

TCanvas * c2 = new TCanvas("c2");
ang_Y->GetXaxis()->SetTitle("Y (rad)");
ang_Y->Draw();

TCanvas * c3 = new TCanvas("c3");
ang_XY->GetXaxis()->SetTitle("X (rad)");
ang_XY->GetYaxis()->SetTitle("Y (rad)");
ang_XY->Draw();

TCanvas * c4 = new TCanvas("c4");
energy->GetXaxis()->SetTitle("MeV");
TH1F* energy_all = (TH1F*)energy_file->Get("targetEkin");
energy->Draw();
energy_all->SetLineColor(2);
energy_all->Draw("same");

TCanvas * c5 = new TCanvas("c5");
TH2F* ang_all = (TH2F*)ang_file->Get("targetdir");
ang_all->Draw("");

// Display some important max/min values
std::cout << "Max energy accepted: " << max_e << " Min energy accepted: " << min_e << std::endl;
std::cout << "Max X angle: " << max_ang_x << " Min X angle: " << min_ang_x << std::endl;
std::cout << "Max Y angle: " << max_ang_y << " Min Y angle: " << min_ang_y << std::endl;


}
