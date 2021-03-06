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
#include "EDBRHistoMaker_a_B.h"
#include "EDBRHistoMaker_d.h"

void loopPlot_signalBCD_161210(){

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
  
  /// Luminosity value in fb^-1
//  double lumiValue = 10.0; 
//  double lumiValue = 4.353;  //12.70;  //5.80  //2.60;  // 4.30;
//	double lumiValue = 2.6;
	double lumiValue = 12.35;
/// Should we scale the histograms to data?
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
//	std::string pathToTrees="./making_root_small/outtree/";
	std::string pathToTrees="./making_root_small/outtree_161210/";
//	std::string pathToTrees="./making_root_small/outtree1/";
//	std::string pathToTrees="./making_root_small/outtree_selfD/";


//  std::string pathToTrees="./";
  std::string outputDir = "./";
  /// Setup names of data files for trees.


  const int nDATA=1;//set to zero if you don't want to plot
//  std::string dataLabels[nDATA]={"outSingleMuon_Run2016B","outSingleMuon_Run2016C","outSingleMuon_Run2016D"};
//	std::string dataLabels[nDATA]={"outSingleMuon_Run2016C_s"};
//	std::string dataLabels[nDATA]={"outSingleMuon_Run2016BCD_s"};

	std::string dataLabels[nDATA]={"outSingleMuon_Run2016BCD_s"};
  std::vector<std::string> fData;
  
  for(int ii=0;ii<nDATA;ii++){
    fData.push_back(pathToTrees+dataLabels[ii]+".root");
  }

  /// Setup names of MC files for trees.

//  const int nMC=6;
  const int nMC=8;
  //  const int nMC=1;
//	std::string mcLabels[nMC]={"ZG","ZJets","VV","ST","TTG","TTJets","WJets","WG"};
//  std::string mcLabels[nMC]={"ZG","VV","ST","TTG","WG","SingleMuon_Run2016B","SingleMuon_Run2016C","SingleMuon_Run2016D","TTJets","ZJets"};
//	std::string mcLabels[nMC]={"ST","TTG","WG","ZG","VV","TTJets","ZJets","WJets"};
//	std::string mcLabels[nMC]={"ST","TTG","TTJets","VV","ZJets","ZG","WJets","WG"};

	std::string mcLabels[nMC]={"ST_s","TTG_s","VV_s","ZG_s","WJets_s","ZJets_s","TTJets_s","WG_s"};
//	std::string mcLabels[nMC]={"ST_s","TTG_s","VV_s","ZG_s","SingleMuon_Run2016BCD_s","WG_s"};

	//	std::string mcLabels[nMC]={"ST_s","TTG_s","VV_s","ZG_s","WJets_s","WG_s"};
//	std::string mcLabels[nMC]={"ZG","ZJets","VV","ST","TTG","WG"};
	//	std::string mcLabels[nMC]={"ZG","ZJets","VV","ST","TTG","TTJets","TTbar","SingleMuon_Run2016C","WG"};

//	std::string mcLabels[nMC]={"ZA","ZJets","VV","ST","TTA","TTJets","WA"};
//    std::string mcLabels[nMC]={"WJets","Z","VV","Top","WA"};
//	std::string mcLabels[nMC]={"signal_160503"};
//outMiniAodv2_Signal_2k_PKU.root
    double kFactorsMC_array[nMC] = {1, 1, 1, 1, 1, 1, 1, 1};
//  double kFactorsMC_array[nMC] = { 1, 1, 1, 1, 1, 1};
//	double kFactorsMC_array[nMC] = {1};
  std::vector<std::string> fMC;
  for(int ii=0;ii<nMC;ii++){
    fMC.push_back(pathToTrees+"out"+mcLabels[ii]+".root");
  }

  std::vector<double> kFactorsMC;
  //std::cout << "The contents of kFactorsMC are:" << std::endl;
  for (int index=0; index<nMC; index++)
    {
      //std::cout << kFactorsMC_array[index] << std::endl;
      kFactorsMC.push_back( kFactorsMC_array[index] );	
    }

  /// Setup names of MC signal files for trees.
  const int nMCSig=1;
//WA2Jets_muon_signal_2k.root  //outWA2Jets_muon_signal_2k 
 // std::string mcLabelsSig[nMCSig]={"outsignal50k_muon_160412"};
//std::string mcLabelsSig[nMCSig]={"outWA+2Jets"}; 
//std::string mcLabelsSig[nMCSig]={"outWA2jets_160425"};
//std::string mcLabelsSig[nMCSig]={"outVBS_WGamma_signal_s"};
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
char buffer[32];
  printf("All strings set\n");


  /// ----------------------------------------------------------------
  /// This first part is the loop over trees to create histogram files 
  /// ----------------------------------------------------------------

  /// The EDBRHistoMaker, for reference
  ///
  ///EDBRHistoMaker::EDBRHistoMaker(TTree* tree, 
  ///		       bool wantElectrons,
  ///		       bool wantMuons,
  ///		       bool wantSideband,
  ///		       bool wantSignal,
  ///		       int  wantNXJets,
  ///              bool isZZchannel)

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
      EDBRHistoMaker_d* maker_data = new EDBRHistoMaker_d(treeData,
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
		
//	  if( i==5 || i==6 || i==7) 
/*		if(i==4)
  		  {          EDBRHistoMaker_a* maker_a = new EDBRHistoMaker_a(treeMC,
                                   fileMC,
                                   hisRatio,
                             wantElectrons,
                             wantMuons, 
                             wantSideband,
                             wantSignal, 
                             wantFullRange,
                             wantNXJets,
                             isZZchannel);
		maker_a->setUnitaryWeights(false);
		maker_a->Loop(buffer);

		}
    else */
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

  //  EDBRHistoMaker::EDBRHistoMaker(TTree* tree,
  //			 bool wantElectrons,
  //			 bool wantMuons,
  //			 bool wantSideband,
  //			 bool wantSignal,
  //			 int  wantNXJets,
  //			 bool isZZchannel){
    
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
      //bool isMJJhisto=(hName.find("mJJ")!=std::string::npos);
      //bool isMZZhisto=(hName.find("mZZ")!=std::string::npos);
      //if( !isMJJhisto && !isMZZhisto)continue;//skip all histos except MJJ and MZZ
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
/*
  fColorsMC.push_back(kRed+1);
  fColorsMC.push_back(kRed+1);
  fColorsMC.push_back(kRed+1);
  fColorsMC.push_back(kGreen);
  fColorsMC.push_back(kGreen);
  fColorsMC.push_back(kGreen);
  fColorsMC.push_back(kGreen);
  fColorsMC.push_back(kBlue);
  fColorsMC.push_back(kBlue);
  fColorsMC.push_back(kMagenta);
  fColorsMC.push_back(2);
  fColorsMC.push_back(2);
  fColorsMC.push_back(210);*/
/*
  fColorsMC.push_back(kMagenta);
  fColorsMC.push_back(kMagenta);
//  fColorsMC.push_back(kMagenta);
  fColorsMC.push_back(kYellow);
  fColorsMC.push_back(kYellow);
//  fColorsMC.push_back(kYellow);
//  fColorsMC.push_back(kYellow);
  fColorsMC.push_back(kBlue);
  fColorsMC.push_back(kGreen);
  fColorsMC.push_back(kMagenta);
  fColorsMC.push_back(kRed);
  fColorsMC.push_back(kYellow);
  fColorsMC.push_back(kYellow);
*/
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
