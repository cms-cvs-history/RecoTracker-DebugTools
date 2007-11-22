void TracksCompare(char* newFile,char* refFile)
{
  //gROOT->ProcessLine(".x HistoCompare_Tracks.C");
 gROOT ->Reset();
 gROOT ->SetBatch();

 //========= style settings ====================
 gROOT->SetStyle("Plain");
 gStyle->SetPadGridX(kTRUE);
 gStyle->SetPadGridY(kTRUE);



 //=============================================


 delete gROOT->GetListOfFiles()->FindObject(refFile);
 delete gROOT->GetListOfFiles()->FindObject(newFile); 

 TText* te = new TText();
 TFile * sfile = new TFile(newFile);
 TFile * rfile = new TFile(refFile);


 //HistoCompare_Tracks * myPV = new HistoCompare_Tracks();

 TCanvas *canvas;

 TH1F *sh1,*rh1;
 TH1F *sh2,*rh2;
 TH1F *sh3,*rh3;
 TH1F *sh4,*rh4;
 TH1F *sh5,*rh5;
 TH1F *sh6,*rh6;

 TH1F *sc1,*rc1;
 TH1F *sc2,*rc2;
 TH1F *sc3,*rc3;

 bool hit=1;
 bool chi2=1;
 bool ctf=1;
 bool rs=0;

 //////////////////////////////////////
 /////////// CTF //////////////////////
 //////////////////////////////////////
 if (ctf){
   //===== building
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/hits_eta",rh1);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/hits_eta",sh1);
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/hits",rh2);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/hits",sh2);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/effic",rh3);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/effic",sh3);
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/efficPt",rh4);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/efficPt",sh4);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/fakerate",rh5);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/fakerate",sh5);
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/num_reco_pT",rh6);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/num_reco_pT",sh6);



   canvas = new TCanvas("Tracks1","Tracks: efficiency & fakerate",1000,1400);


   NormalizeHistograms(rh2,sh2);
   NormalizeHistograms(rh6,sh6);
   rh3->GetYaxis()->SetRangeUser(0.5,1.025);
   sh3->GetYaxis()->SetRangeUser(0.5,1.025);

   rh4->GetXaxis()->SetRangeUser(0,30);
   sh4->GetXaxis()->SetRangeUser(0,30);

   rh6->GetXaxis()->SetRangeUser(0,10);
   sh6->GetXaxis()->SetRangeUser(0,10);


   rh5->GetYaxis()->SetRangeUser(0.,0.05);
   sh5->GetYaxis()->SetRangeUser(0.,0.05);


   plotBuilding(canvas,
		sh3,rh3,sh4,rh4,
		sh5,rh5,sh6,rh6,
		sh1,rh1,sh2,rh2,
		te,"UU",-1);

   canvas->cd();
   //TPaveText* text = new TPaveText(0.25,0.72,0.75,0.77,"prova");
   //text->SetFillColor(0);
   //text->SetTextColor(1);
   //text->Draw();
   l = new TLegend(0.20,0.72,0.8,0.77);
   l->SetTextSize(0.02);
   l->SetLineColor(1);
   l->SetLineWidth(1);
   l->SetLineStyle(1);
   l->SetFillColor(0);
   l->SetBorderSize(3);
   l->AddEntry(rh1,"BJets 50-120, CMSSW_1_7_0+dummy selection","LPF");
   l->AddEntry(sh1,"TTbar,        CMSSW_1_7_0+dummy selection","LPF");
   l->Draw();
   canvas->Print("building.pdf");   
   delete l;

   //===== tuning
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/chi2",rh1);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/chi2",sh1);
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/chi2_prob",rh2);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/chi2_prob",sh2);
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/chi2mean",rh3);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/chi2mean",sh3);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/h_ptshifteta",rh4);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/h_ptshifteta",sh4);


   canvas = new TCanvas("Tracks2","Tracks: chi2 & chi2 probability",1000,1050);

   NormalizeHistograms(rh1,sh1);
   NormalizeHistograms(rh2,sh2);
   fixRangeY(rh1,sh1);
   fixRangeY(rh2,sh2);
   rh3->GetYaxis()->SetRangeUser(0,2.5);
   sh3->GetYaxis()->SetRangeUser(0,2.5);
   rh4->GetYaxis()->SetRangeUser(-1.5,1.5);
   sh4->GetYaxis()->SetRangeUser(-1.5,1.5);
     
   plotTuning(canvas,
	     sh1,rh1,sh2,rh2,
	     sh3,rh3,sh4,rh4,
	     sh4,rh4,
	     te,"UU",-1);
   
   canvas->cd();
   l = new TLegend(0.20,0.72,0.8,0.77);
   l->SetTextSize(0.02);
   l->SetLineColor(1);
   l->SetLineWidth(1);
   l->SetLineStyle(1);
   l->SetFillColor(0);
   l->SetBorderSize(3);
   l->AddEntry(rh1,"BJets 50-120, CMSSW_1_7_0+dummy selection","LPF");
   l->AddEntry(sh1,"TTbar,        CMSSW_1_7_0+dummy selection","LPF");
   l->Draw();
   canvas->Print("tuning.pdf");
   delete l;
   

   //===== pulls
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullPt",rh1);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullPt",sh1);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullQoverp",rh2);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullQoverp",sh2);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullPhi0",rh3);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullPhi0",sh3);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullTheta",rh4);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullTheta",sh4);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullD0",rh5);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullD0",sh5);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullDz",rh6);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/pullDz",sh6);


   canvas = new TCanvas("Tracks4","Tracks: pull of Pt, Qoverp and Phi",1000,1400);

   NormalizeHistograms(rh1,sh1);
   NormalizeHistograms(rh2,sh2);
   NormalizeHistograms(rh3,sh3);
   NormalizeHistograms(rh4,sh4);
   NormalizeHistograms(rh5,sh5);
   NormalizeHistograms(rh6,sh6);

   rh1->GetXaxis()->SetRangeUser(-10,10);
   sh1->GetXaxis()->SetRangeUser(-10,10);
   rh2->GetXaxis()->SetRangeUser(-10,10);
   sh2->GetXaxis()->SetRangeUser(-10,10);
   rh3->GetXaxis()->SetRangeUser(-10,10);
   sh3->GetXaxis()->SetRangeUser(-10,10);
   rh4->GetXaxis()->SetRangeUser(-10,10);
   sh4->GetXaxis()->SetRangeUser(-10,10);
   rh5->GetXaxis()->SetRangeUser(-10,10);
   sh5->GetXaxis()->SetRangeUser(-10,10);
   rh6->GetXaxis()->SetRangeUser(-10,10);
   sh6->GetXaxis()->SetRangeUser(-10,10);


   plotPulls(canvas,
	     sh1,rh1,sh2,rh2,
	     sh3,rh3,sh4,rh4,
	     sh5,rh5,sh6,rh6,
	     te,"UU",-1);

   canvas->cd();

   l = new TLegend(0.20,0.72,0.8,0.77);
   l->SetTextSize(0.02);
   l->SetLineColor(1);
   l->SetLineWidth(1);
   l->SetLineStyle(1);
   l->SetFillColor(0);
   l->SetBorderSize(3);
   l->AddEntry(rh1,"BJets 50-120, CMSSW_1_7_0+dummy selection","LPF");
   l->AddEntry(sh1,"TTbar,        CMSSW_1_7_0+dummy selection","LPF");
   l->Draw();
   canvas->Print("pulls.pdf");
   delete l;




   

   //===== resolutions vs eta
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaphi",rh1);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaphi",sh1);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmacotTheta",rh2);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmacotTheta",sh2);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmad0",rh3);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmad0",sh3);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaz0",rh4);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaz0",sh4);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmapt",rh5);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmapt",sh5);



   canvas = new TCanvas("Tracks7","Tracks: D0, Z0, Theta resolution",1000,1400);

   plotResolutions(canvas,
	     sh1,rh1,sh2,rh2,
	     sh3,rh3,sh4,rh4,
	     sh5,rh5,sh6,rh6,
	     te,"UU",-1);

   canvas->cd();

   l = new TLegend(0.20,0.42,0.8,0.47);
   l->SetTextSize(0.02);
   l->SetLineColor(1);
   l->SetLineWidth(1);
   l->SetLineStyle(1);
   l->SetFillColor(0);
   l->SetBorderSize(3);
   l->AddEntry(rh1,"BJets 50-120, CMSSW_1_7_0+dummy selection","LPF");
   l->AddEntry(sh1,"TTbar,        CMSSW_1_7_0+dummy selection","LPF");
   l->Draw();
   canvas->Print("resolutionsEta.pdf");
   delete l;

   //===== resolutions vs pt
   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaphiPt",rh1);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaphiPt",sh1);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmacotThetaPt",rh2);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmacotThetaPt",sh2);


   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmad0Pt",rh3);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmad0Pt",sh3);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaz0Pt",rh4);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaz0Pt",sh4);

   rfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaptPt",rh5);
   sfile->GetObject("DQMData/Track/cutsCKF_AssociatorByHits/sigmaptPt",sh5);


   rh1->GetXaxis()->SetRangeUser(0,30.);
   sh1->GetXaxis()->SetRangeUser(0,30.);
   rh2->GetXaxis()->SetRangeUser(0,30.);
   sh2->GetXaxis()->SetRangeUser(0,30.);
   rh3->GetXaxis()->SetRangeUser(0,30.);
   sh3->GetXaxis()->SetRangeUser(0,30.);
   rh4->GetXaxis()->SetRangeUser(0,30.);
   sh4->GetXaxis()->SetRangeUser(0,30.);
   rh5->GetXaxis()->SetRangeUser(0,30.);
   sh5->GetXaxis()->SetRangeUser(0,30.);
   rh6->GetXaxis()->SetRangeUser(0,30.);
   sh6->GetXaxis()->SetRangeUser(0,30.);


   canvas = new TCanvas("Tracks7","Tracks: D0, Z0, Theta resolution",1000,1400);

   plotResolutions(canvas,
	     sh1,rh1,sh2,rh2,
	     sh3,rh3,sh4,rh4,
	     sh5,rh5,sh6,rh6,
	     te,"UU",-1);

   canvas->cd();

   l = new TLegend(0.20,0.47,0.8,0.52);
   l->SetTextSize(0.02);
   l->SetLineColor(1);
   l->SetLineWidth(1);
   l->SetLineStyle(1);
   l->SetFillColor(0);
   l->SetBorderSize(3);
   l->AddEntry(rh1,"BJets 50-120, CMSSW_1_7_0+dummy selection","LPF");
   l->AddEntry(sh1,"TTbar,        CMSSW_1_7_0+dummy selection","LPF");
   l->Draw();
   canvas->Print("resolutionsPt.pdf");
   delete l;


}

}


void NormalizeHistograms(TH1F* h1, TH1F* h2)
{
  if (h1==0 || h2==0) return;
  float scale1 = -9999.9;
  float scale2 = -9999.9;

  if ( h1->Integral() != 0 && h2->Integral() != 0 ){
      scale1 = 1.0/(float)h1->Integral();
      scale2 = 1.0/(float)h2->Integral();
    
      //h1->Sumw2();
      //h2->Sumw2();
      h1->Scale(scale1);
      h2->Scale(scale2);
    }
}



void plotTuning(TCanvas *canvas, 
		TH1F *s1,TH1F *r1, TH1F *s2,TH1F *r2, 
		TH1F *s3,TH1F *r3, TH1F *s4,TH1F *r4,
		TH1F *s5,TH1F *r5,
		TText* te,
	       char * option, double startingY, double startingX = .1,bool fit = false){
  canvas->Divide(2,2);

  s1->SetMarkerStyle(20);
  r1->SetMarkerStyle(21);
  s1->SetMarkerColor(2);
  r1->SetMarkerColor(4);
  s1->SetMarkerSize(0.7);
  r1->SetMarkerSize(0.7);
  s1->SetLineColor(2);
  r1->SetLineColor(4);
  s1->SetLineWidth(2);
  r1->SetLineWidth(2);



  s2->SetMarkerStyle(20);
  r2->SetMarkerStyle(21);
  s2->SetMarkerColor(2);
  r2->SetMarkerColor(4);
  s2->SetMarkerSize(0.1);
  r2->SetMarkerSize(0.1);
  s2->SetLineColor(2);
  r2->SetLineColor(4);
  s2->SetLineWidth(2);
  r2->SetLineWidth(2);

  s3->SetMarkerStyle(20);
  r3->SetMarkerStyle(21);
  s3->SetMarkerColor(2);
  r3->SetMarkerColor(4);
  s3->SetMarkerSize(0.7);
  r3->SetMarkerSize(0.7);
  s3->SetLineColor(1);
  r3->SetLineColor(1);
  //r3->SetLineWidth(2);
  //s3->SetLineWidth(2);

  s4->SetMarkerStyle(20);
  r4->SetMarkerStyle(21);
  s4->SetMarkerColor(2);
  r4->SetMarkerColor(4);
  s4->SetMarkerSize(0.7);
  r4->SetMarkerSize(0.7);
  s4->SetLineColor(1);
  r4->SetLineColor(1);
  //  r4->SetLineWidth(2);
  //s4->SetLineWidth(2);


  //setStats(r1,s1, startingY, startingX, fit);
  canvas->cd(1);
  setStats(s1,r1, 0.6, 0.65, false);
  r1->Draw();
  s1->Draw("sames");

  canvas->cd(2);
  setStats(s2,r2, 0.6, 0.65, false);
  r2->Draw();
  s2->Draw("sames");

  canvas->cd(3);
  setStats(s3,r3, -1, 0.65, false);
  r3->Draw();
  s3->Draw("sames");

  canvas->cd(4);
  setStats(s4,r4, -1, 0.65, false);
  r4->Draw();
  s4->Draw("sames");

}

void plotBuilding(TCanvas *canvas, 
		  TH1F *s1,TH1F *r1, TH1F *s2,TH1F *r2, 
		  TH1F *s3,TH1F *r3, TH1F *s4,TH1F *r4,
		  TH1F *s5,TH1F *r5,TH1F *s6,TH1F *r6,
		  TText* te,
	       char * option, double startingY, double startingX = .1,bool fit = false){
  canvas->Divide(2,3);

  s1->SetMarkerStyle(20);
  r1->SetMarkerStyle(21);
  s1->SetMarkerColor(2);
  r1->SetMarkerColor(4);
  s1->SetMarkerSize(0.7);
  r1->SetMarkerSize(0.7);
  s1->SetLineColor(1);
  r1->SetLineColor(1);

  s2->SetMarkerStyle(20);
  r2->SetMarkerStyle(21);
  s2->SetMarkerColor(2);
  r2->SetMarkerColor(4);
  s2->SetMarkerSize(0.7);
  r2->SetMarkerSize(0.7);
  s2->SetLineColor(1);
  r2->SetLineColor(1);

  s3->SetMarkerStyle(20);
  r3->SetMarkerStyle(21);
  s3->SetMarkerColor(2);
  r3->SetMarkerColor(4);
  s3->SetMarkerSize(0.7);
  r3->SetMarkerSize(0.7);
  s3->SetLineColor(1);
  r3->SetLineColor(1);
  s3->SetLineWidth(1);
  r3->SetLineWidth(1);

  s4->SetMarkerStyle(20);
  r4->SetMarkerStyle(21);
  s4->SetMarkerColor(2);
  r4->SetMarkerColor(4);
  s4->SetMarkerSize(0.7);
  r4->SetMarkerSize(0.7);
  s4->SetLineColor(2);
  r4->SetLineColor(4);
  s4->SetLineWidth(2);
  r4->SetLineWidth(2);


  s5->SetMarkerStyle(20);
  r5->SetMarkerStyle(21);
  s5->SetMarkerColor(2);
  r5->SetMarkerColor(4);
  s5->SetMarkerSize(0.7);
  r5->SetMarkerSize(0.7);
  s5->SetLineColor(1);
  r5->SetLineColor(1);

  s6->SetMarkerStyle(20);
  r6->SetMarkerStyle(21);
  s6->SetMarkerColor(2);
  r6->SetMarkerColor(4);
  s6->SetMarkerSize(0.7);
  r6->SetMarkerSize(0.7);
  s6->SetLineColor(2);
  r6->SetLineColor(4);
  s6->SetLineWidth(2);
  r6->SetLineWidth(2);



  //setStats(r1,s1, startingY, startingX, fit);
  canvas->cd(1);
  setStats(s1,r1, -1, 0, false);
  r1->Draw();
  s1->Draw("sames");

  canvas->cd(2);
  setStats(s2,r2, -1, 0, false);
  r2->Draw();
  s2->Draw("sames");

  canvas->cd(3);
  setStats(r3,s3, -1, 0, false);
  r3->Draw();
  s3->Draw("sames");

  canvas->cd(4);
  setStats(s4,r4, 0.6, 0.65, false);
  r4->Draw();
  s4->Draw("sames");

  canvas->cd(5);
  setStats(r5,s5, -1, 0, false);
  r5->Draw();
  s5->Draw("sames");


  canvas->cd(6);
  setStats(s6,r6, 0.6, 0.65, false);
  r6->Draw();
  s6->Draw("sames");
}

void plotPulls(TCanvas *canvas, 
	       TH1F *s1,TH1F *r1, TH1F *s2,TH1F *r2, 
	       TH1F *s3,TH1F *r3, TH1F *s4,TH1F *r4,
	       TH1F *s5,TH1F *r5,TH1F *s6,TH1F *r6,
	       TText* te,
	       char * option, double startingY, double startingX = .1,bool fit = false){
  canvas->Divide(2,3);

  s1->SetMarkerStyle(20);
  r1->SetMarkerStyle(21);
  s1->SetMarkerColor(2);
  r1->SetMarkerColor(4);
  s1->SetMarkerSize(0.7);
  r1->SetMarkerSize(0.7);
  s1->SetLineColor(2);
  r1->SetLineColor(4);
  s1->SetLineWidth(2);
  r1->SetLineWidth(2);


  s2->SetMarkerStyle(20);
  r2->SetMarkerStyle(21);
  s2->SetMarkerColor(2);
  r2->SetMarkerColor(4);
  s2->SetMarkerSize(0.7);
  r2->SetMarkerSize(0.7);
  s2->SetLineColor(2);
  r2->SetLineColor(4);
  s2->SetLineWidth(2);
  r2->SetLineWidth(2);

  s3->SetMarkerStyle(20);
  r3->SetMarkerStyle(21);
  s3->SetMarkerColor(2);
  r3->SetMarkerColor(4);
  s3->SetMarkerSize(0.7);
  r3->SetMarkerSize(0.7);
  s3->SetLineColor(2);
  r3->SetLineColor(4);
  s3->SetLineWidth(2);
  r3->SetLineWidth(2);

  s4->SetMarkerStyle(20);
  r4->SetMarkerStyle(21);
  s4->SetMarkerColor(2);
  r4->SetMarkerColor(4);
  s4->SetMarkerSize(0.7);
  r4->SetMarkerSize(0.7);
  s4->SetLineColor(2);
  r4->SetLineColor(4);
  s4->SetLineWidth(2);
  r4->SetLineWidth(2);


  s5->SetMarkerStyle(20);
  r5->SetMarkerStyle(21);
  s5->SetMarkerColor(2);
  r5->SetMarkerColor(4);
  s5->SetMarkerSize(0.7);
  r5->SetMarkerSize(0.7);
  s5->SetLineColor(2);
  r5->SetLineColor(4);
  s5->SetLineWidth(2);
  r5->SetLineWidth(2);


  s6->SetMarkerStyle(20);
  r6->SetMarkerStyle(21);
  s6->SetMarkerColor(2);
  r6->SetMarkerColor(4);
  s6->SetMarkerSize(0.7);
  r6->SetMarkerSize(0.7);
  s6->SetLineColor(2);
  r6->SetLineColor(4);
  s6->SetLineWidth(2);
  r6->SetLineWidth(2);



  //setStats(r1,s1, startingY, startingX, fit);


  canvas->cd(1);
  setStats(s1,r1, 0.6, 0.65, true);
  r1->Draw();
  s1->Draw("sames");

  canvas->cd(2);
  setStats(s2,r2, 0.6, 0.65, true);
  r2->Draw();
  s2->Draw("sames");

  canvas->cd(3);
  setStats(s3,r3, 0.6, 0.65, true);
  r3->Draw();
  s3->Draw("sames");

  canvas->cd(4);
  setStats(s4,r4, 0.6, 0.65, true);
  r4->Draw();
  s4->Draw("sames");

  canvas->cd(5);
  setStats(s5,r5, 0.6, 0.65, true);
  r5->Draw();
  s5->Draw("sames");


  canvas->cd(6);
  setStats(s6,r6, 0.6, 0.65, true);
  r6->Draw();
  s6->Draw("sames");
}

void plotResolutions(TCanvas *canvas, 
		     TH1F *s1,TH1F *r1, TH1F *s2,TH1F *r2, 
		     TH1F *s3,TH1F *r3, TH1F *s4,TH1F *r4,
		     TH1F *s5,TH1F *r5,TH1F *s6,TH1F *r6,
		     TText* te,
		     char * option, double startingY, double startingX = .1,bool fit = false){
  canvas->Divide(2,3);

  s1->SetMarkerStyle(20);
  r1->SetMarkerStyle(21);
  s1->SetMarkerColor(2);
  r1->SetMarkerColor(4);
  s1->SetMarkerSize(0.7);
  r1->SetMarkerSize(0.7);
  s1->SetLineColor(1);
  r1->SetLineColor(1);

  s2->SetMarkerStyle(20);
  r2->SetMarkerStyle(21);
  s2->SetMarkerColor(2);
  r2->SetMarkerColor(4);
  s2->SetMarkerSize(0.7);
  r2->SetMarkerSize(0.7);
  s2->SetLineColor(1);
  r2->SetLineColor(1);

  s3->SetMarkerStyle(20);
  r3->SetMarkerStyle(21);
  s3->SetMarkerColor(2);
  r3->SetMarkerColor(4);
  s3->SetMarkerSize(0.7);
  r3->SetMarkerSize(0.7);
  s3->SetLineColor(1);
  r3->SetLineColor(1);

  s4->SetMarkerStyle(20);
  r4->SetMarkerStyle(21);
  s4->SetMarkerColor(2);
  r4->SetMarkerColor(4);
  s4->SetMarkerSize(0.7);
  r4->SetMarkerSize(0.7);
  s4->SetLineColor(1);
  r4->SetLineColor(1);


  s5->SetMarkerStyle(20);
  r5->SetMarkerStyle(21);
  s5->SetMarkerColor(2);
  r5->SetMarkerColor(4);
  s5->SetMarkerSize(0.7);
  r5->SetMarkerSize(0.7);
  s5->SetLineColor(1);
  r5->SetLineColor(1);

  s6->SetMarkerStyle(20);
  r6->SetMarkerStyle(21);
  s6->SetMarkerColor(2);
  r6->SetMarkerColor(4);
  s6->SetMarkerSize(0.7);
  r6->SetMarkerSize(0.7);
  s6->SetLineColor(1);
  r6->SetLineColor(1);
  s6->SetLineWidth(2);
  r6->SetLineWidth(2);



  //setStats(r1,s1, startingY, startingX, fit);
  canvas->cd(1);
  setStats(r1,s1, -1, 0, false);
  r1->Draw();
  s1->Draw("sames");

  canvas->cd(2);
  setStats(r2,s2, -1, 0, false);
  r2->Draw();
  s2->Draw("sames");

  canvas->cd(3);
  setStats(r3,s3, -1, 0, false);
  r3->Draw();
  s3->Draw("sames");

  canvas->cd(4);
  setStats(r4,s4, -1, 0, false);
  r4->Draw();
  s4->Draw("sames");

  canvas->cd(5);
  setStats(r5,s5, -1, 0, false);
  r5->Draw();
  s5->Draw("sames");


  //canvas->cd(6);
  //r6->Draw();
  //s6->Draw("sames");
}


void setStats(TH1* s,TH1* r, double startingY, double startingX = .1,bool fit){
  if (startingY<0){
    s->SetStats(0);
    r->SetStats(0);
  } else {
    //gStyle->SetOptStat(1001);

    if (fit){
      s->Fit("gaus");
      TF1* f1 = (TF1*) s->GetListOfFunctions()->FindObject("gaus");
      f1->SetLineColor(2);
      f1->SetLineWidth(1);
    }
    s->Draw();
    gPad->Update(); 
    TPaveStats* st1 = (TPaveStats*) s->GetListOfFunctions()->FindObject("stats");
    if (fit) {st1->SetOptFit(0010);    st1->SetOptStat(1001);}
    st1->SetX1NDC(startingX);
    st1->SetX2NDC(startingX+0.30);
    st1->SetY1NDC(startingY+0.20);
    st1->SetY2NDC(startingY+0.35);
    st1->SetTextColor(2);
    if (fit) {
      r->Fit("gaus");
      TF1* f2 = (TF1*) r->GetListOfFunctions()->FindObject("gaus");
      f2->SetLineColor(4);
      f2->SetLineWidth(1);    
    }
    r->Draw();
    gPad->Update(); 
    TPaveStats* st2 = (TPaveStats*) r->GetListOfFunctions()->FindObject("stats");
    if (fit) {st2->SetOptFit(0010);    st2->SetOptStat(1001);}
    st2->SetX1NDC(startingX);
    st2->SetX2NDC(startingX+0.30);
    st2->SetY1NDC(startingY);
    st2->SetY2NDC(startingY+0.15);
    st2->SetTextColor(4);
  }
}

void fixRangeY(TH1* r,TH1* s){
  double ymin = (r->GetBinContent(r->GetMinimumBin()) < s->GetBinContent(s->GetMinimumBin())) ? 
    r->GetBinContent(r->GetMinimumBin()) : s->GetBinContent(s->GetMinimumBin());
  double ymax = (r->GetBinContent(r->GetMaximumBin()) > s->GetBinContent(s->GetMaximumBin())) ?
    r->GetBinContent(r->GetMaximumBin()) : s->GetBinContent(s->GetMaximumBin());
  r->GetYaxis()->SetRangeUser(ymin*0.9,ymax*1.1);
  s->GetYaxis()->SetRangeUser(ymin*0.9,ymax*1.1);
}
