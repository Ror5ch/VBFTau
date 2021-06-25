// My first (successful) root macro, Braden Allmond, 06/23/2021
//
// to run using root do
// root -l MakeAndDraw.C
// this should draw a graph with 3 cutflows drawn ontop of each other
//
// you can also open root
// root -l
// load the macro
// .L MakeAndDraw()
// and then execute it
// .x MakeAndDraw()
//

void MakeAndDraw_RelEff(){
    TH1F* h1 = new TH1F("h1", "", 7 ,0.0, 7.0);
    //TH1F* h2 = new TH1F("h2", "", 7 ,0.0, 7.0);
    TH1F* h3 = new TH1F("h3", "", 7 ,0.0, 7.0);

    double d1[] = {1,0.27288,0.09009,0.04541,0.04119,0.04119,0.01738,0.01128};
    //double d2[] = {0.99568,0.24347,0.07901,0.04124,0.03824,0.02833,0.00798,0.00620};
    double d3[] = {0.98674,0.24298,0.08744,0.04663,0.04336,0.03370,0.01646,0.01055};

    double dd1[7];
    //double dd2[7];
    double dd3[7];

    size_t dn = sizeof(dd1) / sizeof(double);

    const char *filters[7] = {"L1", "Req. 2nd Tau", "TauID vs Jet", "TauID vs Muon", "L1HLT Tau Matching", "L1HLT Jet Matching", "HLT Jet Tau RmOvlp"};

    for (int i = 0; i < dn; i++){
	dd1[i] = d1[i+1]/d1[i];
	//dd2[i] = d2[i+1]/d2[i];
	dd3[i] = d3[i+1]/d3[i];
    }

    for (int i = 0; i < dn; i++){
	//h1->SetBinContent(i, dd1[i-1]);
	//h2->SetBinContent(i, dd2[i-1]);
	//h3->SetBinContent(i, dd3[i-1]);
	h1->Fill(filters[i],dd1[i]);
	//h2->Fill(filters[i],dd2[i]);
	h3->Fill(filters[i],dd3[i]);
    }

    TCanvas *c1 = new TCanvas("c1","",600,400);
    c1->SetLogy();
    gStyle->SetOptStat(kFALSE);

    h1->SetTitle("Trigger Filter Relative Efficiency Cutflow;; Efficiency");
    //h1->SetAxisRange(0,1.1, "Y");
    h1->GetXaxis()->SetLabelSize(0.039);

    h1->Draw("hist");
    h1->SetLineColor(1);
    //h2->SetLineStyle(2);
    //h2->SetLineColor(2);
    //h2->Draw("hist SAME");
    h3->SetLineStyle(7);
    h3->SetLineColor(9);
    h3->Draw("hist SAME");

    auto legend = new TLegend(0.1, 0.7, 0.4, 0.9);
    legend->SetHeader("Key", "C");
    legend->SetTextSize(0.035);
    legend->AddEntry(h1, "Old Trigger");
    //legend->AddEntry(h2, "New Trigger w/o Eta Fix");
    legend->AddEntry(h3, "New Trigger"); //w/ Eta Fix
    legend->Draw();

    c1->Print("cutflow_graph_RelEff_log.png", "png");
}
