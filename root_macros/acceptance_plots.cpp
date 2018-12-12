#include "TROOT.h"
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>

void acceptance_plots() {

  // call the data files
  TFile *ang_file = new TFile("/home/awen/G4EMMA_data/Ang_acceptance_test_10k/Results/GEMMAoutput.root");
  TFile *energy_file = new TFile("/home/awen/G4EMMA_data/Energy_acceptance_1k/Results/GEMMAoutput.root");

  // creat a new file in case I want to write anything to save
  TFile *file = new TFile("acceptance_plots.root","RECREATE");

  // call the trees in the data files
  TTree *ang_tree = (TTree*)ang_file->Get("fphits");
  TTree *energy_tree = (TTree*)energy_file->Get("fphits");

  // data variables
  Double_t fp_posX_a, fp_posY_a, tar_angX_a, tar_angY_a;
  Double_t fp_posX_e, fp_posY_e, tar_energy;


  ang_tree->SetBranchAddress("fp_posX",&fp_posX_a);
  ang_tree->SetBranchAddress("fp_posY",&fp_posY_a);
  ang_tree->SetBranchAddress("target_angX",&tar_angX_a);
  ang_tree->SetBranchAddress("target_angY",&tar_angY_a);
  Int_t nentries = (Int_t)ang_tree->GetEntries();

  energy_tree->SetBranchAddress("fp_posX",&fp_posX_e);
  energy_tree->SetBranchAddress("fp_posY",&fp_posY_e);
  energy_tree->SetBranchAddress("target_Ekin",&tar_energy);
  Int_t pentries = (Int_t)energy_tree->GetEntries();

  TH1F* ang_X = new TH1F("X angle","Target X angle",100,-0.1,0.1);
  TH1F* ang_Y = new TH1F("Y angle","Target Y angle",100,-0.1,0.1);
  TH2F* ang_XY = new TH2F("angle distribution","Target angle distribution",100,-0.1,0.1,100,-0.1,0.1);

  TH1F* energy = new TH1F("energy","Target energy distribution",100,50,150);

  // get the max and min values of the energy histogram (the one that made it to the focal plane)
  Double_t max=100;
  Double_t min=100;

  // fill the angular acceptance histograms
  for (int i=0; i<nentries; i++) {
    ang_tree->GetEntry(i);
    ang_X->Fill(tar_angX_a);
    ang_Y->Fill(tar_angY_a);
    ang_XY->Fill(tar_angX_a,tar_angY_a);

  }

  // fill the energy acceptance histograms
  for (int i=0; i<pentries; i++) {
    energy_tree->GetEntry(i);
    energy->Fill(tar_energy);

    if (tar_energy >= max) {
      max = tar_energy;
    }
    if (tar_energy <= min) {
      min = tar_energy;
    }
  }

TCanvas * c1 = new TCanvas("c1");
ang_X->GetXaxis()->SetTitle("rad");
ang_X->Draw();
TCanvas * c2 = new TCanvas("c2");
ang_Y->GetXaxis()->SetTitle("rad");
ang_Y->Draw();
TCanvas * c3 = new TCanvas("c3");
ang_XY->GetXaxis()->SetTitle("rad");
ang_XY->GetYaxis()->SetTitle("rad");
ang_XY->Draw();
TCanvas * c4 = new TCanvas("c4");
energy->GetXaxis()->SetTitle("MeV");
TH1F* energy_all = (TH1F*)energy_file->Get("targetEkin");
energy->Draw();
  std::cout << "Max: " << max << " Min: " << min << std::endl;
energy_all->SetLineColor(2);
energy_all->Draw("same");


}
