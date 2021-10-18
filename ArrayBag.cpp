#include <iostream>
#include <vector>
#include "ArrayBag.hpp"

template <class ItemType>
ArrayBag<ItemType>::ArrayBag() {
    static const int DEFAULT_CAPACITY = 10;
    ItemType items_[DEFAULT_CAPACITY];      // Array of bag items
    item_count_ = 0;                        // Current count of bag items
}

template <class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const {
    return item_count_;
}

/**
     @return true if item_count_ == 0, false otherwise
     **/
template <class ItemType>
bool ArrayBag<ItemType>::isEmpty() const {
    return item_count_ == 0;

}

/**
     @return true if new_entry was successfully added to items_, false otherwise
     **/
template <class ItemType>
bool ArrayBag<ItemType>::add(const ItemType &new_entry) {
    if (item_count_ == DEFAULT_CAPACITY) {
        return false;
    }
    else {
        items_[item_count_] = new_entry;
        item_count_++;
        return true;
    }
    

}

/**
     @return true if an_entry was successfully removed from items_, false otherwise
     **/
template <class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType &an_entry) {
    int remove_index = getIndexOf(an_entry);
    if (!isEmpty() && remove_index > -1 && remove_index != DEFAULT_CAPACITY -1) {
        item_count_--;
        items_[remove_index] = items_[item_count_]; //replaces the value of the index with the last value of the array 
        //deletes the last item because the removed entry is replaced by 
        return true; //if this branch is executed than the removal is complete
    }
    else if (!isEmpty() && remove_index > -1 && remove_index == DEFAULT_CAPACITY -1) {
        item_count_--;
        items_[remove_index] = items_[-1];
        return true;
    }
    else {
        return false; //this branch executes if the removal does not occure
    }



}

 /**
     @post item_count_ == 0
     **/
template <class ItemType>
void ArrayBag<ItemType>::clear(){
    item_count_ = 0;
}

 /**
     @return true if an_entry is found in items_, false otherwise
     **/
template <class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType &an_entry) const {
    bool found = false;
    for (int i = 0; i < item_count_; i++) {
        if (items_[i] == an_entry) { //if the current index in the loop contains the matching search argument
            found = true;
        }

    }
    return found;

}

/**
    @return the number of times an_entry is found in items_
  **/
template <class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType &an_entry) const {
    int target_counter = 0; //value will count the number of occurences of the entry in the arraybag
    int array_counter = 0;
    while (array_counter < item_count_) {
        if (items_[array_counter] == an_entry) {
            target_counter++;
        }
        array_counter++;
    }
    return target_counter;
 }


/**
    @return a vector having the same contents as items_
    **/
template <class ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const {
   std::vector<ItemType> stub_value;
    for (int i = 0; i < item_count_; i++) {
        stub_value.push_back(items_[i]);
    }
    return stub_value;
}
/**
    @post prints the contents of items_ to the standard output separated by commas and followed by a new line.
    Example: A, B, C, D, E\n
    Note how there is no comma and space for the last item.
	**/
template <class ItemType>
void ArrayBag<ItemType>::display() const {
    int counter = 0;
    if (item_count_ - 1 == 0) {
        std::cout << items_[counter];
        std::cout << std::endl;
        return;
    }
    while (!isEmpty() && counter < item_count_ - 1) {
        std::cout << items_[counter] << ", ";
        counter++;
    }
    std::cout << items_[item_count_ - 1];
    std::cout << std::endl;

    /*for (int i = 0; i < item_count_-1; i++) {
        std::cout << items_[i] << ", ";
        }
    std::cout << items_[item_count_-1];*/
    

}

/**
      duplicate all the items in the bag 
      meaning that for every item in the bag we add another copy of it. 
      Example: we originally have [A, B] and after duplication we have [A, B, A, B] or [A, A, B, B] or how ever order you want so long as there are 2 A's and 2 B's
      Return true if successfully duplicated 
      but return false if there is nothing to duplicate or if we go above the DEFAULT_CAPACITY which is 10 for this project
    */
template <class ItemType>
bool ArrayBag<ItemType>::duplicateItems() {
    const int org_item_count = item_count_; //the total intial items in the arraybag to be duplicated
    if (item_count_ == 0 || item_count_ > 5) {
        return false;
    }
    else {
        for (int i = 0; i < org_item_count; i++ ) {
            add(items_[i]);
        }
    }
    return true;

}

/**
    @post every instance of an_entry is removed
  */
template <class ItemType>
void ArrayBag<ItemType>::removeAllInstances(const ItemType &an_entry) {
    const int org_item_count = item_count_; 
    if (!isEmpty() && contains(an_entry)) {
        for (int i = 0; i < org_item_count; i++) { //looping through the 
            if (items_[i] == an_entry) {
                remove(items_[i]);
            }
        }
    }
}
        
    
 


/**
    @return true if we managed to remove all items that have duplicates in the bag
    Example: a duplicate would be [A, B, C, C, D, D, D, E]
    What we should have after running this function: [A, B, C, D, E] (may be out of order depending on how you do it, that doesn't matter)
    @return false if there are 1 or less items in the bag
  */
template <class ItemType>
bool ArrayBag<ItemType>::removeDuplicates() {
    bool duplicates_removed = false;
    for (int i = 0; i < item_count_; i++) {
        while (getFrequencyOf(items_[i]) > 1) { //while the frequency of the current item being accesed is > 1
            remove(items_[i]); //we remove the item
        }
    }
    //code block checks if every item in arraybag has a frequency of 1 if so return true
    for (int i = 0; i < item_count_; i++) {
        if (getFrequencyOf(items_[i]) == 1) {
            duplicates_removed = true;
        }
    }
    return duplicates_removed;
    
      
}

/* ---------- OPERATOR OVERLOADS ----------*/

  /** 
    implements Set Union. The union of two sets A and B is the set of elements which are in A, in B, or in both A and B.  
		@param a_bag to be combined with the contents of this (the calling) bag
		@post adds as many items from a_bag as space allows    
	*/
template <class ItemType>
void ArrayBag<ItemType>::operator+=(const ArrayBag<ItemType> &a_bag) {
    for (int i = 0; i < a_bag.getCurrentSize(); i++) {
        if (getCurrentSize() == DEFAULT_CAPACITY ) { //if the size of the arraybag is already at capacity end the addition 
            return;
        }
        else {
        add(a_bag.items_[i]);
        }
    }


}
/** 
    implements Set Difference  The (set) difference between two sets A and B is the set that consists of the elements of A which are not elements of  B 
		@param a_bag to be subtracted from this (the calling) bag
		@post removes all data from items_ that is also found in a_bag
    Example if A has [1, 2, 3, 4, 5] and B has [4, 5, 6, 7], then A-=B will result in A containing [1, 2, 3] and B remaining the same
	*/
template <class ItemType>
void ArrayBag<ItemType>::operator-=(const ArrayBag<ItemType> &a_bag) {
    for (int i = 0; i < a_bag.getCurrentSize(); i++) { //loops through all the items in the a_bag
        if (contains(a_bag.items_[i]) == true ) { //if the current item being accessed in the loop is in the other bag
            remove(a_bag.items_[i]); //we will remove that item since it is also in the other bag 
                                     //after removing every item that is shared in the other bag we end with the set difference of A
        }
    }

}



/** 
    implements Set Intersection  The intersection of two sets A and B is the set that consists of the elements that are in both A and B 
		@param a_bag to be intersected with this (the calling) bag
		@post items_ no longer contains data not found in a_bag    
    Example if bag A has [1,2,3,4,5] and Bag B has [7,8,5,9] then A /= B will result in A containing only 5 since 5 is found in both bag A and bag B
	*/
template <class ItemType>
void ArrayBag<ItemType>::operator/=(const ArrayBag<ItemType> &a_bag) {
    int total_item_count = item_count_ + 1;
    for (int i = 0; i < item_count_ ; i++) { //loops through all the items in the a_bag
        if  (a_bag.contains(items_[i]) == false ) { //looping through bag a if the current item accesed is not in bag b
            remove(items_[i]); //we will remove that item since it is not in a && b intersection
        } //finally we will end up with items in bag a that match bag b
    } 


}
/**
     @param target to be found in items_
     @return either the index target in the array items_ or -1,
     if the array does not contain the target.
     **/
template <class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType &target) const {
    int array_counter = 0;
    while (array_counter != DEFAULT_CAPACITY) {  //we end the loop once we reach all items in the array
        if (items_[array_counter] == target) { //if the current counter index contains the target value in arraybag
            return array_counter; //found the index of the targer now we return it
        }
        else {
            array_counter++; 
        }
    }
    array_counter = -1;
    return array_counter;
}



int main() {
    
    ArrayBag<std::string> backpack;
    ArrayBag<std::string> backpack1;
    ArrayBag<std::string> backpack2;
    backpack.add("A");
    backpack.add("B");
    backpack.add("C");
    backpack.add("D");
    backpack.add("E");
    backpack.add("F");
    backpack.display();
    backpack1.add("B");
    backpack1.add("D");
    backpack1.add("F");
    backpack /= backpack1;
    backpack.display();
    return 0;
} 