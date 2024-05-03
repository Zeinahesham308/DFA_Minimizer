#include <bits/stdc++.h>
using namespace std;
vector<set<int>> prevEQV;
vector<set<int>> currEQV;
int setNoReturner(int stateNo, const int (*DFA3Transitions)[2], int StatesCount, int input) {
    int targetState = DFA3Transitions[stateNo][input];

    // Search for the target state in the prevEQV vector of sets
    for (int i = 0; i < prevEQV.size(); ++i) {
        if (prevEQV[i].count(targetState) > 0) {
            // If found, return its set number
            return i;
        }
    }

    // If not found, return -1 indicating failure
    return -1;
}
bool equalEquivalence(const vector<set<int>>& prevEQV, const vector<set<int>>& currEQV)
{
// Check if the sizes of both vectors are equal
        if (prevEQV.size() != currEQV.size()) return false;

        // Create copies of vectors to sort
        vector<set<int>> sortedPrevEQV = prevEQV;
        vector<set<int>> sortedCurrEQV = currEQV;

        // Sort sets in both vectors
        sort(sortedPrevEQV.begin(), sortedPrevEQV.end());
        sort(sortedCurrEQV.begin(), sortedCurrEQV.end());

        // Compare sorted vectors
        return sortedPrevEQV == sortedCurrEQV;
}
void DFA_Minimizer(){
    cout<<"The language used is {0,1}, states numbering starts from q0  \n";
    int StatesCount=0;
    int FinalStatesCount=0;
    int startState;

    cout<<"How many states do we have ? :";
    cin>>StatesCount;
     cout<<"\n";

     cout<<"What is the start state number? q";
     cin>>startState;
    cout<<"\n";

    cout<<"How many final states do we have ?:";
    cin>>FinalStatesCount;
    cout<<"\n";

    cout<<"Enter the final states\n";
    map<int,bool>finalstates;


    int number;
    for(int i=0;i<FinalStatesCount;i++)
    {
        cout<<"final state no."<<i+1<<": q";
        cin>>number;
        finalstates[number]=true;
        cout<<"\n";
    }
    cout<<"***** Enter Transition table *****\n";

     int DFA3Transitions[StatesCount][2];
    for(int i=0;i<StatesCount;i++)
    {
        for(int j=0;j<2;j++)
        {
            cout<<"q"<<i<<" : ";
            cout<<"When it gets "<<j<<" it goes to q";
            cin>>DFA3Transitions[i][j];
            cout<<"\n";
        }
    }

    prevEQV.push_back(set<int>());
    prevEQV.push_back(set<int>());

    for(int i=0;i<StatesCount;i++)
    {
        if(finalstates[i]) {
            prevEQV[1].insert(i);
        }
        else {
            prevEQV[0].insert(i);
        }
    }


    while(true)
    {
        for (int i = 0; i < prevEQV.size(); i++)
        {

               currEQV.push_back(set<int>());
               currEQV.back().insert(*(prevEQV[i].begin()));
               auto tracker = currEQV[0].begin();

            for (auto j = next(prevEQV[i].begin()); j != prevEQV[i].end(); ++j)
            {

                //cout<< *j<<" ";

                for (int k = 0; k < currEQV.size(); k++)
                {
                        tracker = currEQV[k].begin();
                        if (setNoReturner(*tracker,DFA3Transitions,StatesCount,0) == setNoReturner(*j,DFA3Transitions,StatesCount,0)  &&    setNoReturner(*tracker,DFA3Transitions,StatesCount,1) == setNoReturner(*j,DFA3Transitions,StatesCount,1) )
                        {
                            currEQV[k].insert(*j);
                            break;
                        }
                        else if (k == currEQV.size() - 1)
                        {
                            currEQV.push_back(set<int>());
                            currEQV[k + 1].insert(*j);
                            break;
                        }
                }
            }
//            if (prevEQV[i].size()==1)
//            {
//                currEQV.push_back(prevEQV[i]);
//
//            }
        }
        if(equalEquivalence(prevEQV,currEQV))
        {
            break;
        }
        else
        {
            prevEQV = currEQV; // Make prevEQV equal to currEQV
            currEQV.clear();
        }
    }


cout<<"Minimzed DFA States : \n";
    int startflag;
    int finalflag;
    for(int i=0;i<prevEQV.size();i++)
    {
         startflag=0;
         finalflag=0;
        cout<<"{";

        for (auto j = prevEQV[i].begin(); j != prevEQV[i].end(); ++j) {
            if(finalstates[*j]) finalflag=1;
            if(*j == startState) startflag=1;
            cout<<'q'<< *j<<" ";
        }
        cout<<"}";
        if(startflag)cout<<"It's the start state";
        if(finalflag)cout<<"It's a final state\n";
        cout<<endl;
    }

    int zerodDestination;
    int oneDestination;


    for (int i = 0; i < prevEQV.size(); i++) {
        auto it = prevEQV[i].begin();
        zerodDestination = DFA3Transitions[*it][0];
        oneDestination = DFA3Transitions[*it][1];
       cout<<"state { ";

        for (auto element : prevEQV[i]) {
            cout<<"q" << element << " ";
        }
        cout<<"} when it gets 0 it goes to state {";
        for (int j = 0; j < prevEQV.size(); j++) {
            if (prevEQV[j].find(zerodDestination) != prevEQV[j].end()) {

                for (auto element : prevEQV[j]) {
                    cout<<"q" << element << " ";
                }
                cout << "}\n";
                break; // If found, exit inner loop
            }
        }

        cout<<"When it gets 1 it goes to state {";
        for (int j = 0; j < prevEQV.size(); j++) {
            if (prevEQV[j].find(oneDestination) != prevEQV[j].end()) {
                for (auto element : prevEQV[j]) {
                    cout<<"q" << element << " ";
                }
                cout << "}\n";
                break; // If found, exit inner loop
            }
        }
        cout<<"_____________________________________\n";
    }


}


int main() {


    cout << "Enter a dfa and I will Minimize it\n";
    DFA_Minimizer();


}

