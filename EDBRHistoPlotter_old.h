#include <string>
#include <vector>
#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
//#include "CMSLabels.h"
#include "TVectorD.h"
#include "TGraph.h"
#include "TMath.h"
#include "TLatex.h" 
#include "CMS_lumi.C"
 

class EDBRHistoPlotter {
public:

  EDBRHistoPlotter(std::string nameInDir,
                   std::vector<std::string> nameFileDATA,
                   std::vector<std::string> nameFileMC,
                   std::vector<std::string> nameFileMCSig,
                   double targetLumi,
                   int wantNXJets,
                   int flavour,
                   bool isZZchannel,
                   bool scaleToData,
                   bool scaleOnlyWJets,
                   bool makeRatio,
                   bool isSignalStackOnBkg,
                   std::vector<double> kFactorsMC,
                   std::vector<double> kFactorsMCSig)
  {
    std::cout << "Plotter constructor" << std::endl;
    nameInDir_      = nameInDir;
    fileNamesMC     = nameFileMC;
    fileNamesMCSig  = nameFileMCSig;
    fileNamesDATA   = nameFileDATA;
    kFactorsMC_     = kFactorsMC;
    kFactorsSig_    = kFactorsMCSig;
    targetLumi_     = targetLumi;
    wantNXJets_     = wantNXJets;
    flavour_        = flavour;
    isZZchannel_    = isZZchannel;
    scaleToData_    = scaleToData;
    scaleOnlyWJets_ = scaleOnlyWJets;
    makeRatio_      = makeRatio;
    isSignalStackOnBkg_ = isSignalStackOnBkg;
    debug_          = true;
    if (fileNamesDATA.size() != 0)
      isDataPresent_ = true;
    else
      isDataPresent_ = false;
    std::cout << "Check" << std::endl;
    EDBRColors.resize(20, kWhite);
    EDBRLineColors.resize(20, kWhite);
    std::cout << "Check" << std::endl;
    labels.resize(0);
    labelsSig.resize(0);
    std::cout << "Check" << std::endl;
    makeLabels();
    std::cout << "Check" << std::endl;
   if (fileNamesMCSig.size() != kFactorsSig_.size()) {
      cout << "======> Mismatch in size of input MC Sig arrays !!! " << fileNamesMCSig.size() << "  " << kFactorsSig_.size() << endl;
    }

    printf("Target lumi is %g fb-1\n", targetLumi);
    std::cout << "k factors for MC backgrounds are: " << std::endl;
    int myKindex = 0;
    for (std::vector<double>::iterator it = kFactorsMC_.begin(); it != kFactorsMC_.end(); ++it) {
      std::cout << *it << " for " << fileNamesMC.at(myKindex) << std::endl ;
      myKindex++;
    }
    myKindex = 0;
    for (std::vector<double>::iterator it = kFactorsSig_.begin(); it != kFactorsSig_.end(); ++it) {
      std::cout << *it << " for " << fileNamesMCSig.at(myKindex) << std::endl ;
      myKindex++;
    }

    std::cout << std::endl;
  }//end constructor

  virtual ~EDBRHistoPlotter()
  {
  }//end destructor

  /// Members
  std::vector<std::string> fileNamesMC;
  std::vector<std::string> fileNamesMCSig;
  std::vector<std::string> fileNamesDATA;
  std::vector<std::string> labels;
  std::vector<std::string> labelsSig;
  std::vector<TFile*>      filesMC;
  std::vector<TFile*>      filesMCSig;
  std::vector<TFile*>      filesDATA;
  std::vector<TH1D*>       histosMC;
  std::vector<TH1D*>       histosMCSig;
  std::vector<TH1D*>       histosMCSigOrig;
  std::vector<TH1D*>       histosDATA;
  std::vector<int>         EDBRColors;
  std::vector<int>         EDBRLineColors;
  std::vector<double>      kFactorsMC_;
  std::vector<double>      kFactorsSig_;

  std::string nameInDir_;
  std::string nameOutDir_;
  double dataIntegral_;
  double targetLumi_;
  int    wantNXJets_;
  int    flavour_;
  bool   isZZchannel_;
  bool   scaleToData_;
  bool   scaleOnlyWJets_;
  bool   makeRatio_;
  bool   isSignalStackOnBkg_;
  bool   isDataPresent_;
  bool   debug_;

  /// Functions
  void cleanupMC();
  void cleanupMCSig();
  void cleanupDATA();
  void makeLabels();
  void makeStackPlots(std::string histoName);
  void setOutDir(std::string outDirNew);

  /// set debug mode
  void setDebug(bool debug)
  {
    debug_ = debug;
  }

  /// get reasonable colors for stacks.
  int getFillColor(int index)
  {
    if (index < 20)return EDBRColors[index];
    return kWhite;
  }

  /// set reasonable colors for stacks.
  void setFillColor(std::vector<int> colorList)
  {
//    unsigned int ind = 0;
	unsigned int ind = 0;
    while (ind < 20 && ind < colorList.size()) {
      EDBRColors.at(ind) = colorList.at(ind);
      ind++;
    }
  }

  /// get reasonable colors for stacks.
  int getLineColor(int index)
  {
    if (index < 20)return EDBRLineColors[index];
    return kWhite;
  }

  /// set reasonable colors for stacks.
  void setLineColor(std::vector<int> colorList)
  {
    unsigned int ind = 0;
    while (ind < 20 && ind < colorList.size()) {
      EDBRLineColors.at(ind) = colorList.at(ind);
      ind++;
    }
  }

};

void EDBRHistoPlotter::cleanupMC()
{
  for (size_t i = 0; i != filesMC.size(); ++i) {
    filesMC.at(i)->Close();
  }
  filesMC.clear();

  for (size_t i = 0; i != histosMC.size(); ++i) {
    histosMC.at(i)->Delete();
  }
  histosMC.clear();
}

void EDBRHistoPlotter::cleanupMCSig()
{
  for (size_t i = 0; i != filesMCSig.size(); ++i) {
    filesMCSig.at(i)->Close();
  }
  filesMCSig.clear();

  for (size_t i = 0; i != histosMCSig.size(); ++i) {
    histosMCSig.at(i)->Delete();
    histosMCSigOrig.at(i)->Delete();
  }
  histosMCSig.clear();
  histosMCSigOrig.clear();
}

void EDBRHistoPlotter::cleanupDATA()
{
  for (size_t i = 0; i != filesDATA.size(); ++i) {
    filesDATA.at(i)->Close();
  }
  filesDATA.clear();

  for (size_t i = 0; i != histosDATA.size(); ++i) {
    histosDATA.at(i)->Delete();
  }
  histosDATA.clear();
}

void EDBRHistoPlotter::makeLabels()
{
  int ii=fileNamesMC.size(); 	std::cout<<"number of MC samples: "<<ii<<endl;
  for (size_t i = 0; i != fileNamesMC.size(); i++) {
    TString s1 = fileNamesMC.at(i);
    TString s2 = "_.";
    TObjArray* tokens = s1.Tokenize(s2);
    std::string aLabel  = ((TObjString*)(tokens->At(1)))->String().Data();
    std::string aLabel2 = ((TObjString*)(tokens->At(2)))->String().Data();
    labels.push_back(aLabel);
//    labels.push_back(aLabel + aLabel2);
  }
  std::cout << "Labels MC done" << std::endl;

  for (size_t i = 0; i != fileNamesMCSig.size(); i++) {
//cout<<endl<<endl<<"!!!signal is in!!!"<<endl<<endl;
  	TString s1 = fileNamesMCSig.at(i);
    TString s2 = "_.";
    TObjArray* tokens = s1.Tokenize(s2);

    std::string aLabelType = ((TObjString*)(tokens->At(1)))->String().Data();

    std::string aLabelCoupling = ((TObjString*)(tokens->At(2)))->String().Data();

  //  std::string aLabelMass = ((TObjString*)(tokens->At(3)))->String().Data();
    //  std::cout << "Right3?" << std::endl;

    std::cout << s1.Data();

    std::string aLabel = aLabelType + aLabelCoupling;

    labelsSig.push_back(aLabel);

  }
  std::cout << "Labels MC signal done" << std::endl;

}

///set output directories for plots.
void EDBRHistoPlotter::setOutDir(std::string outDirNew)
{
  char buffer[256];
  nameOutDir_ = outDirNew;

  sprintf(buffer, "%s/pdf", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);

  sprintf(buffer, "%s/root", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);

  sprintf(buffer, "%s/png", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);
}

void EDBRHistoPlotter::makeStackPlots(std::string histoName)
{

  cleanupMC();
  cleanupMCSig();
  cleanupDATA();

  //printf("Making histo %s\n",histoName.c_str());
  std::cout << "\rMaking histo " << histoName.c_str() << std::endl;

  TCanvas* cv = new TCanvas(("cv_" + histoName).c_str(), ("cv_" + histoName).c_str(), 600, 600);

  //create 3 pads in the canvas
  TPad* fPads1 = NULL;
  TPad* fPads2 = NULL;
//  TPad* fPads3 = NULL;

  if (makeRatio_ && isDataPresent_) {
    fPads1 = new TPad("pad1", "", 0.00, 0.20, 0.99, 0.99);
    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.20);
    //fPads2 = new TPad("pad2", "", 0.00, 0.20, 0.99, 0.40);
    //fPads3 = new TPad("pad3", "", 0.00, 0.00, 0.99, 0.20);
    fPads1->SetFillColor(0);
    fPads1->SetLineColor(0);
    fPads2->SetFillColor(0);
    fPads2->SetLineColor(0);
      fPads1->SetBottomMargin(0);
      fPads2->SetTopMargin(0);
      fPads2->SetBottomMargin(0.3);

    //fPads3->SetFillColor(0);
    //fPads3->SetLineColor(0);
    fPads1->Draw();
    fPads2->Draw();
    //fPads3->Draw();
  }


  //============ Data vs MC plots ==============

  if (makeRatio_ && isDataPresent_) {
    fPads1->cd();
  }
 // fPads1->cd();
  ///--------------------
  /// Make the DATA stack
  ///--------------------

  TH1D* sumDATA = NULL;

  for (size_t i = 0; i != fileNamesDATA.size(); ++i) {
    filesDATA.push_back(TFile::Open((nameInDir_ +
                                     fileNamesDATA.at(i)).c_str()));
  }

  for (size_t i = 0; i != filesDATA.size(); ++i) {
    TH1D* histo = (TH1D*)(filesDATA.at(i)->Get(histoName.c_str())->Clone("clone"));
    histo->SetDirectory(0);
    histosDATA.push_back(histo);
  }

  if (histosDATA.size() != 0) {
    sumDATA = (TH1D*)(histosDATA.at(0)->Clone("masterDATA"));
    sumDATA->Reset();
    sumDATA->SetDirectory(0);
  }

  for (size_t i = 0; i != histosDATA.size(); ++i) {
    sumDATA->Add(histosDATA.at(i));
  }

  double sumDataIntegral = 0;
  if (isDataPresent_)
    sumDataIntegral = sumDATA->Integral();

	cout<<"!!!! data integral = "<<sumDataIntegral<<endl;
  ///------------------
  /// Make the MC stack
  ///------------------

  TH1D* sumMC = NULL;
  TH1D* hdiff = NULL;
  double sumBkgAtTargetLumi = 0;

  for (size_t i = 0; i != fileNamesMC.size(); ++i) {
    filesMC.push_back(TFile::Open((nameInDir_ +
                                   fileNamesMC.at(i)).c_str()));
  }

Double_t MC_inte;

  double sumBkgOther = 0.;
  double sumWJets = 0.;
  for (size_t i = 0; i != filesMC.size(); ++i) {
    TH1D* histo = (TH1D*)(filesMC.at(i)->Get(histoName.c_str())->Clone(labels.at(i).c_str()));
    histo->Scale(kFactorsMC_.at(i));

    sumBkgAtTargetLumi += (histo->Integral() * targetLumi_);


    TString filename = filesMC.at(i)->GetName();
    if (filename.Contains("WJets")) sumWJets += (histo->Integral() * targetLumi_);
    else sumBkgOther += (histo->Integral() * targetLumi_);
  }
   double WJetsScaleFactor = 1.;
  if (scaleOnlyWJets_) {
    WJetsScaleFactor = (sumDataIntegral - sumBkgOther) / sumWJets;
    cout << "WJetsScaleFactor " << WJetsScaleFactor << endl;
  }
 double MC_inte_all=0;

  for (size_t i = 0; i != filesMC.size(); ++i) {
    TH1D* histo = (TH1D*)(filesMC.at(i)->Get(histoName.c_str())->Clone(labels.at(i).c_str()));
    histo->SetDirectory(0);
//
  MC_inte = histo->Integral();  
  if(i==5)  cout<<"background !!!!!!!"<<MC_inte*targetLumi_*kfactor <<endl;
  else cout<<"background !!!!!!!"<<MC_inte*targetLumi_ <<endl;

  if(i==5) MC_inte_all = MC_inte_all + MC_inte*targetLumi_*kfactor ;
  else  MC_inte_all = MC_inte_all + MC_inte*targetLumi_ ;
//  cout<<"targetlumi = "<<targetLumi_<<endl;
  cout<<"!!!!! MC inte all ="<<MC_inte_all<<endl<<endl;
//
     histo->SetFillColor(getFillColor(i));
     histo->SetLineColor(getFillColor(i));

    TString filename = filesMC.at(i)->GetName();
    histo->Scale(kFactorsMC_.at(i));
    if (filename.Contains("WJets"))histo->Scale(WJetsScaleFactor);
    histosMC.push_back(histo);
  }



 
  if (histosMC.size() != 0) {
    sumMC = (TH1D*)(histosMC.at(0)->Clone("masterMC"));
    sumMC->Reset();
    sumMC->SetDirectory(0);
    hdiff = (TH1D*)(histosMC.at(0)->Clone("masterMC"));
    hdiff->Reset();
    hdiff->SetDirectory(0);
  }

  /// Do we normalize to data or to lumi?
  /// NOTICE THAT THIS DEPENDS ON THE HISTOGRAMS HAVING BEING
  /// CORRECTLY FILLED WITH PUweight*LumiWeight*GenWeight
  for (size_t is = 0; is != histosMC.size(); is++) {
    if (scaleToData_ && isDataPresent_) {
      histosMC.at(is)->Scale(targetLumi_ *sumDataIntegral / sumBkgAtTargetLumi);
    } else {
		if(is == 5) histosMC.at(is)->Scale(targetLumi_*kfactor);
      	else histosMC.at(is)->Scale(targetLumi_);
    }
  }

  THStack* hs = new THStack("hs", "");
//hs->GetYaxis()->SetRangeUser(1,100);
  // Make a histogram just for the sum
  for (size_t i = 0; i != histosMC.size(); ++i) {
    histosMC.at(i)->SetFillColor(getFillColor(i));
    sumMC->Add(histosMC.at(i));

    hs->Add(histosMC.at(i));
  }




  sumMC->SetFillStyle(0);
//  sumMC->SetLineColor(kBlack);
//  sumMC->SetLineColor(0);
  sumMC->SetLineWidth(2);

  if (scaleToData_ && isDataPresent_) {
    std::cout << "===> Residual DATA/MC Scale Factor is: " << sumDataIntegral / sumBkgAtTargetLumi << std::endl;
  }

  ///-------------------------------
  /// Add the MC signal to the stack
  ///-------------------------------

Double_t num_inte1, num_inte2;	

  for (size_t i = 0; i != fileNamesMCSig.size(); ++i) {
    filesMCSig.push_back(TFile::Open((nameInDir_ +
                                      fileNamesMCSig.at(i)).c_str()));
  
	}

  for (size_t i = 0; i != filesMCSig.size(); ++i) {


    TH1D* histo = (TH1D*)(filesMCSig.at(i)->Get(histoName.c_str())->Clone(labelsSig.at(i).c_str()));
    TH1D* histoOrig = (TH1D*)(filesMCSig.at(i)->Get(histoName.c_str())->Clone(labelsSig.at(i).c_str()));
    histo->SetDirectory(0);
    histo->SetLineColor(2);
    histo->SetFillColor(2);
// the num_inte and num_inte2 are not scaled. should not believe this!
//num_inte2 = histo->Integral(); cout<<"num inte2 !!!!!!!!"<<num_inte2<<endl;

num_inte1 = histoOrig->Integral();

    histoOrig->SetDirectory(0);
     histoOrig->SetLineColor(getLineColor(i));
     histoOrig->SetFillColor(getLineColor(i));	

    if (i % 2 == 0)histoOrig->SetFillStyle(3004);
    else histoOrig->SetFillStyle(3005);
    //histo->Scale(kFactor_); //============= SCALE FACTORS FOR SIGNAL? ==== FIXME

     histosMCSig.push_back(histo);
     histosMCSigOrig.push_back(histoOrig);
  }

  //scale the MC signal histogram
  if (histosMCSig.size() != kFactorsSig_.size()) cout << "+++++++++++++++++ Mismatch in size of input MC Sig arrays !!!" << endl;



  for (size_t is = 0; is != histosMCSig.size(); is++) {
 

    histosMCSig.at(is)->Scale(targetLumi_ * kFactorsSig_.at(is));
    histosMCSigOrig.at(is)->Scale(targetLumi_ * kFactorsSig_.at(is));

	num_inte2 = num_inte1*targetLumi_ * kFactorsSig_.at(is);
	cout<<"!!! scaled integraled signal = "<<num_inte2<<endl;
	cout<<"!!! scale of signal = "<<targetLumi_ * kFactorsSig_.at(is)<<endl;

    hs->Add(histosMCSig.at(is));
    sumMC->Add(histosMCSig.at(is)); 
    //add the signal to the total background
    // histosMCSig.at(is)->Add(sumMC);
  }

  ///-----------------------------------
  /// Draw both MC and DATA in the stack
  ///-----------------------------------

  hs->Draw("HIST");
 // hs->GetXaxis()->SetTitle(histoName.c_str());
  hs->GetYaxis()->SetTitle("Events/bin");//40.24pb-1");
  hs->GetYaxis()->SetTitleOffset(1.15);
//  hs->GetYaxis()->CenterTitle();
//  hs->GetYaxis()->SetRangeUser(1,100);
  
  double maximumMC = 1.4 * sumMC->GetMaximum();
  double maximumDATA = -100;
  if (isDataPresent_)
    maximumDATA = 1.15 * sumDATA->GetMaximum();
  double maximumForStack = -100;
  if (isDataPresent_)
    maximumForStack = (maximumMC > maximumDATA ? maximumMC : maximumDATA);
  else
    maximumForStack = maximumMC;
//  hs->SetMaximum(maximumForStack/10);
	hs->SetMaximum(maximumForStack);
// Some hacks for better aestetics
  // Extra vertical space in eta plots
//  hs->SetMinimum(10.0);
    if (isDataPresent_) {
          sumDATA->SetMarkerColor(1);
          sumDATA->SetMarkerStyle(20);
          sumDATA->Draw("SAME EP");  }

   // histosMCSig.at(0)->Draw("SAME HIST");
      
  // For the legend, we have to tokenize the name "histos_XXX.root"
  TLegend* leg = new TLegend(0.54, 0.7, 0.88, 0.88);
  leg->SetMargin(0.4);
  if (isDataPresent_)
    leg->AddEntry(sumDATA, "Data", "ep");
  for (size_t i = 0; i != histosMC.size(); ++i)
	{
/*		if(i==0 || i==1 ) continue;
		if(i==2) {leg->AddEntry(histosMC.at(i), "Z and dibosons", "f"); continue; }
		
		if(i==3 || i==4 || i==5) continue;
		if(i==6) {leg->AddEntry(histosMC.at(i), "Top", "f"); continue; }
//		if(i==6) {leg->AddEntry(histosMC.at(i), "Fake photon", "f"); continue; }
		if(i==7) {leg->AddEntry(histosMC.at(i), "QCD", "f"); continue;}
	leg->AddEntry(histosMC.at(i), labels.at(i).c_str(), "f"); 
*/
/*
//		if(i==0) {leg->AddEntry(histosMC.at(i), "ZG", "f"); continue; }
//		if(i==1) {leg->AddEntry(histosMC.at(i), "ZJets", "f"); continue; }
		if(i==0 ) continue;
//		if(i==2) {leg->AddEntry(histosMC.at(i), "VV", "f"); continue; }
		if(i==1) {leg->AddEntry(histosMC.at(i), "Z and dibosons", "f"); continue; }
//		if(i==3 || i==4 ) continue;
		if(i==2) continue;
//		if(i==3) {leg->AddEntry(histosMC.at(i), "ST", "f"); continue; }
//		if(i==4) {leg->AddEntry(histosMC.at(i), "TTG", "f"); continue; }
//		if(i==5) {leg->AddEntry(histosMC.at(i), "TTJets", "f"); continue; }
//		if(i==6) {leg->AddEntry(histosMC.at(i), "TTbar", "f"); continue; }
		if(i==3) {leg->AddEntry(histosMC.at(i), "Top", "f"); continue; }
//		if(i==4) {leg->AddEntry(histosMC.at(i), "WJets", "f"); continue; }
//		if(i==4 || i==5) continue;
//		if(i==6) {leg->AddEntry(histosMC.at(i), "Fake Photon", "f"); continue; }
		if(i==4) {leg->AddEntry(histosMC.at(i), "WG", "f"); continue; }
		if(i==5 || i==6) continue;
		if(i==7) {leg->AddEntry(histosMC.at(i), "Fake Photon", "f"); continue; }
		if(i==8) {leg->AddEntry(histosMC.at(i), "TTJets", "f"); continue; }
		if(i==9) {leg->AddEntry(histosMC.at(i), "ZJets", "f"); continue; }
*/
	if(i==0) {leg->AddEntry(histosMC.at(i), "ST_s", "f"); continue; }
	if(i==1) {leg->AddEntry(histosMC.at(i), "TTG_s", "f"); continue; }
	if(i==2) {leg->AddEntry(histosMC.at(i), "VV_s", "f"); continue; }
	if(i==3) {leg->AddEntry(histosMC.at(i), "ZG_s", "f"); continue; }
	if(i==4) {leg->AddEntry(histosMC.at(i), "WJets_s", "f"); continue; }
	if(i==5) {leg->AddEntry(histosMC.at(i), "ZJets_s", "f"); continue; }
//	if(i==4) {leg->AddEntry(histosMC.at(i), "Fake photon", "f"); continue; }
	if(i==6) {leg->AddEntry(histosMC.at(i), "TTJets_s", "f"); continue; }
	if(i==7) {leg->AddEntry(histosMC.at(i), "WG_s", "f"); continue; }
	}
 
  if (histosMCSig.size() > 0) {
    char rescalingLabel[64];
    for (size_t i = 0; i != histosMCSig.size(); ++i) {
      sprintf(rescalingLabel, " (x%g)", kFactorsSig_.at(i));
      std::string rescalingStr(rescalingLabel);
      if (kFactorsSig_.at(i) != 2.0){
        if(i==0) leg->AddEntry(histosMCSig.at(i), "EWK_WA+2Jets", "lf");
	}
      else leg->AddEntry(histosMCSig.at(i), (labelsSig.at(i)).c_str(), "lf");
    }
  }
 

  leg->SetFillColor(kWhite);
  leg->Draw();

  // Nice labels
 // TMathText* l = makeCMSPreliminaryTop(13, 0.50, 0.935);
  //  TMathText* l = makeCMSLumi(13,551.7,0.6,0.935);
  //l->Draw();
  //============ Data-MC/Error ==============

  TLine* lineAtZero = NULL;
  TLine* lineAtPlusTwo = NULL;
  TLine* lineAtMinusTwo = NULL;
  if (makeRatio_ && isDataPresent_) {
    fPads2->cd();

    fPads2->SetGridx();
    fPads2->SetGridy();

    double thisYmin = -5;  //-5
    double thisYmax = 5;   //5

    TVectorD nsigma_x(sumDATA->GetNbinsX());
    TVectorD nsigma_y(sumDATA->GetNbinsX());

    for (int ibin = 0; ibin != sumDATA->GetNbinsX(); ++ibin) {

      double Data = sumDATA->GetBinContent(ibin + 1);
      double Bkg = sumMC->GetBinContent(ibin + 1);
      double eData = sumDATA->GetBinError(ibin + 1);
      double eBkg = sumMC->GetBinError(ibin + 1);
      double x = sumDATA->GetBinCenter(ibin + 1);

      double diff = Data - Bkg;
      double sigma = sqrt((eData * eData) + (eBkg * eBkg));

      if (sigma != 0.0 && Data != 0.0) {
        nsigma_x[ibin] = x;
        nsigma_y[ibin] = diff / sigma;
      } else {
        nsigma_x[ibin] = +999999;
        nsigma_y[ibin] = 0;
      }
    }


    if (nsigma_x.GetNoElements() != 0) {
      TGraph *nsigmaGraph = new TGraph(nsigma_x, nsigma_y);
      nsigmaGraph->SetTitle("");
      nsigmaGraph->GetYaxis()->SetRangeUser(thisYmin, thisYmax);
//      nsigmaGraph->GetYaxis()->SetTitle("(Data-MC)/sigma_sta#sigma");
	  nsigmaGraph->GetYaxis()->SetTitle("(Data-MC)/#sigma");
      nsigmaGraph->GetYaxis()->CenterTitle();
      nsigmaGraph->GetYaxis()->SetTitleOffset(0.23); //0.43
      nsigmaGraph->GetYaxis()->SetTitleSize(0.1);    //0.1
      nsigmaGraph->GetYaxis()->SetLabelSize(0.10);  //0.06
      nsigmaGraph->GetXaxis()->SetTitle(histoName.c_str());
        nsigmaGraph->GetXaxis()->SetTitleSize(0.2);  //0.1
      nsigmaGraph->GetXaxis()->SetLimits(sumMC->GetXaxis()->GetXmin() , sumMC->GetXaxis()->GetXmax());
      nsigmaGraph->GetXaxis()->SetRangeUser(sumMC->GetXaxis()->GetXmin() , sumMC->GetXaxis()->GetXmax());
      nsigmaGraph->GetXaxis()->SetTitleOffset(0.6); //0.9
      nsigmaGraph->GetXaxis()->SetLabelSize(0.16);  //0.08
      nsigmaGraph->SetMarkerStyle(8);
      nsigmaGraph->SetMarkerSize(1.5);  //1.5
      nsigmaGraph->Draw("ape");
    }

    fPads2->Update();

    lineAtZero = new TLine(sumMC->GetXaxis()->GetXmin(), 0, sumMC->GetXaxis()->GetXmax(), 0);
    lineAtZero->SetLineColor(2);
    lineAtZero->Draw();
    lineAtPlusTwo = new TLine(sumMC->GetXaxis()->GetXmin(), 2, sumMC->GetXaxis()->GetXmax(), 2);
    lineAtPlusTwo->SetLineColor(2);
    lineAtPlusTwo->SetLineStyle(2);
    lineAtPlusTwo->Draw();
    lineAtMinusTwo = new TLine(sumMC->GetXaxis()->GetXmin(), -2, sumMC->GetXaxis()->GetXmax(), -2);
    lineAtMinusTwo->SetLineColor(2);
    lineAtMinusTwo->SetLineStyle(2);
    lineAtMinusTwo->Draw();
  }

//  char bufferstr[20];
//  sprintf(bufferstr, "%.3f",targetLumi_);
//  CMS_lumi(fPads1,4,0, bufferstr);
//  CMS_lumi(fPads1,4,0, "2.30");
//	CMS_lumi(fPads1,4,0, "4.30");
//	CMS_lumi(fPads1,4,0, "2.60");
//	CMS_lumi(fPads1,4,0, "35.133");
//	CMS_lumi(fPads1,4,0, "4.353");
	CMS_lumi(fPads1,4,0, "35.103");
// Save the picture
  char buffer[256];
  cv->SetLogy(false);
  sprintf(buffer, "%s/png/can_%s.png", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/root/can_%s.root", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/pdf/can_%s.pdf", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  if (makeRatio_ && isDataPresent_) {
    fPads1->cd();
    fPads1->SetLogy(true);
  } else {
    cv->SetLogy(true);
    fPads1->SetLogy(true);
  }
  //-- resize y axis --
  hs->SetMaximum(10 * maximumForStack);
//	hs->SetMaximum(maximumForStack/10);

	hs->SetMinimum(0.1);
//
  cv->SetLogy(true);
  cv->Update();
  cv->Modified(true);
  cv->Draw();
  sprintf(buffer, "%s/png/LOG_can_%s.png", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
 // sprintf(buffer, "%s/root/LOG_can_%s.root", nameOutDir_.c_str(), histoName.c_str());
 // cv->SaveAs(buffer);
  sprintf(buffer, "%s/pdf/LOG_can_%s.pdf", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);


double significance= num_inte2 / sqrt(MC_inte_all);
double tttt = sqrt(MC_inte_all);
cout<<"signal inte = "<<num_inte2<<endl;
cout<<" root square of MC_inte_all = " << tttt <<endl;
cout<< "significance = "<<significance<<endl;

 }



