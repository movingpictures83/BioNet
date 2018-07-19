#pragma once
#include <iostream>       // std::cout
#include <exception>      // std::exception

namespace BioNet {
	/// Parent Exception class
	/**
		Exception class for BioNet that is used as parent class of all exceptions	
	*/
	class Exception : public std::exception
	{	
		private:
			/// Saves message of a BioNet::Exception
			std::string message;
		
		public:
			/**
				Creates BioNet::Exception and takes a message of exception as a parameter

				@param m - exception message
			*/
			Exception(const std::string &m);
		
			/**
				Returns message of BioNet::Exception

			*/
			const char * what() const throw();
			
			/**
				Destroys BioNet::Exception

			*/
			~Exception();
	};
}

