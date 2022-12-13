#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
			// Add your code here
			size_t w[5];
			for(int i = 0; i < 5; i++){
				w[i] = 0;
			}
			
			int wPP = 4;
			int comp = 0;
			int mult = 1;
			size_t total = 0;

			int temp = k.length() - 1;
			for(int i = temp; i >= 0; i--){
				if(comp == 6){
					w[wPP] = total;
					wPP--;
					mult = 1;
					total = 0;
					comp = 0;
				}
				comp +=  1;
				total = ((letterDigitToNumber(k[i])) * mult) + total;
				mult *= 36;
			}
			if(comp != 0){
				w[wPP] = total;
			}

			HASH_INDEX_T x = 0;
			for(unsigned int j = 0; j < 5; j++){
				x = x + (w[j] * rValues[j]);
			}
			return x;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
			// Add code here or delete this helper function if you do not want it
			HASH_INDEX_T letterToInt = (int) letter;
			HASH_INDEX_T conversion;

			if(letterToInt >= 'a' && letterToInt <= 'z'){  //lower
				conversion = letterToInt - 'a';
			}
			else if(letterToInt >= 'A' && letterToInt <= 'Z'){ //upper
				conversion = letterToInt - 'A'; 
			}
			else if (letterToInt >= '0' && letterToInt <= '9'){ //int
				conversion = letter - '0' + 26;
			}
			return conversion;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
