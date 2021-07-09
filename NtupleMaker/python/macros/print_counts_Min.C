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

void print_counts_Min(char* filename){

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    int passingMinimalSel = tree->Draw("passBase", "passBase>0", "goff");
    int matchedTaus = tree->Draw("matchedTaus", "matchedTaus>0", "goff");
    int matchedJets = tree->Draw("matchedJets", "matchedJets>0", "goff");
    int matchedBoth = tree->Draw("matchedBoth", "matchedBoth>0", "goff");
    int passOldTrig = tree->Draw("passOldTrig", "passOldTrig>0", "goff");
    int passNewTrig = tree->Draw("passNewTrig", "passNewTrig>0", "goff");
    int passBaseAndOldTrig = tree->Draw("passBaseAndOldTrig", "passBaseAndOldTrig>0", "goff");
    int passBaseOldTrigAndMatchedTaus = tree->Draw("passBaseOldTrigAndMatchedTaus", "passBaseOldTrigAndMatchedTaus>0", "goff");
    int passBaseOldTrigAndMatchedJets = tree->Draw("passBaseOldTrigAndMatchedJets", "passBaseOldTrigAndMatchedJets>0", "goff");
    int passBaseOldTrigAndMatchedBoth = tree->Draw("passBaseOldTrigAndMatchedBoth", "passBaseOldTrigAndMatchedBoth>0", "goff");
    int passBaseAndNewTrig = tree->Draw("passBaseAndNewTrig", "passBaseAndNewTrig>0", "goff");
    int passBaseNewTrigAndMatchedTaus = tree->Draw("passBaseNewTrigAndMatchedTaus", "passBaseNewTrigAndMatchedTaus>0", "goff");
    int passBaseNewTrigAndMatchedJets = tree->Draw("passBaseNewTrigAndMatchedJets", "passBaseNewTrigAndMatchedJets>0", "goff");
    int passBaseNewTrigAndMatchedBoth = tree->Draw("passBaseNewTrigAndMatchedBoth", "passBaseNewTrigAndMatchedBoth>0", "goff");

    std::cout << "passing minimal selection: " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "passing matched taus: " << std::endl;	
    std::cout << "passing matched jets: " << std::endl;	
    std::cout << "passing matched both: " << std::endl;	
    std::cout << "------------------" << std::endl;
    std::cout << "passing old trig: " << std::endl;
    std::cout << "passing new trig: " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "passing min sel and old trig: " << std::endl;
    std::cout << "passing min sel, old trig, and matched taus: " << std::endl;
    std::cout << "passing min sel, old trig, and matched jets: " << std::endl;
    std::cout << "passing min sel, old trig, and matched both: " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "passing min sel and new trig: " << std::endl;
    std::cout << "passing min sel, new trig, and matched taus: " << std::endl;
    std::cout << "passing min sel, new trig, and matched jets: " << std::endl;
    std::cout << "passing min sel, new trig, and matched both: " << std::endl;
    
    // vertical lists are easier to copy and paste
    std::cout << passingMinimalSel << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << matchedTaus << std::endl;
    std::cout << matchedJets << std::endl;
    std::cout << matchedBoth << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << passOldTrig << std::endl;
    std::cout << passNewTrig << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << passBaseAndOldTrig << std::endl;
    std::cout << passBaseOldTrigAndMatchedTaus << std::endl;
    std::cout << passBaseOldTrigAndMatchedJets << std::endl;
    std::cout << passBaseOldTrigAndMatchedBoth << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << passBaseAndNewTrig << std::endl;
    std::cout << passBaseNewTrigAndMatchedTaus << std::endl;
    std::cout << passBaseNewTrigAndMatchedJets << std::endl;
    std::cout << passBaseNewTrigAndMatchedBoth << std::endl;

}
