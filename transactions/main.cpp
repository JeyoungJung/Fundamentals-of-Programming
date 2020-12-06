#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  History trans_history{};
  trans_history.read_history();


  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  trans_history.update_acb_cgl();
  trans_history.print();

  std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
  std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;
}
#endif
/*int main() {
	Transaction *first = new Transaction("VGRO", 10, 01, 2020, true, 150, 10300.14);
	Transaction *second = new Transaction("VGRO", 10, 01, 2018, true, 150, 10300.14);
	Transaction *third = new Transaction("VGRO", 10, 01, 2019, true, 150, 10300.14);
	Transaction *fourth = new Transaction("VGRO", 10, 01, 2017, true, 150, 10300.14);
	History trans_history{};
	trans_history.insert(first);
	trans_history.insert(second);
	trans_history.insert(third);
	trans_history.insert(fourth);
	std :: cout << "[unsorted]:"<<std::endl;
	trans_history.print();

	trans_history.sort_by_date();

	std::cout << "[sorted]:" << std :: endl;
	trans_history.print();

	return 0;
}*/
