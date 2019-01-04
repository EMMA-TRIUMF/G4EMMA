#include "TROOT.h"
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include

#define M_PI 3.14159265358979323846L

void dispersion_plots() {

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // call the data files
  TFile *z_file = new TFile("/home/awen/G4EMMA_data/Disp_test_0/Results/GEMMAoutput.root");

  TFile *p1_file = new TFile("/home/awen/G4EMMA_data/Disp_test_+1/Results/GEMMAoutput.root");
  TFile *p2_file = new TFile("/home/awen/G4EMMA_data/Disp_test_+2/Results/GEMMAoutput.root");
  TFile *p3_file = new TFile("/home/awen/G4EMMA_data/Disp_test_+3/Results/GEMMAoutput.root");

  TFile *m1_file = new TFile("/home/awen/G4EMMA_data/Disp_test_-1/Results/GEMMAoutput.root");
  TFile *m2_file = new TFile("/home/awen/G4EMMA_data/Disp_test_-2/Results/GEMMAoutput.root");
  TFile *m3_file = new TFile("/home/awen/G4EMMA_data/Disp_test_-3/Results/GEMMAoutput.root");

  // create a new file in case I want to write anything to save
  //TFile *file = new TFile("acceptance_plots.root","RECREATE");

  // call the trees in the data files
  TTree *z_tree = (TTree*)z_file->Get("fphits");

  TTree *p1_tree = (TTree*)p1_file->Get("fphits");
  TTree *p2_tree = (TTree*)p2_file->Get("fphits");
  TTree *p3_tree = (TTree*)p3_file->Get("fphits");

  TTree *m1_tree = (TTree*)m1_file->Get("fphits");
  TTree *m2_tree = (TTree*)m2_file->Get("fphits");
  TTree *m3_tree = (TTree*)m3_file->Get("fphits");

  // data variables

  Double_t z_x, p1, p2, p3, m1, m2, m3;

// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // get the values of the data from the tree and populate our variables
  z_tree->SetBranchAddress("fp_posX",&z_x);

  p1_tree->SetBranchAddress("fp_posX",&p1);
  p2_tree->SetBranchAddress("fp_posX",&p2);
  p3_tree->SetBranchAddress("fp_posX",&p3);

  m1_tree->SetBranchAddress("fp_posX",&m1);
  m2_tree->SetBranchAddress("fp_posX",&m2);
  m3_tree->SetBranchAddress("fp_posX",&m3);

  Int_t nentries = (Int_t)z_tree->GetEntries();


  // make the histograms to fill

  TH1F* z_hist = new TH1F("z_x","z_x",10000,-50,50);

  TH1F* p1_hist = new TH1F("p1","p1",10000,-50,50);
  TH1F* p2_hist = new TH1F("p2","p2",10000,-50,50);
  TH1F* p3_hist = new TH1F("p3","p3",10000,-50,50);

  TH1F* m1_hist = new TH1F("m1","m1",10000,-50,50);
  TH1F* m2_hist = new TH1F("m2","m2",10000,-50,50);
  TH1F* m3_hist = new TH1F("m3","m3",10000,-50,50);


// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\

  // fill the histograms
  for (Int_t i=0; i<nentries; i++) {

    z_tree->GetEntry(i);
    p1_tree->GetEntry(i);
    p2_tree->GetEntry(i);
    p3_tree->GetEntry(i);
    m1_tree->GetEntry(i);
    m2_tree->GetEntry(i);
    m3_tree->GetEntry(i);

    z_hist->Fill(z_x);
    p1_hist->Fill(p1);
    p2_hist->Fill(p2);
    p3_hist->Fill(p3);
    m1_hist->Fill(m1);
    m2_hist->Fill(m2);
    m3_hist->Fill(m3);

  }

// define the variables that we are interested in finding
Double_t z_mean, p1_mean, p2_mean, p3_mean, m1_mean, m2_mean, m3_mean;
Double_t z_stdev, p1_stdev, p2_stdev, p3_stdev, m1_stdev, m2_stdev, m3_stdev;

// get the mean and stdev from the histogram values, so they can be plotted
z_mean = z_hist->GetMean();   z_stdev = z_hist->GetStdDev();
p1_mean = p1_hist->GetMean(); p1_stdev = p1_hist->GetStdDev();
p2_mean = p2_hist->GetMean(); p2_stdev = p2_hist->GetStdDev();
p3_mean = p3_hist->GetMean(); p3_stdev = p3_hist->GetStdDev();
m1_mean = m1_hist->GetMean(); m1_stdev = m1_hist->GetStdDev();
m2_mean = m2_hist->GetMean(); m2_stdev = m2_hist->GetStdDev();
m3_mean = m3_hist->GetMean(); m3_stdev = m3_hist->GetStdDev();

std::cout << p1_mean << " " << p1_stdev << std::endl;


// /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\ /^(o.o)^\




}
