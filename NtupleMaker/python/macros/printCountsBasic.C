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

void printCountsBasic(char* filename){

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    int passingMinimalSel = tree->Draw("passBase", "passBase>0", "goff"); 
//////////
    int jetsMatched = tree->Draw("matchedJets", "matchedJets>0", "goff");
    int tausMatched = tree->Draw("matchedTaus", "matchedTaus>0", "goff");
    int bothMatched = tree->Draw("matchedBoth", "matchedBoth>0", "goff");
//////////
    int passingSel = tree->Draw("passSel", "passSel>0", "goff");
//////////
    int passingSelAndOld = tree->Draw("passSelAndOldTrig", "passSelAndOldTrig>0", "goff");
    int passingOldJets = tree->Draw("passSelOldTrigAndMatchedJets","passSelOldTrigAndMatchedJets>0","goff");
    int passingOldTaus = tree->Draw("passSelOldTrigAndMatchedTaus","passSelOldTrigAndMatchedTaus>0","goff");
    int passingSelOldAndMatching = tree->Draw("passSelOldTrigAndMatchedBoth", "passSelOldTrigAndMatchedBoth>0", "goff");
//////////
    int passingSelAndNew = tree->Draw("passSelAndNewTrig", "passSelAndNewTrig>0", "goff");
    int passingNewJets = tree->Draw("passSelNewTrigAndMatchedJets","passSelNewTrigAndMatchedJets>0","goff");
    int passingNewTaus = tree->Draw("passSelNewTrigAndMatchedTaus","passSelNewTrigAndMatchedTaus>0","goff");
    int passingSelNewAndMatching = tree->Draw("passSelNewTrigAndMatchedBoth", "passSelNewTrigAndMatchedBoth>0", "goff");
 
    std::cout << "passing minimal selection: " << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "jetsMatched: " << std::endl;
    std::cout << "tausMatched: " << std::endl;
    std::cout << "bothMatched: " << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "passing selection: " << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "passing Sel & Old trigger: " << std::endl;
    std::cout << "Sel & Old Trig, Jets Matching: " << std::endl;
    std::cout << "Sel & Old Trig, Taus Matching: " << std::endl;
    std::cout << "Sel & Old Trig, Both Matching: " << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "passing Sel & New trigger: " << std::endl;
    std::cout << "Sel & New Trig, Jets Matching: " << std::endl;
    std::cout << "Sel & New Trig, Taus Matching: " << std::endl;
    std::cout << "Sel & New Trig, Both Matching: " << std::endl;

   // vertical lists are easier to copy and paste
    std::cout << passingMinimalSel << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << jetsMatched << std::endl;
    std::cout << tausMatched << std::endl;
    std::cout << bothMatched << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << passingSel << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << passingSelAndOld << std::endl;
    std::cout << passingOldJets << std::endl;
    std::cout << passingOldTaus << std::endl;
    std::cout << passingSelOldAndMatching << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << passingSelAndNew << std::endl;
    std::cout << passingNewJets << std::endl;
    std::cout << passingNewTaus << std::endl;
    std::cout << passingSelNewAndMatching << std::endl;

}
