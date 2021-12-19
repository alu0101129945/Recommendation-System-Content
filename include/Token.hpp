#pragma once

#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>


/**
 * @brief      This class describes a token.
 */
class Token {

	private:
		std::string name_;				// The token name
		unsigned ammount_;				// (TF) The ammount of times that the token apears in article
		float idf_;						
		float tf_idf_; 					
		float normalizedValue_;

	public:
		// Builders & Destroyer
		Token (void);
		Token (std::string name);
		~Token (void);

		// Getters 
		std::string get_Name(void) const;
		unsigned get_Ammount (void) const;
		float get_Idf (void) const;		
		float get_Tf_Idf (void) const;
		float get_NormalizedValue (void) const;

		// Setters
		void set_Name (std::string name);
		void set_Ammount (unsigned ammount);
		void set_Idf (unsigned N, unsigned dfx);
		void set_Tf_Idf (void);
		void set_NormalizedValue (float newNormalizedValue);
		
		// Operators overload
		bool operator== (const Token& otherToken) const;
		bool operator== (const std::string& str) const;
		Token& operator= (const Token& otherToken);

		// Function
		void increase (void);
		
		// Write
		void printToken (void) const;
};