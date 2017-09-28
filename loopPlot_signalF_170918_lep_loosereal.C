#include <Riostream.h>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TError.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "EDBRHistoMaker.h"
#include "EDBRHistoPlotter.h"
#include "test.C"
#include "CMSTDRStyle.h"
//add this if you want to plot fake photon fraction on your control plots
//#include "EDBRHistoMaker_a_B.h"
//#include "EDBRHistoMaker_d.h"

void loopPlot_signalF_170918_lep_loose(){

  gErrorIgnoreLevel=kFatal;//suppresses all info messages
  
  setTDRStyle();//TDR style
 
  
  //#####################EDIT THE OPTIONS##############################
  /// Boolean flags to steer the histogram making
  bool wantElectrons = true; // Will make histograms for electrons
  bool wantMuons     = true; // Will make histograms for muons
  bool wantSideband  = true; // Will make histograms for sideband region
  bool wantSignal    = true; // Will make histograms for signal region
  bool wantFullRange = true; // Will not check signal or sideband, ie, pick all jet mass range
  int  wantNXJets    = 1; // Will make histograms for 1 or 2 jet topology
  int  isZZchannel   = 0; //plot label for zz (1) or ww (0)
  int  flavour = 0; 
  if(wantElectrons) flavour=11; if(wantMuons) flavour=13; if(wantElectrons and wantMuons) flavour=0;
  
	double lumiValue = 3.026;
  bool scaleToData = false;
//	bool scaleToData = true;
// Should we scale only wjets to make total MC = DATA?
  bool scaleOnlyWJets = false;
  /// Should we plot the Data/Bkg and Data-Bkg/Error ratios?
  bool makeRatio = true;
  /// Should we REDO histograms?
  bool redoHistograms = true;
  /// Should we put the signal MC stacked on top of the background (or just plot the signal alone)?
  bool isSignalStackOnBkg = false;
    bool dopileupreweight = false;
//	bool dopileupreweight = true;	

  /// Path to wherever the files with the trees are. 
	std::string pathToTrees="./making_root_small/outtree_170918_lep_loose/";


  std::string outputDir = "./";


  const int nDATA=1;//set to zero if you don't want to plot

	std::string dataLabels[nDATA]={"outSingleMuon_Run2016F_s"};
  std::vector<std::string> fData;
  
  for(int ii=0;ii<nDATA;ii++){
    fData.push_back(pathToTrees+dataLabels[ii]+".root");
  }

  /// Setup names of MC files for trees.

//  const int nMC=6;
  const int nMC=8;

	std::string mcLabels[nMC]={"ST_s","TTG_s","VV_s","ZG_s","WJets_s","ZJets_s","TTJets_s","WG_s"};
    double kFactorsMC_array[nMC] = {1, 1, 1, 1, 1, 1, 1, 1};

  	std::vector<std::string> fMC;
  for(int ii=0;ii<nMC;ii++){
    fMC.push_back(pathToTrees+"out"+mcLabels[ii]+".root");
  }

  std::vector<double> kFactorsMC;
  for (int index=0; index<nMC; index++)
    {
      //std::cout << kFactorsMC_array[index] << std::endl;
      kFactorsMC.push_back( kFactorsMC_array[index] );	
    }

  /// Setup names of MC signal files for trees.
  const int nMCSig=1;
std::string mcLabelsSig[nMCSig]={"outVBS_WGamma_signal_s"};
  double kFactorsSig_array[nMCSig] = {1};
  std::vector<double> kFactorsMCSig;
  for (int index=0; index<nMCSig; index++)
    {
      kFactorsMCSig.push_back( kFactorsSig_array[index] );	
    }
 
  cout<<"treeEDBR error?"<<endl; 
  std::vector<std::string> fMCSig;
  for(int ii=0;ii<nMCSig;ii++){
    fMCSig.push_back(pathToTrees+mcLabelsSig[ii]+".root");
  }
  cout<<"treeEDBR error?2"<<endl;

  /// Setup names of files for histograms (data and MC)
  std::vector<std::string> fHistosData;
  std::vector<std::string> fHistosMC;
  std::vector<std::string> fHistosMCSig;
 
//  char buffer[256];
char buffer[64];
char buffer2[64];
  printf("All strings set\n");


  /// ----------------------------------------------------------------
  /// This first part is the loop over trees to create histogram files 
  /// ----------------------------------------------------------------

  /// The EDBRHistoMaker, for reference
  ///

  printf("\nStart making histograms\n\n");

  //loop over data files and make histograms individually for each of them
    TH1F* hisRatio=0;
    for(int i=0;i<nDATA;i++){
cout<<"nDATA = "<<nDATA<<endl<<endl;
    std::cout<<"\n-------\nRunning over "<<dataLabels[i].c_str()<<std::endl;
    std::cout<<"The file is " <<fData.at(i)<<std::endl;
    sprintf(buffer,"histos_%s.root",dataLabels[i].c_str());
    fHistosData.push_back(buffer);
    
        std::cout<<"OK??"<<std::endl;
      TFile *fileData = TFile::Open(fData.at(i).c_str());
    //  TTree *treeData = (TTree*)fileData->Get("treeDumper/PKUCandidates");
          TTree *treeData = (TTree*)fileData->Get("demo");
        std::cout<<"OK??"<<std::endl;

        TFile *fileMC = TFile::Open(fMC.at(i).c_str());
cout<<"no error so far"<<endl;     
//  TTree *treeMC = (TTree*)fileMC->Get("treeDumper/PKUCandidates");
//error down here
          TTree *treeMC = (TTree*)fileMC->Get("demo");

        std::cout<<"OK??"<<std::endl;
        if (dopileupreweight) {
        hisRatio = test(treeData,treeMC);
        std::cout<<"hisRatio = "<<hisRatio<<std::endl;
        }
      if(redoHistograms) {
      EDBRHistoMaker* maker_data = new EDBRHistoMaker(treeData,
                        fileData,
                        hisRatio,
                        wantElectrons,
						 wantMuons,
						 wantSideband,
						 wantSignal,
						 wantFullRange,
						 wantNXJets,
						 isZZchannel);
      maker_data->setUnitaryWeights(true);  //??
      maker_data->Loop(buffer);
      //delete maker_data; // This class is badly written and deleting it isn't safe!
      fileData->Close();
    }
    
  }//end loop on data files

  printf("Loop over data done\n");



  //loop over MC files and make histograms individually for each of them
  for(int i=0;i<nMC;i++){
    std::cout<<"\n-------\nRunning over "<<mcLabels[i].c_str()<<std::endl;
    std::cout<<"The file is " <<fMC.at(i)<<std::endl;    
    sprintf(buffer,"histos_%s.root",mcLabels[i].c_str());
    fHistosMC.push_back(buffer);
    std::cout<<"test"<<std::endl;   
 
    if(redoHistograms){
      TFile *fileMC = TFile::Open(fMC.at(i).c_str()); 
	  cout<<endl<<"we are dealing with : "<<fMC.at(i).c_str()<<endl<<endl;
        //  TTree *treeMC = (TTree*)fileMC->Get("treeDumper/PKUCandidates");
          TTree *treeMC = (TTree*)fileMC->Get("demo");
		
        {  EDBRHistoMaker* maker = new EDBRHistoMaker(treeMC,
                               fileMC,
                               hisRatio,
						 wantElectrons, 
						 wantMuons, 
						 wantSideband, 
						 wantSignal, 
						 wantFullRange,
						 wantNXJets,
						 isZZchannel);

	 	maker->setUnitaryWeights(false);
	    maker->Loop(buffer);	
		}

//      maker->Loop(buffer);
      fileMC->Close();
    }
    
  }//end loop on MC files

  printf("Loop over MC done\n");

  //loop over MC signal files and make histograms individually for each of them
  for(int i=0;i<nMCSig;i++){
//  for(int i=0;i<0;i++){
    std::cout<<"\n-------\nRunning over "<<mcLabelsSig[i].c_str()<<std::endl;
    //std::cout<<"failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    std::cout<<"The file is " <<fMCSig.at(i)<<std::endl;    
    sprintf(buffer,"histos_%s.root",mcLabelsSig[i].c_str());
    fHistosMCSig.push_back(buffer);

    if(redoHistograms){
      TFile *fileMCSig = TFile::Open(fMCSig.at(i).c_str());  
      //  TTree *treeMCSig = (TTree*)fileMCSig->Get("treeDumper/PKUCandidates");
        TTree *treeMCSig = (TTree*)fileMCSig->Get("demo");
      EDBRHistoMaker* maker = new EDBRHistoMaker(treeMCSig,
                        fileMCSig,
                            hisRatio,
                        wantElectrons,
						 wantMuons,
						 wantSideband, 
						 wantSignal, 
						 wantFullRange,
						 wantNXJets,
						 isZZchannel);
//      maker->setUnitaryWeights(false);
	  maker->setUnitaryWeights(false);
      maker->Loop(buffer);
      //delete maker; // This class is badly written and deleting it isn't safe!
      fileMCSig->Close();
    }
    
  }//end loop on MC files

  printf("Loop over MC signal done\n");
  
  /// ------------------------------------------------------------------
  /// This second part is the loop over histograms to create stack plots
  /// ------------------------------------------------------------------  

    
  printf("\nStart looping over histograms\n\n");
  //make nice plots
  std::vector<std::string> listOfHistos;
  if(nMC>0){
    // Open one of the histogram files just to get the list of histograms
    // produced, then loop over all the histograms inheriting 
    // from TH1 contained in the file.
    sprintf(buffer,"histos_%s.root",mcLabels[0].c_str());
    std::cout<<"Opening "<<buffer<<std::endl;
    TFile* oneFile = TFile::Open(buffer);
    TIter next(oneFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *hTMP = (TH1*)key->ReadObj();
      std::string hName=hTMP->GetName();
      printf("Histogram found: %s\n",hName.c_str());
      listOfHistos.push_back(hName);
    }//end while loop
    oneFile->Close();
  }//end if fmc size >0

  std::cout << "Creating plotter" << std::endl;
  EDBRHistoPlotter *plotter=new EDBRHistoPlotter("./",
						 fHistosData,
						 fHistosMC,
						 fHistosMCSig,
						 lumiValue,
						 wantNXJets,
						 flavour,
						 isZZchannel,
						 scaleToData,
						 scaleOnlyWJets,
						 makeRatio,
						 isSignalStackOnBkg,
						 kFactorsMC,kFactorsMCSig);
  std::cout<<"Set output dir"<<std::endl;
  plotter->setOutDir(outputDir);
  plotter->setDebug(false);

  //colors are assigned in the same order of mcLabels
    // For ZZ
  ////// {DYJetsToLL_HT-200to400,DYJetsToLL_HT-200to400,DYJetsToLL_HT-600toInf}
  std::vector<int> fColorsMC;
	fColorsMC.push_back(1);
	fColorsMC.push_back(3);
	fColorsMC.push_back(7);
	fColorsMC.push_back(9);
	fColorsMC.push_back(4);
	fColorsMC.push_back(5);
	fColorsMC.push_back(6);
	fColorsMC.push_back(kMagenta+3);
//	fColorsMC.push_back(kAzure+10);

  std::vector<int> fColorsMCSig;
  fColorsMCSig.push_back(kMagenta);
  fColorsMCSig.push_back(kMagenta);
  
  plotter->setFillColor(fColorsMC);
  plotter->setLineColor(fColorsMCSig);
	
  int numOfHistos = listOfHistos.size();
  for(int i = 0; i != numOfHistos; ++i) 
    plotter->makeStackPlots(listOfHistos.at(i));      

  printf("Plotting done\n");
    
  delete plotter;

}//end main
