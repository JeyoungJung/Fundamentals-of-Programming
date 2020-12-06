#ifndef _HISTORY_TRANSACTION_HPP_
#define _HISTORY_TRANSACTION_HPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK
//
Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,
    unsigned int month_date,  unsigned year_date,
    bool buy_sell_trans,  unsigned int number_shares,
    double trans_amount )
{
	symbol = ticker_symbol;
	day = day_date;
	month = month_date;
	year = year_date;
	shares = number_shares;
	amount = trans_amount;
	trans_type = buy_sell_trans ? "Buy" : "Sell";
	share_balance = 0;
	acb = 0;
	acb_per_share = 0;
	cgl = 0;
	trans_id = assigned_trans_id;
	assigned_trans_id++;
	p_next = nullptr;
}

// Destructor
// TASK
//
Transaction::~Transaction()
{
}

// TASK
// Overloaded < operator.
//
bool Transaction::operator<( Transaction const &other )
{
	if (this->get_year() == other.get_year()) {
		if (this->get_month() == other.get_month()) {
			return this->get_day() < other.get_day();
		} else {
			return this->get_month() < other.get_month();
		}
	} else {
		return this->get_year() < other.get_year();
	}
}
// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK
//
History::History()
{
	// Nothing is in until inserted()
	p_head = nullptr;
}
// Destructor
// TASK
//
History::~History()
{
	Transaction *p_temp { nullptr };
	if(p_head == nullptr)
	{
		delete p_head;
	}
	while(p_head != nullptr)
	{
		p_temp = p_head;
		p_head = p_head->get_next();
		delete p_temp;
		p_temp = nullptr;
	}
}

// TASK
// read_history(...): Read the transaction history from file.
//
void History::read_history()
{

	ece150::open_file();
	for (int i = 0; i < 14; i++) {
		ece150::next_trans_entry();
	  	Transaction *transaction = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(),
													   ece150::get_trans_month(), ece150::get_trans_year(),
													   ece150::get_trans_type(), ece150::get_trans_shares(),
								 					   ece150::get_trans_amount());
	  	History::insert(transaction);
	}
	
	/*while(ece150::next_trans_entry()) {
		std :: cout << ece150::next_trans_entry();

		Transaction *transaction = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(),
			  	  	  	  	  	  	  	  	  	 														ece150::get_trans_month(), ece150::get_trans_year(),
																															 													ece150::get_trans_type(), ece150::get_trans_shares(),
								 			   																														ece150::get_trans_amount());
		History::insert(transaction);
		delete transaction;
	}*/

	ece150::close_file();
}

// insert(...): Insert transaction into linked list.
//
void History::insert(Transaction *p_new_trans)
{
	p_head = this->get_p_head();
	bool isEmpty = p_head == nullptr;
	if(isEmpty)
	{
		p_head = p_new_trans;
	}
	else
	{
		Transaction *p_temp = p_head; //yellow arrow
		while(p_temp->get_next() != nullptr)
		{
			p_temp = p_temp->get_next();
		}
		//p_temp is now pointer to the tail
		p_temp->set_next(p_new_trans);
	}
}


// TASK
// sort_by_date(): Sort the linked list by trade date.
//

void History::sort_by_date()
{
	Transaction *p_sorted = nullptr;
	Transaction *p_previous = nullptr;
	Transaction *p_insert = nullptr;	// initialize p_insert
	Transaction *p_temp = nullptr;
	
	if(p_head == nullptr)			//if p_head is empty end function
	{
		return;
	}

	if(p_head->get_next() == nullptr)  //if the linked list only consists of p_head, end function
	{
		return;
	}
	
 p_sorted = p_head;		// initialize p_sorted to p_head
	p_head = p_head->get_next();
	p_sorted->set_next(nullptr);
	
	while(p_head != nullptr)
	{
			p_temp = p_head;
			p_head = p_head->get_next();
			p_temp->set_next(nullptr);

		if ( *p_temp < *p_sorted )
		{
			// case 1a : Transaction that p_temp is pointing to is earlier than p_sorted Transaction
			p_temp->set_next(p_sorted);		// p_temp ----> p_sorted
			//
			p_sorted = p_temp;
		}
		else if ( !(*p_temp < *p_sorted) && !(*p_sorted < *p_temp))
		{
			// case 1b : same date
			int temp_trans_id = p_temp->get_trans_id();
			int sorted_trans_id = p_sorted->get_trans_id();
			if( sorted_trans_id > temp_trans_id )
			{
				// temp_trans_id < sorted_trans_id, same thing as case 1a
				p_temp->set_next(p_sorted);
				p_sorted = p_temp;
			}
		}
		else
		{
			p_insert = p_sorted;
			while(p_insert->get_next() != nullptr && *p_insert->get_next() < *p_temp )
			{
				p_insert = p_insert->get_next();
			}
			p_temp->set_next(p_insert->get_next());		// linking p_temp to the next node
			p_insert->set_next(p_temp);					// linking p_temp with p_insert*/
		}
	}
	p_head = p_sorted;
}


// TASK
// update_acb_cgl(): Updates the ACB and CGL values.
//

void History::update_acb_cgl()
{	
//acb, acb per share, share balance, cgl
	Transaction *p_temp = p_head;
	bool trans_type;
	double acb = 0.0;
	double amount = 0.0;
	double acb_per_share = 0;
	double cgl = 0;
	int share_balance = 0;
	int shares = 0;
	
	while(p_temp != nullptr)
	{
		trans_type = p_temp->get_trans_type();
		amount = p_temp->get_amount();
		shares = p_temp->get_shares();
		if(trans_type)
		{
			acb += amount;
			share_balance += shares;
			cgl = 0;
		}
		else
		{
			acb -= (shares*acb_per_share);
			share_balance -= shares;
			cgl = amount-(shares*acb_per_share);
		}
		acb_per_share = acb/share_balance;
		p_temp->set_acb(acb);
		p_temp->set_share_balance(share_balance);
		p_temp->set_acb_per_share(acb_per_share);
		p_temp->set_cgl(cgl);
		p_temp = p_temp->get_next();
	}
}

// TASK
// compute_cgl(): )Compute the ACB, and CGL.
//
double History::compute_cgl(unsigned int year)
{
	double cgl = 0;
	Transaction *p_temp = p_head;
	while(p_temp != nullptr)
	{
		if(p_temp->get_year() == year)
		{
			cgl += p_temp->get_cgl();
		}
		p_temp = p_temp->get_next();
	}
	return cgl;
}



// TASK
// print() Print the transaction history.
//

void History::print()
{
	std :: cout << "========== BEGIN TRANSACTION HISTORY ===========" << std :: endl;
	Transaction *p_temp = p_head;
	while(p_temp != nullptr)
	{
		p_temp->print();
		p_temp = p_temp->get_next();
	}
	std :: cout << "========== END TRANSACTION HISTORY ===========" << std :: endl;
	// print transaction private methods
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif
