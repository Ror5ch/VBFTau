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

    int passingMinimalSel = tree->Draw("passMinimalSel", "passMinimalSel>0", "goff");
    int matchedTaus = tree->Draw("matchedTaus", "matchedTaus>0", "goff");
    int matchedJets = tree->Draw("matchedJets", "matchedJets>0", "goff");
    int matchedBoth = tree->Draw("matchedBoth", "matchedBoth>0", "goff");
    int passOldTrig = tree->Draw("passOldTrig", "passOldTrig>0", "goff");
    int passNewTrig = tree->Draw("passNewTrig", "passNewTrig>0", "goff");
    int passMinSelAndOldTrig = tree->Draw("passMinSelAndOldTrig", "passMinSelAndOldTrig>0", "goff");
    int passMinSelOldTrigAndMatchedTaus = tree->Draw("passMinSelOldTrigAndMatchedTaus", "passMinSelOldTrigAndMatchedTaus>0", "goff");
    int passMinSelOldTrigAndMatchedJets = tree->Draw("passMinSelOldTrigAndMatchedJets", "passMinSelOldTrigAndMatchedJets>0", "goff");
    int passMinSelOldTrigAndMatchedBoth = tree->Draw("passMinSelOldTrigAndMatchedBoth", "passMinSelOldTrigAndMatchedBoth>0", "goff");
    int passMinSelAndNewTrig = tree->Draw("passMinSelAndNewTrig", "passMinSelAndNewTrig>0", "goff");
    int passMinSelNewTrigAndMatchedTaus = tree->Draw("passMinSelNewTrigAndMatchedTaus", "passMinSelNewTrigAndMatchedTaus>0", "goff");
    int passMinSelNewTrigAndMatchedJets = tree->Draw("passMinSelNewTrigAndMatchedJets", "passMinSelNewTrigAndMatchedJets>0", "goff");
    int passMinSelNewTrigAndMatchedBoth = tree->Draw("passMinSelNewTrigAndMatchedBoth", "passMinSelNewTrigAndMatchedBoth>0", "goff");

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
    std::cout << matchedTaus << std::endl;
    std::cout << matchedJets << std::endl;
    std::cout << matchedBoth << std::endl;
    std::cout << passOldTrig << std::endl;
    std::cout << passNewTrig << std::endl;
    std::cout << passMinSelAndOldTrig << std::endl;
    std::cout << passMinSelOldTrigAndMatchedTaus << std::endl;
    std::cout << passMinSelOldTrigAndMatchedJets << std::endl;
    std::cout << passMinSelOldTrigAndMatchedBoth << std::endl;
    std::cout << passMinSelAndNewTrig << std::endl;
    std::cout << passMinSelNewTrigAndMatchedTaus << std::endl;
    std::cout << passMinSelNewTrigAndMatchedJets << std::endl;
    std::cout << passMinSelNewTrigAndMatchedBoth << std::endl;

}
