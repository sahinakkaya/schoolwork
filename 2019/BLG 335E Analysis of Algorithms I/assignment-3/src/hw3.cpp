#include "red_black_tree.h"
using namespace std;

int get_smallest_ordinal(vector<Package>& packages) {
  int smallest_ordinal = packages[0].get_ordinal();
  for (unsigned int i = 1; i < packages.size(); i++) {
    if (packages[i].get_ordinal() < smallest_ordinal)
      smallest_ordinal = packages[i].get_ordinal();
  }
  return smallest_ordinal;
}

HW3_Result hw3(int eastWarehousePackageCount, int eastWarehousePackageSizes[],
               int eastWarehousePackageOrdinals[],
               int westWarehousePackageCount, int westWarehousePackageSizes[],
               int westWarehousePackageOrdinals[]) {
  RedBlackTree east_ware_house;
  RedBlackTree west_ware_house;
  for (int i = 0; i < eastWarehousePackageCount; i++) {
    Package package =
        Package(eastWarehousePackageSizes[i], eastWarehousePackageOrdinals[i]);
    east_ware_house.insert(package);
  }

  for (int i = 0; i < westWarehousePackageCount; i++) {
    Package package =
        Package(westWarehousePackageSizes[i], westWarehousePackageOrdinals[i]);
    west_ware_house.insert(package);
  }
  RedBlackTree* ware_houses[2];
  ware_houses[0] = &east_ware_house;
  ware_houses[1] = &west_ware_house;

  RedBlackTree* current_ware_house = &east_ware_house;
  bool shipment_ended =
      east_ware_house.is_empty() || west_ware_house.is_empty();

  cout << "----------------- East ware house -----------------" << endl;
  east_ware_house.print_tree();
  cout << "----------------- West ware house -----------------" << endl;
  west_ware_house.print_tree();
  cout << "----------------- Shipment starts -----------------" << endl;

  int smallest_ordinal = east_ware_house.get_node_count() + 1;
  vector<Package> packages;
  int turn = 0;
  while (!shipment_ended) {
    cout << "------------- current ware house: " << (turn % 2 ? "west" : "east")
         << " ------------" << endl;
    current_ware_house->print_tree();
    if (current_ware_house->get_node_count() >= smallest_ordinal) {
      Node* smallest_element =
          current_ware_house->nth_smallest_element(smallest_ordinal);
      Package nth_smallest_package = smallest_element->data;
      current_ware_house->delete_node(smallest_element);
      cout << "Searching " << smallest_ordinal << "th smallest package." << endl
           << "Package found: ";
      cout << "(" << nth_smallest_package.get_size() << ", "
           << nth_smallest_package.get_ordinal() << ")" << endl;
      cout << "Package is sent to " << ((turn + 1) % 2 ? "west" : "east")
           << " ware house." << endl;
      for (auto package : packages) {
        cout << "Package inserted to " << (turn % 2 ? "west" : "east")
             << " ware house, (" << package.get_size() << ", "
             << package.get_ordinal() << ")" << endl;
        current_ware_house->insert(package);
      }
      packages.clear();
      packages.push_back(nth_smallest_package);
    } else {
      if (packages.size()) {
        cout << "Ware house don't have " << smallest_ordinal
             << "th smallest package." << endl;
        for (auto package : packages) {
          cout << "Package is forwarded to smaller warehouses around the "
                  "globe, ("
               << package.get_size() << ", " << package.get_ordinal() << ")"
               << endl;
        }
      }
      cout << "Preparing the smallest size shipment." << endl;
      packages = current_ware_house->get_smallest_packages();
      for (auto package : packages) {
        cout << "Package is sent to " << ((turn + 1) % 2 ? "west" : "east")
             << " ware house, (" << package.get_size() << ", "
             << package.get_ordinal() << ")" << endl;
      }
    }
    smallest_ordinal = get_smallest_ordinal(packages);
    shipment_ended = current_ware_house->is_empty();
    current_ware_house->print_tree();
    turn++;
    current_ware_house = ware_houses[turn % 2];
  }
  cout << "------------- current ware house: " << (turn % 2 ? "west" : "east")
       << " ------------" << endl;
  current_ware_house->print_tree();
  for (auto package : packages) {
    cout << "Package *directly* inserted to " << (turn % 2 ? "west" : "east")
         << " ware house, (" << package.get_size() << ", "
         << package.get_ordinal() << ")" << endl;
    current_ware_house->insert(package);
  }
  current_ware_house->print_tree();
  cout << "------------------ Shipment ends ------------------" << endl;

  return current_ware_house->report();
}
