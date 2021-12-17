#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// ex line from CSV

//fill,run,LS,avgpu^M
//7118,322079,39,57.6^M

//run, good LS start, good LS end
//325057, 42, 146 (also 149 to 180)


using namespace std;

int main() {

  // read in good csv
  string lineCSV1;
  string wordCSV1;
  vector<float> CSV1info;
  ifstream CSV1 ("GoodLStemp.csv");
  int lineCountCSV1 = 0;
  vector<float> saveCSV1;
  if (CSV1.is_open()) {
    while (getline(CSV1, lineCSV1) && lineCountCSV1 < 100) {
    stringstream sCSV1(lineCSV1);
      while (getline(sCSV1, wordCSV1,',')) {
        try { saveCSV1.push_back(stof(wordCSV1)); }
        catch (const std::invalid_argument& e) { cout << "skipping line with no data" << endl; }
      }
    }
    CSV1.close();
  }
  // parse data into more meaningful containers
  //324835, 40, 155 <---- one line of data from the CSV looks like this
  vector<float> goodRunNumbers;
  vector<float> startGoodLS;
  vector<float> endGoodLS;
  for (int iCSV1 = 0; iCSV1 < saveCSV1.size(); ++iCSV1) {
    //cout << saveCSV1[iCSV1] << endl;
    if (iCSV1%3 == 0) goodRunNumbers.push_back(saveCSV1[iCSV1]);
    if (iCSV1%3 == 1) startGoodLS.push_back(saveCSV1[iCSV1]);
    if (iCSV1%3 == 2) endGoodLS.push_back(saveCSV1[iCSV1]);
  }
  //for (int iCol1 = 0; iCol1 < endGoodLS.size(); ++iCol1) {
  //  cout << endGoodLS[iCol1] << endl;
  //}

  cout << "end first file" << endl;

  string line;
  string word;
  vector<float> row;
  ifstream myfile ("run_lumi.csv");
  int lineCount = 0;
  if (myfile.is_open()) {
    while ( getline (myfile, line) && lineCount < 10) {
      //cout << line << '\n';
      stringstream s(line);
      if (lineCount > 0)
      while ( getline(s,word,',')) {
        try { row.push_back(stof(word)); }
        catch (const std::invalid_argument& e) {
          cout << "skipping line with no data" << endl; }
      }
      lineCount += 1;
    }
    myfile.close();
  }

  double temp_sum = 0;
  if (row.size() > 0) {
    for (int i = 0; i < row.size(); ++i) {
      //i%4 == 0 is fill number
      //i%4 == 1 is run number
      //i%4 == 2 is luminosity section
      //i%4 == 3 is avg pileup
      if (i%4 == 1) {
        if (row[i] == 323755 && row[i+1] > 44 && row[i+1] < 143) {
          temp_sum += 1/row[i+2];
        }
      }
      //if (i%4 == 3) {  
      //  cout << i << '\t' << row[i-2] << '\t' << row[i-1] << '\t' << row[i] << endl;
      //}
    }
  }
  cout << temp_sum << endl;
  cout << temp_sum*53 << endl;

  //else cout << "couldn't open";
  return 0;

}
