#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"


/// The large arrays that were here are now GONE.
/// Instead, we have this helper that holds the
/// information of all our histograms.

class HistoFactory_a{
 public:
  std::vector<std::string> vars;
  std::vector<int> nBins;
  std::vector<double> minBin;
  std::vector<double> maxBin;
  void setHisto(std::string s, int n, double min, double max) {
    vars.push_back(s);
    nBins.push_back(n);
    minBin.push_back(min);
    maxBin.push_back(max);
  }
};

/// EDBRHistoMaker_a is the class that analyzes the flat
/// TTree that comes out from the NTuple dumper module.
/// It doesn't make analysis; it just makes plots.
/// There are a few switches to do different plots:
/// SIGNAL - BACKGROUND,
/// MUON - ELECTRON, etc...

class EDBRHistoMaker_a {
 public:
  EDBRHistoMaker_a(TTree *tree=0,
         TFile *fileTMP=0,
                 TH1F* hR1=0,
		 bool wantElectrons=true,
		 bool wantMuons=true,
		 bool wantSideband=true, 
		 bool wantSignal=true,
		 bool wantFullRange=false,
		 int  wantNXJets=1,
		 bool isZZchannel=1);
  virtual ~EDBRHistoMaker_a();

  /// This is the tree structure. This comes directly from MakeClass
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   // Declaration of leaf types
   Double_t        scalef;
   Int_t           nVtx;
   Double_t        theWeight;
   Double_t        nump;
   Double_t        numm;
//   Double_t        npT;
   Int_t           lep;
//   Double_t        ptVlepJEC;
//   Double_t        yVlepJEC;
//   Double_t        phiVlepJEC;
//   Double_t        massVlepJEC;
   Double_t        mtVlepJECnew;
//   Double_t        Mla;
//   Double_t        Mva;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        philep1;
   Double_t        drla;
   Int_t           nlooseeles;
   Int_t           nloosemus;
   Double_t        photonet;
   Double_t        photoneta;
   Double_t        photonphi;
   Double_t        photone;
//   Double_t        photonsieie;
//   Double_t        photonphoiso;
//   Double_t        photonchiso;
//   Double_t        photonnhiso;
   Double_t        MET_et;
   Double_t        MET_phi;
//   Int_t           HLT_Ele1;
//   Int_t           HLT_Ele2;
   Int_t           HLT_Mu1;
   Int_t           HLT_Mu2;
   Int_t           HLT_Mu3;
   Int_t           isTrue;
   Int_t           isprompt;
   Double_t        lumiWeight;
   Double_t        pileupWeight;
//   Double_t        photon_pt[6];
//   Double_t        photon_eta[6];
//   Double_t        photon_phi[6];
//   Double_t        photon_e[6];
//   Char_t          photon_pev[6];
//   Char_t          photon_pevnew[6];
//   Char_t          photon_ppsv[6];
//   Char_t          photon_iseb[6];
//   Char_t          photon_isee[6];
//   Double_t        photon_hoe[6];
//   Double_t        photon_sieie[6];
//   Double_t        photon_chiso[6];
//   Double_t        photon_nhiso[6];
//   Double_t        photon_phoiso[6];
//   Int_t           photon_istrue[6];
//   Int_t           photon_isprompt[6];
//   Double_t        photon_drla[6];
//   Double_t        photon_mla[6];
   Double_t        jet1pt;
   Double_t        jet1eta;
   Double_t        jet1phi;
//   Double_t        jet1e;
   Double_t        jet2pt;
   Double_t        jet2eta;
   Double_t        jet2phi;
//   Double_t        jet2e;
   Double_t        Mjj;
//   Double_t        deltaeta;
   Double_t        zepp;
//   Double_t		   jet1metPhi;
//   Double_t 	   jet2metPhi;   

    TFile*  fileTMP_;
    TH1F* hR1_;
    
    // List of branches
   TBranch        *b_scalef;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_theWeight;   //!
   TBranch        *b_nump;   //!
   TBranch        *b_numm;   //!
//   TBranch        *b_npT;   //!
   TBranch        *b_lep;   //!
//   TBranch        *b_ptVlepJEC;   //!
//   TBranch        *b_yVlepJEC;   //!
//   TBranch        *b_phiVlepJEC;   //!
//   TBranch        *b_massVlepJEC;   //!
   TBranch        *b_mtVlepJECnew;   //!
//   TBranch        *b_Mla;   //!
//   TBranch        *b_Mva;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_drla;   //!
   TBranch        *b_nlooseeles;   //!
   TBranch        *b_nloosemus;   //!
   TBranch        *b_photonet;   //!
   TBranch        *b_photoneta;   //!
   TBranch        *b_photonphi;   //!
   TBranch        *b_photone;   //!
//   TBranch        *b_photonsieie;   //!
//   TBranch        *b_photonphoiso;   //!
//   TBranch        *b_photonchiso;   //!
//   TBranch        *b_photonnhiso;   //!
   TBranch        *b_MET_et;   //!
   TBranch        *b_MET_phi;
//   TBranch        *b_HLT_Ele1;   //!
//   TBranch        *b_HLT_Ele2;   //!
   TBranch        *b_HLT_Mu1;   //!
   TBranch        *b_HLT_Mu2;   //!
   TBranch        *b_HLT_Mu3;   //!
   TBranch        *b_isTrue;   //!
   TBranch        *b_isprompt;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_pileupWeight;   //!
//   TBranch        *b_photon_pt;   //!
//   TBranch        *b_photon_eta;   //!
//   TBranch        *b_photon_phi;   //!
//   TBranch        *b_photon_e;   //!
//   TBranch        *b_photon_pev;   //!
//   TBranch        *b_photon_pevnew;   //!
//   TBranch        *b_photon_ppsv;   //!
//   TBranch        *b_photon_iseb;   //!
//   TBranch        *b_photon_isee;   //!
//   TBranch        *b_photon_hoe;   //!
//   TBranch        *b_photon_sieie;   //!
//  TBranch        *b_photon_chiso;   //!
//   TBranch        *b_photon_nhiso;   //!
//   TBranch        *b_photon_phoiso;   //!
//   TBranch        *b_photon_istrue;   //!
//   TBranch        *b_photon_isprompt;   //!
//   TBranch        *b_photon_drla;   //!
//   TBranch        *b_photon_mla;   //!
   TBranch        *b_jet1pt;   //!
   TBranch        *b_jet1eta;   //!
   TBranch        *b_jet1phi;   //!
//   TBranch        *b_jet1e;   //!
   TBranch        *b_jet2pt;   //!
   TBranch        *b_jet2eta;   //!
   TBranch        *b_jet2phi;   //!
//   TBranch        *b_jet2e;   //!
   TBranch        *b_Mjj;   //!
//   TBranch        *b_deltaeta;   //!
   TBranch        *b_zepp;   //!
//   TBranch 		  *b_jet1metPhi;
//   TBranch		  *b_jet2metPhi;    

  // Basic functions directly from MakeClass
  Int_t    GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  void     Init(TTree *tree);
  void     Loop(std::string outFileName);

  // Our added functions
  void createAllHistos();
  void printAllHistos();
  void saveAllHistos(std::string outFileName);

  void setWantElectrons(bool doele=false){wantElectrons_=doele;}
  void setWantMuons(bool domu=false){wantMuons_=domu;}
  void setWantSideband(bool dosb=false){wantSideband_=dosb;}
  void setWantSignal(bool dosig=false){wantSignal_=dosig;}
  void setWantNXJets(int nxj=1){wantNXJets_=nxj;}
  void setUnitaryWeights(bool setuniw=false){setUnitaryWeights_=setuniw;}
//  void set_20_to_30_Weights(bool set20=false){set_20_to_30_Weights_=set20;}
//  void set_30_to_40_Weights(bool set30=false){set_30_to_40_Weights_=set30;}
//  void set_40_to_50_Weights(bool set40=false){set_40_to_50_Weights_=set40;}
//  void set_50_to_400_Weights(bool set50=false){set_50_to_400_Weights_=set50;}

  int check ( double pt, vector<double> * ptZ  )
  {
    int goodw=1;
    for(unsigned int i =0; i< ptZ->size(); i++)
      {   
	//printf("Comparing %g and %g\n",pt,ptZ->at(i));
	if(pt==ptZ->at(i)) { goodw=0; break;}
	//else {printf("I think they're different\n");}
      }   

    return goodw;
  }

  // Our added variables
  int nVars;
  bool wantElectrons_;
  bool wantMuons_;
  bool wantSideband_;
  bool wantSignal_;
  bool wantFullRange_;
  bool setUnitaryWeights_;
  bool debug_;
  int wantNXJets_;
//  bool set_20_to_30_Weights_;
//  bool set_30_to_40_Weights_;
//  bool set_40_to_50_Weights_;
//  bool set_50_to_400_Weights_;


  double sidebandVHMassLow_;
  double sidebandVHMassHigh_;
  double signalVHMassLow_;
  double signalVHMassHigh_;
  bool isZZchannel_;

  // The histograms
  HistoFactory_a hs;
  std::map<std::string,TH1D*> theHistograms;
  TH2D *hmjmzz; 
  TH1D *hmzzNEW;
};

void EDBRHistoMaker_a::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
 
  fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
   fChain->SetBranchAddress("nump", &nump, &b_nump);
   fChain->SetBranchAddress("numm", &numm, &b_numm);
//   fChain->SetBranchAddress("npT", &npT, &b_npT);
   fChain->SetBranchAddress("lep", &lep, &b_lep);
//   fChain->SetBranchAddress("ptVlepJEC", &ptVlepJEC, &b_ptVlepJEC);
//   fChain->SetBranchAddress("yVlepJEC", &yVlepJEC, &b_yVlepJEC);
//   fChain->SetBranchAddress("phiVlepJEC", &phiVlepJEC, &b_phiVlepJEC);
//   fChain->SetBranchAddress("massVlepJEC", &massVlepJEC, &b_massVlepJEC);
   fChain->SetBranchAddress("mtVlepJECnew", &mtVlepJECnew, &b_mtVlepJECnew);
//   fChain->SetBranchAddress("Mla", &Mla, &b_Mla);
//   fChain->SetBranchAddress("Mva", &Mva, &b_Mva);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("drla", &drla, &b_drla);
   fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
   fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
   fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
   fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
   fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
   fChain->SetBranchAddress("photone", &photone, &b_photone);
//   fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
//   fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
//   fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
//   fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
   fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
//   fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
//   fChain->SetBranchAddress("HLT_Ele2", &HLT_Ele2, &b_HLT_Ele2);
   fChain->SetBranchAddress("HLT_Mu1", &HLT_Mu1, &b_HLT_Mu1);
   fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
   fChain->SetBranchAddress("HLT_Mu3", &HLT_Mu3, &b_HLT_Mu3);
   fChain->SetBranchAddress("isTrue", &isTrue, &b_isTrue);
   fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
//   fChain->SetBranchAddress("photon_pt", &photon_pt, &b_photon_pt);
//   fChain->SetBranchAddress("photon_eta", &photon_eta, &b_photon_eta);
//   fChain->SetBranchAddress("photon_phi", &photon_phi, &b_photon_phi);
//   fChain->SetBranchAddress("photon_e", &photon_e, &b_photon_e);
//   fChain->SetBranchAddress("photon_pev", &photon_pev, &b_photon_pev);
//   fChain->SetBranchAddress("photon_pevnew", &photon_pevnew, &b_photon_pevnew);
//   fChain->SetBranchAddress("photon_ppsv", &photon_ppsv, &b_photon_ppsv);
//   fChain->SetBranchAddress("photon_iseb", &photon_iseb, &b_photon_iseb);
//   fChain->SetBranchAddress("photon_isee", &photon_isee, &b_photon_isee);
//   fChain->SetBranchAddress("photon_hoe", &photon_hoe, &b_photon_hoe);
//   fChain->SetBranchAddress("photon_sieie", &photon_sieie, &b_photon_sieie);
//   fChain->SetBranchAddress("photon_chiso", &photon_chiso, &b_photon_chiso);
//   fChain->SetBranchAddress("photon_nhiso", &photon_nhiso, &b_photon_nhiso);
//   fChain->SetBranchAddress("photon_phoiso", &photon_phoiso, &b_photon_phoiso);
//   fChain->SetBranchAddress("photon_istrue", &photon_istrue, &b_photon_istrue);
//   fChain->SetBranchAddress("photon_isprompt", &photon_isprompt, &b_photon_isprompt);
//   fChain->SetBranchAddress("photon_drla", &photon_drla, &b_photon_drla);
//   fChain->SetBranchAddress("photon_mla", &photon_mla, &b_photon_mla);
   fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
   fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
   fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
//   fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
   fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
   fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
   fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
//   fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
//   fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
//   fChain->SetBranchAddress("jet1metPhi",&jet1metPhi, &b_jet1metPhi);
//   fChain->SetBranchAddress("jet2metPhi",&jet2metPhi, &b_jet2metPhi);

}

EDBRHistoMaker_a::EDBRHistoMaker_a(TTree* tree,
                               TFile* fileTMP,
                               TH1F* hR1,
			       bool wantElectrons,
			       bool wantMuons,
			       bool wantSideband,
			       bool wantSignal,
			       bool wantFullRange,
			       int  wantNXJets,
			       bool isZZchannel){
  fChain = 0;

  // Which category do we want to analyze?
  wantElectrons_ = wantElectrons;
  wantMuons_ = wantMuons;
  wantSideband_ = wantSideband;
  wantSignal_ = wantSignal;
  wantFullRange_ = wantFullRange;
  wantNXJets_ = wantNXJets;
  isZZchannel_ = isZZchannel;
    fileTMP_ = fileTMP;
    hR1_ = hR1;
    

  debug_ = true;
  Init(tree);
  createAllHistos();
  printAllHistos();
}

EDBRHistoMaker_a::~EDBRHistoMaker_a() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}                  

Int_t EDBRHistoMaker_a::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t EDBRHistoMaker_a::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

//-------------------------
// Infrastructure functions
//-------------------------

void EDBRHistoMaker_a::createAllHistos() {

  /// This part substitutes the big arrays that used to be 
  /// in the beginning of this file.
  /// Much simpler to create histos now: just add them to
  /// hs with hs.setHisto(name,nbins,min,max);
//    hs.setHisto("nVtx", 25, -0.5, 35);
    hs.setHisto("photonet", 20,20,400);
    hs.setHisto("Mjj",20,0,4000);
//    hs.setHisto("photoneta", 25,-2.5,2.5);
//    hs.setHisto("ptVlepJEC", 25,0,1000);
    hs.setHisto("mtVlepJECnew", 16,0,200);
//    hs.setHisto("photonsieie", 10,0,0.02);
//    hs.setHisto("photonphoiso", 40,0,10.);
//    hs.setHisto("ptlep1", 25, 30,330);
//    hs.setHisto("etalep1", 25,-2.5,2.5);
///////    
//	hs.setHisto("zepp",25,0.0,3.5);
//	hs.setHisto("photonphi",25,-4,4);
//	hs.setHisto("photon_pt",25,20,400);
//	hs.setHisto("jet1eta",25,0,5);
//	hs.setHisto("jet2eta",25,0,5);
//	hs.setHisto("jet1phi",25,0,3.2);
//	hs.setHisto("jet2phi",25,0,3.2);
//	hs.setHisto("eta_jj",20,2.4,5.2);
//	hs.setHisto("phi_jj",20,0,3.2);
//	hs.setHisto("jet1pt",25,40,340);
//	hs.setHisto("jet2pt",25,30,230);
//    hs.setHisto("MET_et",25,35,185); */
//    hs.setHisto("nVtx", 25, -0.5, 35);
/*	    hs.setHisto("photonet", 16,0,400);
		    hs.setHisto("Mjj", 20,0,4000);
			    hs.setHisto("photoneta", 25,-2.5,2.5);
				    hs.setHisto("ptVlepJEC", 25,0,1000);
					    hs.setHisto("mtVlepJECnew", 16,0,200);
						    hs.setHisto("photonsieie", 25,0,0.02);
							    hs.setHisto("photonphoiso", 20,0,10.);
								    hs.setHisto("photonchiso",20,0,10);
									    hs.setHisto("ptlep1", 25, 30,330);
										    hs.setHisto("etalep1", 25,-2.5,2.5);
											///////    
											    hs.setHisto("zepp",25,0.0,3.5);
												    hs.setHisto("photonphi",25,-4,4);
													    hs.setHisto("photon_pt",25,20,400);
														    hs.setHisto("jet1eta",25,0,5);
															    hs.setHisto("jet2eta",25,0,5);
																    hs.setHisto("jet1phi",25,0,3.2);
																	    hs.setHisto("jet2phi",25,0,3.2);
																		    hs.setHisto("eta_jj",20,2.4,5.2);
																			    hs.setHisto("phi_jj",20,0,3.2);
																				    hs.setHisto("jet1pt",25,40,340);
																					    hs.setHisto("jet2pt",25,30,230);
																						    hs.setHisto("MET_et",25,35,185);

	
*/	
	//    hs.setHisto("",,,);
//    hs.setHisto("",,,);
//    hs.setHisto("",,,);
//    hs.setHisto("",,,);
 
  char buffer[256];
  char buffer2[256];

  nVars = hs.vars.size();

  for(int i = 0; i!= nVars; ++i) {
    sprintf(buffer,"%s_mu",hs.vars[i].c_str());
//    sprintf(buffer,"%s_el",hs.vars[i].c_str());
    sprintf(buffer2,"%s;%s;Number of events;",hs.vars[i].c_str(),hs.vars[i].c_str());
    TH1D* histogram = new TH1D(buffer,
			       buffer2,
			       hs.nBins[i],
			       hs.minBin[i],
			       hs.maxBin[i]);
    histogram->SetStats(kFALSE);
	    histogram->SetMinimum(0.01);   
	histogram->SetDirectory(0);
    histogram->Sumw2();
    theHistograms[hs.vars[i]] = histogram;
  }

}

void EDBRHistoMaker_a::printAllHistos() {
  printf("We have %i histograms \n",int(theHistograms.size()));
  typedef std::map<std::string, TH1D*>::iterator it_type;
  for(it_type iterator = theHistograms.begin(); iterator != theHistograms.end(); iterator++) {
    //iterator->second->Print();
    // Repeat if you also want to iterate through the second map.
  }
}

void EDBRHistoMaker_a::saveAllHistos(std::string outFileName) {

  TFile* outFile = TFile::Open(outFileName.c_str(),"RECREATE");

  for(int i = 0; i!=nVars; ++i) {
    std::string name = hs.vars[i];
    const TH1D* thisHisto = this->theHistograms[name];
    thisHisto->Write();
  }
  outFile->Close();
}

///----------------------------------------------------------------
/// This is the important function, the loop over all events.
/// Here we fill the histograms according to cuts, weights,
/// and can also filter out events on an individual basis.
///----------------------------------------------------------------
void EDBRHistoMaker_a::Loop(std::string outFileName){

 // TFile * input1 = new TFile ("test.root");
//  TH1F* hR1= (TH1F*)input1->Get("hRatio");
  if (fChain == 0) return;
 // double lumivalue = 0.57831;
    int numbe_out = 0;
    double actualWeight;
  Long64_t nentries = fChain->GetEntriesFast();
//    std::cout<<"nentries"<<nentries<<std::endl;
  Long64_t npp = fChain->GetEntries("theWeight>0.");
  Long64_t nmm = fChain->GetEntries("theWeight<0.");
  Double_t nn;
//  std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;
  Long64_t nbytes = 0, nb = 0;

    for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //    for (Long64_t jentry=0; jentry<10000;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    nb = fChain->GetEntry(jentry);   nbytes += nb;

//    if(jentry%1000000==0); std::cout << "Entry num " << jentry << std::endl;

 
    // int bin = hR1_->FindBin(nVtx);
   // pileupWeight = hR1_->GetBinContent(bin);
 

    if(theWeight>0) nn=1;
    else nn= -1;

   // if(npp>0) actualWeight = lumiWeight*pileupWeight/(npp-nmm)*nn*lumivalue;
   // else actualWeight = lumiWeight*pileupWeight/nentries*lumivalue;//0.00810255;//0.0521;//0.04024;//0.00559;
	//if(lumiWeight <0) continue;
   //      actualWeight = lumiWeight*pileupWeight*scalef;
//              if(photonet>=20 && photonet<30) actualWeight=0.186;
//			          else if(photonet>=30 && photonet<40) actualWeight=0.129;
//					          else if(photonet>=40 && photonet<50) actualWeight=0.110;
//							          else if(photonet>=50 && photonet<70) actualWeight=0.096;
//			  else if(photonet>=70 && photonet<100) actualWeight=0.074;
//			  else if(photonet>=100 && photonet<400) actualWeight=0.045;
//			  else if(photonet>=80 && photonet<400) actualWeight=0.06/2.6;
//				else actualWeight=0;									  
	  //      actualWeight =scalef;
    if(setUnitaryWeights_) {
      if(jentry==0)printf("Unitary weights set!\n");
      actualWeight=1.0;
    }

    // We get the histogram from the map by string and fill it.
    // We could wrap all the fills in the this->eventPassesCut()
    // to fill histograms only for the events which pass a given
    // cut (Sideband / SignalRegion, Muon / Electron, 
    // Single / Double jet ...) 

    // Remember: bool eventPassesCut(double ptZ_threshold, double ptlep1_threshold );
    //if(eventPassesCut(20, 20)){


   //   int bveto=1;
     // for(int i=0; i<8; i++)  {

	//if(ak4jet_pt[i]>30 && ak4jet_icsv[i]>0.890  && fabs(ak4jet_eta[i])<2.4  && ak4jet_IDLoose[i]>0 && deltaRAK4AK8[i]>=0.8) {bveto=0; break;}

 //     }

	//Int_t nLooseLep=nLooseEle+nLooseMu;
  
      
//		if(lep==13 && photonet>15. && photonet<100. && HLT_Mu1>0 && drla>0.5 && fabs(photoneta)<1.44 && ptlep1>25. && fabs(etalep1)<2.1 && nlooseeles==0 && nloosemus<2 && MET_et>35.0 );

 
//       if(lep==13 && photonet>20. &&photonet<400 /* && HLT_Mu1>0*/ && drla>0.5 && fabs(photoneta)<1.44 && ptlep1>25. && fabs(etalep1)<2.1 && nlooseeles==0     && nloosemus<3 && MET_et>35.0 && /*jet1pt>85 && jet2pt>75*/ jet1pt>40 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 &&  Mjj>400 && fabs(jet2eta-jet1eta)>2.4 && fabs(MET_phi-jet1phi)>0.4 && fabs(MET_phi-jet2phi)> 0.4  &&  sqrt((philep1-photonphi)*(philep1-photonphi)+(etalep1-photoneta)*(etalep1-photoneta))>0.5  &&   sqrt((jet1phi-philep1)*(jet1phi-philep1)+(jet1eta-etalep1)*(jet1eta-etalep1))>0.5  &&  sqrt((jet2phi-philep1)*(jet2phi-philep1)+(jet2eta-etalep1)*(jet2eta-etalep1))>0.5  &&  sqrt((jet1phi-photonphi)*(jet1phi-photonphi)+(jet1eta-photoneta)*(jet1eta-photoneta))>0.5 && sqrt((jet2phi-photonphi)*(jet2phi-photonphi)+(jet2eta-photoneta)*(jet2eta-photoneta))>0.5   && zepp < 0.5);
//        if(lep==13 && photonet>15. && photonet<45. && HLT_Mu1>0 && drla>0.7 && fabs(photoneta)>1.556 && fabs(photoneta)<2.5 && ptlep1>30. && fabs(etalep1)<2.1 && nlooseeles==0 && nloosemus<2 && MET_et>40.0);
//	 if(lep==13 && photonet>20.&& fabs(photoneta)<1.4442 && MET_et>20 && ptlep1>20 && fabs(etalep1)<2.4 && Mjj>700 && fabs(jet2eta-jet1eta)>2.4 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 && sqrt((philep1-photonphi)*(philep1-photonphi)+(etalep1-photoneta)*(etalep1-photoneta))>0.4  &&   sqrt((jet1phi-philep1)*(jet1phi-philep1)+(jet1eta-etalep1)*(jet1eta-etalep1))>0.4  &&  sqrt((jet2phi-philep1)*(jet2phi-philep1)+(jet2eta-etalep1)*(jet2eta-etalep1))>0.4  &&  sqrt((jet1phi-photonphi)*(jet1phi-photonphi)+(jet1eta-photoneta)*(jet1eta-photoneta))>0.4 && sqrt((jet2phi-photonphi)*(jet2phi-photonphi)+(jet2eta-photoneta)*(jet2eta-photoneta))>0.4 && zepp < 0.5) ;  

/*if(lep==13 && mtVlepJECnew>50. && ptlep1>20. && fabs(etalep1)<2.4 && MET_et>20. && nlooseeles==0 && nloosemus<2
		        && photonet>20 && fabs(photoneta)<1.4442 && drla>0.7 && photonet<400
				        && jet1pt>40 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 &&  Mjj>700  && fabs(jet2eta-jet1eta)>2.4 

						        && fabs(MET_phi-jet1phi)>0.4 && fabs(MET_phi-jet2phi)> 0.4 &&  sqrt((philep1-photonphi)*(philep1-photonphi)+(etalep1-photoneta)*(etalep1-photoneta))>0.5  &&   sqrt((jet1phi-philep1)*(jet1phi-philep1)+(jet1eta-etalep1)*(jet1eta-etalep1))>0.5  &&  sqrt((jet2phi-philep1)*(jet2phi-philep1)+(jet2eta-etalep1)*(jet2eta-etalep1))>0.5  &&  sqrt((jet1phi-photonphi)*(jet1phi-photonphi)+(jet1eta-photoneta)*(jet1eta-photoneta))>0.5 && sqrt((jet2phi-photonphi)*(jet2phi-photonphi)+(jet2eta-photoneta)*(jet2eta-photoneta))>0.5	);*/
double dphijj_v =-10;   if(fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7) {if(fabs(jet1phi-jet2phi)>=3.1415926) dphijj_v=(fabs(jet1phi-jet2phi))-3.1415926; else dphijj_v=(fabs(jet1phi-jet2phi));}
    if(lep==13 && mtVlepJECnew>50. && ptlep1>30. &&  fabs(etalep1)<2.1 && MET_et>30. && nlooseeles==0 && nloosemus<3 &&
		         photonet>20 && fabs(photoneta)<1.4442 && drla>0.7 && photonet<400 &&
			          jet1pt>40 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7 &&  Mjj>400  &&
				            fabs(jet2eta-jet1eta) > 2.4 
					//		&& dphijj_v > 0.3
							//		&&	zepp < 1.6
	 && fabs(MET_phi-jet1phi)>0.4 && fabs(MET_phi-jet2phi)> 0.4 &&  sqrt((philep1-photonphi)*(philep1-photonphi)+(etalep1-photoneta)*(etalep1-photoneta))>0.5  &&   sqrt((jet1phi-philep1)*(jet1phi-philep1)+(jet1eta-etalep1)*(jet1eta-etalep1))>0.5  &&  sqrt((jet2phi-philep1)*(jet2phi-philep1)+(jet2eta-etalep1)*(jet2eta-etalep1))>0.5  &&  sqrt((jet1phi-photonphi)*(jet1phi-photonphi)+(jet1eta-photoneta)*(jet1eta-photoneta))>0.5 && sqrt((jet2phi-photonphi)*(jet2phi-photonphi)+(jet2eta-photoneta)*(jet2eta-photoneta))>0.5       
	 
	  );







	else continue;

		if(photonet>=20 && photonet<40) actualWeight=0.193/5.8;
		else if(photonet>=40 && photonet<50) actualWeight=0.129/5.8;
		else if(photonet>=50 && photonet<70) actualWeight=0.113/5.8;
		else if(photonet>=70 && photonet<100) actualWeight=0.069/5.8;
		else if(photonet>=10 && photonet<200) actualWeight=0.028/5.8;
		//else if(photonet>=100 && photonet<400) actualWeight=0.045/4.353;

		int iswjets = 0;
            int isnotwets = 0;
            int iszjets = 0;
            int isttjets = 0;

            TString filename = fileTMP_->GetName();
            if (filename.Contains("WJets") && isprompt!= 1){
                iswjets = 1;
             //   std::cout<<"WJETs"<<iswjets<<std::endl;
                }
            if (filename.Contains("ZJets") && isprompt!= 1){
                iszjets = 1;
                }
            if (filename.Contains("TTJets") && isprompt!= 1){
                isttjets = 1;
                }
            if (!(filename.Contains("WJets")) && !(filename.Contains("ZJets")) && !(filename.Contains("TTJets")) ) {
                isnotwets = 1;
                }
 
 
            if (isnotwets>0 || iswjets>0 || iszjets>0 || isttjets>0) {
//if(jet1pt>40 && jet2pt>30 && abs(jet1eta)<4.7 && abs(jet2eta)<4.7 && abs(jet1metPhi)>0.4 && abs(jet2metPhi)>0.4 && Mjj>200 && drla>0.5  ) 
//{
//      (theHistograms["nVtx"])->Fill(nVtx,actualWeight);
      (theHistograms["photonet"])->Fill(photonet,actualWeight);
      (theHistograms["Mjj"])->Fill(Mjj,actualWeight);
//      (theHistograms["photoneta"])->Fill(photoneta,actualWeight);
//    (theHistograms["ptVlepJEC"])->Fill(ptVlepJEC,actualWeight);
      (theHistograms["mtVlepJECnew"])->Fill(mtVlepJECnew,actualWeight);
//      (theHistograms["photonsieie"])->Fill(photonsieie,actualWeight);
//      (theHistograms["photonphoiso"])->Fill(photonphoiso,actualWeight);
//	  (theHistograms["photonchiso"])->Fill(photonchiso,actualWeight);
//    (theHistograms["ptlep1"])->Fill(ptlep1,actualWeight);
//      (theHistograms["etalep1"])->Fill(etalep1,actualWeight);
//////
// 	  (theHistograms["zepp"])->Fill(zepp,actualWeight);			//zepp
//	  (theHistograms["photonphi"])->Fill(photonphi,actualWeight);//photonphi
//      (theHistograms["photon_pt"])->Fill(photon_pt[0],actualWeight);
//	  (theHistograms["jet1pt"])->Fill(jet1pt,actualWeight);
//	  (theHistograms["jet2pt"])->Fill(jet2pt,actualWeight);
//	  (theHistograms["jet1eta"])->Fill(jet1eta,actualWeight);
//	  (theHistograms["jet2eta"])->Fill(jet2eta,actualWeight);
//	  (theHistograms["jet1phi"])->Fill(jet1phi,actualWeight);
//	  (theHistograms["jet2phi"])->Fill(jet2phi,actualWeight);
//	  (theHistograms["MET_et"])->Fill(MET_et,actualWeight);
	double etajj=jet2eta-jet1eta; if((etajj)<0) etajj=-etajj;  
//	  (theHistograms["eta_jj"])->Fill(etajj,actualWeight);
	double phijj=jet2phi-jet1phi; if(phijj<0) phijj=-phijj; if(phijj>3.14159265358) phijj=2*3.14159265358-phijj;
//if(phijj>3.14) cout<<"no"<<endl<<phijj<<endl;
//	  (theHistograms["phi_jj"])->Fill(phijj,actualWeight);
    //  (theHistograms["philep1"])->Fill(philep1,actualWeight);
    //  (theHistograms["MET_et"])->Fill(MET_et,actualWeight);
     // }//end if eventPassesCut
// } 
              }
  }//end loop over entries
//   cout << "after cut: " << numbe_out << "*actualweight" << actualWeight << " result " << numbe_out*actualWeight << endl; 
  //std::cout<<"From makeHisto: the histo with #vtx has "<<(theHistograms["nVtx"])->GetEntries()<<" entries"<<std::endl;
  this->saveAllHistos(outFileName);
}
