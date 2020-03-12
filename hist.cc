int hist(){
	int nbin=10;
	float purewgt,scale;
	int nVert;
	TH1F *h_wz=new TH1F("","",nbin,0,50);
	TH1F *h_wz_w=new TH1F("","",nbin,0,50);

	TH1F *h_zh=new TH1F("","",nbin,0,50);
	TH1F *h_zh_w=new TH1F("","",nbin,0,50);
	
	TH1F *h_other=new TH1F("","",nbin,0,50);
	TH1F *h_other_w=new TH1F("","",nbin,0,50);

	TH1F *h_data=new TH1F("","",nbin,0,50);

	TChain *wz=new TChain("result");
	TChain *wh=new TChain("result");
	TChain *zh=new TChain("result");
	TChain *other=new TChain("result");
	TChain *data=new TChain("result");

	wz->SetBranchAddress("purewgt",&purewgt);
        wz->SetBranchAddress("nVert",&nVert);
	wz->SetBranchAddress("scale",&scale);

	zh->SetBranchAddress("purewgt",&purewgt);
        zh->SetBranchAddress("nVert",&nVert);
        zh->SetBranchAddress("scale",&scale);

	other->SetBranchAddress("purewgt",&purewgt);
        other->SetBranchAddress("nVert",&nVert);
        other->SetBranchAddress("scale",&scale);

	data->SetBranchAddress("nVert",&nVert);

	wz->Add("./wz_result.root");
	zh->Add("./zh_result.root");
	other->Add("./other_result.root");
	
	data->Add("./data_result.root");

	for(int i=0;i<data->GetEntries();i++){
		data->GetEntry(i);
		h_data->Fill(nVert);
	}
	for(int i=0;i<wz->GetEntries();i++){
		wz->GetEntry(i);
		h_wz->Fill(nVert,scale*59.7);
		h_wz_w->Fill(nVert,scale*59.7*purewgt);
	}

	for(int i=0;i<zh->GetEntries();i++){
                zh->GetEntry(i);
                h_zh->Fill(nVert,scale*59.7);
                h_zh_w->Fill(nVert,scale*59.7*purewgt);
        }


	for(int i=0;i<other->GetEntries();i++){
		other->GetEntry(i);
		h_other->Fill(nVert,scale*59.7);
                h_other_w->Fill(nVert,scale*59.7*purewgt);

	}
	THStack *hs=new THStack("",";N_{vertex};");
	THStack *hs_w=new THStack("",";N_{vertex};");
	
	h_zh->SetFillColor(kViolet+4);
	h_zh->SetLineColor(kViolet+4);
        h_zh_w->SetFillColor(kViolet+4);
	h_zh_w->SetLineColor(kViolet+4);


	h_wz->SetFillColor(kBlue);
	h_wz->SetLineColor(kBlue);
	h_wz_w->SetFillColor(kBlue);
	h_wz_w->SetLineColor(kBlue);
	
	h_other->SetFillColor(kGray);
	h_other->SetLineColor(kGray);
	h_other_w->SetFillColor(kGray);
	h_other_w->SetLineColor(kGray);

	

	hs->Add(h_wz);
	hs->Add(h_zh);
	hs->Add(h_other);
	
	hs_w->Add(h_wz_w);
	hs_w->Add(h_zh_w);
	hs_w->Add(h_other_w);

	h_data->SetMarkerStyle(8);
	h_data->SetMarkerColor(1);

	TLegend *l=new TLegend(0.7,0.7,0.9,0.9);
	l->AddEntry(h_data,"data");
	l->AddEntry(h_wz,"WZ");
	l->AddEntry(h_zh,"ZH");
	l->AddEntry(h_other,"other");
	

	TCanvas *c1=new TCanvas("c1","c1",1920,1080);

	hs->Draw("hist");
	h_data->Draw("ex0 same");
	l->Draw();
	TCanvas *c2=new TCanvas("c2","c2",1920,1080);

	hs_w->Draw("hist");
	h_data->Draw("ex0 same");
	l->Draw();

	return 0;
}
