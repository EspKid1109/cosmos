//
// Created by Alex Chase on 7/26/21.
//
#include <vector>
using namespace std;
#ifndef DATASTRUCTURESEARCHENGINEP3_HASHMAP_H
#define DATASTRUCTURESEARCHENGINEP3_HASHMAP_H

template<typename K, typename V>
class HashMap{
private:
    struct HMNode{
        K key; //Hash key value
        V val; // Hash secondary value

        HMNode(const K &k = K(), const V &v = V()){//Create node, Timing O(1) * n values
            this->key = k;
            this->val = v;
        }
    };
    int getHash(const K &k) const{//Convert provided key to hashed key Timing O(1) * n values
        unsigned int hash = 0;

        //Convert data into a usable type for hashing
        const char* _k = reinterpret_cast<const char*>(&k);

        for(size_t i = 0; i < sizeof(K); i++){
            hash = 39 * (hash + _k[i]); //Equation for hashing (26 letters + 10 numbers + 2 for extra space = 39)
        }

        return hash % vec.size();
    }
    vector<HMNode> vec; //Holds hash nodes
    int curSize; //current number of elements

public:
    HashMap<K,V>(){//Create hashmap Timing  O(1)
        vec.resize(100000); //Set vector size to 100,000 by default
        curSize = 0; // there are zero elements starting out
    }
    void insert(const K &k, const V &v){//Insert value Timing O(1) * n values
        int ind = getHash(k); //Hash key
        vec[ind] = HMNode(k,v); //place key  val pair
        curSize++; //update number of values
    }
    bool getVal(const K &k){ //Get value  from map, Timing O(1) * v number of accesses
        int ind = getHash(k);//get hash key
        if(vec[ind].key == k){ //if found return true
            return true;
        }
        else{ //else return false
            return false;
        }
    }
};
#endif //DATASTRUCTURESEARCHENGINEP3_HASHMAP_H

/* Links to websites and example code for Hash Map
 * Template use: http://users.cis.fiu.edu/~weiss/Deltoid/vcstl/templates
 *Typename: https://en.cppreference.com/w/cpp/language/type_alias
*/