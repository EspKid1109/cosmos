//
// Created by Alex Chase on 7/26/21.
//
#include <iostream>
#include <fstream>
#include <set> //Sets will hold random access values
#include <chrono> // for std::chrono functions
#include "BST.h" //BST implementation
#include "HashMap.h" //HashMap implementation
//Note add in vector library in report*****************************
using namespace std;

//This timer class will allow the project to calculate the elapsed time for the project
class Timer{//All timing is O(1)
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::steady_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> begin;

public:
    Timer() : begin(clock_t::now())
    {
    }

    void reset()
    {
        begin = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - begin).count();
    }
};

class SearchData{// All timing is O(1)
public:
    double entry;
    double totalOut; //Will hold the sum of the 100 item selections
    //maybe put in some helper functions
    SearchData(){
        this->entry = 0.0;
        this->totalOut = 0.0;
    }

    void enterE(double e){ //setter for entry
        this->entry = e;
    }
    void addT(double t){ // Add elapsed time to the total which will later be processed
        this->totalOut = t;
    }
    double returnT() const{
        return this->totalOut/100.0;
    }
};

bool checkInput(string* input){ // Timing O(1)
    if(input->size() > 6){
        return false;
    }
    //Check number is only numbers (ASCII codes 48-57) timing <= O(6)
    for(int i = 0; i < input->size(); i++){
        if( (int)(input->at(i)) < 48 || (int)(input->at(i)) > 57 || (int)(input->at(i)) == 34){
            return false;
        }
    }
    return true; //no isues with input
}


int main() {//Overall Timing O((n^2 * log n) + (n^2 * log n)) => O(n^2 * log n)
    //Holds timing data for implemented structures
    SearchData Bst;
    SearchData Hm;
    std::cout << "Hello there! Tell us what data type you need and we'll see what works faster for you!" << endl;
    string input;
    int cap =  200000; //Set  outside of capacity bounds
    int ran = 100; //number of random access points

    //select number of data points
    while(cap > 190000){
        cout << "Please input a number between 0 and 190,000 for the number of data points." << endl;
        cin >> input;
        if(checkInput(&input)){
            cap = stoi(input);
        }
        else{
            cout << "Please check what number you put in and try again." << endl;
        }
    }

    //Set number of random access points
    if(cap < ran){
        ran = cap;
    }

    //Get Input Data Type
    while(input != "string" && input != "int"){
        cout << "Please input what data type you'd like to input, type either string or int and hit enter." << endl;
        cin >> input;
    }

    cout << "You chose the data type: " << input << ". Let's run the numbers!" << endl;

    if(input == "int"){//Input integers from 0-99,999; Timing O((log n * n^2) + (log n) + (n) + (n) => O( (n^2) * log n)
        //implemented hash map
        BST<int> bst;
        HashMap<int, int> hm;
        set<int> random; //Holds random access variables

        cout << "Please give us a moment while we generate some test cases..." << endl;

        while(random.size() < ran){ //create 100 access cases, timing undefined due to random
            random.emplace(rand()%cap); //(99,999-0+1) + 0
        }

        Timer t; //Create timer and start count for input
        for(int i = 0; i < cap; i++){//Start with BST, Timing O(log cap) * O(n^2) for balancing
            bst.insert(bst.curRoot, i);
        }
        Bst.enterE(t.elapsed()); //Should be around two minutes for entry
        cout << "Entry time for implemented BST: " << Bst.entry << " seconds." << endl;

        //BST access timing
        auto it = random.begin();
        t.reset();
        while(it != random.end()){// Timing O(100) * O(log n)
            bst.getVal(bst.curRoot,*it);//Access each of the random values
            it++;
        }
        Bst.addT(t.elapsed()); //This value will be averaged for accuracy
        cout << "Average access time for implemented BST: " << Bst.returnT() << " seconds." << endl;

        //Begin with hashmap
        t.reset();
        for(int i = 0; i < cap; i++){ //Timing O(n)
            hm.insert(i,i);
        }
        Hm.enterE(t.elapsed());
        cout << "Entry time for implemented HashMap: " << Hm.entry << " seconds." << endl;

        //hashmap access timing
        it = random.begin();
        t.reset();
        while(it != random.end()){ //Timing O(n)
            hm.getVal(*it);
            it++;
        }
        Hm.addT(t.elapsed());
        cout << "Average access time for implemented HashMap: " << Hm.returnT() << " seconds." << endl;
    }

    else if(input == "string"){//Input strings from the "english3.txt" file, Timing O((n^2 * log n) + log n + n + n) => O(n log n)
        BST<string> bst;
        HashMap<string, int> hm;
        set<string> random;
        //file components
        ifstream file;
        file.open("text.txt");

        cout << "Please give us a moment while we generate some test cases..." << endl;

        while(random.size() < ran){ //create 100 access cases, Timing is undefined
            int ind = rand()%cap;//(99,999-0+1) + 0
            for(int i = 0; i < ind; i++){//get the random line from file
                getline(file, input);
            }
            getline(file, input);
            random.emplace(input);
            file.close();
            file.open("text.txt");
        }
        //Input into BST
        if(file.is_open()) {
            Timer t;
            for (int i = 0; i < cap; i++) {//Read cap number of inputs, files holds 194,433 lines, Timing(cap^2 * log cap)
                getline(file, input);
                bst.insert(bst.curRoot, input);
            }
            Bst.enterE(t.elapsed());
            cout << "Entry time for implemented BST: " << Bst.entry << " seconds." << endl;

            //BST access timing
            auto it = random.begin();
            t.reset();
            while(it != random.end()){ //Timing O(log cap)
                bst.getVal(bst.curRoot,*it);//Access each of the random values
                it++;
            }
            Bst.addT(t.elapsed()); //This value will be averaged for accuracy
            cout << "Average access time for implemented BST: " << Bst.returnT() << " seconds." << endl;
        }
        file.close();//close file to reset inputs
        file.open("text.txt");

        //Input into Hashmap
        if(file.is_open()) {
            Timer t;
            for (int i = 0; i < cap; i++) {//Read cap number of inputs, files holds 194,433 lines, Timing O(cap)
                getline(file, input);
                hm.insert(input, i);
            }
            Hm.enterE(t.elapsed());
            cout << "Entry time for implemented HashMap: " << Hm.entry << " seconds." << endl;

            //hashmap access timing
            auto it = random.begin();
            t.reset();
            while(it != random.end()){//Timing O(cap)
                //hm.getVal(*it);
                it++;
            }
            Hm.addT(t.elapsed());
            cout << "Average access time for implemented HashMap: " << Hm.returnT() << " seconds." << endl;
        }
    }

    //Display entry ranking, All the below are timing O(1)
    cout << "Rankings for structures using " << cap << " data point";
    if(cap == 1){
        cout << "." << endl;
    }
    else{
        cout << "s." << endl;
    }
    if(Bst.entry == Hm.entry){//Equal timing
        cout << "Both data structures entered their values with the same speed at "<< Bst.entry << " seconds." << endl;
    }
    else if(Bst.entry < Hm.entry){//BST is faster
        cout << "The implemented BST entered its values faster at " << Bst.entry << " seconds." << endl;
    }
    else{//HashMap is faster
        cout << "The implemented Hash Map entered its values faster at " << Hm.entry << " seconds." << endl;
    }

    //Display access ranking
    if(Bst.returnT() == Hm.returnT()){//Equal timing
        cout << "Both data structures accessed their values with the same speed at " << Bst.returnT() << " seconds on average." << endl;
    }
    else if(Bst.returnT() < Hm.returnT()){//BST is faster
        cout << "The implemented BST accessed its values faster at " << Bst.returnT() << " seconds on average." << endl;
    }
    else{//HashMap is faster
        cout << "The implemented Hash Map accessed its values faster at " << Hm.returnT() << " seconds on average." << endl;
    }
    return 0;
}
/*Website references for Main functions
 *Random number generator reference: https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
 *Iterator reference: https://thispointer.com/different-ways-to-iterate-over-a-set-in-c/
 *Timer model: https://www.learncpp.com/cpp-tutorial/timing-your-code/
 */
