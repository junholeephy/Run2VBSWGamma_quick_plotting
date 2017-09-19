void make_small_root_dataC()
{
	TFile *f = new TFile("/Volumes/ExHard/Run2VBSWGamma_plotting/PKUTree/outtree_170916/outSingleMuon_Run2016C.root","READ");
	TFile *fout = new TFile("outSingleMuon_Run2016C_s.root","RECREATE");
	
	TTree *t = (TTree*)f->Get("demo");
	TTree *tout = new TTree("demo","demo");		
	double jet1eta;
	double jet2eta;
	double jet1phi;
	double jet2phi;
	double Mjj;
	
	int lep;
	int nVtx;
	double mtVlepJECnew;
	double ptlep1;
	double muisolation, d0vtx, dzvtx;
	double etalep1;
	double MET_et;
	int nlooseeles;
	int nloosemus;
	double photonet;
	double photoneta;
	double drla;
	double jet1pt;
	double jet2pt;
	
	double scalef;
	double theWeight;
	double nump;
	double numm;
	int HLT_Mu3;
	int HLT_Mu2;
	int HLT_Mu1;

	int isTrue;
	int isprompt;
	double lumiWeight;
	double pileupWeight;
	double zepp;
    double photonphi;
    double MET_phi;

    double philep1;
 //   double etalep1;
	double photon_sieie[6];
	double photon_pt[6];
	char photon_pev[6];
	double photon_hoe[6];
	double photon_chiso[6];
	double photon_nhiso[6];
	double photon_phoiso[6];
	double photon_eta[6];
		

    t->SetBranchAddress("philep1",&philep1);
    t->SetBranchAddress("etalep1",&etalep1);	
    t->SetBranchAddress("photonphi",&photonphi);
	t->SetBranchAddress("MET_phi",&MET_phi);	
	t->SetBranchAddress("jet1eta",&jet1eta);
	t->SetBranchAddress("jet2eta",&jet2eta);
	t->SetBranchAddress("jet1phi",&jet1phi);
	t->SetBranchAddress("jet2phi",&jet2phi);
	t->SetBranchAddress("Mjj",&Mjj);
	t->SetBranchAddress("lep",&lep);
	t->SetBranchAddress("nVtx",&nVtx);
	t->SetBranchAddress("mtVlepJECnew",&mtVlepJECnew);
	t->SetBranchAddress("ptlep1",&ptlep1);
	t->SetBranchAddress("muisolation",&muisolation);
	    t->SetBranchAddress("d0vtx",&d0vtx);
		    t->SetBranchAddress("dzvtx",&dzvtx);
	t->SetBranchAddress("MET_et",&MET_et);
	t->SetBranchAddress("nlooseeles",&nlooseeles);
	t->SetBranchAddress("nloosemus",&nloosemus);
	t->SetBranchAddress("photonet",&photonet);
	t->SetBranchAddress("photoneta",&photoneta);
	t->SetBranchAddress("drla",&drla);
	t->SetBranchAddress("jet1pt",&jet1pt);
	t->SetBranchAddress("jet2pt",&jet2pt);
	t->SetBranchAddress("scalef",&scalef);
	t->SetBranchAddress("theWeight",&theWeight);
	t->SetBranchAddress("nump",&nump);
	t->SetBranchAddress("numm",&numm);
	t->SetBranchAddress("HLT_Mu3",&HLT_Mu3);
	t->SetBranchAddress("HLT_Mu2",&HLT_Mu2);
	t->SetBranchAddress("HLT_Mu1",&HLT_Mu1);
	t->SetBranchAddress("isTrue",&isTrue);
	t->SetBranchAddress("isprompt",&isprompt);
	t->SetBranchAddress("lumiWeight",&lumiWeight);
	t->SetBranchAddress("pileupWeight",&pileupWeight);
	t->SetBranchAddress("zepp",&zepp);
	t->SetBranchAddress("photon_sieie",&photon_sieie);
	t->SetBranchAddress("photon_pt",&photon_pt);
	t->SetBranchAddress("photon_pev",&photon_pev);
	t->SetBranchAddress("photon_hoe",&photon_hoe);
	t->SetBranchAddress("photon_chiso",&photon_chiso);
	t->SetBranchAddress("photon_nhiso",&photon_nhiso);
	t->SetBranchAddress("photon_phoiso",&photon_phoiso);
	t->SetBranchAddress("photon_eta",&photon_eta);

    tout->Branch("philep1",&philep1,"philep1/D");
   tout->Branch("etalep1",&etalep1,"etalep1/D");	
    tout->Branch("photonphi",&photonphi,"photonphi/D");
    tout->Branch("MET_phi",&MET_phi,"MET_phi/D");	
	tout->Branch("jet1eta",&jet1eta,"jet1eta/D");
	tout->Branch("jet2eta",&jet2eta,"jet2eta/D");
	tout->Branch("jet1phi",&jet1phi,"jet1phi/D");
	tout->Branch("jet2phi",&jet2phi,"jet2phi/D");
	tout->Branch("Mjj",&Mjj,"Mjj/D");
	tout->Branch("lep",&lep,"lep/I");
	tout->Branch("nVtx",&nVtx,"nVtx/I");
	tout->Branch("mtVlepJECnew",&mtVlepJECnew,"mtVlepJECnew/D");
	tout->Branch("ptlep1",&ptlep1,"ptlep1/D");
	tout->Branch("muisolation",&muisolation,"muisolation/D");
	    tout->Branch("d0vtx",&d0vtx,"d0vtx/D");
		    tout->Branch("dzvtx",&dzvtx,"dzvtx/D");
	tout->Branch("MET_et",&MET_et,"MET_et/D");
	tout->Branch("nlooseeles",&nlooseeles,"nlooseeles/I");
	tout->Branch("nloosemus",&nloosemus,"nloosemus/I");
	tout->Branch("photonet",&photonet,"photonet/D");
	tout->Branch("photoneta",&photoneta,"photoneta/D");
	tout->Branch("drla",&drla,"drla/D");
	tout->Branch("jet1pt",&jet1pt,"jet1pt/D");
	tout->Branch("jet2pt",&jet2pt,"jet2pt/D");
	tout->Branch("scalef",&scalef,"scalef/D");
	tout->Branch("theWeight",&theWeight,"theWeight/D");
	tout->Branch("nump",&nump,"nump/D");
	tout->Branch("numm",&numm,"numm/D");
	tout->Branch("HLT_Mu3",&HLT_Mu3,"HLT_Mu3/I");
	tout->Branch("HLT_Mu2",&HLT_Mu2,"HLT_Mu2/I");
	tout->Branch("HLT_Mu1",&HLT_Mu1,"HLT_Mu1/I");
	tout->Branch("isTrue",&isTrue,"isTrue/I");
	tout->Branch("isprompt",&isprompt,"isprompt/I");
	tout->Branch("lumiWeight",&lumiWeight,"lumiWeight/D");
	tout->Branch("pileupWeight",&pileupWeight,"pileupWeight/D");
	tout->Branch("zepp",&zepp,"zepp/D");
	tout->Branch("photon_sieie",&photon_sieie,"photon_sieie/D");
	tout->Branch("photon_pt",&photon_pt,"photon_pt/D");
	tout->Branch("photon_pev",&photon_pev,"photon_pev/C");
	tout->Branch("photon_hoe",&photon_hoe,"photon_hoe/D");
	tout->Branch("photon_chiso",&photon_chiso,"photon_chiso/D");
	tout->Branch("photon_nhiso",&photon_nhiso,"photon_nhiso/D");
	tout->Branch("photon_phoiso",&photon_phoiso,"photon_phoiso/D");
	tout->Branch("photon_eta",&photon_eta,"photon_eta/D");

	Long64_t nentries = t->GetEntries();
	cout<<"number of entries = "<<nentries<<endl;
	int iii=0;
	Int_t d_ii;
	Double_t perc =0;

	for(d_ii=0; d_ii<nentries; d_ii++)
	{
		if(d_ii%300000==0) {perc=double(d_ii*100/nentries);    cout<<"now looping "<<d_ii<<" th event"<<"  total event num "<<nentries <<endl;  cout<<"finished "<<perc<<"%"<<endl; }
		t->GetEntry(d_ii);
		if(lep!=13 || nlooseeles!=0 || nloosemus>=2 ) {continue;}
		tout->Fill();
		iii++;
		if(iii%100000==0) cout<<"gathered "<<iii<<"events"<<"  on "<<d_ii<<"th event"<<endl;
	}	


	tout->Write();
	f->Close();
	fout->Close();



}
