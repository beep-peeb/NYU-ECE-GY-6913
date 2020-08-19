#include<iostream>
#include<string>
#include<vector>
#include<bitset>
#include <sstream>
#include<fstream>
#include<map>
#include <math.h>

using namespace std;

int statusModify(int stringVal, string intCh){
    int nextStatus;
    if (stringVal == 3 & intCh == "1 ") {
        nextStatus = 3;
    } else if (stringVal == 3 & intCh == "0 ") {
        nextStatus = 2;
    } else if (stringVal == 2 & intCh == "1 ") {
        nextStatus = 3;
    } else if (stringVal == 2 & intCh == "0 ") {
        nextStatus = 0;
    } else if (stringVal == 0 & intCh == "1 ") {
        nextStatus = 1;
    } else if (stringVal == 0 & intCh == "0 ") {
        nextStatus = 0;
    } else if (stringVal == 1 & intCh == "1 ") {
        nextStatus = 3;
    } else if (stringVal == 1 & intCh == "0 ") {
        nextStatus = 0;
    }
    return nextStatus;
}

main()
{
    // read file
    ifstream configTxt("config.txt");
    string configString;
    vector<int> configVec;
    int m, k;
    while(getline(configTxt,configString)) {
        configVec.push_back(stoul(configString,nullptr,0));
    }
    m = configVec[0];
    k = configVec[1];
    configTxt.close();

    ifstream traceTxt("trace.txt");
    string traceString;
    string hexStr;
    vector<vector<string>> traceVec;
    while(getline(traceTxt,traceString)) {
        vector<string> vecTmp;
        hexStr = traceString.substr(0,8);
        stringstream bitstr;
        bitstr << hex << hexStr;
        unsigned n;
        bitstr >> n;
        bitset<32> b(n);
        vecTmp.push_back(b.to_string().substr(b.to_string().length()-m,m));
        vecTmp.push_back(traceString.substr(9,1)+" ");
        traceVec.push_back(vecTmp);
    }
    traceTxt.close();

    ofstream branchsimulator;
    branchsimulator.open ("trace.txt.out");
    string defaultVal = "11";
    string BHR = "";
    for (int i = 0; i < k; i++) {
        BHR+='1';
    }

    // initialize record table
    map<int, vector<int>> matrixRecord;
    vector<int> BHRvec;
    for (int i = 0; i<pow(2,k); i++) {
        BHRvec.push_back(3);
    }
    int addressNum;
    for (int j = 0; j<traceVec.size(); j++){
        addressNum = stoi(traceVec[j][0], nullptr, 2);
        matrixRecord.insert({addressNum, BHRvec});
    }

    int rowNum;
    int BHRNum;
    for (int j = 0; j<traceVec.size(); j++){
        rowNum = stoi(traceVec[j][0], nullptr, 2);
        BHRNum = stoi(BHR, nullptr, 2);
        if (matrixRecord[rowNum][BHRNum] == 3 | matrixRecord[rowNum][BHRNum] == 2) {
            branchsimulator << "1\n";
        } else {
            branchsimulator << "0\n";
        }
        matrixRecord[rowNum][BHRNum] = statusModify(matrixRecord[rowNum][BHRNum], traceVec[j][1]);
        BHR = traceVec[j][1][0] + BHR.substr(0,BHR.length()-1);
    }
    /*
    int row = pow(2,m);
    int col = pow(2,k);
    int matrixRecord[row][col];
    for (int i = 0; i < row; i++ ) {
        for (int j = 0; j < col; j++ ) {
            matrixRecord[i][j] = 3;
        }
    }
    for (int j = 0; j<traceVec.size(); j++){
        int rowNum = stoi(traceVec[j][0], nullptr, 2);
        int BHRNum = stoi(BHR, nullptr, 2);
        if (matrixRecord[rowNum][BHRNum] == 3 | matrixRecord[rowNum][BHRNum] == 2) {
            branchsimulator << "1\n";
        } else {
            branchsimulator << "0\n";
        }
        matrixRecord[rowNum][BHRNum] = statusModify(matrixRecord[rowNum][BHRNum], traceVec[j][1]);
        BHR = traceVec[j][1][0] + BHR.substr(0,BHR.length()-1);
    }
    */
    branchsimulator.close();
}
