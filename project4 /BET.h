#ifndef BET_H
#define BET_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class BET
	{ 	
		private:
  			struct BinaryNode
			{
				std::string element;
				BinaryNode *left;
	        	BinaryNode *right;
		
			BinaryNode(const std:: string &theElement, BinaryNode *lt, BinaryNode *rt)
			: element{theElement}, left{lt}, right{rt} {}
	        BinaryNode(string  && theElement, BinaryNode *lt, BinaryNode *rt)
			: element{std::move(theElement)}, left{lt}, right{rt} {}
		 };
	

	public:
		BET(); //default zero parameter constructor
		BET(const string  postfix); //one parameter constructor 
		BET(const BET&); //copy constructor
		~BET(); //destructor

		bool buildFromPostfix(const string  postfix);
		const BET & operator= (const BET &);
		void printInfixExpression();
		void printPostfixExpression();
	 	size_t size();
		size_t leaf_nodes();
		bool empty();
		

	//all private mem func must be implemeted
	private:

		void printInfixExpression(BinaryNode *n);
		void makeEmpty(BinaryNode* &t);
		BinaryNode * clone(BinaryNode *t) const;
		void printPostfixExpression(BinaryNode *n);
		size_t size(BinaryNode *t);
		size_t leaf_nodes(BinaryNode *t);
		//helper function 
		//bool needsParentheses(const string& left, const string& current, const string& right);
		BinaryNode * root;
	};
	
#endif
