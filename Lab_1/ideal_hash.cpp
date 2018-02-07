/*Step into the digital dimension to find ourselves a new quality of life*/

/*Michael "Hyst3r1a" Gorshenin, 2018*/

////////////
//Perfect hash
////////////

/*The main idea of perfect hashing system is all about getting constant search times
for constant(or rarely changing) key dictionaries. 
The process can be explained as follows:
1. Hash function 1 - h. It hashes keys into a typical hash table. Call it Level 1 Hash Table(L1HT);
2. For each element hashed into the same place(see: Collisions) we run additional hash function - h2.
3. Results of h2 are then stored in the other hash table - Level 2 Hash Table(L2HT). With proper h and h2
there will be no collisions in Level 2 HT.
4. After all keys are parsed(and for each element in L1HT there is L2HT) we can get the key's value by using h on input data
to determine the index in L1HT and then run h2 at this index to get the final L2HT index we are looking for.

Perfect hashing runs search operations for O(1) memory operations in worst scenario,
but works only for static key dictionaries.

This realisation is made for hashing numbers from 0 to 100, as "p" argument is set to 101 and {0, 1, ..., p-1} has
to include all possible input data. To change possible data range use bigNDNumber define below.

This realisation only finds the input value in two-level tables. It would need another struct to have hashed values
represent useful payload.
*/

//h[a,b](k) = ((ak+b)mod(p))mod(m); where p - non-dividable number(p>max(allkeys)), a = {0,1, ... n-1}, b = {1, 2,... n-1}, m = max(tablesize)
#include<iostream>
#include<vector>
#define firstRandomArgumentLvl1 3;
#define secondRandomArgumentLvl1 42;
#define bigNDNumber 101;
#define Lvl1HashSize 10;

using namespace std;


    //hashing function
int hashF(int a, int b, int p, int k, int m) {
	//h[a,b](k) = ((ak+b)mod(p))mod(m);
	//where p - non-dividable number(p>max(allkeys)), a = {0,1, ... n-1}, b = {1, 2,... n-1}, m = max(tablesize)
	return(((a*k + b) % p) % m);
}

//array of those structs represents L1HT
struct secondLevelHashTable {
	int numHashed = 0;//the number of values hashed into the same place in L1HT
	int a;//randomed a value(used for L2HT hasing)
	int b;//randomed b value
	vector<int> lvl2array;//dynamic array for L2HT
	
	
	//there can be collisions in L2HT with given a and b. If so, we use that function to get new a and b and avoid collisions.
	void regenerateABVar() {
		if (numHashed == 1) {
			a = 0;
			b = 0;
		}
		else if (a == 0 && b == 0) {
			a = rand() % 101 + 1; b = rand() % 101 + 1;
		}
	}
	
	//L2HT Build/Rebuild function.
	void EditArray(int newHashedValue) {
		
		    int sizeK = numHashed * numHashed;//sizeK is the L2HT size. Has to be num_of_values_hashed^2 to avoid collisions
			vector<int> tempVector(sizeK);//temporary array where we store re-hashed things after regeneration of a and b in case of collisions
			vector<int> indexes;//collision detection array
			int p = bigNDNumber;
			int m = numHashed;
			int index, newindex;
			bool flag = false;
			
			newindex = hashF(a, b, p, newHashedValue, sizeK);//getting index of new value being hashed into array
			indexes.push_back(newindex);
			for (int i = 0; i < lvl2array.size();++i) { //collision avoidance cycle. If it finds anything already hashed into the table it checks
			//if it collides with a new index. In case of regenerated values - checks if anything collides with anything.
				cout << "Operation number :" << i << endl;
				cout << lvl2array[i] << endl;
				index = hashF(a, b, p, lvl2array[i], sizeK);
				if (lvl2array[i] != 0) {
					
					
					cout << "Indexes size: " << indexes.size() << endl;;
					for(int j = 0; j<indexes.size(); ++j){//collision detector
						cout << index << " vs " << indexes[j] << " num "<<j<<endl;
						if (indexes[j] == index) {
							cout << "Regenerating random numbers" << endl;
							a = 0;
							b = 0;
							regenerateABVar();//this call gets us new a and b and returns us to the start of collicion avoidance check.
							//this happens over and over again, until we find a function that suits all of our keys.
							newindex = hashF(a, b, p, newHashedValue, m);
							i = -1;
							flag = true;
							indexes.clear();
							indexes.push_back(newindex);
							break;
						}
						
						flag = false;
					}
					
				}
				if (!flag) {
					cout << index << " Number "<<a<<", "<< b << endl;

					tempVector[index] = lvl2array[i];//adds current key to the new collision-free array
					indexes.push_back(index);//and to the collision detection array too
				}
				else { i = -1; }
				
			}
			
			newindex = hashF(a, b, p, newHashedValue, m);
			
			tempVector[newindex] = newHashedValue;
			lvl2array.clear();
			for (int i = 0; i < tempVector.size();++i) {
				//array copy cycle. Copies new array into the old one. Then clears the new array making it ready for future use
			
				cout << "Pushing back value: " << tempVector[i] << endl;
				lvl2array.push_back(tempVector[i]);
			}
			tempVector.clear();
	}

	
};

int sizeL1 = Lvl1HashSize;
secondLevelHashTable *Lvl1Table = new secondLevelHashTable[sizeL1];//an array that represents L1HT



//Perfect hashing search function. Determines the index in L1HT, and uses a/b values from this index to get the index in L2HT, where the value is stored
int search() {
	int k, a, b, p, m;//hash function varables(See comments for hashF func)
	int searchHash;//temp searchHash

	cin >> k;//get input value to find 

	//prepare variables for hashF pass:
	a = firstRandomArgumentLvl1;
	b = secondRandomArgumentLvl1;
	p = bigNDNumber;
	m = Lvl1HashSize;
	//pass variables to hashF to get L1HT index
	searchHash = hashF(a, b, p, k, m);
	//get L2HT from that index
	secondLevelHashTable currentCollisionMap = Lvl1Table[searchHash];
	cout << "Input value is hashed into the table with the index " << searchHash;
	//prepare variables for second hashF pass:
	a = currentCollisionMap.a;
	b = currentCollisionMap.b;
	m = currentCollisionMap.numHashed*currentCollisionMap.numHashed;
	//get value's index in L2HT
	searchHash = hashF(a, b, p, k, m);

	cout << "Input value is found in the position " << searchHash << endl;
	cout << "[DEBUG] If everything is Okay, then the following value has to be the input value: "<< currentCollisionMap.lvl2array[searchHash];
	return currentCollisionMap.lvl2array[searchHash];
}



//main function implements example random keys generation. 5 keys total.
void main() {
	
	int key = 0;
	int currentLvl1Hash;

	//hash function pass preparation
	int a = firstRandomArgumentLvl1;
	int b = secondRandomArgumentLvl1;
	int p = bigNDNumber;
	int m = Lvl1HashSize;

	
	
	//random key generation and L2HT regeneration
	for (int i = 0; i < 5; ++i) {
		key = rand() % 101;//rand key generation
		currentLvl1Hash = hashF(a, b, p, key, m);//determines index of that key in L1HT
		Lvl1Table[currentLvl1Hash].numHashed++;//"m" value increase. "m" is number of keys hashed into that index
		Lvl1Table[currentLvl1Hash].regenerateABVar();//creates random a and b for current L2HT
		Lvl1Table[currentLvl1Hash].EditArray(key);//increases L2HT length and hashes the key into it
		cout << "Hashed value: " << key << endl;
	}
	
	while (true) {
		cout << endl<<"Value to find: " << endl;
		search();
	}
}