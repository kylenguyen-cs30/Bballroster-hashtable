//
//  BballRoster.cpp
//  Project_One
//
//  Created by Kyle Nguyen on 10/7/19.
//  Copyright © 2019 CS-30. All rights reserved.
//

#include <stdio.h>
#include "BballRoster.h"

#include <string>
#include <iostream>


BballRoster::BballRoster()
{
    for (int i = 0; i < tableSize; i++)
    {
        
        HashTable [i] = new item;
        HashTable [i]->firstName = "empty";
        HashTable [i]->lastName = "empty";
        HashTable [i]->value = "0";
        HashTable[i]->next = NULL;
        
    }
}

BballRoster::BballRoster( const BballRoster &rhs)
{
    for (int i = 0; i < tableSize; i++) {
        item* ptrRhs = rhs.HashTable[i];
        //item* ptr = HashTable[i];
        //case 1 : empty bucket
        if(ptrRhs->firstName == "empty" && ptrRhs->next == nullptr)
        {
            HashTable [i] = new item;
            HashTable [i]->firstName = "empty";
            HashTable [i]->lastName = "empty";
            HashTable [i]->value = "0";
            HashTable[i]->next = NULL;
            //continue;
        }
        //case 2 : One element in the bucket
        if (ptrRhs->firstName != "empty" && ptrRhs->next == nullptr) {
            HashTable[i] = new item;
            HashTable[i]->firstName = ptrRhs->firstName;
            HashTable[i]->lastName = ptrRhs->lastName;
            HashTable[i]->value = ptrRhs->value;
            HashTable[i]->next = nullptr;
        }
        //case 3 : Linked list
        if (ptrRhs->firstName != "empty" && ptrRhs->next != nullptr)
        {
            HashTable[i] = new item; // creating the first bucket
            HashTable[i]->firstName = ptrRhs->firstName;
            HashTable[i]->lastName = ptrRhs->lastName;
            HashTable[i]->value = ptrRhs->value;
            item* currThis = HashTable[i];
            while (ptrRhs->next != nullptr )
            {
                ptrRhs = ptrRhs->next; //traverse rhs list
                
                item* n = new item; // construct new bucket
                
                
                n->firstName = ptrRhs->firstName;
                n->lastName = ptrRhs->lastName;
                n->value = ptrRhs->value;
                currThis->next = n; // connect to the end of this bucket
                
                currThis = currThis->next;
                
            }
            currThis->next =nullptr;
        }
    }
    
    
    
    
    
}

const BballRoster& BballRoster::operator=(const BballRoster &rhs)
{
    //if this list is not empty. reset to default constructor
    if(!rosterEmpty() && howManyPlayers() != rhs.howManyPlayers() )
    {
        
        for(int i = 0; i < tableSize; i++)
        {
            if(HashTable[i]->next == nullptr && HashTable[i]->firstName == "empty")
                continue;
            
            if(HashTable[i]->next == nullptr && HashTable[i]->firstName != "empty")
            {
                renouncePlayer(HashTable[i]->firstName, HashTable[i]->lastName);
            }
            
            if(HashTable[i]->next != nullptr)
            {
                item* ptrDel = HashTable[i];
                while(ptrDel != nullptr)
                {
                    renouncePlayer(ptrDel->firstName, ptrDel->lastName);
                    ptrDel = ptrDel->next;
                }
            }
        }
    }
    
    for (int i = 0; i < tableSize; i++) {
        //case 1: the bucket empty
        if ( rhs.HashTable[i]->firstName == "empty" ) {
            continue;
        }
        
        //case 2: the bucket has one elements
        if (rhs.HashTable[i]->firstName != "empty" && rhs.HashTable[i]->next == nullptr)
        {
            HashTable[i]->firstName = rhs.HashTable[i]->firstName;
            HashTable[i]->lastName = rhs.HashTable[i]->lastName;
            HashTable[i]->value = rhs.HashTable[i]->value;
            
            
        }
        //case 3 : the bucket has more than one elemnts
        if(rhs.HashTable[i]->firstName !="empty" && rhs.HashTable[i]->next != nullptr)
        {
            item* ptrRhs = rhs.HashTable[i];
            while( ptrRhs != NULL)
            {
                signPlayer(ptrRhs->firstName, ptrRhs->lastName, ptrRhs->value);
                ptrRhs = ptrRhs->next;
            }
        }
    }
    return *this;
}

BballRoster::~BballRoster()
{
    for( int i = 0; i < tableSize; i++)
    {
        item* current = HashTable[i]; // Assigning Current to head
        item* next;
        
        while(current != NULL)
        {
            next = current->next; // next go to head->next
            delete current; // delete head
            current = next; // next drag head back.
        }
    }
    
    std::cout << "The Linked List at the address " << this << " is destroyed "
    << " Thank you for saving my memory " << std::endl;
  
}






int BballRoster::Hash( const  std::string& key) const
{
    int Hash = 0;
    int index;
    //Hash = Hash + (((int)toupper(key[0])) - 65);
    for (int i = 0; i < key.length(); i++) {
        Hash = Hash + (int)key[i];
    }
    index = Hash % tableSize;
    return index;
}



bool BballRoster::signPlayer(const std::string &firstName, const std::string &lastName, const SomeType &value)
{
    //Checking Player.
    int index = Hash(lastName);
    
    if (playerOnRoster(firstName, lastName)) {
        return false;
    }
    
    
    //Case 1 : if this is an empty bucket
    if(HashTable[index]->lastName == "empty" )
    {
        HashTable[index]->firstName = firstName; // sign first name
        HashTable[index]->lastName = lastName;// sign last name
        HashTable[index]->value = value; // sign value
        HashTable[index]->next = nullptr; // sign nullptr
        return true;
    }
    
    
    // case 2 : if this is not an empty bucket
    if (HashTable[index]->lastName != "empty")
    {
        item* ptr = HashTable[index];
        item* n = new item;
        n->firstName = firstName;
        n->lastName = lastName;
        n->value = value;
        n->next = NULL;
        while ( ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = n;
        
    }
    
    //Sorting Alphabetical Order
    item* sortPtr = HashTable[index];
    if(sortPtr->next != NULL)
    {
        while (sortPtr->next != NULL)
        {
            if(sortPtr->firstName.substr(0,1).compare(sortPtr->next->firstName.substr(0,1)) > 0 )
                // if the comparision is true, then performing swap.
            {
                std::string tmp1 = sortPtr->firstName;
                sortPtr->firstName = sortPtr->next->firstName;
                sortPtr->next->firstName = tmp1;
                
                std::string tmp2 = sortPtr->lastName;
                sortPtr->lastName = sortPtr->next->lastName;
                sortPtr->next->lastName = tmp2;
                
                std::string tmp3 = sortPtr->value;
                sortPtr->value = sortPtr->next->value;
                sortPtr->next->value = tmp3;
            }
            sortPtr = sortPtr->next;
        }
        return true;
    }
    return 0;
}

void BballRoster::dump() const // checking the function
{
    
    for (int i =0; i < tableSize; i++ )
    {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        
        std::cout << "Index [" <<i<<"]" << "\n"
        << " First Name: " << HashTable[i]->firstName << "\n"
        << " Last  Name: " << HashTable[i]->lastName << "\n"
        << " Value: " << HashTable[i]->value
        << std::endl;
        
        item* ptr = HashTable[i];
        if( ptr->next != NULL)
        {
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
                std::cout << std::endl;
                std::cout << "First Name: " << ptr->firstName <<"\n"
                <<" Last Name: " << ptr->lastName <<"\n"
                <<" Value: " << ptr->value <<"\n";
                
            }
        }
        
    }
}


int BballRoster::howManyPlayers() const
{
    
    int count = 0;
    
    for (int i = 0; i < tableSize; i++)
    {
        item* ptr = HashTable[i];
        //case 1 : if the Bucket has one or no element.
        if (ptr->next == nullptr)
        {
            //case 1.1 : If the Bucket has no element
            if (ptr->firstName == "empty" )
            {
                count = count; // hold the count
            }
            //case 1.2: If the bucket has one element
            else
            {
                count++;
            }
        }
        //case 2 : if the Bucket has more than one elements.
        else
        {
            count ++;
            while ( ptr->next != NULL)
            {
                count ++;
                ptr = ptr->next;
                
            }
        }
    }
    return count++;
}

bool BballRoster::rosterEmpty() const
{
    
    if (howManyPlayers() > 0) // check the number of players
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool BballRoster::resignPlayer(const std::string &firstName, const std::string &lastName, const SomeType &value)
{
    //case 1: List is empty
    if (rosterEmpty()) {
        return false;
    }
    //case 2: List is not empty
    int index = Hash(lastName);
    if (playerOnRoster(firstName, lastName)) // checking if the player is on the list or not
    {
        item* ptr = HashTable[index];
        while (ptr != nullptr)
        {
            if (ptr->firstName == firstName && ptr->lastName == lastName) // if the player is found
            {
                ptr->value = value; // assign player's value a new value
                return true;
            }
            ptr = ptr->next;
        }
    }
    else // player is not found.
    {
        return false;
    }
    return 0;
}


bool BballRoster::playerOnRoster( const std::string &firstName,const  std::string &lastName) const
{
    
    //case 0: Checking empty list
    if (rosterEmpty()) {
        return false;
    }
    int index = Hash(lastName);
    
    //case 1: The player is found on the first element of in the bucket.
    if (HashTable[index]->firstName == firstName && HashTable[index]->lastName == lastName && HashTable[index]->next == NULL)
    {
        return true;
    }
    
    //case 2: The Player is not found and the bucket is empty.
    if (HashTable[index]->firstName == "empty" && HashTable[index]->lastName == "empty") {
        
        return false;
    }
    //case 3: The Player is not found on the first element but the in linked list.
    
    else
    {
        item* ptr = HashTable[index];
        while (ptr != NULL)
        {
            if (ptr->firstName == firstName && ptr->lastName == lastName) // checking first name and last name
            {
                return true;
            }
            ptr = ptr->next;
        }
        if ( ptr == NULL)
        {
            return false;
        }
    }
    return 0;
}


bool BballRoster::renouncePlayer(const std::string &firstName, const std::string &lastName)
{
    //case 0 : Check the list empty
    if (rosterEmpty()) {
        return false;
    }
    
    int index = Hash(lastName);
    item* delPtr;
    item* p1;
    item* p2;
    //case 1: The player is found on the first element of in the bucket.
    if (HashTable[index]->firstName == firstName && HashTable[index]->next == nullptr)
    {
        HashTable[index]->firstName = "empty";
        HashTable[index]->lastName = "empty";
        HashTable[index]->value = "0";
        return true;
    }
    
    //case 2: Match is located in the first element of the bucket but there are elements in the list.
    if (HashTable[index]->firstName == firstName && HashTable[index]->lastName == lastName && HashTable[index]->next != nullptr) {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;
    }
    
    
    //case 2: The Player is not found and the bucket is empty.
    if (HashTable[index]->firstName == "empty" && HashTable[index]->lastName == "empty") {
        
        return false;
    }
    //case 3: The Player is not found on the first element but the in linked list.
    else
    {
        p1 = HashTable[index]->next; // next pointer
        p2 = HashTable[index]; // head pointer
        
        while (p1 != NULL && p1->firstName != firstName)
        {
            p2 = p1; // head go next
            p1 = p1->next; // next go to the following pointer
        }
        //Case 3.1 : No Match
        if ( p1 == NULL)
        {
            return false;
        }
        //case 3.2 : match is found
        else
        {
            delPtr = p1; //delete head
            p1 = p1->next; // head become next pointer
            p2->next = p1; // next connect back to head
            
            delete delPtr;
            return true;
        }
    }
    return 0;
}

bool BballRoster::lookupPlayer(const std::string& firstName, const std::string& lastName, SomeType& value) const
{
    int index = Hash(lastName); // find index with the last name.
    
    
    if (HashTable[index]->firstName == firstName && HashTable[index]->lastName == lastName && HashTable[index]->next == NULL)
    {
        value = HashTable[index]->value;
        return true;
    }
    
    //case 2: The Player is not found and the bucket is empty.
    if (HashTable[index]->firstName == "empty" && HashTable[index]->lastName == "empty") {
        return false;
    }
    
    //case 3: The Player is not found on the first element but the in linked list.
    if(HashTable[index]->firstName != firstName && HashTable[index]->next != NULL)
    {
        item* ptr = HashTable[index];
        while (ptr->next != NULL)
        {
            if (ptr->firstName == firstName && ptr->lastName == lastName) // check first name and last name
            {
                
                value = ptr->value;
                return true;
            }
            ptr = ptr->next;
        }
        if( ptr->next == NULL)
        {
            return false;
        }
    }
    
    return 0;
    
    
    
}

bool BballRoster::choosePlayer(int i, std::string& firstName, std::string& lastName, SomeType& value) const
{
    //Case 1 : if the table is empty.
    if (rosterEmpty() || i < 0 || i > howManyPlayers() ) // if this list is empty or position i is negative or i bigger than number of player
    {
        return false;
    }
    
  
    
    // Case 3 : Traverse the Hash Table
    int count = 0;
    for (int index = 0; index < tableSize; index++)
    {
        item* ptr = HashTable[index]; // Assigning ptr for head of the bucket
        if(ptr->firstName != "empty" ) // if there are element(s) in this bucket.
        {
            while(ptr != NULL) // Head Pointer is not NULL. So the first player can be extracted
            {
                if(count == i) // checking dublicate value
                {
                    firstName  = ptr->firstName; // return first name
                    lastName  = ptr->lastName; // return last name
                    value = ptr->value; // return value
                    return true;
                }
                count++; // increment count
                ptr = ptr->next; // go next pointer.
                
            }
        }
    }
    
    
    return 0;
}


void BballRoster::swapRoster(BballRoster &other)
{
    
    for (int i = 0; i <tableSize; i++) {
        item* temp = HashTable[i]; // Putting Head of the pointer into temp pointer
        HashTable[i] = other.HashTable[i]; // Head of other Hash Table into this Hash Table
        other.HashTable[i] = temp; // Other Hash Table put into this temp
    }
}


bool BballRoster::signOrResign(const std::string& firstName, const std::string& lastName, const SomeType& value)
{
    if(!playerOnRoster(firstName, lastName)) // if the player is not found on the team
    {
        signPlayer(firstName, lastName, value); // sign the player in
        return true;
    }
    if(playerOnRoster(firstName, lastName)) // if the player is found
    {
        resignPlayer(firstName, lastName, value); // re-sign player's value
        return true;
    }
    return 0;
}







bool joinRosters(const BballRoster &bbOne, const BballRoster &bbTwo, BballRoster &bbJoined)
{
    //Case 1 : bbJoined is not empty
    if(!bbJoined.rosterEmpty())
    {
        //copy value from bbOne to bbJoined
        for (int n = 0; n < bbOne.howManyPlayers(); n++) {
            std::string firstName = "empty";
            std::string lastName;
            std::string bbOneValue;
            std::string value;
            std::string bbTwoValue;
            
            
            bbOne.choosePlayer(n, firstName, lastName, bbOneValue); // construct player's info
            bbJoined.lookupPlayer(firstName, lastName, value); // use player's info to extract
            if (bbJoined.playerOnRoster(firstName, lastName) && bbOneValue == value) // Checking if the bbJoined has duplicate player with bbONe and has same value
            {
                continue;
            }
            else if(bbJoined.playerOnRoster(firstName, lastName) && bbOneValue != value) // Check if the bbJioned has duplicate player with bbOne and has different value
            {
                //continue;
                bbJoined.resignPlayer(firstName, lastName, bbOneValue);
            }
            bbTwo.lookupPlayer(firstName, lastName, bbTwoValue);
            if(bbTwo.playerOnRoster(firstName, lastName) && bbOneValue != bbTwoValue)
            {
                continue;
            }
            else
            {
                bbJoined.signPlayer(firstName, lastName, bbOneValue); //if this is a new player, sign player in the bbJoined
            }
        }
        
        
        
        
        
        
        // copy value from bbTwo to bbJoined
        for (int i = 0; i < bbTwo.howManyPlayers(); i++) {
            std::string firstName = "empty";
            std::string lastName;
            std::string value;
            std::string bbTwovalue;
            std::string bbOneValue;
            
            
            bbTwo.choosePlayer(i, firstName, lastName, bbTwovalue);
            bbJoined.lookupPlayer(firstName, lastName, value);
            
            if (bbJoined.playerOnRoster(firstName, lastName) && value == bbTwovalue ) // Check if bbJoined has duplicate player in bbTwo and has same value
            {
               
                continue;
            }
            else if(bbJoined.playerOnRoster(firstName, lastName)) // Check if bbJoined has duplicate player in bbTwo but has different value
            {
               
                bbJoined.resignPlayer(firstName, lastName, bbTwovalue);
            }
            
            bbOne.lookupPlayer(firstName, lastName, bbTwovalue);
            if(bbOne.playerOnRoster(firstName, lastName) && bbOneValue != bbTwovalue)
            {
                continue;
            }
            else
            {
                bbJoined.signPlayer(firstName, lastName, bbTwovalue); // if this is a new player, sign player
            }
            
        }
        
        //Checking duplicate player and return true/false bbTwo and bbOne
        for(int i = 0; i < bbTwo.howManyPlayers(); i++)
        {
            std::string fn;
            std::string ln;
            std::string val;
            std::string valOne;
            bbTwo.choosePlayer(i,fn,ln,val);
            bbOne.lookupPlayer(fn, ln, valOne);
            //if bbOne and bbTwo has a same player and same value
            if(bbOne.playerOnRoster(fn, ln) && val == valOne )
            {
                continue;
            }
            //if bbOne and bbTwo has a same player but different value
            else if(bbOne.playerOnRoster(fn, ln) && val != valOne)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        
        
        return true;
    }
    
    
    
    //------------------------------------------------------------------------------
    
    
    
    
    //Case 2 : bbJoined is empty
    if(bbJoined.rosterEmpty())
    {
        for (int n = 0; n <bbOne.howManyPlayers(); n++)
        {
            std::string firstName = "empty";
            std::string lastName;
            std::string value;
            bbOne.choosePlayer(n, firstName, lastName, value); // construct player's info at position n
            bbJoined.signPlayer(firstName, lastName, value); // sign player for first time. bbjoined is empty
        }
        
        
        
        for (int i = 0; i < bbTwo.howManyPlayers(); i++)
        {
            std::string firstName = "empty";
            std::string lastName;
            std::string bbTwoValue;
            std::string value;
            std::string bbOneValue;
            
            
            
            bbTwo.choosePlayer(i, firstName, lastName, bbTwoValue); // construct player's info at position n
            bbJoined.lookupPlayer(firstName, lastName, value); // using player's info to extract the value
            
            if(bbJoined.playerOnRoster(firstName, lastName) && bbTwoValue == value) //if player is found and has same value
            {
                continue;
            }
            else if(bbJoined.playerOnRoster(firstName, lastName)) // if player is found but has different value
            {
                continue;
            }
            
//            bbOne.lookupPlayer(firstName, lastName, bbTwoValue);
//            if(bbOne.playerOnRoster(firstName, lastName) && bbOneValue != bbTwoValue) //Checking if this player is the same player in bbOne and has different value
//            {
//                continue;
//            }
            else // if the player is a new player
            {
                bbJoined.signPlayer(firstName, lastName, bbTwoValue); // sign the player in
            }
        }
        
        //Checking duplicate player and decide return true/false
        for(int i = 0; i < bbTwo.howManyPlayers(); i++)
        {
            std::string fn;
            std::string ln;
            std::string valTwo;
            std::string valOne;
            bbTwo.choosePlayer(i,fn,ln,valTwo);
            bbOne.lookupPlayer(fn, ln, valOne);
            //if bbOne and bbTwo has a same player and different value
            if(bbOne.playerOnRoster(fn,ln) && valTwo == valOne )
            {
                continue;
            }
            else if(bbOne.playerOnRoster(fn, ln) && valTwo != valOne)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        return true;
    }
    return 0;
}








void checkRoster (const std::string& fsearch, const std::string& lsearch,const BballRoster& bbOne,BballRoster& bbResult)
{
    //Case 0 : bbOne is empty list
    if ( bbOne.rosterEmpty()) {
        //std::cout << "bbONe is empty" << std::endl;
        return;
    }
    //Case 0.1 : bbResult is not empty list
    if(!bbResult.rosterEmpty())
    {
        //Reset bbResult
        for(int i = 0; i < bbResult.howManyPlayers(); i++)
        {
            std::string fname;
            std::string lname;
            std::string val;
            bbResult.choosePlayer(i, fname, lname, val);
            bbResult.renouncePlayer(fname, lname);
        }
    }
    
    //Case 1 : found one specific player.
    if( fsearch != "*" && lsearch != "*")
    {
        std::string val;
        if(bbOne.lookupPlayer(fsearch, lsearch, val))
        {
            bbResult.signPlayer(fsearch, lsearch, val);
        }
    }
    //Case 2 : if the fsearch = "*" and lsearch = "string"
    if( fsearch == "*")
    {
        
        for (int i = 0; i < bbOne.howManyPlayers();i++)
        {
            std::string firstName = "empty";
            std::string lastName;
            std::string val2;
            bbOne.choosePlayer(i, firstName, lastName, val2);
            if(lsearch == lastName)
            {
                bbResult.signPlayer(firstName,lastName,val2);
            }
        }
    }
    //Case 3 : if the fsearch = "string" and lsearch = "*"
    if( lsearch == "*")
    {
        for (int i = 0; i < bbOne.howManyPlayers();i++)
        {
            std::string firstName = "empty";
            std::string lastName;
            std::string val3;
            bbOne.choosePlayer(i, firstName, lastName, val3);
            if(fsearch == firstName)
            {
                bbResult.signPlayer(firstName,lastName,val3);
            }
        }
        
    }
    
    //Case 4 : if the fseach = "*" and lsearch = "*"
    if(fsearch =="*" && lsearch == "*")
    {
        bbResult = bbOne;
    }
    
}








