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

void print_counts(char* filename){

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    int passingMinimalSel = tree->Draw("passMinimalSel", "passMinimalSel>0", "goff");

    std::cout << "passing minimal selection: " << std::endl;

    int passingSel = tree->Draw("passSel", "passSel>0", "goff");

    std::cout << "passing selection: " << std::endl;

    int passingSelAndOld = tree->Draw("passSelAndOldTrig", "passSelAndOldTrig>0", "goff");
    int passingOldJets = tree->Draw("passSelOldTrigAndMatchedJets","passSelOldTrigAndMatchedJets>0","goff");
    int passingOldTaus = tree->Draw("passSelOldTrigAndMatchedTaus","passSelOldTrigAndMatchedTaus>0","goff");
    int passingSelOldAndMatching = tree->Draw("passSelOldTrigAndMatchedBoth", "passSelOldTrigAndMatchedBoth>0", "goff");

    // print statements for old trigger
    std::cout << "passing Old trigger: " << std::endl;
    std::cout << "Old, Jets Matching: " << std::endl;
    std::cout << "Old, Taus Matching: " << std::endl;
    std::cout << "Old, Both Matching: " << std::endl;

    int passingSelAndNew = tree->Draw("passSelAndNewTrig", "passSelAndNewTrig>0", "goff");
    int passingNewJets = tree->Draw("passSelNewTrigAndMatchedJets","passSelNewTrigAndMatchedJets>0","goff");
    int passingNewTaus = tree->Draw("passSelNewTrigAndMatchedTaus","passSelNewTrigAndMatchedTaus>0","goff");
    int passingSelNewAndMatching = tree->Draw("passSelNewTrigAndMatchedBoth", "passSelNewTrigAndMatchedBoth>0", "goff");

    // print statements for new trigger

    std::cout << "passing New trigger: " << std::endl;
    std::cout << "New, Jets Matching: " << std::endl;
    std::cout << "New, Taus Matching: " << std::endl;
    std::cout << "New, Both Matching: " << std::endl;

    int jetsMatched = tree->Draw("matchedJets", "matchedJets>0", "goff");
    int tausMatched = tree->Draw("matchedTaus", "matchedTaus>0", "goff");
    int bothMatched = tree->Draw("matchedBoth", "matchedBoth>0", "goff");

    std::cout << "jetsMatched: " << std::endl;
    std::cout << "tausMatched: " << std::endl;
    std::cout << "bothMatched: " << std::endl;

    // vertical lists are easier to copy and paste
    std::cout << passingMinimalSel << std::endl;
    std::cout << passingSel << std::endl;
    std::cout << passingSelAndOld << std::endl;
    std::cout << passingOldJets << std::endl;
    std::cout << passingOldTaus << std::endl;
    std::cout << passingSelOldAndMatching << std::endl;
    std::cout << passingSelAndNew << std::endl;
    std::cout << passingNewJets << std::endl;
    std::cout << passingNewTaus << std::endl;
    std::cout << passingSelNewAndMatching << std::endl;
    std::cout << jetsMatched << std::endl;
    std::cout << tausMatched << std::endl;
    std::cout << bothMatched << std::endl;

}
